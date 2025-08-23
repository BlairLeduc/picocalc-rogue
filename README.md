# PicoCalc Rogue

A port of the classic [Rogue 5.4.4](http://rogue.rogueforge.net/rogue-5-4/) to the [PicoCalc kit](https://www.clockworkpi.com/product-page/picocalc).

# Exploring The Dungeons of Doom

Rogue is a computer fantasy game with a new twist. It is crt oriented
and the object of the game is to survive the attacks of various
monsters and get a lot of gold, rather than the puzzle solving
orientation of most computer fantasy games.

To get started you really only need to know two commands. The command
`?` will give you a list of the available commands and the command `/`
will identify the things you see on the screen.

To win the game (as opposed to merely playing to beat other people's
high scores) you must locate the Amulet of Yendor which is somewhere
below the 20th level of the dungeon and get it out. Nobody has
achieved this yet and if somebody does, they will probably go down in
history as a hero among heroes.

When the game ends, either by your death, when you quit, or if you (by
some miracle) manage to win, rogue will give you a list of the top-ten
scorers. The scoring is based entirely upon how much gold you get.
There is a 10% penalty for getting yourself killed.

## Authors

Michael C. Toy, Kenneth C. R. C. Arnold, Glenn Wichman

# Helpful Notes

You will find learning the movement keys to be essential to playing
effectively. On the PicoCalc kit, the arrow keys are mapped to the
up, down, left and right directions, but not the diagonal directions.
Moving diagonally uses half the food than moving horizontally/vertically
in series.

The movement keys are as follows:

```
Y  K  U
 \ | /
H -*- L
 / | \
B  J  N
```

The movement keys are based on the standard vi editor movement keys, with the addition of diagonal movement.

Combining a movement with the `Shift` key allows you to run in that direction
until you hit something; such as a wall, an item or a monster.

The `Ctrl` combination allows you to move in the specified direction and stop
if you before you hit something or come across an item or monster next to your
path.

Use `?` to get a list of available commands.

Use `/` to identify things on the screen.



To get started, read the [A Guide to the Dungeons of Doom](GUIDE.html).
