/*
  Author:	Gregory Mitchell
  Date Created:	 11/20/14
  Last Modified: 11/23/14

  email:  mitchgre@onid.oregonstate.edu

  Filename:	 gameOfLife-ncurses-menu.cpp

  Overview: this is an ncurses animated implementation of Conway's
            game of life.
		        

-------------------------------------------------------*/



#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <ncurses.h>
#include <menu.h>
#include <unistd.h>  // usleep
#include <cstdlib>  // calloc for menu


#define ROWS 22
#define COLS 80
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0])) // used for menu


using namespace std;


struct cell {
  int x;
  int y;
  bool occupied;
};


class game{
public:
  void init() // constructor
  {
  sgPtr = &(startGen[0][0]);
  ngPtr = &(nextGen[0][0]);
  speed = 38000;

  configuration = 0;

  configs();
  }
  void configs();
  int generation;
  int configuration;
  cell configurations[12]; // initial conditions
  char startGen[COLS][ROWS];  // current generation
  char nextGen[COLS][ROWS]; // next generation
  // pointers to generations
  char* sgPtr;
  char* ngPtr;
  int speed; // (microseconds). higher is slower
};


void game::configs()
{
  for (int i = 0; i < ROWS*COLS; i++)
    sgPtr[i] = ' ';

  switch (configuration)
    {
    case 0: // r-pentomino
      {
	// r-pentomino
	startGen[40][10] = '.';
	startGen[40][11] = '.';
	startGen[40][12] = '.';

	startGen[39][11] = '.';
	startGen[41][10] = '.';

	break;
      }
    case 1: // glider
      {
	startGen[1][10] = '.';
	startGen[2][10] = '.';
	startGen[3][10] = '.';
	startGen[3][9] = '.';
	startGen[2][8] = '.';
	break;
      }
    case 2: // 14x14 pulsar:  pad with 
      {

	startGen[36][10] = '.';
	startGen[37][10] = '.';
	startGen[38][10] = '.';

	startGen[42][10] = '.';
	startGen[43][10] = '.';
	startGen[44][10] = '.';

	startGen[34][12] = '.';
	startGen[34][13] = '.';
	startGen[34][14] = '.';

	startGen[39][12] = '.';
	startGen[39][13] = '.';
	startGen[39][14] = '.';

	startGen[41][12] = '.';
	startGen[41][13] = '.';
	startGen[41][14] = '.';

	startGen[46][12] = '.';
	startGen[46][13] = '.';
	startGen[46][14] = '.';

	startGen[46][12] = '.';
	startGen[46][13] = '.';
	startGen[46][14] = '.';

	startGen[36][15] = '.';
	startGen[37][15] = '.';
	startGen[38][15] = '.';

	startGen[42][15] = '.';
	startGen[43][15] = '.';
	startGen[44][15] = '.';
	


	break;
      }
    case 3: // clock
      {
	startGen[40][5] = '.';
	startGen[41][5] = '.';
	startGen[40][6] = '.';
	startGen[41][6] = '.';

	startGen[38][8] = '.';
	startGen[39][8] = '.';
	startGen[40][8] = '.';
	startGen[41][8] = '.';

	startGen[34][9] = '.';
	startGen[35][9] = '.';
	startGen[34][10] = '.';
	startGen[35][10] = '.';

	startGen[37][9] = '.';
	startGen[37][10] = '.';
	startGen[37][11] = '.';
	startGen[37][12] = '.';
	
	startGen[38][13] = '.';
	startGen[39][13] = '.';
	startGen[40][13] = '.';
	startGen[41][13] = '.';

	startGen[42][12] = '.';
	startGen[42][11] = '.';
	startGen[42][10] = '.';
	startGen[42][9] = '.';

	startGen[44][11] = '.';
	startGen[45][11] = '.';
	startGen[44][12] = '.';
	startGen[45][12] = '.';

	startGen[38][15] = '.';
	startGen[39][15] = '.';
	startGen[38][16] = '.';
	startGen[39][16] = '.';

	// hands
	startGen[39][10] = '.';
	startGen[40][10] = '.';
	startGen[41][11] = '.';
	break;
      }
    case 4: // kok's galaxy
      {
	// double check cleanliness
	for (int i = 0; i < ROWS; i++)
	  for (int j = 0; j < COLS; j++)
	    nextGen[j][i] = ' ';

	int i = 40;
	for (i; i > 34; i--)
	  {
	    startGen[i][6] = '.';
	    startGen[i][7] = '.';
	  }

	for (i = 6 ; i < 12; i++)
	  {
	    startGen[42][i] = '.';
	    startGen[43][i] = '.';
	  }
	
	for (i = 43; i > 37; i--)
	  {
	    startGen[i][14] = '.';
	    startGen[i][13] = '.';
	  }
	

	for (i = 14; i > 8; i--)
	  {
	    startGen[35][i] = '.';
	    startGen[36][i] = '.';
	  }
	
	break;
      }
    case 5: // early test cases
      {
	//   // // simple blinker: (test left-right wrapping)
	startGen[79][5] = '.';
	startGen[0][5] = '.';
	startGen[1][5] = '.';
	
	// simple blinker (blows up block):
	
	startGen[78][10] = '.';
	startGen[79][10] = '.';
	startGen[0][10] = '.';
	

	// simple blinker (test top-bottom wrapping)
	
	startGen[40][20] = '.';
	startGen[40][21] = '.';
	startGen[40][0] = '.';
	


	// simple block:
	startGen[1][10] = '.';
	startGen[2][10] = '.';
	startGen[1][11] = '.';
	startGen[2][11] = '.';
	break;
      }

    }
}



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
	      nextGen[j][i] = '#';
	  }
	else // me am vacant
	  {
	    if (rebirth(me, startGen) )
	      {
		nextGen[j][i] = '#';
		// printf("birthed nextGen[%d][%d] from vacancy\n",j,i);
	      }
	    else
	      nextGen[j][i] = ' ';
	  }
      }
}



void displayGen(WINDOW* board, char (&world)[COLS][ROWS])
{
  // top border
  /*
  for (int i = 0; i < COLS; i++) 
    printw("-");
  printw("\n");
  */  
  //move(0,0);
  for (int i = 0; i < ROWS; i++)
    {
      move(i,0);
      for (int j = 0; j < COLS; j++)
	wprintw(board,"%c",world[j][i]);
    }

  // bottom border
  /*
  for (int i = 0; i < COLS; i++)
    printw("-");
  printw("\n");
  */
}


void gameDriver(game& life)
{
  life.configs();
  life.generation = 0;
  timeout(0);
  int ch;

  displayGen(stdscr,life.startGen);
  wprintw(stdscr,"\ngeneration: %d  ",life.generation);
  refresh();
  usleep(life.speed*10);


  while ((ch = getch()) != 'q') // while not tab
    {
      if (ch == 'r') // reset init cond.
	gameDriver(life);
	
      if (ch == 'p') // reset init cond.
	life.speed += 5000;

      if (ch == 'o') // reset init cond.
	life.speed -= 5000;


	 
      // draw_borders(stdscr);
  
      // wipe the next generation clean
      for (int i = 0; i < ROWS*COLS; i++)
	life.ngPtr[i] = ' ';
      
      // repopulate the next generation
      processWorlds(life.startGen, life.nextGen);

      // display next generation cout << string(nextGen);
      displayGen(stdscr,life.nextGen);
      
      // startGen = nextGen on the next pass
      for (int i = 0; i < ROWS*COLS; i++)
	life.sgPtr[i] = life.ngPtr[i];
      
      life.generation++;

      wborder(stdscr,0,0,0,0,0,0,0,0);
      wprintw(stdscr,"\ngeneration: %d  ",life.generation);
      wprintw(stdscr,"Press 'q' to return to menu, ");
      wprintw(stdscr,"Press 'r' to reset initial conditions");
      //refresh();

      wmove(stdscr,0,35);
      wprintw(stdscr,"Config: %d", life.configuration);

      refresh();
      usleep(life.speed);
    }

  // endwin();
}

void initOptions(game& life)
{
  clear();
  int choice = 0;
  timeout(10000);
  cbreak();
  echo();
  //timeout(0);
  //timeout();
  printw( "Game of Life ");
  printw("Initial Conditions\n\n");

  printw("0. R-Pentomino\n");
  printw("1. Glider \n");
  printw("2. Pulsar (broken. should be infinite.)\n");
  printw("3. Clock  \n");
  printw("4. Kok's Galaxy  (should be infinite, but broken)\n");
  printw("5. Early Test \n\n");

  printw("The following have not been implemented yet:\n");
  printw("6. PinWheel  \n");
  printw("7. Octagon  \n");
  printw("8. Fumarole  \n");
  printw("9. Pentoad  \n");

  printw("10. Pentadecathod  \n");
  printw("11. Star \n");
  printw("12. French Kiss \n");



  //choice = forceInt("Please enter your selection now:");
  printw("Please enter your selection now:");
  refresh();
  scanw("%d",&choice);
  life.configuration = choice;
  life.configs();
  gameDriver(life);
  //choice = getch();
  //return choice;
}


// void initialConditions(game& life)
// {
//   // clear the start generation
//   for (int i = 0; i < ROWS*COLS; i++)
//     life.sgPtr[i] = ' ';

//   bool flag = true;

//   // while (flag)
//   //   {
//   //     life.configuration(
//   // /*
//   // // simple blinker: (test left-right wrapping)
//   // startGen[79][5] = '.';
//   // startGen[0][5] = '.';
//   // startGen[1][5] = '.';

//   // simple blinker (blows up block):
  
//   startGen[78][10] = '.';
//   startGen[79][10] = '.';
//   startGen[0][10] = '.';
  

//   // simple blinker (test top-bottom wrapping)
  
//   startGen[40][20] = '.';
//   startGen[40][21] = '.';
//   startGen[40][0] = '.';



//   // simple block:
//   startGen[1][10] = '.';
//   startGen[2][10] = '.';
//   startGen[1][11] = '.';
//   startGen[2][11] = '.';
//   */
  
//   // glider
//   /*
//   startGen[1][10] = '.';
//   startGen[2][10] = '.';
//   startGen[3][10] = '.';
//   startGen[3][9] = '.';
//   startGen[2][8] = '.';
//   */

//   // r-pentomino
//   life.startGen[12][10] = '.';
//   life.startGen[13][10] = '.';
//   life.startGen[12][9] = '.';
//   life.startGen[11][9] = '.';
//   life.startGen[12][8] = '.';
  
// }


int menuOptions()
{
  clear();
  int choice = 0;
  timeout(5000);
  cbreak();
  echo();
  //timeout(0);
  //timeout();
  printw( "Game of Life\n");
  printw("Please select from the following options\n\n");

  printw("1. set initial conditions\n");
  printw("2. set update speed\n");
  printw("3. play\n");
  printw("4. exit\n\n");


  //choice = forceInt("Please enter your selection now:");
  printw("Please enter your selection now:");
  refresh();
  scanw("%d",&choice);
  //choice = getch();
  return choice;
}


int menu(game& life)
{
  clear();
  bool flag = true;
  int choice;
  while (flag)
    {
      choice = menuOptions();
      
      switch (choice)
	{
	case 1: // set initial conditions
	  {
	    //life.config(life);
	    initOptions(life);
	    break;
	  }
	case 2: // set update speed
	  {
	    clear();
	    printw("Enter a pause time in microseconds.");
	    scanw("%d",&life.speed);
	    break;
	  }
	case 3: // play
	  {
	    gameDriver(life);  
	    break;
	  }
	case 4: // exit program
	  {
	    flag = false;
	    break;
	  }
	default:
	  {
	    clear();
	    printw("%d is not a valid option",choice);
	    break;
	  }
	}
    }
}

int main()
{
  // set pseudo-gui parameters
  initscr();
  start_color();
  noecho();
  //cbreak();
  raw();
  keypad(stdscr, TRUE);
  
  game life; // create a game object
  life.init();

  //  while (generation <= limit)
  menu(life);

  //printw("\n");
  endwin();
  return 0;
}
