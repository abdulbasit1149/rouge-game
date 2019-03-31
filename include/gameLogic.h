#ifndef __ABASIT__GAMELOGIC__
#define __ABASIT__GAMELOGIC__

#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "roomInfo.h"
#include "gameControl.h"
#include "hero.h"

/**
*checkChar
*Checks from which direction hero moving, and negates move, if they are going into wall, monster, etc...
*IN:char,Hero*
*POST:calls the function checkChar(char) to see what he is player going to move on
*/
int checkChar(char,Hero*);

/**
*teleportNextRoom
*Teleports the hero to the next room in the sequence
*IN:gameRoom**,int**, Hero*, int*, int, char
*POST:calls other function to execute certain commands
*/
void action(gameRoom**,int**, Hero*, int*, int, char);

/**
*evaluateItem
* Based of item, it will run the proper commands
*IN:gameRoom**, int** , Hero*, int
*POST: calls the function searchItems() to find which item, hero stepped and then calls pickUpItem() to pick that item up
*/
void evaluateItem(gameRoom**, int** , Hero*, int);

/**
*searchMonster
*searches the room player is in, to find the index of a monster the hero stepped on.
*IN:gameRoom**, int**, Hero*
*OUT: index value of monster
*/
int searchMonster(gameRoom**, int**, Hero* );

/**
*searchItems
*searches the room player is in, to find the index of a item the hero stepped on.
*IN:gameRoom**, int**, Hero*
*OUT: return value of item
*/
int searchItems(gameRoom**, int**, Hero*);

/**
*pickUpItem
*Adds the item to the hero inventory
*IN:gameRoom**, int**, Hero*, int
*POST: print message to the top of screen, if the item breaks
*/
void pickUpItem(gameRoom**, int**, Hero*, int);

/**
*potionUse
*when user presses 'p', the potion use algorithm runs
*IN:Hero*
*/
void potionUse(Hero*);

/**
*printNotification
* Based of check value, it will print the appriorate message to the top of the screen
*IN:char, char*, int
*ERROR:If two of these function are called back to back, the first will not appear (to the user)
*/
void printNotification(char, char*, int);

/**
*moveEnemies
*Moves all the enemies in all rooms
*IN:gameRoom**, int**, Hero*, int
*/
void moveEnemies(gameRoom**, int**, Hero*, int);

/**
*moveEnemy
*Based of which enemy and which cycle its in, the enemy will move according
*IN:gameRoom**, int**, Hero*, int, int,char, int
*/
void moveEnemy(gameRoom**, int**, Hero*, int, int,char, int);

/**
*detection
*To check if monster walks on any item, monster, door, wall, player.
*IN:char
*OUT: return true(1) if monster stepped on certain entity, false (0), if not
*/
int detection(char);

#endif
