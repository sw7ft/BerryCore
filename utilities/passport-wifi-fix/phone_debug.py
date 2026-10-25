"""BB10 ARM32 procfs debugger primitives; Python 3.2 compatible."""
import os
import struct
import time
import binascii
import qnx.devctl as d


class Process:
    def __init__(self, pid):
        self.pid = int(pid)
        self.fd = os.open('/proc/%d/as' % self.pid, os.O_RDWR)
        self.breakpoints = set()

    def control(self, cmd, direction, data):
        size = data if isinstance(data, int) else len(data)
        # GET/SETGREG encode the union size, although only 68 ARM bytes are used.
        encoded_size = 8192 if cmd in (10, 11) else size
        op = d.build_op(8, cmd, direction, encoded_size)
        return d.devctl(self.fd, op, data)

    def status(self):
        return self.control(7, d.DEVDIR_FROM, 224)

    def stop(self):
        return self.control(5, d.DEVDIR_FROM, 224)

    def regs(self):
        return list(struct.unpack('<17I', self.control(10, d.DEVDIR_FROM, 8192)[:68]))

    def setregs(self, regs):
        self.control(11, d.DEVDIR_TO, struct.pack('<17I', *regs))

    def breakpoint(self, address, remove=False):
        data = bytearray(struct.pack('<HhI', 1,
                                     -1 if remove else (2 if address & 1 else 0),
                                     address & ~1))
        self.control(14, d.DEVDIR_TOFROM, data)
        if remove:
            self.breakpoints.discard(address)
        else:
            self.breakpoints.add(address)

    def run(self):
        # Clear old fault/signal, trace faults (including breakpoint traps).
        self.control(9, d.DEVDIR_TO,
                     struct.pack('<9I', 0x13, 1, 0, 0, 0, 0, 0xffffffff, 0xffffffff, 0))

    def wait(self, expected, timeout=5):
        until = time.time() + timeout
        while time.time() < until:
            s = self.status()
            flags = struct.unpack_from('<I', s, 8)[0]
            if flags & 3 == 3:
                regs = self.regs()
                if regs[15] != expected:
                    raise RuntimeError('Unexpected stop PC %x, expected %x, status %s' %
                                       (regs[15], expected, binascii.hexlify(s[:24])))
                return regs
            time.sleep(.01)
        self.stop()
        raise RuntimeError('Timed out; process stopped')

    def read(self, address, size):
        os.lseek(self.fd, address, os.SEEK_SET)
        data = os.read(self.fd, size)
        if len(data) != size:
            raise RuntimeError('Short memory read')
        return data

    def write(self, address, data):
        os.lseek(self.fd, address, os.SEEK_SET)
        if os.write(self.fd, data) != len(data):
            raise RuntimeError('Short memory write')

    def mappings(self):
        result = {}
        with open('/proc/%d/pmap' % self.pid) as f:
            for line in f:
                fields = line.rstrip().split(',')
                if len(fields) == 13 and fields[0].startswith('0x'):
                    name = fields[-1].split('/')[-1]
                    if name not in result and int(fields[3], 16) & 4:
                        result[name] = int(fields[0], 16)
        return result

    def close(self):
        for address in list(self.breakpoints):
            self.breakpoint(address, True)
        os.close(self.fd)


def selftest(pid, thumb=False):
    """Only use on an expendable on -h sleep process."""
    p = Process(pid)
    try:
        p.stop()
        original = p.regs()
        m = p.mappings()
        c, base = m['libc.so.3'], m['sleep']
        entry = base + struct.unpack('<I', p.read(base+24, 4))[0]
        if thumb:
            entry = base+0x8f4  # This build's sleep() main, reached through BLX.
        bp_address = entry | (1 if thumb else 0)
        print('held PC=%x entry=%x cpsr=%x' % (original[15], entry, original[16]))
        p.breakpoint(bp_address)
        import signal
        os.kill(p.pid, signal.SIGCONT)
        p.run()
        original = p.wait(entry)
        p.breakpoint(bp_address, True)
        ret = c+0x251d4
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
            print('rpc %x -> %x' % (function, result))
            assert result == 0

        rpc(c+0x25150, base, 4096, 0x700)
        old = p.read(entry, 4)
        p.write(entry, old)
        assert p.read(entry, 4) == old
        rpc(c+0x25150, base, 4096, 0x500)
        rpc(c+0x256bc, base, 4096, 0x1000000)
        p.breakpoint(ret, True)
        p.write(scratch, saved_stack)
        p.setregs(original)
        assert p.regs() == original
        p.run()
        print('SELFTEST PASSED')
    finally:
        p.close()


if __name__ == '__main__':
    import ctypes
    import sys
    assert ctypes.CDLL(None).setuid(0) == 0
    assert sys.argv[1] in ('selftest', 'selftest-thumb')
    selftest(int(sys.argv[2]), sys.argv[1] == 'selftest-thumb')
