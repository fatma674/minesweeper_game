#ifndef CURSOR_H_INCLUDED
#define CURSOR_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include<conio.h>
#include <windows.h>
#include <ctype.h>
#include <time.h>

///variables declerations
extern struct cell
{
    int x;           ///x_pos of cell
    int y;          ///y_pos of cell
    int color;      ///color of cell state
    char state;     ///default state='X'
    int open;     /// say if this cell has opened or not(1 for open & 0 for close)
    char guess;  ///for flag or ques state
    int guess_color; ///flag or ques color

};

 COORD coord= {0,0}; // this is global variable
 int space;
 struct cell area[20][20];

 ///function declerations
void gotoxy(int x,int y);
void setColor(int i); ///to change color of output
void ShowConsoleCursor(int showFlag); ///to show cursor
void hidecursor(); ///to hide cursor
void cell_cursor_state(struct cell *this_cell);///to indicate where cursor is


#endif // CURSOR_H_INCLUDED
