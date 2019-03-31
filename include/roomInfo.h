#ifndef __ABASIT__ROOMINFO__
#define __ABASIT__ROOMINFO__

#include <stdio.h>
#include <stdlib.h>

typedef struct door{
	char look;		//discription on screen
	char type;		//letter which appears in file
	int dist;
	int x;
	int y;
	int doorNum;
	char location;
	int infoFilled;
	int onScreen;
}Door;

typedef struct item{
	char look;		//discription on screen
	char type;		//letter which appears in file
	int y;
	int x;
	int stat;
	int value;		//all have zero, except gold (0 - 50 or large gold (50 - 250)) 
	int infoFilled;
	int onScreen;
}Item;

typedef struct monster{
	char look;		//discription on screen
	char type;		//letter which appears in file
	int x;
	int y;
	int health;
	int attack;
	int speed;
	int cycle;
	int infoFilled;
	int onScreen;
}Monster;

typedef struct element{		//double pointer as the number of each type is unknown to program
	Door** gameDoor;
	Item** gameItem;
	Monster** gameMonster;
}Element;

typedef struct roomGame{
	int x;
	int y;
	int cols;
	int rows;
	Element* gameElements;
}gameRoom;

typedef struct inventory{
	char type;
	int stat;
	int filled;			//check whether an inventory is filled or not
}Inventory;

typedef struct hero{
	int x;
	int y;
	int health;
	int roomNum;
	int gold;
	int potionCount;
	int inventoryCount;
	Inventory ingameInventory[5];
	int attack;
	char type;		//letter which appears in file
	char look;		//discription on screen
}Hero;

/**
*storeElemInfo
*Store information for an item
*IN:gameRoom**, int, int **, char, char, int*, int*, int, int
*/
void storeElemInfo(gameRoom**, int, int**, char, char, int*, int*, int, int);

/**
*initialize
*Preps the room structs to ensure they have all the values they need to play the game
*IN: gameRoom**, Hero*, int**, int
*/
void initialize(gameRoom**, Hero*, int**, int);

/**
*storeMonsterInfo
*Stores information for an monster
*IN: gameRoom**, int, int ,int ,char, int ,int
*/
void storeMonsterInfo(gameRoom**, int, int ,int ,char, int ,int);

#endif
