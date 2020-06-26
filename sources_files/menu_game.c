
#include"menu_game.h"

///returns void and take nothing,it close your game
void exit_game()
{ system("cls");
 gotoxy(15,15);
 system("color 7");
 printf("are you sure to exit game??\n 'y' or 'n'");
 char ch;
 scanf(" %c",&ch);
 if(ch=='y')
    exit(1);
 else
    menu();

}

///returns void and take nothing,it enable user to select game level
void level_select()
{ setColor(9);       //change color of output
  system("cls");
   printf("\n\n\n1-beginner\n");
   printf("2-intermediate\n");
   printf("3-hard\n");
  printf("4-main menu\n");

 scanf("%d",&level);
 //choose levels
  if(level==1)
    {*ptrsize=9;//size of game
    space=7;
    mines=10;
    lives=3;
    play();}

    if(level==2)
    {*ptrsize=12;//size of game
    space=7;
    mines=20;
    lives=5;
    play();}

    if(level==3)
    {*ptrsize=15;//size of game
    space=5;
    mines=40;
    lives=7;
    play();}

  if(level==4)
     menu();

}

///returns void and take nothing,it print some instructions to follow when playing
void show_instructions()
{ system("cls");
setColor(7);
    printf("\n\nto know how to play...\n\n check that video..\n https://www.youtube.com/watch?v=pYvkkmaEzu4\n \n \n\n\n");
    setColor(7);
    printf("1-YOU SHOULD AVOID ALL BUMB TO WIN\n\n2-PRESS ENTER TO OPEN A CELL\n\n3-PRESS 'F' TO FLAG A CELL\n\n WHICH YOU GUESS IT IS A BUMB\n\n4-PRESS 'ESC' TO EXIT\n\n5-GAME WILL NOT RUN UNTILL YOU PRESS FIRST ENTER\n\nyou should select level now\n\n ");
    system("pause");
   level_select();
   system("pause");

}


///returns void and take nothing,it shows main_menu of the game ,it is the first function called in our code
void menu()
{
    system("cls");
     system("color 5");
    gotoxy(3,1);
    printf("***MAIN MNNU***\n");
    system("color 9");
    gotoxy(3,3);
    printf("1-select level\n");
    gotoxy(3,5);
    printf("2-instructions\n");
    gotoxy(3,7);
    printf("3-exit game\n");
    scanf("%d",&choose);
    if(choose==1)
        level_select(1);
    if(choose==2)
        show_instructions();
    if(choose==3)
        { exit_game();}

}
