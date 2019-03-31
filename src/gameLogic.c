#include "gameLogic.h"

int checkChar(char direction,Hero* player)
{

    /*
        checks to see if hero will walk on walls, empty space, monster
    */

    char checker;
    checker = mvinch(player->y, player->x);  //grab character at where user is going to move
    if(checker == '-' || checker == '|' || checker == ' ' || ((isalnum((int)checker)) && checker != 'A' && checker != 'B' && checker != 'S' && checker != 'Z' && checker != 'T' && checker == 8)) 
    {
        switch(direction)
        {
            case 'w':
                player->y = player->y + 1;
                return 0;
                break;
            case 's':
                player->y = player->y - 1;
                return 0;
                break;
            case 'a':
                player->x = player->x + 1;
                return 0;
                break;
            case 'd':
                player->x = player->x - 1;
                return 0;
                break;
            default:
                return 1;
        }
    }
    else
    {
        return 1;
    }
    return 1;
}


void action(gameRoom** room,int** elementsCount, Hero* player, int* overStairs, int totalRooms, char input)
{
	int index;
    char checker;

    index = 0;
    checker = mvinch(player->y, player->x);  //grab character at where user is going to move

    /*
        based of entity, certain command will run
    */

    switch(checker)
    {
        case '+':       //door
            printNotification('D', "nothing",0);
            break;
        case 'A':       //monsters
        case 'B':
        case 'S':
        case 'Z':
        case 'T':
        	index = searchMonster(room, elementsCount, player);
        	battleMode(input, index, player, room, elementsCount);
            break;
        case '*':   //unique items
        case '8':
        case ']':
        case ')':
        case '(':
        case '!':
            evaluateItem(room, elementsCount, player, totalRooms);
            break;
        case '>':       //staircases
        case '<':
            *overStairs = 1;
            break;
    }
}

void evaluateItem(gameRoom** room, int** elementsCount, Hero* player, int totalRooms)
{
	int index;
	index = 0;
	char checker;
    checker = mvinch(player->y, player->x);  //grab character at where user is going to move

    /*
        Based of what user steppd on, certain command will rub
    */

    switch(checker)
    {
        case '*':
        	index = searchItems(room, elementsCount, player);
            printNotification('P',"small gold", room[player->roomNum]->gameElements->gameItem[index]->value);
        	player->gold = player->gold + room[player->roomNum]->gameElements->gameItem[index]->value;
        	room[player->roomNum]->gameElements->gameItem[index]->onScreen = 0;        //make it disappear from screen
        	break;

        case '8':
            index = searchItems(room, elementsCount, player);
            printNotification('P',"large gold", room[player->roomNum]->gameElements->gameItem[index]->value);
        	player->gold = player->gold + room[player->roomNum]->gameElements->gameItem[index]->value;
        	room[player->roomNum]->gameElements->gameItem[index]->onScreen = 0;        //make it disappear from screen
        	break;

        case ']':
        	index = searchItems(room, elementsCount, player);
            printNotification('P',"equipment", room[player->roomNum]->gameElements->gameItem[index]->stat);
        	pickUpItem(room,elementsCount ,player,index);
        	room[player->roomNum]->gameElements->gameItem[index]->onScreen = 0;        //make it disappear from screen
        	break;

        case ')':
        	index = searchItems(room, elementsCount, player);
            printNotification('P',"common weapon", room[player->roomNum]->gameElements->gameItem[index]->stat);
        	pickUpItem(room,elementsCount ,player,index);
        	room[player->roomNum]->gameElements->gameItem[index]->onScreen = 0;        //make it disappear from screen
        	break;

        case '(':
        	index = searchItems(room, elementsCount, player);
            printNotification('P',"rare weapon", room[player->roomNum]->gameElements->gameItem[index]->stat);
        	pickUpItem(room,elementsCount ,player,index);
        	room[player->roomNum]->gameElements->gameItem[index]->onScreen = 0;        //make it disappear from screen
        	break;

        case '!':
        	printNotification('P',"potion", 1);
        	index = searchItems(room, elementsCount, player);
        	player->potionCount = player->potionCount + 1;
        	room[player->roomNum]->gameElements->gameItem[index]->onScreen = 0;        //make it disappear from screen
        	break;

    }
}

int searchMonster(gameRoom** room, int** elementsCount, Hero* player)
{
	for (int i = 0; i < elementsCount[player->roomNum][1]; i = i + 1)      //searches only monsters
	{
		if (player->y == room[player->roomNum]->gameElements->gameMonster[i]->y)
		{
			if (player->x == room[player->roomNum]->gameElements->gameMonster[i]->x)
			{
                if (room[player->roomNum]->gameElements->gameMonster[i]->onScreen == 1)
                {
                    return i;       //return value of the index of the monster
                }
			}
		}
	}
	return 0;
}


int searchItems(gameRoom** room, int** elementsCount, Hero* player)
{
	for (int i = 0; i < elementsCount[player->roomNum][2]; i = i + 1)  //search only items
	{
		if (player->y == room[player->roomNum]->gameElements->gameItem[i]->y)
		{
			if (player->x == room[player->roomNum]->gameElements->gameItem[i]->x)
			{
				return i;  //return value of the index of the item
			}
		}
	}
	return 0;
}

void pickUpItem(gameRoom** room, int** elementsCount, Hero* player, int index)
{
	int copy;
	copy = 0;

	player->inventoryCount = player->inventoryCount + 1;

	for (int i = 0; i < 5; ++i)
	{
		if (player->ingameInventory[i].filled == 0 && copy == 0)      //store the information
		{
			player->ingameInventory[i].type = room[player->roomNum]->gameElements->gameItem[index]->type;
			player->ingameInventory[i].stat = room[player->roomNum]->gameElements->gameItem[index]->stat;
			player->ingameInventory[i].filled = 1;
			copy = 1;
		}
	}
	if (player->inventoryCount > 5)        //if bag is full
	{
		if (room[player->roomNum]->gameElements->gameItem[index]->type == 'e')
		{
			printNotification('B',"equipment", 0);
		}
		else if (room[player->roomNum]->gameElements->gameItem[index]->type == 'w')
		{
			printNotification('B',"common weapon", 0);
		}
		else
		{
			printNotification('B',"rare weapon" , 0);
		}
	}
}

void potionUse(Hero* player)
{
	if (player->potionCount > 0)
	{
		player->potionCount = player->potionCount - 1;
		player->health = 50;
		printNotification('U',"nothing" , 0);     //print proper message
	}
	else
	{
		printNotification('E',"nothing" , 0);     //print proper message
	}
}

void printNotification(char event, char* object, int num)
{
	int x, y;
	getyx( stdscr, y , x);
    move(0,0);
    clrtoeol();                 //clear line
    attrset(COLOR_PAIR(1));     //makes the colour green

    /*
        Based of event from the function call, certain things will be printed
    */
	switch(event)
	{
		case 'P':
			mvprintw(0,38, "Hero picked up %s (value/stat: +%d)", object, num);
			break;
		case 'B':
			mvprintw(0,38, "Hero stepped on %s, and broke it", object);
			break;
		case 'T':
			mvprintw(0,38, "Hero lost %d health or attack", num);
			break;
		case 'G':
            mvprintw(0,38, "Hero caused %d damage", num);
			break;
		case 'K':
                move(0,0);
                clrtoeol(); //clear line
            mvprintw(0,38, "Hero killed %s", object);
			break;
		case 'D':
            mvprintw(0,38, "Hero opened a door");
			break;
		case 'U':
			mvprintw(0,38, "Hero recovered full health");
			break;
		case 'E':
			mvprintw(0,38, "Out of potions");
			break;
	}
	move(y,x);     //move back to last drawing location
}

void moveEnemies(gameRoom** room, int** elementsCount, Hero* player, int totalRooms)
{
    char look;
    look = '?';
    for (int i = 0; i < totalRooms; ++i)
    {
        for (int j = 0; j < elementsCount[i][1]; ++j)       //search monster only
        {
            look = room[i]->gameElements->gameMonster[j]->look;     //what it appears on screen
            switch(look)
            {
                case 'A':
                    break;
                case 'B':
                    moveEnemy(room, elementsCount, player, i, j,'B' , 0);       //bats move randomly
                    break;
                case 'S':                                       //all other monster move based of cycle number
                    if (room[i]->gameElements->gameMonster[j]->cycle  < 2)
                    {
                        moveEnemy(room, elementsCount, player, i, j,'S' , 1);
                        room[i]->gameElements->gameMonster[j]->cycle += 1;
                    }
                    else
                    {
                        moveEnemy(room, elementsCount, player, i, j,'S' , 3);
                        room[i]->gameElements->gameMonster[j]->cycle += 1;
                        if(room[i]->gameElements->gameMonster[j]->cycle == 4)
                        {
                            room[i]->gameElements->gameMonster[j]->cycle = 0;
                        }
                    }
                    break;
                case 'Z':
                    if (room[i]->gameElements->gameMonster[j]->cycle == 0)
                    {
                        moveEnemy(room, elementsCount, player, i,j, 'Z' , 0);
                        room[i]->gameElements->gameMonster[j]->cycle = 1;
                    }
                    else
                    {
                        moveEnemy(room, elementsCount, player, i,j, 'Z' , 2);
                        room[i]->gameElements->gameMonster[j]->cycle = 0;
                    }
                    break;
                case 'T':
                    switch(room[i]->gameElements->gameMonster[j]->cycle) //to check which cycle the monster is on
                    {
                        case 0:
                            moveEnemy(room, elementsCount, player, i,j, 'T' , 0);
                            room[i]->gameElements->gameMonster[j]->cycle += 1;
                            break;
                        case 1:
                            moveEnemy(room, elementsCount, player, i, j,'T' , 1);
                            room[i]->gameElements->gameMonster[j]->cycle += 1;
                            break;
                        case 2:
                            moveEnemy(room, elementsCount, player, i, j,'T' , 2);
                            room[i]->gameElements->gameMonster[j]->cycle += 1;
                            break;
                        case 3:
                            moveEnemy(room, elementsCount, player, i,j, 'T' , 3);
                            room[i]->gameElements->gameMonster[j]->cycle += 1;
                            room[i]->gameElements->gameMonster[j]->cycle = 0;
                            break;
                        default:
                            room[i]->gameElements->gameMonster[j]->cycle = 0;
                    }
                    break;
            }
        }
    }
}

void moveEnemy(gameRoom** room, int** elementsCount, Hero* player, int roomLoc, int monsterLoc,char enemyType, int randN)
{
    int enemyY, enemyX;

    enemyY = 0;
    enemyX = 0;

    if (enemyType == 'B')
    {
        randN  = rand() % 4;        //monster move in random direction
    }

    switch(randN)       //move based of cycle number
    {
        case 0:
            room[roomLoc]->gameElements->gameMonster[monsterLoc]->y -= 1;
            enemyY = room[roomLoc]->gameElements->gameMonster[monsterLoc]->y;
            enemyX = room[roomLoc]->gameElements->gameMonster[monsterLoc]->x;
            if (detection(mvinch(enemyY, enemyX)))      //checks for items, monster, walls etc.
            {
                room[roomLoc]->gameElements->gameMonster[monsterLoc]->y += 1;
                if ((mvinch(enemyY, enemyX)& A_CHARTEXT) == '@' && room[roomLoc]->gameElements->gameMonster[monsterLoc]->onScreen == 1)
                {
                    battleMode('?', monsterLoc, player, room, elementsCount);   //if object is hero, engage combat
                }
            }

            break;
        case 1:
            room[roomLoc]->gameElements->gameMonster[monsterLoc]->x += 1;
            enemyY = room[roomLoc]->gameElements->gameMonster[monsterLoc]->y;
            enemyX = room[roomLoc]->gameElements->gameMonster[monsterLoc]->x;
            if (detection(mvinch(enemyY, enemyX)))//checks for items, monster, walls etc.
            {
                room[roomLoc]->gameElements->gameMonster[monsterLoc]->x -= 1;
                if ((mvinch(enemyY, enemyX) & A_CHARTEXT) == '@' && room[roomLoc]->gameElements->gameMonster[monsterLoc]->onScreen == 1)
                {
                    battleMode('?', monsterLoc, player, room, elementsCount);//if object is hero, engage combat
                }
            }
            break;
        case 2:
            room[roomLoc]->gameElements->gameMonster[monsterLoc]->y += 1;
            enemyY = room[roomLoc]->gameElements->gameMonster[monsterLoc]->y;
            enemyX = room[roomLoc]->gameElements->gameMonster[monsterLoc]->x;
            if (detection(mvinch(enemyY, enemyX)))//checks for items, monster, walls etc.
            {
                room[roomLoc]->gameElements->gameMonster[monsterLoc]->y -= 1;
                if ((mvinch(enemyY, enemyX) & A_CHARTEXT )== '@' && room[roomLoc]->gameElements->gameMonster[monsterLoc]->onScreen == 1)
                {
                    battleMode('?', monsterLoc, player, room, elementsCount);//if object is hero, engage combat
                }
            }
            break;
        case 3:
            room[roomLoc]->gameElements->gameMonster[monsterLoc]->x -= 1;
            enemyY = room[roomLoc]->gameElements->gameMonster[monsterLoc]->y;
            enemyX = room[roomLoc]->gameElements->gameMonster[monsterLoc]->x;
            if (detection(mvinch(enemyY, enemyX)))//checks for items, monster, walls etc.
            {
                room[roomLoc]->gameElements->gameMonster[monsterLoc]->x += 1;
                if ((mvinch(enemyY, enemyX) & A_CHARTEXT)== '@' && room[roomLoc]->gameElements->gameMonster[monsterLoc]->onScreen == 1)
                {
                    battleMode('?', monsterLoc, player, room, elementsCount);//if object is hero, engage combat
                }
            }
            break;
    }
}

int detection(char type)
{
    switch(type)    //if monster walks on any of these, return true
    {
        case 'A':
        case 'B':
        case 'S':
        case 'Z':
        case 'T':
        case ']':
        case ')':
        case '(':
        case '!':
        case '*':
        case '8':
        case '|':
        case '-':
        case '<':
        case '>':
        case '+':
        case '@':
            return 1;
    }
    return 0;
}
