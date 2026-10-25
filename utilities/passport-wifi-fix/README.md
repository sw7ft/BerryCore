# Passport Wi-Fi scan runtime fix

Opt-in workaround for [issue #8](https://github.com/sw7ft/BerryCore/issues/8), tested on one rooted BlackBerry Passport SQW100-1 running BB10 10.3.3.3216 with BCM4339 and getroot v4. These four scripts are the unchanged versions used for the successful on-device test and reboot on 2026-10-24. They are not installed by BerryCore's general installer.

Nearby APs with more than 512 bytes of information elements can cause the scan result batch to be rejected. This was observed around Wi-Fi 6 APs, but the trigger is IE length, not simply support for 802.11ax. The original issue's “overflow” describes a rejected length; an exploitable buffer overflow was not established.

The helper patches RAM in newly started Wi-Fi processes. It leaves signed OS images, executables and libraries on disk unchanged. Normal Settings scanning, the Wi-Fi switch, saved-profile reconnection and WPA2-PSK connection worked after the fix. No external debugger or computer is needed once the boot addon is installed.

## Supported build

All four SHA-256 hashes must match before any service is stopped. A matching OS version label alone is insufficient. Do not remove these checks or copy these offsets to another device/build.

| Original device file | SHA-256 |
| --- | --- |
| `/usr/sbin/wpa_pps` | `4740e29a6a151777bf17e687eccbf274f2f0c289e5bbc7ef6de8deff92032449` |
| `/usr/lib/libwlandrv_bcm_dhd.so.1` | `36f6905d2f23b973e397113ba490ff503a4ede4a193eae7546270ef1177e0ec9` |
| `/usr/sbin/wpa_supplicant` | `33e5d4a149eaa3f7aec6593dc3b2e6c899248cfc6daf35f4fd2dacb13cd1db91` |
| `/proc/boot/libc.so.3` | `cd0dd08e8bed74ed6a9fc01a860656f7882c454ca6b7866789f6c59302228e3c` |

Requires the phone's Python 3.2 with `qnx.devctl`, root access, and the tested getroot v4 addon mechanism for automatic startup. The root bootstrap also relies on `on` and `/base/bin/__root`. No proprietary binaries are included.

## Install and first run

Use a working root USB SSH session: applying the patch restarts Wi-Fi and interrupts a Wi-Fi SSH connection. Replace `passport` below with your device's root SSH alias. Run host commands from this directory.

Create a private directory and initially disable automatic application:

```sh
ssh passport 'umask 077; mkdir -p /var/rootdata/wifi-fix; chmod 700 /var/rootdata/wifi-fix; touch /var/rootdata/wifi-fix/disabled'
scp boot_patch.py phone_debug.py start.sh passport:/var/rootdata/wifi-fix/
ssh passport 'chmod 600 /var/rootdata/wifi-fix/boot_patch.py /var/rootdata/wifi-fix/phone_debug.py /var/rootdata/wifi-fix/start.sh'
```

Perform the first manual application before installing the boot addon:

```sh
ssh passport 'unset PYTHONOPTIMIZE; rm /var/rootdata/wifi-fix/disabled; /bin/sh < /var/rootdata/wifi-fix/start.sh'
ssh passport 'cat /var/rootdata/wifi-fix/boot.log'
```

The log should end with `SUCCESS: all six patch sites verified; normal services running`. Check the phone's Wi-Fi switch, network list and connection. An already-patched pair of processes is left running. Do not use Python `-O`, `-OO`, or `PYTHONOPTIMIZE`: this tested implementation uses assertions for preflight and verification.

Unsigned scripts must be fed to the shell on stdin as shown; direct execution or `/bin/sh FILE` was rejected on the tested phone. The launcher starts Python as UID 100 with the setuid ability and the script transitions to root. Child Wi-Fi services explicitly do not inherit that nonroot setuid ability.

If manual application works, install the getroot v4 boot addon:

```sh
ssh passport 'umask 077; mkdir -p /var/addons/passport-wifi/init'
scp addon-start.sh passport:/var/addons/passport-wifi/init/start.sh
ssh passport 'chmod 700 /var/addons/passport-wifi /var/addons/passport-wifi/init /var/addons/passport-wifi/init/start.sh'
```

On the next reboot, getroot v4 discovers `/var/addons/*/init/start.sh` during its root stage. The addon normalizes real/effective credentials with `__root`, waits up to 90 seconds for `Script finished successfully` in `/tmp/root_install_x.log`, then invokes the launcher. Do not replace `/var/rootdata/install.sh`; that was not a working hook in this setup. The getroot startup environment must also leave `PYTHONOPTIMIZE` unset.

## Verify, disable and remove

Read-only verification of the six RAM instructions (does not stop/restart the Wi-Fi services):

```sh
ssh passport 'unset PYTHONOPTIMIZE; on -ePYTHONHOME=/usr:/usr -u 100:0 -A nonroot,allow,setuid,inherit /usr/bin/python3.2 -u /var/rootdata/wifi-fix/boot_patch.py --verify'
```

Success reports matching hashes and `Existing patches: wpa=True supp=True`, with exit status 0. This verifies instruction bytes, not every page permission or network behavior.

Disable future application:

```sh
ssh passport 'touch /var/rootdata/wifi-fix/disabled'
```

The current RAM patches remain until the affected processes exit. Reboot with the marker present to return to original code. To remove only the automatic startup hook:

```sh
ssh passport 'rm /var/addons/passport-wifi/init/start.sh'
```

To re-enable, remove the `disabled` marker. If either Wi-Fi process restarts independently, rerun the manual launcher or reboot. This is a one-shot boot addon, not a supervisor. The launcher uses a `/tmp/passport-wifi-fix.lock` file because this QNX `/tmp` does not support directories; a killed launcher can leave a stale lock until reboot. Remove it manually only after confirming no patch helper is running.

## Why a single driver byte was insufficient

The driver's `wlan_drvlib_parse_iscan_results` compares the BSS IE length with 512 and returns 22 on an oversized record, bypassing the success return. The caller discards the batch. Downstream processing has four additional 512-byte checks. Raising only the driver limit therefore does not complete the fix.

Offsets below are ELF virtual offsets (also file offsets at these locations in the verified build). The tool derives current mapping bases from `/proc/PID/pmap`, checks old instructions, and writes the complete four-byte instructions in RAM.

| Component | Offset | Original bytes | Patched bytes | Purpose |
| --- | --- | --- | --- | --- |
| `libwlandrv_bcm_dhd.so.1` | `0x9cc6` | `b3 f5 00 7f` | `b3 f5 00 6f` | IE limit 512 → 2048 |
| `wpa_pps` | `0x3f7f8` | `b6 f5 00 7f` | `b6 f5 00 6f` | IE limit 512 → 2048 |
| `wpa_pps` | `0x3ad50` | `b2 f5 00 7f` | `b2 f5 00 6f` | IE limit 512 → 2048 |
| `wpa_supplicant` | `0x2627c` | `b7 f5 00 7f` | `b7 f5 00 6f` | First-result IE limit |
| `wpa_supplicant` | `0x262ca` | `b7 f5 00 7f` | `b7 f5 00 6f` | Subsequent-result IE limit |
| `wpa_pps` | `0x3ad3e` | `47 f6 e4 51` | `47 f2 b0 71` | Batch threshold → 30640 |

The batch threshold reserves room in the 32768-byte transport buffer: `30640 + 2048 IE bytes + 56 record bytes + 24 transport bytes = 32768`. The existing supplicant array limit of 128 records is retained. Relevant IE destination allocations are dynamic, but raising the limits is not comprehensive parser hardening: source-record bounds validation remains limited. 2048 covers the observed 542–561-byte IEs; it does not guarantee compatibility with every possible beacon.

## How the phone-local patch works

Ordinary writes to RX text fail, but QNX software breakpoints through `DCMD_PROC_BREAK` work on this target. Changing GDB's memory-region description does not change target page permissions. Hardware breakpoints were refused.

The helper launches each service held with `on -h`, attaches through `/proc/PID/as`, clears the job-control stop with SIGCONT and runs to a software breakpoint. For `wpa_pps`, the stop is `+0x81dc`, after loading the driver but before its ability lockdown. For `wpa_supplicant`, it is the ELF entry point. This avoids injecting calls into a thread blocked in MsgReceive.

Using procfs register operations, it calls the target's ARM-mode `mprotect_r` (`libc+0x25150`) to change RX → RW, writes the instructions, restores RX, and calls `msync_r` (`libc+0x256bc`, flag `0x1000000`) to synchronize the instruction cache. The return breakpoint is at `libc+0x251d4`. All 17 ARM registers and the scratch stack region are restored. QNX protection flags here are READ `0x100`, WRITE `0x200`, EXEC `0x400`.

Timing matters: after `wpa_pps` initialization, restoring execution permission was denied. Patching before its normal ability drop solves this without disabling that lockdown. `/proc/PID/pmap` can show stale region protection summaries; independent inspection used `/proc/PID/mappings` for actual page protections.

The helper saves/restores seven Wi-Fi PPS ACLs and reapplies stock user 42 access to `wifi/status`. Without this, restarting the services left Settings unable to read status even though the backend worked. Truncated `getfacl` account names are resolved against local account tables to numeric IDs. Saved-profile backups are private mode 0600 files under `/var/rootdata/wifi-fix`; do not publish that directory wholesale because these backups may contain credentials.

On a patch exception, the injected target is killed rather than resumed with temporary registers. The outer handler attempts to restart the original signed services and restore ACLs. This is best-effort recovery, not a guarantee against every failure, and the original scan limitation returns on fallback.

## Validation and remaining uncertainty

On 2026-10-24, the phone-local scripts patched freshly started services, restored RX and reconnected to a saved WPA2-PSK network. After a real phone reboot, the final v2 addon entered at 23:56:01 Singapore time, getroot completed at 23:56:08, and all six patches were applied automatically by 23:56:16. No manual patch was applied after that reboot. An independent read-only check passed at 23:56:36; page inspection showed `mi_prot=5` (RX) at all six sites. The user confirmed normal Wi-Fi connection; Settings switch/list/connection had also been confirmed during validation.

An earlier reboot produced a black screen and required a forced restart. No addon entry was found for that event, and its cause remains unresolved. One successful reboot does not establish broad boot reliability. The first addon revision also failed because real/effective group IDs differed; the included v2 normalizes those credentials and waits for getroot completion.

Evidence is limited to this one device/build and WPA2-PSK. WPA3, other models/builds, repeated long-term boot reliability and arbitrary malformed scan input are not validated. No radio firmware or authentication-protocol support is added.

Interface references used during development:

- [Historical ARM32 QNX procfs definitions](https://github.com/vocho/openqnx/blob/master/trunk/services/system/public/sys/procfs.h)
- [Historical debug definitions](https://github.com/vocho/openqnx/blob/master/trunk/services/system/public/sys/debug.h)
- [QNX process/debugging documentation](https://qnx.com/developers/docs/6.5.0SP1.update/com.qnx.doc.neutrino_prog/process.html)

The actual constants/layouts were checked against this device. Do not substitute modern QNX 8.x 64-bit structure layouts based on BB10's kernel version string.
