#ifndef PLAY_GAME_H_INCLUDED
#define PLAY_GAME_H_INCLUDED

#include <stdlib.h>
#include<conio.h>
#include <windows.h>
#include <ctype.h>
#include <time.h>

//define buttons
#define esc 27
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

///define variables
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
const int W=20;
 const int H=20;
 int flag_color=13;
 int mine_color=4;
 int quest_color=10;
 int current_x;
 int current_y;
 int first=0;
  const int DIM ;
 int *ptrsize=&DIM;///no of cells in your level
 int choose;
 int mines;///no of mines created in your level
 int space;
 int level;
 int lives;
 int win;
 struct cell area[20][20];///area of the game with max size



//functions decleration
void gotoxy(int x,int y);
 void setColor(int i);
 void ShowConsoleCursor(int showFlag);
 void hidecursor();
void fill_default_cells();
void draw_frame();
void draw_cell_state(struct  cell* this_cell);
void create_mines(struct cell *first_cell);
int find_no_of_mines(int x_pos,int y_pos );
void open_neighbour(struct cell*this_cell);
void modify_cell_state( struct cell* this_cell);
void cheat_game();
void press_enter(int x_pos,int y_pos);
void move_player(int x,int y);
void cell_cursor_state(struct cell *this_cell);
struct cell* player_first_press(int x,int y);
void play();
void check_draw(int x,int y);
void press_flag(int current_x,int current_y);
void open_eight(int x,int y);
void press_Ques(int current_x,int current_y);
void draw_guess(struct  cell* this_cell);
void you_win();
int check_win();
void you_loss();


#endif // PLAY_GAME_H_INCLUDED
