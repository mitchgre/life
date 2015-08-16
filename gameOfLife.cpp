/*
  Author:	Gregory Mitchell
  Date Created:	 11/20/14
  Last Modified: 11/23/14
  Filename:	 gameOfLife.cpp

  Overview:  this is a driver program for two implementations
             of Conway's game of life		        

-------------------------------------------------------*/


#include <iostream>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <stdio.h>

using namespace std;

/*------------------isInt---------------------------
Entry:  send a string containing potential integers

Exit:  returns true if integer or false if not

Purpose:   
       force user to enter a valid integer
--------------------------------------------------- */



bool isInt(string input)
{
  int integer;
  bool returnVal = true;
  // initialize char array
  char *inputArray = new char[input.length()+1]; 
  strcpy(inputArray, input.c_str());  // copy input to char array
  
  
  if ( (isdigit(inputArray[0])) ||  (inputArray[0] == '-') )
    {
      for (int i = 1; i < strlen(inputArray); i++)
	{
	  if (isdigit(inputArray[i]))
	    returnVal = returnVal && true;
	  else
	    return false;
	}
      return returnVal;
    }
  else
    {
      return false;
    }
}


/*------------------string2int---------------------------
Entry:  send a string containing integers

Exit:  returns a validated integer from string using atoi()

Purpose:   
       force user to enter a valid integer
--------------------------------------------------- */


int string2int (string input)
{
  int integer;
  if ( isInt(input) )
    {
      char *inputArray = new char[input.length()+1]; 
      strcpy(inputArray, input.c_str());  // copy input to char array

      integer = atoi(inputArray); // convertt string to int
      return integer;
    }
}

/*------------------forceInt--------------------------------
Entry:  send a string containing a message to prompt for integer
	prompts for integer until input is validated

Exit:  returns a validated integer

Purpose:   
       force user to enter a valid integer
---------------------------------------------------------- */

int forceInt (string promptMessage)
{
  int integer;  
  string buffer;
  while (1)
    {
      cout << promptMessage << endl;
      getline(cin,buffer);
      if (isInt(buffer))
	{
	  integer = string2int(buffer);
	  return integer; // breaks while loop
	}
    }
}


int displayMainMenu()
{
  int choice;
  
  cout << "1. Use Animations" << endl;
  cout << "2. Avoid Animations" << endl;
  cout << "3. exit program" << endl;
  choice = forceInt("Please enter your choice:");
  return choice;
}

void mainMenuLoop()
{
  // run make here to ensure that all executable files are in place

  system("make");
  cout << "Good to go." << endl;
  cout << endl;


  while (1)
    {
      int choice = displayMainMenu();
      
      switch (choice)
	{
	case 1:
	  system("./gameOfLife-ncurses-menu");
	  break;
	case 2:
	  system("./gameOfLife-noAnim");
	  break;
	case 3:
	  exit(1);
	default:
	  cout << "That is not a valid option" << endl;
	}
    }
}


int main()
{
  mainMenuLoop();
  return 0;
}
