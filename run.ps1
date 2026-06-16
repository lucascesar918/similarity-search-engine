if (-not (Test-Path "builddir")) {
    meson setup builddir
}
meson compile -C builddir
.\builddir\search-engine.exe
