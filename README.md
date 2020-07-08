# gba-tileeditor
A simple tile editor for the Game Boy Advance.

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

## Original

The remainder of this readme is from Ian Finalyson's GBA Tile Editor.

Installing on Ubuntu Linux:
-------------
1. Navigate to https://github.com/IanFinlayson/gba-tileeditor/releases
2. Download the source code and unpack it.
3. `sudo apt-get install qt5-default`
4. `qmake gba-tileeditor.pro`
5. `make`
6. Run gba-tileeditor
7. To install globally, copy gba-tileeditor to /usr/local/bin
    
Installing on Windows:
-------------
1. Navigate to https://github.com/IanFinlayson/gba-tileeditor/releases
2. Download gba-tileeditor-windows.zip file.
3. Unpack it some place.
4. Run gba-tileeditor.exe

Installing on OSX:
-------------
1. Navigate to https://github.com/IanFinlayson/gba-tileeditor/releases
2. Download gba-tileeditor-osx.app.zip
3. Unzip the archive file.
4. Drag the .app file into your Applications folder.
5. Click yes, when it warns you about an untrusted developer.
