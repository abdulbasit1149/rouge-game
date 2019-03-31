#include "parseFile.h"

int totalRoomCount(FILE* roomFile)
{
	fseek(roomFile, 0, SEEK_SET);	//moves file pointer to the begining of the file
	int numRooms;
	char input[150];

	numRooms = 0;

	while(fgets(input, 150, roomFile) != NULL)
	{
		if (input[1] != '\n')	//checks for new line, to count the number of room
		{
			numRooms = numRooms  + 1;
		}
	}
	return numRooms;		//return total number of rooms
}

void numElements(FILE* roomFile, int** elementsCount, int totalRooms)
{
	fseek(roomFile, 0, SEEK_SET);	 //moves file pointer to the begining of the file
	char input[150];
	int index, checker;			//to check for double entities

	index = 0;					//stores will room number counter
	checker = 0;

	while(fgets(input,150,roomFile) != NULL)
	{
		int length = strlen(input);

		for (int i = 0; i < length; ++i)
		{
			if (i != 0)
			{
				checker = checkType(input[i]) && !checkType(input[i - 1]);
			}
			else
			{
				checker = checkType(input[i]);
			}

			if (checker)
			{
				if (index < totalRooms && input[i] != 'X' && input[i] != 'h')
				{
					if (input[i] == 'd')
					{
						elementsCount[index][0] = elementsCount[index][0] + 1;	//counter for doors
					}
					else if(input[i] == 'm' || input[i] == 'M')
					{
						elementsCount[index][1] = elementsCount[index][1] + 1;	//counter for monsters
					}
					else
					{
						elementsCount[index][2] = elementsCount[index][2] + 1;	////counter for items
					}
				}
			}
		}
		index = index + 1;		//increase room checker
	}
}

int checkType(enum type c)	//return true(1) if any element found	//ensuring no member of any struct is full
{
	switch(c)
	{
		case X:
		case d:
		case h:
		case z:
		case a:
		case g:
		case G:
		case w:
		case W:
		case m:
		case e:
		case M:
		case p:
			return 1;
		default:
			return 0;

	}
	return 0;
}

void parseFile(gameRoom** room,int totalRooms,FILE* roomFile, int** elementsCount, Hero* player)
{
	fseek(roomFile, 0, SEEK_SET);	 //moves file pointer to the begining of the file
	char line[150];
	int roomNum;

	roomNum = 0;

	for (int i = 0; i < totalRooms; i = i + 1)
	{
		for (int j = 0; j < 3; j = j + 1)
		{
			for (int k = 0; k < elementsCount[i][j]; k = k + 1)
			{
				switch(j)
				{
					case 0:
						room[i]->gameElements->gameDoor[k]->infoFilled = 0;	//ensuring no member of any struct is full
						break;
					case 1:
						room[i]->gameElements->gameMonster[k]->infoFilled = 0;	//ensuring no member of any struct is full
						break;
					case 2:
						room[i]->gameElements->gameItem[k]->infoFilled = 0;	//ensuring no member of any struct is full
						break;
					default:
						printf("Member does not exist\n");
				}
			}
		}
	}

 	while(fgets(line, 150 , roomFile) != NULL)
 	{
	 	//checks for any weird characters (newline, return key), and replaces it with a null terminator
	 	int length = strlen(line);

	 	for (int i = 0; i < length; ++i)
	 	{
	 		if(iscntrl((int)line[i]))
	 		{
	 			line[i]='\0';
	 		}
	 	}
	 	char* token = strtok(line, " ");	//grabs the first collection of character until space

	 	do
	 	{
	 		checkIdentifer(token, roomNum, elementsCount, room, player);
	 		token = strtok(NULL, " ");		//grab next word separated by a space
	 	}while(token != NULL);
	 	roomNum = roomNum + 1;
 	}
}

void checkIdentifer(char* token, int roomNum, int** elementsCount, gameRoom** room, Hero* player)
{
	int length;
	length = 0;
	length = strlen(token);
	for (int i = 0; i < length; ++i)
	{
		if (checkType(token[i]) && !checkType(token[i - 1]))
		{
			toStorage(token[i], token, roomNum, elementsCount, room, player);	//to store information into structs
		}
	}
}

void toStorage(enum type c, char* token, int roomNum, int** elementsCount, gameRoom** room, Hero* player)
{
	int roomY, roomX, dist, copy, y, x;
	char look, type, location;

	roomY = 0;
	roomX = 0;
	dist = 0;
	copy = 0;
	x = 0;
	y = 0;
	look = '?';
	type = '?';
	location = '?';

	switch(c)
	{
		case X:
			sscanf(token,"%3dX%3d", &roomY, &roomX);	//to break string into smaller parts to save
			room[roomNum]->rows = roomY;
			room[roomNum]->cols = roomX;
			room[roomNum]->y = 5;
			room[roomNum]->x = 5;
			break;
		case d:
			sscanf(token,"%1c%1c%2d", &look,&location,&dist);
			copy = 1;
			for (int i = 0; i < elementsCount[roomNum][0]; ++i)
			{
				if (room[roomNum]->gameElements->gameDoor[i]->infoFilled == 0 && copy == 1)
				{
					room[roomNum]->gameElements->gameDoor[i]->dist = dist;
					room[roomNum]->gameElements->gameDoor[i]->look = '+';
					room[roomNum]->gameElements->gameDoor[i]->location = location;
					room[roomNum]->gameElements->gameDoor[i]->type = 'd';
					room[roomNum]->gameElements->gameDoor[i]->x = 0;
					room[roomNum]->gameElements->gameDoor[i]->y = 0;
					room[roomNum]->gameElements->gameDoor[i]->doorNum = i;
					room[roomNum]->gameElements->gameDoor[i]->onScreen = 1;
					room[roomNum]->gameElements->gameDoor[i]->infoFilled = 1;
					copy = 0;
				}
			}
			break;
		case M:
			sscanf(token,"%1c%2d,%2d", &type,&y,&x);	//breaks string into smaller parts to store
			copy = 1;
			for (int i = 0; i < elementsCount[roomNum][1]; ++i)
			{
				if (room[roomNum]->gameElements->gameMonster[i]->infoFilled == 0 && copy == 1)
				{
					room[roomNum]->gameElements->gameMonster[i]->y = y;
					room[roomNum]->gameElements->gameMonster[i]->x = x;
					room[roomNum]->gameElements->gameMonster[i]->look = 'T';
					room[roomNum]->gameElements->gameMonster[i]->type = 'M';
					room[roomNum]->gameElements->gameMonster[i]->health = 50;
					room[roomNum]->gameElements->gameMonster[i]->attack = 5;
					room[roomNum]->gameElements->gameMonster[i]->speed = 3;
					room[roomNum]->gameElements->gameMonster[i]->cycle = 0;
					room[roomNum]->gameElements->gameMonster[i]->onScreen = 1;
					room[roomNum]->gameElements->gameMonster[i]->infoFilled = 1;
					copy = 0;
				}
			}
			break;
		case m:
			sscanf(token,"%1c%2d,%2d", &type,&y,&x);	//breaks string into smaller parts to store
			copy = 1;
			for (int i = 0; i < elementsCount[roomNum][1]; i = i + 1)
			{
				if (room[roomNum]->gameElements->gameMonster[i]->infoFilled == 0 && copy == 1)
				{
					room[roomNum]->gameElements->gameMonster[i]->y = y;
					room[roomNum]->gameElements->gameMonster[i]->x = x;
					room[roomNum]->gameElements->gameMonster[i]->look = 'A';
					room[roomNum]->gameElements->gameMonster[i]->type = 'm';
					room[roomNum]->gameElements->gameMonster[i]->health = 5;
					room[roomNum]->gameElements->gameMonster[i]->attack = 1;
					room[roomNum]->gameElements->gameMonster[i]->cycle = 0;
					room[roomNum]->gameElements->gameMonster[i]->speed = 2;
					room[roomNum]->gameElements->gameMonster[i]->onScreen = 1;
					room[roomNum]->gameElements->gameMonster[i]->infoFilled = 1;
					copy = 0;
				}
			}
			break;
		case h:
			sscanf(token,"%1c%2d,%2d", &type,&y,&x);	//breaks string into smaller parts to store
			player->x = room[roomNum]->x + x + 1;
			player->y = room[roomNum]->y + y;
			player->health = 50;
			player->gold = 0;
			player->roomNum = roomNum;
			player->potionCount = 1;
			player->attack = 5;
			player->type = type;
			player->look = '@';
			player->inventoryCount = 0;
			for (int i = 0; i < 5; ++i)
			{
				player->ingameInventory[i].type = '?';
				player->ingameInventory[i].stat = 0;
				player->ingameInventory[i].filled = 0;
			}
			break;
		case z:
			sscanf(token,"%1c%2d,%2d", &type,&y,&x);	//breaks string into smaller parts to store
			storeElemInfo(room, roomNum, elementsCount, '<', type, &y, &x, 0 , 0);
			break;
		case a:
			sscanf(token,"%1c%2d,%2d", &type,&y,&x);	//breaks string into smaller parts to store
			storeElemInfo(room, roomNum, elementsCount, '>', type, &y, &x, 0 , 0);
			break;
		case g:
			sscanf(token,"%1c%2d,%2d", &type,&y,&x);	//breaks string into smaller parts to store
			storeElemInfo(room, roomNum, elementsCount, '*', type, &y, &x, 0 , 0);
			break;
		case G:
			sscanf(token,"%1c%2d,%2d", &type,&y,&x);	//breaks string into smaller parts to store
			storeElemInfo(room, roomNum, elementsCount, '8', type, &y, &x, 0 , 0);
			break;
		case w:
			sscanf(token,"%1c%2d,%2d", &type,&y,&x);	//breaks string into smaller parts to store
			storeElemInfo(room, roomNum, elementsCount, ')', type, &y, &x, 0 , 0);
			break;
		case W:
			sscanf(token,"%1c%2d,%2d", &type,&y,&x);	//breaks string into smaller parts to store
			storeElemInfo(room, roomNum, elementsCount, '(', type, &y, &x, 0 , 0);
			break;
		case e:
			sscanf(token,"%1c%2d,%2d", &type,&y,&x);	//breaks string into smaller parts to store
			storeElemInfo(room, roomNum, elementsCount, ']', type, &y, &x, 0 , 0);
			break;
		case p:
			sscanf(token,"%1c%2d,%2d", &type,&y,&x);	//breaks string into smaller parts to store
			storeElemInfo(room, roomNum, elementsCount, '!', type, &y, &x, 0 , 0);
			break;
		default:
			printf("Member does not exist\n");
	}
}
