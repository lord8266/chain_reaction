# Chain Reaction
A port of the android game chain reaction

###

The objective of Chain Reaction is to take control of the board by eliminating your opponents' orbs.

Players take it in turns to place their orbs in a cell.
Once a cell has reached critical mass the orbs explode into the surrounding cells
adding an extra orb and claiming the cell for the player.
 A player may only place their orbs in a blank cell or a cell that contains orbs of their own colour.
As soon as a player looses all their orbs they are out of the game.

###

# Status
Core game logic complete  
Need to add menu to choose configuration   
Only supporting linux.

# Prerequisites
This application used [SDL](https://www.libsdl.org/) ( Simple DirectMedia Layer)
## Linux 
Run  
```
sh install.sh
```
This will download and compile the required packages  
Files are downloaded by default to ~/sdl_source, You can change the directory in the sh file if you want

# Compiling
```
make
```
# Running the game
```
./main
```


