#!/bin/bash
# Build the release UF2s into dist/
#
#   scripts/build_release.sh [version]
#
# The version defaults to PICOCALC_ROGUE_VERSION in CMakeLists.txt.

set -euo pipefail

cd "$(dirname "$0")/.."

VERSION="${1:-$(sed -nE 's/^ *set\(PICOCALC_ROGUE_VERSION "([^"]+)".*/\1/p' CMakeLists.txt)}"
if [ -z "$VERSION" ]; then
    echo "Cannot find PICOCALC_ROGUE_VERSION in CMakeLists.txt" >&2
    exit 1
fi

# Prefer the tools installed by the Raspberry Pi Pico VS Code extension
CMAKE="$(ls -d "$HOME"/.pico-sdk/cmake/*/bin/cmake 2>/dev/null | tail -1 || true)"
NINJA="$(ls "$HOME"/.pico-sdk/ninja/*/ninja 2>/dev/null | tail -1 || true)"
CMAKE="${CMAKE:-$(command -v cmake)}"
NINJA="${NINJA:-$(command -v ninja)}"

DIST=dist
rm -rf "$DIST"
mkdir -p "$DIST"

# name board no_flash
build() {
    local name=$1 board=$2 no_flash=$3
    local dir="$DIST/build/$name"

    echo "Building $name..."
    "$CMAKE" -S . -B "$dir" -G Ninja \
        -DCMAKE_MAKE_PROGRAM="$NINJA" \
        -DCMAKE_BUILD_TYPE=Release \
        -DPICO_BOARD="$board" \
        -DPICOCALC_ROGUE_VERSION="$VERSION" \
        -DPICOCALC_ROGUE_NO_FLASH="$no_flash" > /dev/null
    "$NINJA" -C "$dir" > /dev/null

    local uf2=picocalc-rogue.uf2
    if [ "$no_flash" = ON ]; then
        uf2=picocalc-rogue-noflash.uf2
    fi
    cp "$dir/$uf2" "$DIST/picocalc-rogue-v$VERSION-$name.uf2"
}

build pico pico OFF
build pico2 pico2 OFF
build pico2-noflash pico2 ON

rm -rf "$DIST/build"

echo "Release v$VERSION built:"
ls -1 "$DIST"/*.uf2
