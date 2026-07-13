Game data (IWAD) for QNX Doom
=============================

This port ships with Freedoom Phase 1 (freedoom1.wad) — a free replacement
for Doom game data. You can add your own WAD files here too.

Bundled:
  freedoom1.wad   — Freedoom Phase 1 (GPL/BSD, https://freedoom.github.io/)

Optional (copy here):
  freedoom2.wad   — Freedoom Phase 2 (Doom II-style)
  doom.wad        — original Doom (your copy)
  doom2.wad       — Doom II (your copy)

The launcher picks the first match: freedoom1, freedoom2, doom, doom2.

Force a specific file:
  qnx-doom -iwad /path/to/doom2.wad
