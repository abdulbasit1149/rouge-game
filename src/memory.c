#include "memory.h"

int** mallocArrayElements(int totalRooms)
{
	int** temp;            //to store temp address of all 2D array
	temp = (int**)malloc(sizeof(int*) * totalRooms);   //malloc 1D array
    if (temp == NULL)
    {
        fprintf(stderr, " 0 Out of memory\n");
        exit(1);
    }

    for (int i = 0; i < totalRooms; ++i)
    {
    	temp[i] = (int*)malloc(sizeof(int) * 3);   ///malloc 2D array
    }

    for (int i = 0; i < totalRooms; i = i + 1)
    {
    	for (int j = 0; j < 3; j = j + 1)
    	{
    		temp[i][j] = 0;           //set every value to zero
    	}
    }
    return temp;	//return address of the pointer on the heap
}

gameRoom** mallocRooms(FILE* roomFile, int** elementsCount, int totalRooms)
{
    gameRoom** room;

    room = (gameRoom**)malloc(sizeof(gameRoom*) * totalRooms);  //malloc perfect amount of rooms
    if (room == NULL)
    {
        fprintf(stderr, " 1 Out of memory\n");
        exit(1);
    }

    for (int i = 0; i < totalRooms; ++i)
    {
        room[i] = (gameRoom*)malloc(sizeof(gameRoom));  //malloc the structs per room
        if (room[i] == NULL)
        {
            fprintf(stderr, "2 Out of memory\n");
            exit(1);
        }
        room[i]->gameElements = (Element*)malloc(sizeof(Element));      //malloc pointer to types of elements in each struct
        if (room[i]->gameElements == NULL)
        {
            fprintf(stderr, " 3 Out of memory\n");
            exit(1);
        }
    }

    for (int i = 0; i < totalRooms; ++i)
    {
        room[i]->gameElements->gameDoor = (Door**)malloc(sizeof(Door*) * elementsCount[i][0]);  //malloc the # of doors
        if (room[i]->gameElements->gameDoor == NULL)
        {
            fprintf(stderr, " 4 Out of memory\n");
            exit(1);
        }

        room[i]->gameElements->gameMonster = (Monster**)malloc(sizeof(Monster*) * elementsCount[i][1]); //malloc the # of monsters
        if (room[i]->gameElements->gameMonster == NULL)
        {
            fprintf(stderr, " 5 Out of memory\n");
            exit(1);
        }

        room[i]->gameElements->gameItem = (Item**)malloc(sizeof(Item*) * elementsCount[i][2]);  //malloc the # of items
        if (room[i]->gameElements->gameItem == NULL)
        {
            fprintf(stderr, " 6 Out of memory\n");
            exit(1);
        }
    }

    for (int i = 0; i < totalRooms; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            for (int k = 0; k < elementsCount[i][j]; ++k)
            {
                switch(j)
                {
                case 0:
                    room[i]->gameElements->gameDoor[k] = (Door*)malloc(sizeof(Door));   //malloc doors
                        if (room[i]->gameElements->gameDoor[k] == NULL)
                        {
                            printf(" 7 Out of  memory\n");
                            exit(1);
                        }
                    break;
                case 1:
                    room[i]->gameElements->gameMonster[k] = (Monster*)malloc(sizeof(Monster));  //malloc monsters
                        if (room[i]->gameElements->gameMonster[k] == NULL)
                        {
                            printf(" 8 Out of  memory\n");
                            exit(1);
                        }
                    break;
                case 2:
                    room[i]->gameElements->gameItem[k] = (Item*)malloc(sizeof(Item));   //malloc items
                        if (room[i]->gameElements->gameItem[k] == NULL)
                        {
                            printf(" 9 Out of  memory\n");
                            exit(1);
                        }
                    break;
                default:
                    printf("Problem with malloc\n");
                }
            }
        }
    }

    return room;
}

void freeAllMemory(gameRoom** room, int** elementsCount, int totalRooms)
{

    for (int i = 0; i < totalRooms; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            for (int k = 0; k < elementsCount[i][j]; ++k)
            {
                switch(j)
                {
                case 0:
                    free(room[i]->gameElements->gameDoor[k]);   //free doors
                    break;
                case 1:
                    free(room[i]->gameElements->gameMonster[k]);    //free monsters
                    break;
                case 2:
                    free(room[i]->gameElements->gameItem[k]);   //free items
                    break;
                default:
                    printf("Problem with freeing\n");
                }
            }
        }
    }
    for (int i = 0; i < totalRooms; ++i)
    {
        free(room[i]->gameElements->gameDoor);
        free(room[i]->gameElements->gameMonster);
        free(room[i]->gameElements->gameItem);
    }

    for (int i = 0; i < totalRooms; ++i)
    {
        free(room[i]->gameElements);    //free pointer to game element
        free(room[i]);      //free rooms
    }

    free(room);     //free all the rooms

    for (int i = 0; i < totalRooms; ++i)
    {
        free(elementsCount[i]);     //free stuff inside 2D array
    }
    free(elementsCount);    //free 2D array
}
