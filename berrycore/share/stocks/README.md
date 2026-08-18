# The Tape (stocks)

ES5 stock ticker and research for berry-browser. Port **8096**. Night-tape desk, not the Waterway chrome.

```sh
qpkg install stocks
stocks
berry-browser http://127.0.0.1:8096/
```

Also: `ticker`.

- Custom lists
- Live quotes (Yahoo spark/chart)
- Per-symbol up-tick hub notifications
- Price above/below alerts
- Research: range, sector, 5-day spark, headlines

Alerts append to `/pps/services/notify/control` the same way Rocket.Chat does.
