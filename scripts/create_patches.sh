diff -u modules/rogue/extern.c working/extern.c > patches/rogue.patch
diff -u modules/rogue/io.c working/io.c >> patches/rogue.patch
#diff -u modules/rogue/main.c working/main.c >> patches/rogue.patch
diff -u modules/rogue/rogue.h working/rogue.h >> patches/rogue.patch
sed -i '' -E 's/^(---) (modules\/rogue|working)\/([a-z_]+\.[ch])/\1 a\/rogue\/\3/; s/^(\+\+\+) (modules\/rogue|working)\/([a-z_]+\.[ch])/\1 b\/rogue\/\3/' patches/rogue.patch
