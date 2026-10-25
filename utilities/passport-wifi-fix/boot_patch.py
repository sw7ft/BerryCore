"""Passport BB10 WLAN RAM fix. Exact-build-only, Python 3.2, no pdebug needed."""
import os
import sys
import time
import signal
import ctypes
import hashlib
import binascii
import struct
import traceback
import shutil
from phone_debug import Process

ROOT = '/var/rootdata/wifi-fix'
PATCHES = {
    'wpa_pps': [(0x3f7f8, 'b6f5007f', 'b6f5006f'),
                (0x3ad50, 'b2f5007f', 'b2f5006f'),
                (0x3ad3e, '47f6e451', '47f2b071')],
    'libwlandrv_bcm_dhd.so.1': [(0x9cc6, 'b3f5007f', 'b3f5006f')],
    'wpa_supplicant': [(0x2627c, 'b7f5007f', 'b7f5006f'),
                       (0x262ca, 'b7f5007f', 'b7f5006f')],
}
HASHES = {
    '/usr/sbin/wpa_pps': '4740e29a6a151777bf17e687eccbf274f2f0c289e5bbc7ef6de8deff92032449',
    '/usr/lib/libwlandrv_bcm_dhd.so.1': '36f6905d2f23b973e397113ba490ff503a4ede4a193eae7546270ef1177e0ec9',
    '/usr/sbin/wpa_supplicant': '33e5d4a149eaa3f7aec6593dc3b2e6c899248cfc6daf35f4fd2dacb13cd1db91',
    '/proc/boot/libc.so.3': 'cd0dd08e8bed74ed6a9fc01a860656f7882c454ca6b7866789f6c59302228e3c',
}
COMMANDS = {
    'wpa_pps': '-p 16 -A nonroot,allow,clockset,inherit -u 43:0,43,424 '
               '/usr/sbin/wpa_pps -d -D libwlandrv_bcm_dhd.so.1 -i bcm0 -j bcm1 '
               '-h /usr/sbin/hostapd -R broadcom -f bcm0 -k bcm1 -z p2pdev -v broadcom',
    'wpa_supplicant': '-p 15 -u 43:0,43,424,1000,1200 '
                      '/usr/sbin/wpa_supplicant -t -Dbroadcom -ibcm0 -c /etc/wpa_supplicant.conf',
}
PPS = ['control', 'status', 'status_p2p', 'status_public', 'escreen',
       'limited/control', 'restricted/control']


def log(message):
    print(time.strftime('%Y-%m-%d %H:%M:%S') + ' ' + message)
    sys.stdout.flush()


def shell(command):
    # Python 3.2's fork-based subprocess hangs on this QNX build after setuid.
    # libc system uses the platform's native spawn implementation.
    result = ctypes.CDLL(None).system(command.encode('ascii'))
    if result != 0:
        raise RuntimeError('Command failed (%d): %s' % (result, command))


def pids(name):
    found = []
    for item in os.listdir('/proc'):
        if item.isdigit():
            try:
                with open('/proc/'+item+'/exefile', 'rb') as f:
                    path = f.read().rstrip(b'\0').decode('ascii')
                if path.split('/')[-1] == name:
                    found.append(int(item))
            except (IOError, UnicodeError):
                pass
    return sorted(found)


def one(name, timeout=15):
    end = time.time()+timeout
    while time.time() < end:
        found = pids(name)
        if len(found) == 1:
            return found[0]
        if len(found) > 1:
            raise RuntimeError('Multiple instances: '+name)
        time.sleep(.1)
    raise RuntimeError('Missing process: '+name)


def terminate(name):
    for pid in pids(name):
        os.kill(pid, signal.SIGTERM)
    end = time.time()+4
    while pids(name) and time.time() < end:
        time.sleep(.1)
    for pid in pids(name):
        os.kill(pid, signal.SIGKILL)
    end = time.time()+4
    while pids(name) and time.time() < end:
        time.sleep(.1)
    if pids(name):
        raise RuntimeError('Unable to terminate '+name)


def launch(name, held):
    command = ('on -d '+('-h ' if held else '')+
               '-eSOCK_SO_SETFIB=15 -eWLANCHP=bcm4339 '
               '-A nonroot,deny,setuid,noinherit '+COMMANDS[name])
    shell(command+' </dev/null >>'+ROOT+'/'+name+'.log 2>&1 &')
    return one(name)


def wait_file(path, timeout=20):
    end = time.time()+timeout
    while time.time() < end:
        if os.path.exists(path):
            return
        time.sleep(.1)
    raise RuntimeError('Missing service object: '+path)


def code_state(pid, names):
    # Opening read-only avoids attaching/stopping an already working service.
    p = Process.__new__(Process)
    p.pid, p.breakpoints = pid, set()
    p.fd = os.open('/proc/%d/as' % pid, os.O_RDONLY)
    try:
        m = p.mappings()
        state = []
        for name in names:
            for offset, old, new in PATCHES[name]:
                current = binascii.hexlify(p.read(m[name]+offset, 4)).decode('ascii')
                if current not in (old, new):
                    raise RuntimeError('Unknown RAM code: %s+%x' % (name, offset))
                state.append(current == new)
        return all(state)
    finally:
        os.close(p.fd)


def patch_held(pid, name):
    log('Patching held %s pid=%d' % (name, pid))
    p = Process(pid)
    success = False
    try:
        p.stop()
        m = p.mappings()
        base, c = m[name], m['libc.so.3']
        entry = base+struct.unpack('<I', p.read(base+24, 4))[0]
        stop = base+0x81dc if name == 'wpa_pps' else entry
        bp = stop | (1 if name == 'wpa_pps' else 0)
        p.breakpoint(bp)
        os.kill(pid, signal.SIGCONT)  # Clear on -h's job-control stop.
        p.run()
        original = p.wait(stop, 20)
        p.breakpoint(bp, True)
        m = p.mappings()
        names = ['wpa_pps', 'libwlandrv_bcm_dhd.so.1'] if name == 'wpa_pps' else [name]
        patches = [(m[n]+off, binascii.unhexlify(old.encode('ascii')), binascii.unhexlify(new.encode('ascii')))
                   for n in names for off, old, new in PATCHES[n]]
        for address, old, new in patches:
            assert p.read(address, 4) == old, 'Original byte check failed'
        assert p.read(c+0x25150, 16) == binascii.unhexlify(b'30402de92cd04de26ce09fe500c0a0e3')
        assert p.read(c+0x256bc, 16) == binascii.unhexlify(b'a0309fe5d2cce0e7f0402de903308fe0')
        ret = c+0x251d4  # ARM mprotect wrapper; injected calls use mprotect_r.
        p.breakpoint(ret)
        scratch = original[13]-0x400
        saved_stack = p.read(scratch, 0x400)

        def rpc(function, a, b, v):
            regs = list(original)
            regs[:3] = [a, b, v]
            regs[13] = (original[13]-0x200)&~7
            regs[14:17] = [ret, function, original[16]&~0x20]
            p.setregs(regs)
            p.run()
            result = p.wait(ret)[0]
            if result != 0:
                raise RuntimeError('Target call %x returned %x' % (function, result))

        for page in sorted(set(a & ~4095 for a, o, n in patches)):
            rpc(c+0x25150, page, 4096, 0x300)
            for address, old, new in patches:
                if address & ~4095 == page:
                    p.write(address, new)
                    assert p.read(address, 4) == new
            rpc(c+0x25150, page, 4096, 0x500)
            rpc(c+0x256bc, page, 4096, 0x1000000)
        p.breakpoint(ret, True)
        p.write(scratch, saved_stack)
        p.setregs(original)
        assert p.regs() == original
        p.run()
        success = True
        log('Patched '+name+'; RX and registers restored')
    finally:
        if not success:
            # Never release a process with injected registers or non-executable text.
            try:
                os.kill(pid, signal.SIGKILL)
            except OSError:
                pass
            p.breakpoints.clear()
        p.close()


def backup_acl():
    saved = []
    for path in PPS:
        full = '/pps/services/wifi/'+path
        if os.path.exists(full):
            dest = ROOT+'/acl-'+path.replace('/', '_')
            shell('getfacl '+full+' >'+dest)
            saved.append((full, dest))
    return saved


def numeric_acl(source):
    # BB10 getfacl truncates account names (e.g. cellular_control).
    # Resolve against the local account tables and feed setfacl numeric IDs.
    tables = {}
    for kind, path in [('user', '/etc/passwd'), ('group', '/etc/group')]:
        with open(path) as f:
            tables[kind] = dict((parts[0], parts[2]) for parts in
                                (line.rstrip().split(':') for line in f)
                                if len(parts) >= 3)
    lines = []
    with open(source) as f:
        for line in f:
            if not line.strip() or line.startswith('#'):
                continue
            fields = line.strip().split(':')
            if fields[0] in tables and fields[1] and not fields[1].isdigit():
                accounts = tables[fields[0]]
                name = fields[1]
                matches = [key for key in accounts if key.startswith(name)]
                if name in accounts:
                    fields[1] = accounts[name]
                elif len(matches) == 1:
                    fields[1] = accounts[matches[0]]
                else:
                    raise RuntimeError('Ambiguous ACL account: '+name)
            lines.append(':'.join(fields))
    dest = source+'.numeric'
    with open(dest, 'w') as f:
        f.write('\n'.join(lines)+'\n')
    return dest


def restore_acl(saved):
    wait_file('/pps/services/wifi/status')
    for path, source in saved:
        if os.path.exists(path):
            shell('setfacl -M '+numeric_acl(source)+' '+path)
    # The stock startup.sh adds this after launching wpa_pps.
    shell('setfacl -m user:42:rw- /pps/services/wifi/status')
    log('PPS ACLs restored, including stock net service access')


def main():
    assert ctypes.CDLL(None).setuid(0) == 0, 'Root transition failed'
    os.umask(0o077)
    for path, expected in HASHES.items():
        with open(path, 'rb') as f:
            assert hashlib.sha256(f.read()).hexdigest() == expected, 'Wrong build: '+path
    log('All four signed file hashes match')
    wp, sp = one('wpa_pps', 180), one('wpa_supplicant', 180)
    wdone = code_state(wp, ['wpa_pps', 'libwlandrv_bcm_dhd.so.1'])
    sdone = code_state(sp, ['wpa_supplicant'])
    log('Existing patches: wpa=%s supp=%s' % (wdone, sdone))
    if '--verify' in sys.argv:
        assert wdone and sdone, 'RAM patches are not all installed'
        return
    if wdone and sdone and '--reapply' not in sys.argv:
        return
    saved = backup_acl()
    # Keep a private pre-restart backup of saved profiles, without logging contents.
    for name in ['wpa_pps.conf', 'wpa_pps_protected.conf', 'wpa_pps_p2p.conf']:
        source = '/var/etc/netsecure/'+name
        if os.path.exists(source):
            shutil.copyfile(source, ROOT+'/backup-'+name)
            os.chmod(ROOT+'/backup-'+name, 0o600)
    changed = False
    try:
        changed = True
        terminate('wpa_pps')
        terminate('wpa_supplicant')
        time.sleep(.5)
        patch_held(launch('wpa_supplicant', True), 'wpa_supplicant')
        wait_file('/var/wlan/wpa_supplicant/bcm0')
        time.sleep(.3)
        patch_held(launch('wpa_pps', True), 'wpa_pps')
        time.sleep(1)
        restore_acl(saved)
        assert code_state(one('wpa_pps'), ['wpa_pps', 'libwlandrv_bcm_dhd.so.1'])
        assert code_state(one('wpa_supplicant'), ['wpa_supplicant'])
        log('SUCCESS: all six patch sites verified; normal services running')
    except Exception:
        traceback.print_exc()
        if changed:
            log('Failure recovery: restart original signed services without patches')
            terminate('wpa_pps')
            terminate('wpa_supplicant')
            time.sleep(.5)
            launch('wpa_supplicant', False)
            wait_file('/var/wlan/wpa_supplicant/bcm0')
            launch('wpa_pps', False)
            time.sleep(1)
            restore_acl(saved)
        raise


if __name__ == '__main__':
    main()
