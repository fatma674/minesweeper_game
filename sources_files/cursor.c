#include"cursor.h"

///returns void and take cursor coordinate,it enable cursor to move wherever wanted
void gotoxy(int x,int y)
{
    coord.X=x;///COORD is struct to get position of cell
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
///returns void and take color number,it change output color
void setColor(int i)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), i);
}
///returns void ,it makes cursor visible
void ShowConsoleCursor(int showFlag) ///to show cursor
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

///returns void and take nothing,it make cursor invisible
void hidecursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

///returns void and take pointer to struct cell,it show game cursor when user play,move and navigate during playing
void cell_cursor_state(struct cell *this_cell)
{
    gotoxy(this_cell->x+space,this_cell->y+space);
    setColor(9);
    printf("^");   //cursor state
    gotoxy(this_cell->x+space,this_cell->y+space);
}
