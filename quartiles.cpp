/*
  Author:	Gregory Mitchell
  Date Created:	 11/15/14
  Last Modified: 11/14/14
  Filename:	 quartiles.cpp

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
#include <stdlib.h>
#include <time.h>
#include <algorithm>

using namespace std;


struct quartiles 
{
  int count;
  double m1;
  double m2;
  double m3;

  string filename;
  fstream stream;

  vector<double> members;
  vector<double> h1;
  vector<double> h2;

  vector<double> q1;
  vector<double> q2;
  vector<double> q3;
  vector<double> q4;
  
  vector<double> q1_vals;
  vector<double> q2_vals;
  vector<double> q3_vals;

};

void vecFromFile(quartiles& Q)
{
  string buffer;
  // clean container
  Q.members.clear();

  // try to open file
  Q.stream.open(Q.filename.c_str(), ios::in);
  if (Q.stream.fail())
    {
      cout << "failed to open " 
	   << Q.filename
	   << endl;
      exit (1);
    }

  // dump file contents into "members"
  while (Q.stream >> buffer)
    Q.members.push_back(atof(buffer.c_str()));

}


void displayVec (vector<double>& thisVec){
  for (int i = 0; i < thisVec.size(); i++)
    printf("%.0f, ",thisVec[i]);
}

void getMedianCounts (vector<double>& thisVec, vector<double>& medians)
{
  int median;
  int count = thisVec.size();
  medians.clear();

  if (count % 2 == 0)
    {
      median = count / 2;
      medians.push_back(median);
      medians.push_back(median-1);
    }
  
  else 
    {
      median = (count - 1) / 2;
      medians.push_back(median);
    }
}




void getMedians(vector<double>& thisVec,
		vector<double>& medianVals,
		vector<double>& h1_contents,
		vector<double>& h2_contents
		)
{
  vector<double> medians;

  sort(thisVec.begin(), thisVec.end());

  getMedianCounts(thisVec,medians);
  sort(medians.begin(),medians.end());

  medianVals.clear();
  h1_contents.clear();
  h2_contents.clear();

  // fill medians
  for (int i = 0; i < medians.size(); i++)
    medianVals.push_back(thisVec[medians[i]]);

  // fill 1st half
  for (int i = 0; i <= medians[0]; i++)
    h1_contents.push_back(thisVec[i]);

  // fill 2nd half
  if (medians.size() == 2) // even
    for (int i = medians[1]; i < thisVec.size(); i++)
      h2_contents.push_back(thisVec[i]);

  else // odd
    for (int i = medians[0]; i < thisVec.size(); i++)
      h2_contents.push_back(thisVec[i]);
	
}

double medianVal(vector<double>& medians)
 {
   double median;
   if (medians.size() % 2 == 0)
     median = ( medians[0] + medians[1] ) / 2;
   else 
     median = medians[0];
   return median;
 }

void handleQuartiles(quartiles& Q)
{

  // read file contents into vector "members"
  vecFromFile(Q);
  
  getMedians(Q.members,Q.q2_vals,Q.h1,Q.h2); // split into halves
  getMedians(Q.h1, Q.q1_vals, Q.q1, Q.q2); // split first half into quarters
  getMedians(Q.h2, Q.q3_vals, Q.q3, Q.q4); // split second half into quarters

  Q.m1 = medianVal(Q.q1_vals);
  Q.m2 = medianVal(Q.q2_vals);
  Q.m3 = medianVal(Q.q3_vals);

  // display full vector contents
  printf("vector (%li):",Q.members.size());
  displayVec(Q.members);
  printf("\n");

  // display h1 vals
  printf("h1 (%li):",Q.h1.size());
  displayVec(Q.h1);
  printf("\n");

  // display h2 vals
  printf("h2 (%li):",Q.h2.size());
  displayVec(Q.h2);
  printf("\n");

  // display q1 vals 
  printf("q1 (%li):",Q.q1.size());
  displayVec(Q.q1);
  printf("\n");
   
  // display q2 vals
  printf("q2 (%li):",Q.q2.size());
  displayVec(Q.q2);
  printf("\n");

  // display q3 vals
  printf("q3 (%li):",Q.q3.size());
  displayVec(Q.q3);
  printf("\n");

  // display q4 vals
  printf("q4 (%li):",Q.q4.size());
  displayVec(Q.q4);
  printf("\n\n");

  // display medians 
  printf("quartile medians:\n");
  printf("=================\n");
  printf("m1: %.2f\n", Q.m1);
  printf("m2: %.2f\n", Q.m2);
  printf("m3: %.2f\n", Q.m3);
  
}



int main(int argc, char** argv)
{
  quartiles Q;

  cout << "argc: " << argc << endl;
  cout << "argv[0]: " << argv[0] << endl;
  cout << "argv[1]: " << argv[1] << endl;

  if (argc >= 2)   // use file from commandlibe
    {
      Q.filename = argv[1];
      cout << "using filename: \"" << Q.filename << "\"" << endl;
      handleQuartiles(Q);
    }

  else  
    {
      Q.filename = string("quartile-data.txt");
      cout << "using filename: \"" << Q.filename << "\"" << endl;
      handleQuartiles(Q);
    }

    

  return 0;
}
