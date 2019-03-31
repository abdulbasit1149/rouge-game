#include "hero.h"

void printStatus(Hero* player)
{
	int y ,x, count;
	count = 0;
	getmaxyx(stdscr, y, x);

	for (int i = 0; i < 5; ++i)
	{
		if (player->ingameInventory[i].filled == 1)
		{
			count = count + 1;       //checks to see how many items the hero has in its inventory
		}
	}
    attrset(COLOR_PAIR(1));     //prints colour green
	mvprintw(y - 1,w/2 - 24, "Health: %d, Potions: %d, Attack: %d, Inv: %d/5", player->health, player->potionCount, player->attack, count);
	move(y,x);
}

void getPlayerRoom(gameRoom** room,Hero* player,int totalRooms)
{
    for (int i = 0; i < totalRooms; ++i)
    {
        if (player->y > room[i]->y - 2 && player->y < room[i]->y + room[i]->rows + 1)
        {
            if (player->x >= room[i]->x && player->x <= (room[i]->x + room[i]->cols) + 1)
            {
                player->roomNum = i;        //store the room location of the hero
            }
        }
    }
}

/*
    Move hero based of user's input
*/
void moveHero(char input, Hero* player)
{
    if (input == 'w')
    {
        player->y =  player->y - 1;
    }
    else if (input == 's')
    {
         player->y =  player->y + 1;
    }
    else if (input ==  'a')
    {
        player->x = player->x - 1;
    }
    else if (input == 'd')
    {
        player->x = player->x + 1;
    }
}


void battleMode(char input, int index, Hero* player, gameRoom** room, int** elementsCount)
{
    int playerSpeed, enemySpeed;
    playerSpeed = (rand() % 10) + 1;        //random hero speed
    enemySpeed = room[player->roomNum]->gameElements->gameMonster[index]->speed;    //stores enemy speed locally

    if (playerSpeed > enemySpeed)
    {
        if(playerAttack(room, player, index))   //player attacks enemy, if enemy dies(returns 1). Take him off the screen
        {
            printNotification('K', "monster", 0);
            room[player->roomNum]->gameElements->gameMonster[index]->onScreen = 0;
        }
    }
    else
    {
        enemyAttack(room, player, index);       //enemy attacks player
    }
    if (room[player->roomNum]->gameElements->gameMonster[index]->health > 0)    //if enemy is still alive, move player back
    {
        switch(input)
        {
            case 'w':
                player->y = player->y + 1;
                break;
            case 's':
                player->y = player->y - 1;
                break;
            case 'a':
                player->x = player->x + 1;
                break;
            case 'd':
                player->x = player->x - 1;
                break;
        }
    }
}

int playerAttack(gameRoom** room, Hero* player, int index)
{
    int enemyHealth = 0;
    enemyHealth = room[player->roomNum]->gameElements->gameMonster[index]->health;  //store enemy health locally

    enemyHealth = enemyHealth - player->attack;                                     //attacking
    room[player->roomNum]->gameElements->gameMonster[index]->health =enemyHealth;   //reassign new enemy health
    printNotification('G',"nothing" ,player->attack );
    if (room[player->roomNum]->gameElements->gameMonster[index]->health < 1)
    {
        return 1;                                                               //enemy dies
    }
    return 0;
}

void enemyAttack(gameRoom** room, Hero* player, int index)
{
    int enemyDamage = 0;
    enemyDamage = room[player->roomNum]->gameElements->gameMonster[index]->attack;

    if (room[player->roomNum]->gameElements->gameMonster[index]->look == 'A' && player->attack > 0)
    {
        player->attack = player->attack - enemyDamage;      //decrease hero's attack
        printNotification('T', "nothing", enemyDamage);
    }
    else if(!(room[player->roomNum]->gameElements->gameMonster[index]->look == 'A'))
    {
        player->health = player->health - enemyDamage;      //decrease hero's health
        printNotification('T', "nothing", enemyDamage);
    }
}
