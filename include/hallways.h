#ifndef __ABASIT__HALLWAYS__
#define __ABASIT__HALLWAYS__

#include <ncurses.h>
#include "roomInfo.h"

typedef struct doorCreator{
	int y;
	int x;
	char look;
	char location;
	int roomNum;
	int doorNum;
}doorCreator;

/**
*printAllHallways
*Randomly generates hallways between two sets of x, and y points.
*IN:gameRoom**, int, int**
*POST: uses avoidVerticalWall() and avoidHorizontalWall() to move around unwanted characters to draw the room
*ERROR:if the algorithm cannot be reached, there is a loop counter (set max at 4) to exit the loop
*/
void printAllHallways(gameRoom**, int, int**);

/**
*searchDoor
* searches for a door location in the next door
*IN:gameRoom** , int** , int
*OUT: returns the index of the next room
*/
int searchDoor(gameRoom** , int** , int);

/**
*avoidVerticalWall
*Keeps moving the door y location until the checking character is not a wall
*IN:int ,int, int, char
*OUT: new x,y value of door location (return as a door struct)
*/
doorCreator avoidVerticalWall(int ,int, int, char);

/**
*avoidHorizontalWall
*Keeps moving the door x location until the checking character is not a wall
*IN:int ,int, int, char, int
*OUT: new x,y value of door location (return as a door struct)
*/
doorCreator avoidHorizontalWall(int ,int, int, char, int);

/**
*cleanHallways
*Adds empty character to areas the have too many hash (#) around them
*POST:Runs through many checks to see, if that area needs to be cleaned
*/
void cleanHallways();

#endif
