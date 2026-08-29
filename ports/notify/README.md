# notify — Term49 Hub notifications

BPS `notification_notify` from the shell (Term49 has `post_notification`). PPS fallback writes `/pps/services/notify/control`.

```sh
qpkg install notify
notify
notify "Hello" "from Term49"
notify rocket "RocketChat" "new message"
```

Built on xps (`bb10-kitchen-sink`) for **armle-v7**. Rebuild: `bash /root/ports/notify/build-notify-passport.sh`
