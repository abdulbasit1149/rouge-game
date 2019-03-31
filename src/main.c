#include <stdio.h>
#include <stdlib.h>

#include "gameControl.h"
#include "roomInfo.h"
#include "parseFile.h"
#include "memory.h"
#include "hero.h"
#include "gameLogic.h"

/*
*Main
*runs the entire program
*IN: int, char**
*POST:calls other functions to malloc, free and run the game
*ERROR: if user enters incorrect about of arguments on the command line
*       Also, if file does not exist, it will terminate the program
*/
int main(int argc, char *argv[])
{
	FILE* roomFile;			//points to the file
	gameRoom** room;		//pointer to all the rooms
	Hero* player;
	srand(time(NULL));			//for random monster type etc.
	int** elementsCount;		//array to store the number of elements per room
	int totalRooms = 0;

	if (argc != 2)		//to ensure proper command line arguments
	{
		printf("Incorrect command line arguments\n");
		exit(1);
	}
	roomFile = fopen(argv[1], "r");

	if (roomFile == NULL)
	{
		printf("file does not exist\n");
		exit(1);
	}

	totalRooms = totalRoomCount(roomFile);					//calculate the total number of rooms
	elementsCount = mallocArrayElements(totalRooms);		//malloc the array for just enough rooms
	numElements(roomFile, elementsCount, totalRooms);		//stores the number of monsters, doors, and items per room into a 2D array
	room = mallocRooms(roomFile, elementsCount, totalRooms);	//malloc for the room structs

	player = (Hero*)malloc(sizeof(Hero));				//malloc memory for the player

	if (player == NULL)							//check if memory exist
	{
		fprintf(stderr, "Out of memory\n");
	}

	parseFile(room, totalRooms, roomFile, elementsCount, player);
	fclose(roomFile);
	initialize(room, player, elementsCount,totalRooms);

	if(gameSetup(room, totalRooms))			//check to see if the rooms will fit on the screen
	{
		gameLoop(room, totalRooms, elementsCount, player); 	//to run the game until certain end game requirement is met
	}

	//free memory
	free(player);
	freeAllMemory(room, elementsCount, totalRooms);

	return 0;
}
