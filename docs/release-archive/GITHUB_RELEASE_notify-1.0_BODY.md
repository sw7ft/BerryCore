## notify 1.0 — Hub notifications from Term49

BPS `notification_notify` (Term49 already has `post_notification`). PPS fallback for the RocketChat recipe.

```
qpkg install notify
notify
notify "Hello" "from Term49"
notify rocket "RocketChat" "new message"
notify pps TITLE SUB
```

Zip: `util-notify-1.0.zip`.
