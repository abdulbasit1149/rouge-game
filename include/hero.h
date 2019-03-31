#ifndef __ABASIT__HERO__
#define __ABASIT__HERO__

#include <ncurses.h>
#include <roomInfo.h>
#include "gameLogic.h"

/**
*moveHero
*Moves the hero depending on which key they press (w,a,s,d)
*IN:char, Hero*
*/
void moveHero(char, Hero*);

/**
*getPlayerRoom
*Gets the player room number relative to the room it is in
*IN:gameRoom** ,Hero*,int
*/
void getPlayerRoom(gameRoom** ,Hero*,int);

/**
*printStatus
*Prints the status at the bottom of the screen
*IN:Hero*
*/
void printStatus(Hero*);

/**
*battleMode
*Either enemy walks on hero or vice versa, to start battlemode
*IN:char, int, Hero*, gameRoom** , int**
*POST: calls functions playerAttack() and enemyAttack(), to battle
*/
void battleMode(char, int, Hero*, gameRoom** , int**);

/**
*playerAttack
*player reduces the health of that monster
*IN:gameRoom**, Hero*, int
*OUT: return true(1) if enemy dies and false(0), if not.
*/
int playerAttack(gameRoom**, Hero*, int);

/**
*enemyAttack
*enemy reduces the hero's health
*IN:gameRoom**, Hero*, int
*/
void enemyAttack(gameRoom**, Hero*, int);

#endif
