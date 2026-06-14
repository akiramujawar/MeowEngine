#!/bin/bash

ENGINE_PATH="/Users/akira/Downloads/physicat/meowengine"

brew update
brew install cmake
export PATH="/opt/homebrew/bin:$PATH"
cmake --version

cmake \
    -DPROJECT_PATH="$(pwd)" \
    -S "${ENGINE_PATH}" \
    -B "$(pwd)/.cache"

cmake --build "$(pwd)/.cache" --parallel
#cmake --build "$(pwd)/Build" --verbose