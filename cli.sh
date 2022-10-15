#!/bin/bash

if [[ "$1" = "configure" ]]; then
  cmake -S . -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -DCMAKE_TOOLCHAIN_FILE=../vcpkg/scripts/buildsystems/vcpkg.cmake
  cp ./output/compile_commands.json ./compile_commands.json
elif [[ "$1" = "build" ]]; then
  cmake --build build
fi