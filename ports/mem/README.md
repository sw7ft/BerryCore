# mem — Term49 process memory peek

Read our own `/proc/<pid>/as` (maps + hex). Will not open `/dev/mem` or other uids.

```sh
qpkg install mem
mem
mem maps
mem read 0x1418000
mem read -p PID 0x1418000 64
```

Built on xps (`bb10-kitchen-sink`) for **armle-v7**. Rebuild: `bash /root/ports/mem/build-mem-passport.sh`
