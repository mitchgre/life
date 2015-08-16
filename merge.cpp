/*
  Author:	Gregory Mitchell
  Date Created:	 11/15/14
  Last Modified: 11/14/14
  Filename:	 merge.cpp

  Overview: 
		
  Inputs: 
		

  Outputs: 
        

-------------------------------------------------------*/

#include <iostream>
#include <fstream>
#include <string> 
#include <cstring> 
#include <stdlib.h>
#include <vector>

using namespace std;

struct contents{
  string filename;
  fstream stream;
  vector<int> vec;
};


void file2stream(string filename, fstream& thisStream)
{
  thisStream.open(filename.c_str(), ios::in | ios::out);
  if (thisStream.fail())
    {
      cout << "failed to open " << filename << endl;
      exit (1);
    }
}

void stream2vec(fstream& thisStream, vector<int>& thisVec)
{
  string buffer;
  while (thisStream >> buffer)
    thisVec.push_back(atoi(buffer.c_str()));
}


void displayVec(vector<int>& thisVec, const char separator)
{

  for (int i = 0; i < thisVec.size(); i++)
    cout << thisVec[i] << separator;
  cout << endl;
}

void insertionSortVector(vector<int>& V)
{
  int j,x;
  for (int i = 1; i < V.size(); i++)
    {
      x = V[i];
      j = i;
      while ( (j > 0) && V[j-1] > x )
	{
	  V[j] = V[j-1];
	  j = j - 1;
	}
      V[j] = x; 
    }
}

void file2vec(contents& c)
{
  file2stream(c.filename, c.stream);
  stream2vec(c.stream,c.vec);
  /*
  // sanity check
  cout << "v1:" << endl;
  displayVec(v1, ','); 
  */
}


void mergeStuff(contents& c1,
		contents& c2,
		contents& c3)
{

  

  // read file 1, store to vector1
  file2vec(c1);
  cout << "input file 1:" << endl;
  displayVec(c1.vec, ',');

  // read file 2, store to vector2
  file2vec(c2);
  cout << "input file 2:" << endl;
  displayVec(c2.vec, ',');


  // merge vector1, vector2 into vector3
  c3.vec = c1.vec;
  c3.vec.insert(c3.vec.end(), c2.vec.begin(), c2.vec.end());
  
  // sort vector3 (insertion sort)
  insertionSortVector(c3.vec);
  cout << "sorted output file:" << endl;
  displayVec(c3.vec, ',');
  

  // write vector3 members to file3
  // file2stream("data-file2.txt",fin3);
  //c3.stream.open("data-file2.txt", ios::out);
  c3.stream.open(c3.filename.c_str(), ios::out);
  if (c3.stream.fail())
    {
      cout << "failed to open " 
	   << c3.filename
	   << endl;
      exit (1);
    }
  for (vector<int>::const_iterator i = c3.vec.begin(); 
       i != c3.vec.end(); 
       ++i)
    c3.stream << *i << '\n';

}

int main(int argc, char** argv)
{
  /*
  string fn1, fn2, fn3; // filenames
  fstream fin1, fin2, fin3; // file io streams
  vector<int> v1,v2,v3; // containers to sort
  */

  contents c1,c2,c3;  // filenames, fstreams, vectors

  if (argc >= 4)   // use files from commandlibe
    {
      c1.filename = argv[1];
      c2.filename = argv[2];
      c3.filename = argv[3];
      mergeStuff(c1,c2,c3);
    }
  else // use predefined files
    {
      c1.filename = "data-file0.txt";
      c2.filename = "data-file1.txt";
      c3.filename = "data-file2.txt";
      mergeStuff(c1,c2,c3);
    }
  
  


  return 0;
}
