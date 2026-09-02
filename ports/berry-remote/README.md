# Berry Remote — Chromium viewer on :8080

The Berry Browser we built for the Passport: QNX `content_shell` plus an
ES5 viewer at **http://127.0.0.1:8080/**.

```sh
qpkg install berry-remote
berryremote
# open http://127.0.0.1:8080/
```

Needs the Chromium engine (`content_shell` + Node `--jitless`) from
`qpkg install berry-browser` or from the **Berry Browser** BAR (rooted
device). The BAR also ships a Term49 bin to play with.

## Commands

```
berryremote                 Start (DuckDuckGo HTML)
berryremote https://…       Start or navigate
berryremote stop
berryremote status
```

Alias: `berrybrowser`
