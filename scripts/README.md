# Create patches

Create a `working` directory and copy the original source files that need to be modified into it. Then, make your changes in the `working` directory.

If you add new files that will need to be patched, add that file to the `create_patches.sh` script.

Finally, run the `create_patches.sh` script to generate the `patches/rogue.patch` file.
# Build a release

Run `scripts/build_release.sh` to build the release UF2s into `dist/`: the Pico (RP2040) and Pico 2 (RP2350) builds, and a Pico 2 build that runs from SRAM without writing flash. The version comes from `PICOCALC_ROGUE_VERSION` in `CMakeLists.txt`, or pass it as the first argument (`scripts/build_release.sh 1.3`).
