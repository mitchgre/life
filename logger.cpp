/*
  Author:	Gregory Mitchell
  Date Created:	 11/15/14
  Last Modified: 11/23/14
  Filename:	 logger.cpp

  Overview: this program signs people in and out of a log vector
		
  Inputs: strings of names

  Outputs: strings of names
        

-------------------------------------------------------*/

#include <iostream>
#include <string> 
#include <cstring> 
#include <stdlib.h>
#include <vector>

using namespace std;



/*------------------forceNonEmptyString--------------------------------
Entry:  send a string containing a message to prompt for string
	prompts for non-empty string until input is validated

Exit:  returns a non empty string

Purpose:   
       force user to enter a non empty string
---------------------------------------------------------- */

string forceNonEmptyString(string prompt)
{
  string stringName = "";
  while (stringName == "")
    {
      cout << prompt << endl;    
      getline(cin, stringName);
    }
  return stringName;
}


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

      integer = atoi(inputArray); // convert string to int
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


int menu()
{
  bool flag = true;
  int choice; 


  while (flag)
    {
      cout << "Please select from the following options:" << endl;
      cout << endl;
      
      cout << "1. Sign in" << endl;
      cout << "2. Sign out" << endl;
      cout << "3. Show who is signed in" << endl;
      cout << "4. Exit Program" << endl;
      cout << endl;

      choice = forceInt("Please enter your selection now:");

      if (choice > 0)
	if (choice < 5)
	  flag = false;
	else 
	  cout << choice << " is not a valid option.  Try again."
	       << endl;
	  
    }
  return choice;
}


void signIn(vector<string>& names)
{
  string name = forceNonEmptyString("Please enter your name");
  names.push_back(name);
}

void signOut(vector<string>& names)
{
  string name = forceNonEmptyString("Please enter your name");

  for (int i = 0; i < names.size(); i++)
    if (names[i] == name)
      names.erase(names.begin() + i);
}


int main()
{
  vector<string> names;
  bool flag = true;
  int choice;

  while (flag)
    {
      choice = menu();
      switch (choice)
	{
	case 1:
	  {
	    signIn(names);
	    break;
	  }
	case 2:
	  {
	    signOut(names);
	    break;
	  }
	case 3:  // display who is signed in
	  {
	    for (int i = 0; i < names.size(); i++)
	      cout << names[i] << endl;
	    break;
	  }
	case 4:
	  flag = false;
	}
    }

  return 0;
}
