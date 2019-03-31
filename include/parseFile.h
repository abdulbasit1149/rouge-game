#ifndef __ABASIT__PARSEFILE__
#define __ABASIT__PARSEFILE__

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "roomInfo.h"
#include "memory.h"

enum type{
	X = 'X',
	d = 'd',
	h = 'h',
	z = 'z',
	a = 'a',
	g = 'g',
	G = 'G',
	w = 'w',
	W = 'W',
	m = 'm',
	e = 'e',
	M = 'M',
	p = 'p'
};

/**
*totalRoomCount
*Counts the total number of rooms
*IN:FILE*
*OUT: return the total number of rooms as an integer
*ERROR:If file is empty, total room count will be zero
*/
int totalRoomCount(FILE*);

/**
*numElements
*Counts the number of elements that need to be malloced per room
*IN: FILE*, int*, int
*ERROR: if file elements are not separated by a space, it will cause seg. fault
*/
void numElements(FILE*, int**, int);

/**
*checkType
*checks to see what element is in the file
*IN: enum type(character)
*OUT: int, either true (1) and or false (0)
*/
int checkType(enum type);

/**
*toStorage
*stores information from string (from file) in to structs
*IN: enum type (character), char*, int, int**, gameRoom**, Hero*
*POST: stores information into appriorate struct
*/
void toStorage(enum type, char*, int, int**, gameRoom**, Hero*);

/**
*checkIdentifer
*checks to see if the character within the textfile is an element
*IN: char*, int, int**, gameRoom**, Hero*
*POST:call the function toStorage() to store informaion into structs
*/
void checkIdentifer(char* ,int, int**, gameRoom**, Hero*);

/**
*parseFile
*Goes through each line and stores its elements within structs
*IN:gameRoom** (struct pointer), int, FILE*
*POST:Takes one line from file and breaks it into small piece separated by a space. An store that information into the appriorate struct.
*ERROR: if file is changed than the tradition look, it will lead to programming becoming confused on where to parse each line.
*/
void parseFile(gameRoom** ,int,FILE*, int**, Hero*);

#endif
