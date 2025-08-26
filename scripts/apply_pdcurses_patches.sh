#!/bin/bash

# Apply the patch
patch -p1 < ./patches/pdcurses.patch

echo "P\PDCurses patches applied successfully."