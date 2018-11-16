# textMines
Basic text implementation of mines in C++ using a textbased interface.  

## How to compile the game on a Unix-system (Linux or Mac OS)
Run the following command in the root of the folder:
```zsh
g++ main.cpp source/game.cpp source/helperClasses.cpp -o main
```
The main program can then be run by:
```zsh
./main
```


## How to play the game
- Use the command Dx,y to dig in the ground.
- Use the command Fx,y to place a flag.
- Use the command ?x,y to place a questionmark.
- Use the command C to close the program.

To win the game, you must find all the bombs. The numbers on the fields show the number of bombs next to that field.
