#include "roomInfo.h"

/*
	To store all the information for an item
*/
void storeElemInfo(gameRoom** room, int roomNum, int** elementsCount, char look, char type, int* y, int* x, int value, int stat)
{
	int copy;		//to make sure more than one item struct is on filled by same information
	copy = 1;

	for (int i = 0; i < elementsCount[roomNum][2]; i = i + 1)
	{
		if (room[roomNum]->gameElements->gameItem[i]->infoFilled == 0 && copy == 1)
		{
			room[roomNum]->gameElements->gameItem[i]->y = *y;
			room[roomNum]->gameElements->gameItem[i]->x = *x;
			room[roomNum]->gameElements->gameItem[i]->look = look;
			room[roomNum]->gameElements->gameItem[i]->type = type;
			room[roomNum]->gameElements->gameItem[i]->stat = stat;
			room[roomNum]->gameElements->gameItem[i]->value = value;
			room[roomNum]->gameElements->gameItem[i]->onScreen = 1;
			room[roomNum]->gameElements->gameItem[i]->infoFilled = 1;
			copy = 0;
		}
	}
}

void initialize(gameRoom** room, Hero* player, int** elementsCount, int totalRooms)
{
	int shiftX, shiftY, tempX, tempY, moveX, moveY, doorY, doorX, randType;

	shiftX = 0;
	shiftY = 0;
	tempY = 0;		//to compare y values of rooms
	tempX = 0;		//to compare x values of rooms
	moveX = 0;
	moveY = 0;
	doorY = 0;
	doorX = 0;
	randType = 0;

/*
	Store location of x and y into proper room based of location of previous room
*/
	for (int i = 1; i < totalRooms; ++i)
	{
		switch(i)
		{
			case 1:
			case 2:
				shiftX = room[i - 1]->x + room[i - 1]->cols + 10;	//Gets x value of previos room
				shiftY = room[0]->y;								//Gets y value of first room
				room[i]->x = shiftX;
				room[i]->y = shiftY;
				break;
			case 3:
				shiftX = room[0]->x;
				shiftY = room[0]->y + room[0]->rows + 6;  //Gets new y value for third room, based first room
				room[i]->x = shiftX;
				room[i]->y = shiftY;
				break;
			case 4:
			case 5:
				tempY = room[i - 4]->y + room[i - 4]->rows + 6;
				shiftY = room[i - 3]->y + room[i - 3]->rows + 6;
				if (tempY > shiftY)	//compares y values of rooms, and moves room relative to largest value
				{
					shiftY = tempY;
				}
				tempX = room[i - 4]->x + room[i - 4]->cols + 10;
				shiftX = room[i - 1]->x + room[i - 1]->cols + 10;
				if (tempX > shiftX) //compares x values of rooms, and moves room relative to largest value
				{
					shiftX = tempX;
				}
				room[i]->x = shiftX;
				room[i]->y = shiftY;
				break;
			default:			//fail case
				room[i]->x = 0;
				room[i]->y = 0;
		}
	}

	for (int i = 0; i < totalRooms; i = i + 1)
	{
		for(int j = 0; j < 3; j = j + 1)
		{
			for(int k = 0; k < elementsCount[i][j]; k = k + 1)
			{
				/*
					Converts door file location (e.g de4) into y,x location of door within the room.
				*/
				switch(j)
				{
					case 0:
						switch(room[i]->gameElements->gameDoor[k]->location)
						{
							case 'e':
								doorX = room[i]->x + room[i]->cols + 1;
								doorY = room[i]->y + room[i]->gameElements->gameDoor[k]->dist;
								room[i]->gameElements->gameDoor[k]->x = doorX;
								room[i]->gameElements->gameDoor[k]->y = doorY;
								break;
							case 's':
								doorX = room[i]->x + room[i]->gameElements->gameDoor[k]->dist + 1;
								doorY = room[i]->y + room[i]->rows;
								room[i]->gameElements->gameDoor[k]->x = doorX;
								room[i]->gameElements->gameDoor[k]->y = doorY;
								break;
							case 'w':
								doorX = room[i]->x;
								doorY = room[i]->y + room[i]->gameElements->gameDoor[k]->dist;
								room[i]->gameElements->gameDoor[k]->x = doorX;
								room[i]->gameElements->gameDoor[k]->y = doorY;
								break;
							case 'n':
								doorX = room[i]->x + room[i]->gameElements->gameDoor[k]->dist + 1;
								doorY = room[i]->y - 1;
								room[i]->gameElements->gameDoor[k]->x = doorX;
								room[i]->gameElements->gameDoor[k]->y = doorY;
								break;
						}
						break;
					case 1:
							moveX = room[i]->x + room[i]->gameElements->gameMonster[k]->x + 1;
							moveY = room[i]->y + room[i]->gameElements->gameMonster[k]->y;
							room[i]->gameElements->gameMonster[k]->x = moveX;
							room[i]->gameElements->gameMonster[k]->y = moveY;
						break;
					case 2:
							moveX = room[i]->x + room[i]->gameElements->gameItem[k]->x + 1;
							moveY = room[i]->y + room[i]->gameElements->gameItem[k]->y;
							room[i]->gameElements->gameItem[k]->x = moveX;
							room[i]->gameElements->gameItem[k]->y = moveY;
						break;
					default:
						printf("Problem with store x,y relative to room\n");
				}
			}
		}
	}

	for (int i = 0; i < totalRooms; ++i)
	{
		for (int j = 0; j < elementsCount[i][2]; ++j)
		{
			if (room[i]->gameElements->gameItem[j]->type == 'g')
			{
				room[i]->gameElements->gameItem[j]->value = (rand() % 51);	//randomly store a value for small gold
			}
			else if (room[i]->gameElements->gameItem[j]->type == 'G')
			{
				room[i]->gameElements->gameItem[j]->value  = (rand() % 201) + 50;//randomly store a value for large gold
			}
			else
			{
				switch(room[i]->gameElements->gameItem[j]->type)	//generate random stats values
				{
					case 'w':
						room[i]->gameElements->gameItem[j]->stat = (rand() % 9) + 1;
						break;
					case 'W':
						room[i]->gameElements->gameItem[j]->stat = (rand() % 6) + 10;
						break;
					case 'e':
						room[i]->gameElements->gameItem[j]->stat = rand() % 21;
						break;
					default:
						room[i]->gameElements->gameItem[j]->stat = 0;
				}
			}
		}
	}

	for (int i = 0; i < totalRooms; ++i)
	{
		for (int j = 0; j < elementsCount[i][1]; ++j)
		{
			if (room[i]->gameElements->gameMonster[j]->type == 'm')
			{
				randType = rand() % 4;
				switch(randType)			 //pick random monster type
				{
					case 0:
						storeMonsterInfo(room, 5, 1 ,2, 'A',i, j);
						break;
					case 1:
						storeMonsterInfo(room, 2, 5 ,4, 'B',i, j);
						break;
					case 2:
						storeMonsterInfo(room, 5, 5 ,4, 'S',i, j);
						break;
					case 3:
						storeMonsterInfo(room, 15, 5 ,3, 'Z',i, j);
						break;
					default:
						storeMonsterInfo(room, 5, 1 ,2, 'A',i, j);
				}
			}
		}
	}
}

void storeMonsterInfo(gameRoom** room,int health, int attack,int speed,char look, int i, int j)	//store information for monster
{
	room[i]->gameElements->gameMonster[j]->look = look;
	room[i]->gameElements->gameMonster[j]->health = health;
	room[i]->gameElements->gameMonster[j]->attack = attack;
	room[i]->gameElements->gameMonster[j]->speed = speed;
}
