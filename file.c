#include <iostream>
#include <fstream>
#include <stdio.h>
#include<string>
#include<list>
#include<assert.h>
using namespace std;
ifstream inputFile;
ofstream outputFile;

int main(int argc, char *argv[])
{
int i;
printf ("argc = %d \n",argc);
for (i = 0; i < argc; i++)
{
cout << "argv[" << i << "] = " << argv[i] << endl;
}
if (argc != 3)
{
printf ("Error: Usage: uniqueStrings <input file> <output file> \n");
assert(false);
}
ifstream inputFile ( argv[1] , ios::in );
if ( inputFile.good() == false )
{
printf ("inputFile failed to open \n");
assert(false);
}
// ofstream outputFile ( argv[2] , ios::out | ios::app );
 ofstream outputFile ( argv[2] , ios::out | ios::trunc );
if ( outputFile.good() == false )
{
printf ("outputFile failed to open \n");
assert(false);
}
char buffer[1000];
list<string> stringList;
int count = 0;
while (!inputFile.eof())
{
inputFile.getline (buffer,1000);
string s = buffer;
if (inputFile.eof() == false)
{
printf ("count = %4d s = %s \n",count,s.c_str());
#if 0
// Remove the path to where we store the ROSE headers
string targetString ="/usr/casc/overture/dquinlan/";
if (s.find(targetString) != string::npos)
{
s.replace(s.find(targetString),targetString.size(),"");
}
#endif
stringList.push_front(s);
count++;
}
}
inputFile.close();
stringList.sort();
stringList.unique();
for (list<string>::iterator i = stringList.begin(); i != stringList.end(); i++)
{
printf ("%s \n",(*i).c_str());
outputFile << (*i) << endl;
}
outputFile.close();
return 0;
}

