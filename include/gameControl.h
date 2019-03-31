#ifndef __ABASIT__GAMECONTROLS__
#define __ABASIT__GAMECONTROLS__

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "roomInfo.h"
#include "memory.h"
#include "hero.h"
#include "gameLogic.h"
#include "hallways.h"

/**
*gameSetup
*Check to see if screen is appropriate size
*IN: gameRoom** (struct pointer), int
*OUT: returns 0, if all the rooms will fit on one screen, or 0 if not
*POST:ncurses function initsrc() is called
*/
int gameSetup(gameRoom**, int);

/**
*gameLoop
*Keeps the game running until, uses presses 'q', and or goes over staircases
*IN: gameRoom** (struct pointer), int, int**, Hero*
*POST:ncurses is updated frequently based off user's input
*ERROR: if endwin() is not reached after game ends, it will still keep the screen loaded
*/
void gameLoop(gameRoom**, int, int**, Hero*);

/**
*printAllRooms
*Prints all the rooms
*IN: gameRoom** (struct pointer), int, int**
*POST:
*/
void printAllRooms(gameRoom**, int, int**);

/**
*printRoom
*Prints all the rooms and game elements inside them
*IN:int, int ,int ,int
*POST: Check to see if game element on screen varable is one or zero. If one, it will draw, if not it will not draw
*/
void printRoom (int , int ,int ,int);

#endif

