#!/bin/bash

ENGINE_PATH="/Users/akira/Downloads/physicat/meowengine"
SH_DIRECTORY="$(cd "$(dirname "$0")" && pwd)"

brew update
brew install cmake
export PATH="/opt/homebrew/bin:$PATH"
cmake --version

cmake \
    -DPROJECT_PATH="${SH_DIRECTORY}" \
    -S "${ENGINE_PATH}" \
    -B "${SH_DIRECTORY}/.cache"

cmake --build "${SH_DIRECTORY}/.cache" --parallel
#cmake --build "$(pwd)/Build" --verbose