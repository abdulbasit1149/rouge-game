#ifndef __ABASIT__MEMORY__
#define __ABASIT__MEMORY__

#include <stdlib.h>
#include <stdio.h>
#include "roomInfo.h"
#include "parseFile.h"

/**
*mallocArrayElements
*Allocates memory for the number of elements per room, into an array
*IN:int
*OUT: return a pointer to malloced array on the heap
*POST: initialize every element value to zero
*ERROR: if the return store value is not a integer pointer
*/
int** mallocArrayElements(int);

/**
*mallocRooms
*Allocates memory for the rooms, and the elements inside each room
*IN:FILE*, int**, int
*OUT: return pointer to all the rooms
*POST:use malloc to make memory
*/
gameRoom** mallocRooms(FILE*, int**, int);

/**
*freeAllMemory
* frees all the memory (except for player)
*IN:gameRoom**, int**, int
*/
void freeAllMemory(gameRoom**, int**, int);

#endif

