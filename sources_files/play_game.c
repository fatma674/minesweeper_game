#include"play_game.h"

///draw functions

///returns void and take nothing,it draw main frame of the game
void draw_frame()
{
    setColor(12);
    gotoxy(26,10);
    printf("HELLO FRIEND !! TO CREATE FLAGS ENTER 'F'\n");
    gotoxy(26,11);
    printf("LEVEL(%d): lives=%d, MINES=%d",level,lives,mines);
    gotoxy(26,26);
    setColor(6);
    printf("press 'ESC' to exit\n");
    setColor(136);
    gotoxy(2,2);
    for(int i=0; i<=W+2; i++)
    {
        printf(" ");
    }
    for(int i=0; i<H+1; i++)
    {
        gotoxy(2,i+3);
        printf(" ");
        gotoxy(W+4,i+3);
        printf(" ");
    }
    gotoxy(2,H+3);
    for(int i=0; i<=W+1; i++)
    {
        printf(" ");
    }
    setColor(8);
}

///returns void and take pointer to struct cell,it draw every cell in game
void draw_cell_state(struct  cell* this_cell)
{
    gotoxy(this_cell->x+space,this_cell->y+space);
    setColor(this_cell->color);
    printf("%c",this_cell->state);

}

///returns void and take pointer to struct cell,it draw flagged or quested cells which user enter
void draw_guess(struct  cell* this_cell)
{
    gotoxy(this_cell->x+space,this_cell->y+space);
    setColor(this_cell->guess_color);
    printf("%c",this_cell->guess);

}
/////////////////////////////////////////////////////////////////////////////////////////////
///fill function

///returns void and take nothing,it fill default initialized data for every cell
void fill_default_cells()
{
    for(int i=0; i<=*ptrsize-1; i++)
        for(int j=0; j<= *ptrsize-1; j++)
        {
            area[i][j].x=i;
            area[i][j].y=j;
            area[i][j].color=15;   ///default color
            area[i][j].state='X'; ///default state
            area[i][j].open=0; ///default color
            area[i][j].guess=area[i][j].state;

            area[i][j].guess_color=area[i][j].color;

        }
}
/////////////////////////////////////////////////////////
///press functions


///returns void and take current coordinates,it make an action when user press enter
void press_enter(int x_pos,int y_pos)   //user open this cell
{   win= check_win();
    if(win!=1)///to check you still not a winner
    {
        area[x_pos][y_pos].open=1;
        if(area[x_pos][y_pos].state=='M')
        {
            ///OH!! you pressed a bumb
            cheat_game();
            gotoxy(26,15);
            setColor(4);
            system("pause");
            you_loss();
        }
        else///if it has a number
        {
            modify_cell_state(&area[x_pos][y_pos]);


        }
    }
    else
      you_win();
}


///returns pointer to struct cell and take current coordinates,it decide if user press his first enter and return this first pressed cell
struct cell* player_first_press(int x,int y)///check for first pressed cell
{
    //static int TRY=0;
    cell_cursor_state(&area[current_x][current_y]);
    char cursor;

//timeIdle=time(NULL);
    while(1)
    {
        cursor=_getch();
        if(cursor==(char)13)///press enter
        {
            first= 1;     ///return first pressed cell
            return &area[current_x][current_y];
        }

        else
        {
            switch(cursor)
            {
            case(char) KEY_LEFT:
            {
                if(x>0)
                {
                    x=x-1;
                    gotoxy(x,y);
                    fill_default_cells(&area[current_x][current_y]);
                    draw_cell_state(&area[current_x][current_y]);
                    current_x=x;
                    current_y=y;
                    cell_cursor_state(&area[current_x][current_y]);
                    //fill_default_cells();
                    break;
                }
            }
            case (char) KEY_RIGHT:
            {
                if(x<*(ptrsize)-1)
                {
                    x=x+1;
                    gotoxy(x,y);
                    fill_default_cells(&area[current_x][current_y]);
                    draw_cell_state(&area[current_x][current_y]);
                    current_x=x;
                    current_y=y;
                    cell_cursor_state(&area[current_x][current_y]);
                }
                break;
            }
            case (char)KEY_UP:
            {
                if(y>0)
                {
                    y=y-1;
                    gotoxy(x,y);
                    fill_default_cells(&area[current_x][current_y]);
                    draw_cell_state(&area[current_x][current_y]);
                    current_x=x;
                    current_y=y;
                    cell_cursor_state(&area[current_x][current_y]);

                }
                break;
            }
            case (char)KEY_DOWN:
            {
                if(y<*(ptrsize)-1)
                {
                    y=y+1;
                    gotoxy(x,y);
                    fill_default_cells(&area[current_x][current_y]);
                    draw_cell_state(&area[current_x][current_y]);
                    current_x=x;
                    current_y=y;
                    cell_cursor_state(&area[current_x][current_y]);
                }
                break;
            }
            }///end switch

        }///end else

    } ///end while



}



///returns void and take current cursor coordinates,it make a flagged cell when user guess there is an bumb
void press_flag(int current_x,int current_y)
{
    if(area[current_x][current_y].open!=1) /// any cell was opend or modified will never be a flag
    {
        area[current_x][current_y].guess='F';
        area[current_x][current_y].guess_color=13;
        draw_guess(&area[current_x][current_y]);

    }


}


///returns void and take current cursor coordinates,it make a quested cell when user guess there is not a bumb
void press_Ques(int current_x,int current_y)
{
    if(area[current_x][current_y].open!=1) /// any cell was opend or modified will never be a quest
    {
        area[current_x][current_y].guess='Q';
        area[current_x][current_y].guess_color=10;
        draw_guess(&area[current_x][current_y]);
    }


}
//////////////////////////////////////////////////////////////////
///game logic functions



///returns void and take pointer to struct cell,it drop bumbs randomly in the game
void create_mines(struct cell *first_cell) //create mines position randomly in main space and fill main space with'-'
{
    ///fill main space
    ///no of mines created =10
    int c=mines;

    int col, row;
    srand(time(0)); ///at the beginning of the program to initialize the random seed
    while(c>0)///form to create mines
    {
        row = rand() % (*(ptrsize)-1 );  ///get random location
        col = rand() % (*(ptrsize)-1 );
        if((row!=first_cell->x) && (col!=first_cell->y))///to avoid creation bumb befor first open cell
            if(area[row][col].state!='M')
            {
                area[row][col].state = 'M';
                area[row][col].color = 4;
                c--;
            }
    }
}


///returns void and take current position,it calculate number of mines surrounding a certain cell which taken
int find_no_of_mines(int x_pos,int y_pos )    //check if element space is mine or not that return num of mines
{
    int mines = 0;
    int x=x_pos;
    int y=y_pos;

    if(x==0)
    {
        if(y==0) ///at edge of area
        {
            ///first cell y=x=0

            if(area[x+1][y+1].state=='M')
                mines++;
            if(area[x][y+1].state=='M')
                mines++;
            if(area[x+1][y].state=='M')
                mines++;

        }
        else if(y==*(ptrsize)-1) ///edge of area
        {
            ///LAST CELL y=0 and x=8

            if(area[x+1][y-1].state=='M')
                mines++;
            if(area[x][y-1].state=='M')
                mines++;
            if(area[x+1][y].state=='M')
                mines++;
        }
        else ///at first col in general y=0 and  else
        {

            if(area[x+1][y-1].state=='M')
                mines++;
            if(area[x+1][y].state=='M')
                mines++;
            if(area[x+1][y+1].state=='M')
                mines++;
            if(area[x][y-1].state=='M')
                mines++;
            if(area[x][y+1].state=='M')
                mines++;
        }
    }
    else if(x==*(ptrsize)-1) ///at last raw
    {

        if(y==0)
        {
            ///top right cell y=8 and x=0

            if(area[x-1][y+1].state=='M')
                mines++;
            if(area[x][y+1].state=='M')
                mines++;
            if(area[x-1][y].state=='M')
                mines++;

        }
        else if(y==*(ptrsize)-1)
        {
            ///last right cell y=8 and =8

            if(area[x-1][y-1].state=='M')
                mines++;
            if(area[x][y-1].state=='M')
                mines++;
            if(area[x-1][y].state=='M')
                mines++;

        }
        else
        {
            ///last col in general y=8 and =else

            if(area[x-1][y-1].state=='M')
                mines++;
            if(area[x-1][y].state=='M')
                mines++;
            if(area[x-1][y+1].state=='M')
                mines++;
            if(area[x][y-1].state=='M')
                mines++;
            if(area[x][y+1].state=='M')
                mines++;
        }
    }
    else
    {
        ///y!=0 or 8
        if(y==0)
        {
            ///x=0 and y=else


            if(area[x-1][y].state=='M')
                mines++;
            if(area[x+1][y].state=='M')
                mines++;
            if(area[x-1][y+1].state=='M')
                mines++;
            if(area[x][y+1].state=='M')
                mines++;
            if(area[x+1][y+1].state=='M')
                mines++;

        }
        else if(y==*(ptrsize)-1)
        {
            ///y=8 and x=else

            if(area[x-1][y].state=='M')
                mines++;
            if(area[x+1][y].state=='M')
                mines++;
            if(area[x-1][y-1].state=='M')
                mines++;
            if(area[x][y-1].state=='M')
                mines++;
            if(area[x+1][y-1].state=='M')
                mines++;

        }
        else
        {
            //y and x in general

            if(area[x-1][y-1].state=='M')
                mines++;
            if(area[x-1][y].state=='M')
                mines++;
            if(area[x-1][y+1].state=='M')
                mines++;
            if(area[x][y-1].state=='M')
                mines++;
            if(area[x][y+1].state=='M')
                mines++;
            if(area[x+1][y-1].state=='M')
                mines++;
            if(area[x+1][y].state=='M')
                mines++;
            if(area[x+1][y+1].state=='M')
                mines++;

        }
    }

    return mines;

}


///returns void and take pointer to struct cell,it open a neighbour cell automatically
void open_neighbour(struct cell*this_cell)
{
    this_cell->open=1;
    int x=this_cell->x;
    int y=this_cell->y;
    int n_mines;
    //if(this_cell->state!='M')
    //{
    n_mines=find_no_of_mines(x,y );

    if( n_mines==0 )
    {
        this_cell->color=9;
        this_cell->state='0';
        draw_cell_state(*(&this_cell));
    }

    else if(n_mines>0 )
    {
        this_cell->color=6;
        this_cell->state=( '0' + n_mines );
        draw_cell_state(*(&this_cell));

    }
    //}
    //else
    //this_cell->color=4;///set color for mine

}

///returns void and take current position,it open eight neighboured cells to a certain cell
void open_eight(int x,int y)
{
    area[x][y].open=1;
    if(x==0)
    {
        if(y==0) ///at edge of area
        {
            ///first cell y=x=0


            open_neighbour(&area[x+1][y+1]);

            open_neighbour(&area[x][y+1]);

            open_neighbour(&area[x+1][y]);

        }
        else if(y==*(ptrsize)-1) ///edge of area
        {
            ///LAST CELL y=0 and x=8


            open_neighbour(&area[x+1][y-1]);

            open_neighbour(&area[x][y-1]);

            open_neighbour(&area[x+1][y]);
        }
        else ///at first col in general y=0 and  else
        {


            open_neighbour(&area[x+1][y-1]);

            open_neighbour(&area[x+1][y]);

            open_neighbour(&area[x+1][y+1]);

            open_neighbour(&area[x][y-1]);

            open_neighbour(&area[x][y+1]);
        }
    }
    else if(x==*(ptrsize)-1) ///at last raw
    {

        if(y==0)
        {
            ///top right cell y=8 and x=0


            open_neighbour(&area[x-1][y+1]);

            open_neighbour(&area[x][y+1]);

            open_neighbour(&area[x-1][y]);

        }
        else if(y==*(ptrsize)-1)
        {
            ///last right cell y=8 and =8


            open_neighbour(&area[x-1][y-1]);

            open_neighbour(&area[x][y-1]);

            open_neighbour(&area[x-1][y]);

        }
        else
        {
            ///last col in general y=8 and =else


            open_neighbour(&area[x-1][y-1]);

            open_neighbour(&area[x-1][y]);

            open_neighbour(&area[x-1][y+1]);

            open_neighbour(&area[x][y-1]);

            open_neighbour(&area[x][y+1]);
        }
    }
    else
    {
        ///y!=0 or 8
        if(y==0)
        {
            ///x=0 and y=else



            open_neighbour(&area[x-1][y]);

            open_neighbour(&area[x+1][y]);

            open_neighbour(&area[x-1][y+1]);

            open_neighbour(&area[x][y+1]);

            open_neighbour(&area[x+1][y+1]);

        }
        else if(y==*(ptrsize)-1)
        {
            ///y=8 and x=else


            open_neighbour(&area[x-1][y]);

            open_neighbour(&area[x+1][y]);

            open_neighbour(&area[x-1][y-1]);

            open_neighbour(&area[x][y-1]);

            open_neighbour(&area[x+1][y-1]);

        }
        else
        {
            //y and x in general


            open_neighbour(&area[x-1][y-1]);

            open_neighbour(&area[x-1][y]);

            open_neighbour(&area[x-1][y+1]);

            open_neighbour(&area[x][y-1]);

            open_neighbour(&area[x][y+1]);

            open_neighbour(&area[x+1][y-1]);

            open_neighbour(&area[x+1][y]);

            open_neighbour(&area[x+1][y+1]);

        }
    }


}


///returns void and take pointer to struct cell,it modify a cell data
void modify_cell_state( struct cell* this_cell)
{
    this_cell->open=1;
    int x=this_cell->x;
    int y=this_cell->y;
    int n_mines;
    if(this_cell->state!='M')
    {
        n_mines=find_no_of_mines(x,y );

        if( n_mines==0 )
        {
            this_cell->color=9;
            this_cell->state='0';
            draw_cell_state(*(&this_cell));
            open_eight(x,y);
        }

        else if(n_mines>0 )
        {
            this_cell->color=6;
            this_cell->state=( '0' + n_mines );
            draw_cell_state(*(&this_cell));
        }
    }
    else
        this_cell->color=4;///set color for mine

}


///returns void and take nothing,it cheat your game when loss
void cheat_game()
{

    for(int i=0; i< *ptrsize; i++)
        for(int j=0; j< *ptrsize; j++)
        {
            modify_cell_state(&area[i][j]);
            draw_cell_state(&area[i][j]);
        }

}


///returns void and take current poistion,it make an action when player move and navigate within game area
void move_player(int x,int y)
{

    cell_cursor_state(&area[current_x][current_y]);
    char cursor;
    while(1)
    {
        cursor=_getch();

        switch(cursor)
        {
        case(char) KEY_LEFT:
        {
            if(x>0)
            {
                x=x-1;
                gotoxy(x,y);
                cell_cursor_state(&area[current_x][current_y]);

                if(area[current_x][current_y].state!='M')
                {
                    draw_cell_state(&area[current_x][current_y]);
                    if(area[current_x][current_y].guess=='F'|| area[current_x][current_y].guess=='Q')
                        draw_guess(&area[current_x][current_y]);
                }

                else
                {
                    if(area[current_x][current_y].guess=='F'|| area[current_x][current_y].guess=='Q')
                        draw_guess(&area[current_x][current_y]);

                    else
                    {
                        setColor(15);
                        printf("X");
                    }
                }

                current_x=x;
                current_y=y;
                cell_cursor_state(&area[current_x][current_y]);

                break;
            }
        }
        case (char) KEY_RIGHT:
        {
            if(x<*(ptrsize)-1)
            {
                x=x+1;
                gotoxy(x,y);
                cell_cursor_state(&area[current_x][current_y]);

                if(area[current_x][current_y].state!='M')
                {
                    draw_cell_state(&area[current_x][current_y]);
                    if(area[current_x][current_y].guess=='F'|| area[current_x][current_y].guess=='Q')
                        draw_guess(&area[current_x][current_y]);
                }

                else
                {
                    if(area[current_x][current_y].guess=='F'|| area[current_x][current_y].guess=='Q')
                        draw_guess(&area[current_x][current_y]);

                    else
                    {
                        setColor(15);
                        printf("X");
                    }
                }
                current_x=x;
                current_y=y;

                cell_cursor_state(&area[current_x][current_y]);

            }
            break;
        }

        case (char)KEY_UP:
        {
            if(y>0)
            {
                y=y-1;
                gotoxy(x,y);
                cell_cursor_state(&area[current_x][current_y]);

                if(area[current_x][current_y].state!='M')
                {
                    draw_cell_state(&area[current_x][current_y]);
                    if(area[current_x][current_y].guess=='F'|| area[current_x][current_y].guess=='Q')
                        draw_guess(&area[current_x][current_y]);
                }

                else
                {
                    if(area[current_x][current_y].guess=='F'|| area[current_x][current_y].guess=='Q')
                        draw_guess(&area[current_x][current_y]);

                    else
                    {
                        setColor(15);
                        printf("X");
                    }
                }
                current_x=x;
                current_y=y;

                cell_cursor_state(&area[current_x][current_y]);


            }
            break;
        }

        case (char)KEY_DOWN:
        {
            if(y<*(ptrsize)-1)
            {
                y=y+1;
                gotoxy(x,y);
                cell_cursor_state(&area[current_x][current_y]);

                if(area[current_x][current_y].state!='M')
                {
                    draw_cell_state(&area[current_x][current_y]);
                    if(area[current_x][current_y].guess=='F'|| area[current_x][current_y].guess=='Q')
                        draw_guess(&area[current_x][current_y]);
                }

                else
                {
                    if(area[current_x][current_y].guess=='F'|| area[current_x][current_y].guess=='Q')
                        draw_guess(&area[current_x][current_y]);

                    else
                    {
                        setColor(15);
                        printf("X");
                    }
                }
                current_x=x;
                current_y=y;

                cell_cursor_state(&area[current_x][current_y]);


            }
            break;
        }///end case
        default: ///press enter
        {
            if(cursor==(char)13)
            {
                area[current_x][current_y].open=1;
                press_enter(current_x,current_y);
            }
            else if(cursor=='F')               ///press flag
                press_flag(current_x,current_y);
            else if(cursor=='Q')                    ///press Ques
                press_Ques(current_x,current_y);
            else if(cursor==(char) esc)             ///press escape
                exit_game();

            break;
        }///end case
            //check_draw(current_x,current_y);
        }///end switch

    } ///end while
}


///returns void and take nothing,it is main function which call all functions in a certain correct order
void play()
{
    system("cls");
    hidecursor();
    draw_frame();
    fill_default_cells();
    for(int i=0; i<*ptrsize; i++)
    {
        for(int j=0; j<*ptrsize; j++)
            draw_cell_state(&area[i][j]);
        printf("\n");
    }

    gotoxy(space,space);///go to the first cell
    current_x=0;
    current_y=0;
    cell_cursor_state(&area[current_x][current_y]);///to make this cell with certain shape
    struct cell *first_cell;
    first_cell =player_first_press(current_x,current_y);///is first cell pressed in the game???and where is it??
    create_mines(*(&first_cell));///create bomb and avoid first cell
    move_player(current_x,current_y);
    hidecursor();

}
/////////////////////////////////////////////////////////////////////////////////
///result functions

///returns void and take nothing,it check if user win every time player press enter to open a cell
int check_win()
{   int check=0;
    for(int i=0;i<*ptrsize;i++)
       {for(int j=0;j<*ptrsize;j++)
         {  if(area[i][j].state!='M'&&area[i][j].open==1)
                    check++;
         }
       }
   if(check==((*ptrsize) * (*ptrsize))-mines)
         return 1;
}

///returns void and take nothing,it make an action when player loss,send a failed message and ask if he want to try again
void you_loss()
{
    static int TRY=0;
    TRY++;
    system("cls");
    system("color 7");
    gotoxy(15,15);
    printf("you pressed a bumb ...so,you loss\n do you want to try again??? (y) or (n)");
    char ch;
    scanf(" %c",&ch);
    if(ch=='y')
    {
        if(TRY<lives) /// lives
            play();
        else
        {
            system("cls");
            gotoxy(15,15);
            printf("you can't play again you died!!!!");
            system("pause");
            exit_game();

        }
    }
    else
        { system("cls");exit(1);}
}


///returns void and take nothing,it make an action when player win,and send a congratulation message
void you_win()
{
    system("cls");
    gotoxy(15,15);
    printf("congratulation!!you win.....\n     you have avoided all BumBs \n GO TO MAIN MENUE!!!");
    system("pause");
    menu();

}




