# gba-tileeditor
A simple tile editor for the Game Boy Advance.

## Badges

[![Codacy Badge](https://app.codacy.com/project/badge/Grade/21d36801cdfb4bfcac550b31ab9eb619)](https://www.codacy.com/manual/quentin-dev/gba-tileeditor?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=quentin-dev/gba-tileeditor&amp;utm_campaign=Badge_Grade)

![Build GBA Tile Editor 🛠️](https://github.com/quentin-dev/gba-tileeditor/workflows/Build%20GBA%20Tile%20Editor%20%F0%9F%9B%A0%EF%B8%8F/badge.svg)

### gba-tileeditor

![AUR last modified](https://img.shields.io/aur/last-modified/gba-tileeditor)

### gba-tileeditor-git

![AUR last modified](https://img.shields.io/aur/last-modified/gba-tileeditor-git)

## Info

This project is a fork of Ian Finlayson's GBA Tile Editor. The goal of
this fork is to update the existing codebase and add features to the
existing program. As of writing this, the project was just recently forked
and has not been renamed or anything yet, as the original project has been
untouched for the last two years.

## Features

- [X] Export to C source files (.c & .h)
- [X] Serialize maps to JSON for saving & loading

## Upcoming

You can check out the project's [Trello](https://trello.com/b/py7VmhQo/gba-tile-editor)
board to see what the features being worked on and the overall progress. You can also
check out the project's `TODO.md`.

## Installing

### Arch Linux

GBA Tile Editor is available on the AUR in two different packages:

- The development version: [`gba-tileeditor-git`](https://aur.archlinux.org/packages/gba-tileeditor-git/)
- The release version: [`gba-tileeditor`](https://aur.archlinux.org/packages/gba-tileeditor/)

The development version of the package is available on the AUR as 


### Other Linux distributions

#### Requirements

* Qt 5

#### Instructions

1. Clone the repo and `cd` into it
2. `qmake gba-tileeditor-client/gba-tileeditor-client.pro`
3. `make -j$(nproc)`

You can then run the program with `./gba-tileeditor`
