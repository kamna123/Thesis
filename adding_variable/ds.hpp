#ifndef DS
#define DS
#include <iostream>
#include <cstring>
#include <set>
struct StringNode
 {
  char* a;
  StringNode* next;
 };
struct dep_data
{
   int statement_no;
   std::vector<SgNode*> write_ref;
   std::vector<SgNode*> read_ref;
   dep_data* next;
};

struct loop
{
  /* data */
  int loop_number;
  dep_data* dep;
  loop* next;
};

struct loop_data
{
 std::string lb,ub,loop_variable,step;
 int loop_number;
  loop_data* next;
};

extern loop_data* head_loop;
extern loop* intersect_RAW;
extern loop* intersect_WAW;
extern loop* head;
//extern StringNode* curr;
 
#endif