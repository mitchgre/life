/*
  Author:	Gregory Mitchell
  Date Created:	 11/23/14
  Last Modified: 11/23/14
  Filename:	 getInt.cpp

  Overview: takes string input and returns integer output
            using stringstreams.

            Used for input validation.
	    Note that this method is not as robust 
	    as earlier methods that used looped c-strings,
	    but it's a lot simpler.
	    
		
  Inputs:  string to convert to integer
		

  Outputs: integer
        

-------------------------------------------------------*/

#include <iostream>
#include <string> 
#include <sstream>


using namespace std;

int getInt(string thisString)
{
  int integer;
  istringstream buffer(thisString);
  buffer >> integer;
  return integer;
}


int main()
{
  string buffer;
  int fromString;
  //bool flag = true;

  while (true)
    {
      cout << "Type Control-C to quit. " << endl;
      cout << "Enter a string to convert to an integer:" << endl;
      getline(cin,buffer);
      fromString = getInt(buffer);
      cout << "Your integer is " << fromString << endl;
    }
  return 0;
}
