#!/bin/bash

if [ ! -d "builddir" ]; then
    meson setup builddir
fi

meson compile -C builddir
./builddir/search-engine
