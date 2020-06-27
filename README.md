# minesweeper_game
#### This is Minesweeper Game (command prompt game) implemented in C Language.

## what will you need to run it?
you will need  an IDE with only standard libraries. 

## what is minesweeper game?
Minesweeper is a single-player puzzle video game. The objective of the game is to clear a rectangular board containing hidden "mines" or bombs without detonating any of them, with help from clues about the number of neighboring mines in each field.
In its original form, mines are scattered throughout a board. This board is divided into cells, which have three states: uncovered, covered and flagged. A covered cell is blank a, while an uncovered cell is exposed, either containing a number (the mines adjacent to it), or a mine. When a cell is uncovered by a player pressing enter, and if it bears a mine, the game ends. A flagged cell is similar to a covered one, in the way that mines are not triggered when a cell is flagged, and it is impossible to lose through the action of flagging a cell. However, flagging a cell implies that a player thinks there is a mine underneath, which causes the game to deduct an available mine from the display.

In order to win the game, players must logically deduce where mines exist through the use of the numbers given by uncovered cells. To win, all non-mine cells must be uncovered. . Commonly all mine cells are also flagged, but this is not required.

When a player press 'Enter' on a cell, the game will uncover it. If there are no mines adjacent to that particular cell, the mine will display   a "0", and all  8 adjacent cells will automatically be uncovered. pressing "F" on a cell will flag it, causing a flag to appear on it. Note that flagged cells are still covered, and a player can press 'Enter' on it to uncover it, like a normal covered cell (in many implementations, one must first unflag it, by pressing "Q" on it).
