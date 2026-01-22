
# Commodore 64 (6502) — Conway's Game of Life

This folder contains the C64 target for the 8-bit Challenge implementation of Conway's Game of Life.

## Overview

A compact implementation targeted at the Commodore 64. A prebuilt program is available in `bin/` and the C source is provided as `life.c`.

## Files

- `life.c` — C source for the C64 build.
- `vc.config` — Build/run configuration for the target (if used by helper scripts).
- `bin/life.prg` — Prebuilt PRG ready to run on an emulator or real hardware.

## Requirements

- `vbcc` (vc toolchain) to build from `life.c`.
- A C64 emulator such as VICE (`x64` / `x64sc`) for testing, or real hardware and a suitable transfer method.

## Build (example)

Build locally with the cc65 toolchain. From this directory:

```bash
vc -O4 -o bin/life.prg life.c
```

## Run

Start the VICE emulator and load the PRG:

```bash
x64sc bin/life.prg
```

Or drag `bin/life.prg` into a running VICE window. On real hardware, create a disk image or use a transfer tool to load the PRG.

## Notes

- Controls and runtime options are documented in the source comments in `life.c`.

## License & Credits

See the project root `LICENSE` for licensing. This target is part of the Conway's Game of Life — 8-Bit Challenge collection.
