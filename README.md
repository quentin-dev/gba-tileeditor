# gba-tileeditor
A simple tile editor for the Game Boy Advance.

## Badges

[![Codacy Badge](https://app.codacy.com/project/badge/Grade/21d36801cdfb4bfcac550b31ab9eb619)](https://www.codacy.com/manual/quentin-dev/gba-tileeditor?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=quentin-dev/gba-tileeditor&amp;utm_campaign=Badge_Grade)

## Info

This project is a fork of Ian Finlayson's GBA Tile Editor. The goal of
this fork is to update the existing codebase and add features to the
existing program. As of writing this, the project was just recently forked
and has not been renamed or anything yet, as the original project has been
untouched for the last two years.

## Features

- [X] Export to C source files (.c & .h)

## Upcoming

You can check out the project's [Trello](https://trello.com/b/py7VmhQo/gba-tile-editor)
board to see what the features being worked on and the overall progress.

## Installing

### Arch Linux

This package is available on the AUR as `gba-tileeditor-git`.

### Other Linux distributions

#### Requirements

* Qt 5

#### Instructions

1. Clone the repo and `cd` into it
2. `qmake gba-tileeditor.pro`
3. `make -j$(nproc)`

You can then run the program with `./gba-tileeditor`

## Planned

See the repo's TODO.md for what might come next.
