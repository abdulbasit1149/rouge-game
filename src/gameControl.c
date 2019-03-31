#include "gameControl.h"

int gameSetup(gameRoom** room, int totalRooms)
{
    int maxCol, maxRow;

    maxRow = 0;
    maxCol = 0;

    initscr(); //initalize ncurses
    noecho();   //reduces characters to go on string
    cbreak();   //give me input and output when it is available
    curs_set(0);    //remove the cursor from screen
    start_color();      //starts the colour function within ncurses

    /*
        Pairing background and foreground colour
    */
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_WHITE, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
    init_pair(5, COLOR_CYAN, COLOR_BLACK);
    init_pair(6, COLOR_MAGENTA, COLOR_BLACK);

    attrset(COLOR_PAIR(2)); //display that pair of colours

    getmaxyx(stdscr, maxRow, maxCol);

    /*
        Checks If rooms will fit on the screen
    */
    for (int i = 0; i < totalRooms; ++i)
    {
        if ((room[i]->y + room[i]->rows + 2) > maxRow - 2 || (room[i]->x + room[i]->cols + 1) >= maxCol)
        {
            endwin();
            printf("Game screen problem(s):\n\n");
            printf(" Screen Max Row: %d\n Screen Max Cols: %d\n\nRoom number:%d\n\n", maxRow - 2,maxCol ,i + 1);
            printf(" Max Row for Room: %d\n Max Col for Room: %d\n\n", room[i]->y + room[i]->rows + 2, room[i]->x + room[i]->cols + 1);
            printf("**ERROR CAUSE: Either Room row > Screen row | Room col > Screen col**\n");
            return 0;
        }
    }
    return 1;
}


void gameLoop(gameRoom** room, int totalRooms, int** elementsCount, Hero* player)
{
    int overStairs;     //check if user is over stairs
    char input;         //user input

    input = '?';        //user actions
    overStairs = 0;

    do
    {
        getPlayerRoom(room,player,totalRooms);              //get the room, the player is in
        printAllRooms(room, totalRooms, elementsCount);     //print everything but hallways
        printAllHallways(room, totalRooms, elementsCount);  //prints hallways

        if(input == 'p')
        {
            potionUse(player);
        }
        else
        {
            moveHero(input, player);    //move hero, and checks if user presses w,a,s,d
        }

        if(checkChar(input ,player))                        //to set if hero is going to walk on wall, and or monsters
        {
            action(room,elementsCount ,player, &overStairs, totalRooms, input); //hero's action based of element
        }

        attrset(COLOR_PAIR(1));     //display green colour
        mvprintw(1, 5 ,"Hero Gold: %d", player->gold);
        printStatus(player);

        attrset(COLOR_PAIR(2));     //display white colour
        mvaddch(player->y, player->x, '@');

        if(input != '?')        //to make sure this code runs AFTER user input
        {
            moveEnemies(room, elementsCount, player, totalRooms);       //move all the enemies
            printAllRooms(room, totalRooms, elementsCount);     //print rooms
            printStatus(player);
            printAllHallways(room, totalRooms, elementsCount);

            attrset(COLOR_PAIR(2)); //display white colour
            mvaddch(player->y, player->x, '@');
        }

        if (!overStairs && player->health > 0)        //if hero walks on staircase and or health is < 0:do not ask for user input
        {
            input = getch();
        }
        refresh();
        clear(); //clear entire screen

    } while(input != 'q' && overStairs == 0 && player->health > 0);       //if user's presses 'q' and or hero's goes on stairs or health < 0

    endwin(); //deinitalize ncurses
    printf(" GAME OVER:\n\n");
    printf(" Hero Gold: %d\n\n", player->gold);
    printf(" Hero's Inventory\n ------------------\n");
    for (int i = 0; i < 5; ++i)
    {
        if (player->ingameInventory[i].filled == 1)
        {
            switch(player->ingameInventory[i].type)     //print all the collected items
            {
                case 'e':
                    printf(" Item Number:%d\n Type: Equipment\n Stat: %d\n\n", i + 1,player->ingameInventory[i].stat);
                    break;
                case 'w':
                    printf(" Item Number:%d\n Type: Common Weapon\n Stat: %d\n\n", i + 1,player->ingameInventory[i].stat);
                    break;
                case 'W':
                    printf(" Item Number:%d\n Type: Rare weapon\n Stat: %d\n\n", i + 1,player->ingameInventory[i].stat);
                    break;
            }
        }
    }
    if (player->inventoryCount == 0)        //if no item is collected
    {
        printf(" No items collected\n");
    }
}

void printAllRooms(gameRoom** room, int totalRooms, int** elementsCount)
{
    attrset(COLOR_PAIR(5));
    for (int i = 0; i < totalRooms; i = i + 1)
    {
        printRoom(room[i]->y,room[i]->x ,room[i]->cols,room[i]->rows);
    }
    attrset(COLOR_PAIR(2));

    for (int i = 0; i < totalRooms; ++i)
    {
        for (int j = 0; j < 3; j = j + 1)
        {
            for (int k = 0; k < elementsCount[i][j]; ++k)
            {
                switch(j)
                {
                    case 0:
                        attrset(COLOR_PAIR(1));
                        if (room[i]->gameElements->gameDoor[k]->onScreen == 1)
                        {
                            mvaddch(room[i]->gameElements->gameDoor[k]->y,room[i]->gameElements->gameDoor[k]->x,'+');   //draw doors
                        }
                        attrset(COLOR_PAIR(2));
                        break;

                    case 1:
                        attrset(COLOR_PAIR(3));
                        if (room[i]->gameElements->gameMonster[k]->onScreen == 1)
                        {
                            mvaddch(room[i]->gameElements->gameMonster[k]->y,room[i]->gameElements->gameMonster[k]->x,room[i]->gameElements->gameMonster[k]->look);   //draw doors
                        }
                        attrset(COLOR_PAIR(2));
                        break;

                    case 2:
                        attrset(COLOR_PAIR(6));
                        if (room[i]->gameElements->gameItem[k]->onScreen == 1)
                        {
                            mvaddch(room[i]->gameElements->gameItem[k]->y,room[i]->gameElements->gameItem[k]->x,room[i]->gameElements->gameItem[k]->look);   //draw doors
                        }
                        attrset(COLOR_PAIR(2));
                        break;

                    default:
                        mvaddch(0,0,' ');

                }
            }
        }
    }
}

void printRoom(int y, int x, int cols, int rows)
{
    for (int i = 0; i <= cols + 1; ++i)
    {
        mvaddch(y -  1, x + i ,'-');    //top wall of room
        mvaddch(y + rows,x + i,'-');    //bottom wall of room
    }
    for (int i = 0; i < rows; ++i)
    {
        mvaddch(y+i, x,'|');                //left wall of room
        mvaddch(y+i, x + cols + 1,'|');     //right wall of room
    }
    for (int i = x + 1; i <= cols + x; i = i + 1)
    {
        for (int j = y; j < rows + y; j = j + 1)
        {
            attrset(COLOR_PAIR(5)); ////display cyan colour
            mvaddch(j,i,'.');       //floor ties
        }
    }
}
