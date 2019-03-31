#include "hallways.h"

void printAllHallways(gameRoom** room, int totalRooms, int** elementsCount)
{
    int above;      //to check if door is above or below
    int isleft;     //to check if door is on the left or right
    int nextDoor;   //location of the door to track too
    int distX;      //X distance that needs to be covered.
    int swap;       //if starting door, is on the right then end door, swap positions
    int loop;           //to keep drawing hallways from start door to end door
    int exitWhileLoop;      //safe fail case for loop
    int randNum;            //for random colours

    doorCreator door;       //start door
    doorCreator endDoor;    //end door

    above = 0;
    nextDoor = 0;
    distX = 0;
    swap = 0;
    isleft = 0;
    loop = 1;
    exitWhileLoop = 0;
    randNum = 0;

    door.look = '^';
    door.y = 0;
    door.x = 0;
    endDoor.roomNum = 0;
    door.location = '?';

    endDoor.look = '?';
    endDoor.y = 0;
    endDoor.x = 0;
    endDoor.roomNum = 0;
    endDoor.location = '?';

   for (int i = 0; i < totalRooms; ++i)
   {
        randNum = (rand() % 4) + 3;

        for (int j = 0; j < elementsCount[i][0]; ++j)
        {
            attrset(COLOR_PAIR(randNum));   //random hallways colour
            if (i == 5) //if start door is in the last room, next door is in first room
            {
                endDoor.roomNum = 0;
                endDoor.y = room[0]->gameElements->gameDoor[nextDoor]->y;
                endDoor.x = room[0]->gameElements->gameDoor[nextDoor]->x;
                endDoor.location = room[0]->gameElements->gameDoor[nextDoor]->location;
                endDoor.doorNum = room[0]->gameElements->gameDoor[nextDoor]->doorNum;
            }
            else  //end door is in next room
            {
                nextDoor = searchDoor(room, elementsCount,  i + 1);
                endDoor.roomNum = i + 1;
                endDoor.y = room[i + 1]->gameElements->gameDoor[nextDoor]->y;
                endDoor.x = room[i + 1]->gameElements->gameDoor[nextDoor]->x;
                endDoor.doorNum = room[0]->gameElements->gameDoor[nextDoor]->doorNum;
                endDoor.location = room[i  + 1]->gameElements->gameDoor[nextDoor]->location;
            }

            /*
                save information about the starting door
            */
            door.location = room[i]->gameElements->gameDoor[j]->location;
            door.x = room[i]->gameElements->gameDoor[j]->x;
            door.y = room[i]->gameElements->gameDoor[j]->y;
            door.roomNum = i;
            door.doorNum = j;
            loop  = 1;
            exitWhileLoop = 0;

            /*
                swap positions of doors
            */
            if (door.x > endDoor.x)
            {
                swap = door.x;
                door.x = endDoor.x;
                endDoor.x = swap;

                swap = door.y;
                door.y = endDoor.y;
                endDoor.y = swap;

                swap = door.location;
                door.location = endDoor.location;
                endDoor.location = swap;

                swap = door.roomNum;
                door.roomNum = endDoor.roomNum;
                endDoor.roomNum = swap;

                swap = door.doorNum;
                door.doorNum = endDoor.doorNum;
                endDoor.doorNum = swap;
            }

            /*
                check the relative position of the two doors
            */
            if (door.y - endDoor.y < 0 )
            {
                above = 1;
            }
            else if (door.y - endDoor.y > 0 )
            {
                above = 0;
            }
            else
            {
                above = -1;
            }

            if (door.x - endDoor.x < 0)
            {
                isleft = 1;
            }
            else if (door.x - endDoor.x > 0)
            {
                isleft = 0;
            }
            else
            {
                isleft = -1;
            }

            /*
                the starting location, in x and y of the algorithm
            */
            switch(door.location)
            {
                case 'n':
                    door.y = room[door.roomNum]->gameElements->gameDoor[door.doorNum]->y - 1;
                    door.x = room[door.roomNum]->gameElements->gameDoor[door.doorNum]->x;
                    break;
                case 's':
                    door.y = room[door.roomNum]->gameElements->gameDoor[door.doorNum]->y + 1;
                    door.x = room[door.roomNum]->gameElements->gameDoor[door.doorNum]->x;
                    break;
                case 'e':
                    door.y = room[door.roomNum]->gameElements->gameDoor[door.doorNum]->y;
                    door.x = room[door.roomNum]->gameElements->gameDoor[door.doorNum]->x + 1;
                    break;
                case 'w':
                    door.y = room[door.roomNum]->gameElements->gameDoor[door.doorNum]->y;
                    door.x = room[door.roomNum]->gameElements->gameDoor[door.doorNum]->x - 2;
                    mvaddch(door.y,door.x + 1,'#');
                    mvaddch(door.y,door.x,'#');
                     break;
            }

            /*
                the ending location, in x and y of the algorithm
            */
            switch(endDoor.location)
            {
                case 'n':
                	distX = endDoor.x;
                    break;
                case 's':
                    distX = endDoor.x;
                    endDoor.y = endDoor.y + 1;
                    mvaddch(endDoor.y + 1, endDoor.x,'#');
                    if (door.location == 'n')
                    {
                        mvaddch(endDoor.y + 2, endDoor.x - 1,'#');
                        mvaddch(endDoor.y + 2, endDoor.x - 2,'#');
                    }
                    break;
                case 'w':
                    distX = endDoor.x - 3;
                    mvaddch(endDoor.y, endDoor.x - 1,'#');
                    mvaddch(endDoor.y, endDoor.x - 2,'#');
                    mvaddch(endDoor.y, endDoor.x - 3,'#');
                    break;
                case 'e':
                    distX = endDoor.x + 3;
                    mvaddch(endDoor.y, endDoor.x + 1,'#');
                    mvaddch(endDoor.y, endDoor.x + 2,'#');
                    mvaddch(endDoor.y, endDoor.x + 3,'#');
                    endDoor.x = endDoor.x + 3;
                    break;
            }
////////////////////////////////////////////////////////////////////////////////
            do
            { 
                exitWhileLoop = exitWhileLoop + 1;      //check safe case
                if (isleft == 1)        //to move right
                {
                    for (int k = door.x; k <= distX; k = k + 1)
                    {
                        if ((mvinch(door.y, k + 1) & A_CHARTEXT) == '|' || (mvinch(door.y, k + 1) & A_CHARTEXT)== '-' || ((mvinch(door.y, k + 1) & A_CHARTEXT) == '+' && (door.location == 'w' || endDoor.location == 'e' || endDoor.location == 'n'))) 
                        {
                            door = avoidVerticalWall(door.y,k + 1, above, door.location);   //avoid wall
                            mvaddch(door.y,k,'#');
                        }
                        else
                        {
                            mvaddch(door.y,k,'#');
                        }

                        if ((mvinch(door.y - 1, k + 1) & A_CHARTEXT)== '-')
                        {
                            mvaddch(door.y + 1,k,'#');
                            door.y = door.y + 1;
                        }
                        door.x = k;
                    }
                }
                else if(isleft == 0)        //to move left
                {
                    for (int k = door.x; k > distX; --k)
                    {
                        if ((mvinch(door.y, k - 1) & A_CHARTEXT)== '|' || (mvinch(door.y, k - 1) & A_CHARTEXT) == '-' || ((mvinch(door.y, k + 1) & A_CHARTEXT)== '+' && door.location == 'w'))
                        {
                            door = avoidVerticalWall(door.y,k - 1, above, door.location); //avoid wall
                            mvaddch(door.y,k,'#');
                        }
                        else
                        {
                            mvaddch(door.y,k,'#');
                        }

                        if ((mvinch(door.y - 1, k - 1) & A_CHARTEXT)== '-')
                        {
                            mvaddch(door.y + 1,k,'#');
                            door.y = door.y + 1;
                        }
                        door.x = k;
                    }
                }

                if (above == 1) // to move down
                {
                    for (int m = door.y; m < endDoor.y; ++m)
                    {
                        if ((mvinch(door.y + 1, door.x) & A_CHARTEXT)== '-' || ((mvinch(door.y + 1, door.x)& A_CHARTEXT) == '+' && (endDoor.location == 's' || endDoor.location == 'n')))
                        {
                            door = avoidHorizontalWall(door.y + 1,door.x, isleft, door.location, -1); //avoid wall
                        }
                        else
                        {
                            mvaddch(m,door.x,'#');
                        }

                        door.y = m;
                    }
                }
                else if(above == 0)     // to move up
                {
                    for (int m = door.y; m >= endDoor.y; --m)
                    {
                        if ((mvinch(door.y - 1, door.x)& A_CHARTEXT) == '-' || (((mvinch(door.y - 1, door.x) & A_CHARTEXT)== '+') && (endDoor.location == 'n' || endDoor.location == 's' || endDoor.location == 'e') && (door.location == 'e' || door.location == 's' || door.location == 'n')))
                        {
                            door = avoidHorizontalWall(door.y - 1,door.x, isleft, door.location , 1); //avoid wall
                        }
                        else
                        {
                            mvaddch(m,door.x,'#');
                        }
                        door.y = m;
                    }
                }

                /*
                    Checks to see, if door pathway is complete
                */

                switch(endDoor.location)
                {
                    case 'n':
                        if (door.y + 1 == endDoor.y && door.x == endDoor.x)
                        {
                            loop = 0;
                        }

                        break;
                    case 's':
                        if (door.y - 2 == endDoor.y && door.x == endDoor.x)
                        {
                            loop = 0;
                        }
                        break;
                    case 'e':
                        if (door.y == endDoor.y && above == 0 && door.x  - 1== endDoor.x)
                        {
                            loop = 0;
                        }
                        else if(door.y + 1 == endDoor.y && above == 1)
                        {
                            loop = 0;
                        }
                        break;
                    case 'w':
                        if (door.y == endDoor.y && above == 0)
                        {
                            loop = 0;
                        }
                        else if(door.y + 1 == endDoor.y && above == 1 && door.x == endDoor.x)
                        {
                            loop = 0;
                        }
                        break;
                    default:
                        loop = 0;
                }

                /*
                    checks the relative position of the two doors
                */

                if (door.y - endDoor.y < 0 )
                {
                    above = 1;
                }
                else if (door.y - endDoor.y > 0 )
                {
                    above = 0;
                }
                else
                {
                    above = -1;
                }

                if (door.x - endDoor.x < 0)
                {
                    isleft = 1;
                }
                else if (door.x - endDoor.x > 0)
                {
                    isleft = 0;
                }
                else
                {
                    isleft = -1;
                }

            }while(loop && exitWhileLoop < 6);  //re-loops if pathway is not complete

        }
    }
    cleanHallways(); //makes the hallways look alot nicer
}

doorCreator avoidHorizontalWall(int y,int x, int isleft, char location, int direction)
{
    int run = 1;
    doorCreator door;

    door.y = y;
    door.x = x;

    do
    {
        char checker = mvinch(y , x) & A_CHARTEXT;        //character to check
        if (checker == '-' || (mvinch(y, x + 1) & A_CHARTEXT) == '-' || checker == '+')
        {
            if (isleft == 1)
            {
                x = x + 1;
            }
            else
            {
                x = x - 1;
            }
            mvaddch(y + direction,x,'#');
            run = 1;
        }
        else
        {
            if (isleft == 1)
            {
                x = x + 1;
            }
            else
            {
                x = x - 1;
            }
            mvaddch(y,x,'#');
            mvaddch(y - 1,x,'#');
            mvaddch(y + 1,x ,'#');
            run = 0;
        }
    }while(run);        //keep looping, if wall is detected

    door.y = y;
    door.x = x;
    return door;        //return new x and y location
}

doorCreator avoidVerticalWall(int y,int x, int above, char location)
{
	int run = 1;
	doorCreator door;

	door.y = y;
	door.x = x;

	do
	{
        char checker = mvinch(y, x) & A_CHARTEXT;    //character to check

	    if (checker== '|' || checker == '-' || (checker == '+' && !(location == 'n')))
	    {
	        if(above == 1)
            {
                y = y + 1;
            }
            else
            {
                y = y - 1;
            }

            mvaddch(y,x - 2,'#');
		    run = 1;
	    }
	    else
	    {
            if(above == 1)
            {
                y = y + 1;
            }
            else
            {
                y = y - 1;
            }
            mvaddch(y,x - 2,'#');
	        run = 0;
	    }
	}while(run);   //keep looping, if wall is detected

    door.y = y;
    door.x = x;
	return door;       //return new x and y location
}

int searchDoor(gameRoom** room, int** elementsCount, int roomNum)
{
    for (int i = 0; i < elementsCount[roomNum][0]; i = i + 1)
    {
        return i;       //location of door in next room
    }
    return 0;   //fail case, returns the first door
}

void cleanHallways()
{
    int hashes;
    int maxX;
    int maxY;

    hashes = 0;
    maxY = 0;
    maxX = 0;

    getmaxyx(stdscr, maxY, maxX);
    int cleanArray[maxY][maxX];     //2D array for hash counters

    /*
        Goes through every spot on the screen, to check if there are too many hallways spot around that area,and cleans it
    */

    for (int c = 0; c < maxY; ++c)
    {
        for (int v = 0; v < maxX; ++v)
        {
            if ((mvinch(c,v) & A_CHARTEXT)== '#')
            {
                for (int s = v - 1; s <= v + 1; s = s + 2)
                {
                    if ((mvinch(c,s) & A_CHARTEXT) == '#')
                    {
                        hashes = hashes + 1;
                    }
                }
                for (int z = c - 1; z <= c + 1; z = z  + 2)
                {
                    if ((mvinch(z,v)  & A_CHARTEXT ) == '#')
                    {
                        hashes = hashes + 1;
                    }
                }

                if ((mvinch(c - 1, v - 1) & A_CHARTEXT)== '#' || (mvinch(c - 1, v + 1) & A_CHARTEXT)== '#' || (mvinch(c + 1, v - 1)& A_CHARTEXT) == '#' || (mvinch(c + 1, v + 1)& A_CHARTEXT) == '#')
                {
                    hashes = hashes + 1;
                }
                if ((mvinch(c, v - 1) & A_CHARTEXT)== '#' && (mvinch(c, v + 1) & A_CHARTEXT)== '#' && (mvinch(c - 1, v )& A_CHARTEXT) == '#' && (mvinch(c + 1, v) & A_CHARTEXT)== '#')
                {
                    hashes = hashes - 1;
                }
                if ((mvinch(c, v - 1) & A_CHARTEXT)== '#' && !((mvinch(c, v + 1) & A_CHARTEXT)== '#') &&( mvinch(c - 1, v) & A_CHARTEXT) == '#' && ((mvinch(c + 1, v) & A_CHARTEXT)== '#'))
                {
                    hashes = hashes - 1;
                }
                if (cleanArray[c - 1][v] > 3 && !(mvinch(c, v  - 1) == ' '))
                {
                    hashes = hashes + 1;
                }
                if (((mvinch(c - 1,v) & A_CHARTEXT) == '#' && (mvinch(c - 2, v)  & A_CHARTEXT)== '#') && ((mvinch(c,v - 1)& A_CHARTEXT) == '#' && (mvinch(c , v - 2) & A_CHARTEXT ) == '#'))
                {
                    hashes = hashes - 1;
                }
                if ((mvinch(c - 1, v - 1) & A_CHARTEXT)== '+' || (mvinch(c - 1, v + 1) & A_CHARTEXT)== '+' || (mvinch(c + 1, v - 1)& A_CHARTEXT) == '+' || (mvinch(c + 1, v + 1)& A_CHARTEXT) == '+')
                {
                    hashes = hashes - 1;
                }
            }
            cleanArray[c][v] = hashes;  //stores hashes counter into an 2D array
            hashes = 0;                 //reset value for new spot on the screen
        }
    }

    for (int c = 0; c < maxY; ++c)
    {
        for (int v = 0; v < maxX; ++v)
        {
            if (cleanArray[c][v] > 4)
            {
                mvaddch(c,v,' ');   //checks if hashes > 4, wipe that hallway spot
            }
        }
    }
}
