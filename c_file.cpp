#include <iostream>
#include <set>
#include <vector>
#include <map>
using namespace std;
int  main()
{
  map<string ,string> mymap;
  mymap.insert(pair<string,string>("a","20"));
   mymap.insert(pair<string,string>("a","20"));
   mymap.insert(pair<string,string>("b","20"));
std::cout << "mymap contains:\n";
 std::map<string,string>::iterator it;
  for (it=mymap.begin(); it!=mymap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';
return 0;
}

