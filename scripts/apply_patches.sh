#!/bin/bash

# Apply the patch
patch -p1 < ./patches/rogue.patch

echo "Patches applied successfully."