# Conway's Game of Life — 8‑Bit Challenge

This repository collects compact, platform-targeted implementations of Conway's Game of Life for classic 8‑bit systems.

## Goals

- Implement small, idiomatic versions of the Game of Life for a variety of 8‑bit targets.
- Provide buildable source, example binaries, and minimal instructions to run on emulators or hardware.

## Targets

- `src/targets/6502/c64` — Commodore 64 (C64) implementation (C source + prebuilt `bin/life.prg`).
- `src/targets/z80/cpc` — Amstrad CPC / Z80 target (see the folder for details).

Each target directory contains platform-specific source, any helper config, and notes on building/running.

## Building

Most targets include short build instructions in their target README. Example for the C64 target (requires cc65/cl65):

```bash
cd src/targets/6502/c64
cl65 -t c64 -o bin/life.prg life.c
```

## Running

Use an emulator (recommended) such as VICE for C64 targets:

```bash
x64sc src/targets/6502/c64/bin/life.prg
```

For CPC/Z80 targets follow the instructions in `src/targets/z80/cpc/README.md`.

## Contributing

Contributions are welcome. Keep changes target-scoped (place code under `src/targets/...`) and include build instructions. Open an issue or PR with a short description and test instructions.

## License

See the repository `LICENSE` file for licensing terms.
