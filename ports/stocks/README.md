# Stocks

ES5 stock ticker, research, custom lists, up-ticks, and PPS alerts. Port **8096**.

## Install

```sh
qpkg install stocks
```

`qpkg install ticker` is the same package.

## Usage

```sh
stocks
stocks status
stocks stop
ticker
berry-browser http://127.0.0.1:8096/
```

Lists and alerts persist in `$NATIVE_TOOLS/.tmp/stocks-state.json`.
Hub banners write `/pps/services/notify/control` (Rocket.Chat notify path).
