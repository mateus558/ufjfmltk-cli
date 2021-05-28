# UFJF-MLTK: Command-Line Interface
[![Meson](https://github.com/mateus558/ufjfmltk-cli/actions/workflows/meson.yml/badge.svg?=windows-build)](https://github.com/mateus558/ufjfmltk-cli/actions/workflows/meson.yml)
[![CMake](https://github.com/mateus558/ufjfmltk-cli/actions/workflows/cmake.yml/badge.svg)](https://github.com/mateus558/ufjfmltk-cli/actions/workflows/cmake.yml)

## Building and Running

with meson
```
meson build
meson compile -C build
./build/ufjfmltk_cli
```
with cmake
```
cmake -B build
cmake --build build
./build/ufjfmltk_cli
```

**Requirements:**

All requirements besides meson are installed on ``meson build`` command.
- meson or cmake
- gnuplot
- ufjfmltk 
