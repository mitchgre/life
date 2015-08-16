/*
  Author:	Gregory Mitchell
  Date Created:	 11/20/14
  Last Modified: 11/23/14
  Filename:	 gameOfLife-week7.cpp

  Overview: this is an static (not animated) implementation of Conway's 
            game of life.
		        

-------------------------------------------------------*/

#include <iostream>
#include <string>
#include <cstring>
#include <stdio.h>

#define ROWS 22
#define COLS 80

using namespace std;

struct cell {
  int x;
  int y;
  bool occupied;
};

// walk clockwise around the current cell to get 8 neighbors
struct neighbors {
  cell topLeft;
  cell topCenter;
  cell topRight;
  cell centerRight;
  cell bottomRight;
  cell bottomCenter;
  cell bottomLeft;
  cell centerLeft;
  cell all[8];
};


int mod(int a, int b)
{
    int r = a % b;
    return r < 0 ? r + b : r;
}

cell getTopLeft(cell current)
{
  cell block;  // create a new cell
  block.x = mod(current.x - 1, COLS);
  block.y = mod(current.y - 1, ROWS);
  return block;
}

cell getTopCenter(cell current)
{
  cell block;  // create a new cell
  block.x = mod(current.x, COLS);
  block.y = mod(current.y - 1, ROWS);
  return block;
}

cell getTopRight(cell current)
{
  cell block;  // create a new cell
  block.x = mod(current.x + 1, COLS);
  block.y = mod(current.y - 1, ROWS);
  return block;
}

cell getCenterRight(cell current)
{
  cell block;  // create a new cell
  block.x = mod(current.x + 1, COLS);
  block.y = mod(current.y, ROWS);
  return block;
}


cell getBottomRight(cell current)
{
  cell block;  // create a new cell
  block.x = mod(current.x + 1, COLS);
  block.y = mod(current.y + 1, ROWS);
  return block;
}


cell getBottomCenter(cell current)
{
  cell block;  // create a new cell
  block.x = mod(current.x, COLS);
  block.y = mod(current.y + 1, ROWS);
  return block;
}


cell getBottomLeft(cell current)
{
  cell block;  // create a new cell
  block.x = mod(current.x - 1, COLS);
  block.y = mod(current.y + 1, ROWS);
  return block;
}


cell getCenterLeft(cell current)
{
  cell block;  // create a new cell
  block.x = mod(current.x - 1, COLS);
  block.y = mod(current.y, ROWS);
  return block;
}


// purpose: return a structure containing all neighboring cells
neighbors getNeighbors (cell current)
{
  neighbors hood;
  hood.topLeft = getTopLeft(current);
  hood.topCenter = getTopCenter(current);
  hood.topRight = getTopRight(current);
  hood.centerRight = getCenterRight(current);
  hood.bottomRight = getBottomRight(current);
  hood.bottomCenter = getBottomCenter(current);
  hood.bottomLeft = getBottomLeft(current);
  hood.centerLeft = getCenterLeft(current);
  // store everything in array for easy iteration.
  hood.all[0] = hood.topLeft;
  hood.all[1] = hood.topCenter;
  hood.all[2] = hood.topRight;
  hood.all[3] = hood.centerRight;
  hood.all[4] = hood.bottomRight;
  hood.all[5] = hood.bottomCenter;
  hood.all[6] = hood.bottomLeft;
  hood.all[7] = hood.centerLeft;
  return hood;
}

// purpose: search the world array for current cell to determine if it is empty
bool isVacant(cell current, char (&world)[COLS][ROWS])
{
  char occupied = world[current.x][current.y];
  if (occupied == ' ')
    return true;
  else
    return false;
}


// purpose: get number of occupied/vacant neighbors
int numberOfVacantNeighbors(cell current, char (&world)[COLS][ROWS])
{
  int vacancies = 0; 
  neighbors hood = getNeighbors(current);

  // determine vacancy for each neighbor
  for (int i = 0; i < 8; i++)
    {
      if (isVacant(hood.all[i], world))
	vacancies++;
    }
  return vacancies;  
}

// purpose: see if occupied cell can survive loneliness
// "If an occupied cell has zero or one neighbor, it dies of loneliness."
bool loneliness (cell current, char (&world)[COLS][ROWS])
{
  int vacancies = numberOfVacantNeighbors(current, world);
  int occupancies = 8 - vacancies;
  if (occupancies <= 1)
    return true;
  else
    return false;
}

// purpose: see if occupied cell can survive overcrowding
// "If an occupied cell has more than three neighbors, it dies of overcrowding." 
bool overcrowding (cell current, char (&world)[COLS][ROWS])
{
  int vacancies = numberOfVacantNeighbors(current, world);
  int occupancies = 8 - vacancies;
  if (occupancies > 3) 
    return true;
  else
    return false;
}

// purpose: see if vacant cell can regenerate
// "If an empty cell has exactly three occupied neighbor cells, 
// there is a birth of a new cell to replace the empty cell."
bool rebirth (cell current, char (&world)[COLS][ROWS])
{
  int vacancies = numberOfVacantNeighbors(current, world);
  int occupancies = 8 - vacancies;
  if (occupancies == 3)
    return true;
  else
    return false;
}


void processWorlds (char (&startGen)[COLS][ROWS], char (&nextGen)[COLS][ROWS])
{
  // generate cells for the next world
  for (int i = 0; i < ROWS; i++)
    for (int j = 0; j < COLS; j++)
      {
	cell me;
	me.x = j;
	me.y = i;
	
	me.occupied = !isVacant(me, startGen);
	if (me.occupied)
	  {
	    if (loneliness(me, startGen))
	      {
		nextGen[j][i] = ' ';
		// printf("killed nextGen[%d][%d] from loneliness\n",j,i);
	      }
	    else if (overcrowding(me, startGen))
	      {
		nextGen[j][i] = ' ';
		// printf("killed nextGen[%d][%d] from overcrowding\n",j,i);
	      }
	    else // not lonely or overcrowded so me live on
	      nextGen[j][i] = '.';
	  }
	else // me am vacant
	  {
	    if (rebirth(me, startGen) )
	      {
		nextGen[j][i] = '.';
		// printf("birthed nextGen[%d][%d] from vacancy\n",j,i);
	      }
	    else
	      nextGen[j][i] = ' ';
	  }
      }
}



void displayGen(char (&world)[COLS][ROWS])
{
  // top border
  
  for (int i = 0; i < COLS; i++) 
    printf("-");
  printf("\n");
  

  for (int i = 0; i < ROWS; i++)
    {
      for (int j = 0; j < COLS; j++)
	printf("%c",world[j][i]);
      printf("\n");
    }

  // bottom border
  
  for (int i = 0; i < COLS; i++)
    printf("-");
  printf("\n");
  
}

int main()
{
  int generation = 0;
  int limit;

  char startGen[COLS][ROWS];  // current generation
  char nextGen[COLS][ROWS]; // next generation
  
  char* sgPtr = &(startGen[0][0]);
  char* ngPtr = &(nextGen[0][0]);

  cout << "Enter a generation limit: " << endl;
  cin >> limit;

  // define initial conditions somehow.

  // wipe the startGen clean
  for (int i = 0; i < ROWS*COLS; i++)
    {
      sgPtr[i] = ' ';
    }
  
  
  // simple blinker: (test left-right wrapping)
  startGen[79][5] = '.';
  startGen[0][5] = '.';
  startGen[1][5] = '.';

  // simple blinker (blows up block):
  /*
  startGen[78][10] = '.';
  startGen[79][10] = '.';
  startGen[0][10] = '.';
  */

  // simple blinker (test top-bottom wrapping)
  
  startGen[40][20] = '.';
  startGen[40][21] = '.';
  startGen[40][0] = '.';



  // simple block:
  startGen[1][10] = '.';
  startGen[2][10] = '.';
  startGen[1][11] = '.';
  startGen[2][11] = '.';

  printf("\ngeneration: %d\n",generation);

  // display generation
  displayGen(startGen);
  generation++;

  while (generation <= limit)
    {
      printf("\ngeneration: %d\n",generation);
  
      // wipe the next generation clean
      /*
      for (int i = 0; i < ROWS*COLS; i++)
	{
	  ngPtr[i] = ' ';
	}
      */

      for (int i = 0; i < ROWS; i++)
	for (int j = 0; j < COLS; j++)
	  nextGen[j][i] = ' ';
      
      // repopulate the next generation
      processWorlds(startGen, nextGen);

      /*
      // clear screen
      for (int i = 0; i < ROWS+1; i++)
	cout << endl;
      */

      // display next generation cout << string(nextGen);
      printf("\n");
      displayGen(nextGen);
      printf("\n");

      
      // startGen = nextGen on the next pass
      for (int i = 0; i < ROWS*COLS; i++)
	{
	  sgPtr[i] = ngPtr[i];
	}
      
      /*
      for (int i = 0; i < ROWS; i++)
	for (int j = 0; j < COLS; j++)
	  startGen[j][i] = nextGen[j][i];
      */
      generation++;
    }
  printf("\n");
  return 0;
}
