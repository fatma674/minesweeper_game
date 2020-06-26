#ifndef MENU_GAME_H_INCLUDED
#define MENU_GAME_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include<conio.h>
#include <windows.h>
#include <ctype.h>
#include <time.h>

  struct cell
{
    int x;           ///x_pos of cell
    int y;          ///y_pos of cell
    int color;      ///color of cell state
    char state;     ///default state='X'
    int open;     /// say if this cell has opened or not(1 for open & 0 for close)
    char guess;  ///for flag or ques state
    int guess_color; ///flag or ques color

};

///extern global variables
extern int *ptrsize;
extern int mines;
extern int space;
extern int level;
extern int lives;
extern int choose;
 extern const int DIM ;

///functions decleration
 void exit_game();
 void level_select();
 void show_instructions();


#endif // MENU_GAME_H_INCLUDED
