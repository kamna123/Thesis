#ifndef DS
#define DS
#include <iostream>
#include <cstring>

struct dep_data
{
   int statement_no;
   std::vector<SgNode*> write_ref;
   std::vector<SgNode*> read_ref;
   dep_data* next;
};
extern std::string store_upper[];
extern std::ofstream outputfile;
extern std::ofstream outputfile1;
extern std::ifstream  inputfile;
struct  StringNode
{
	char* a;
	StringNode* next;/* data */
};
struct loop
{
  /* data */
  int loop_number;
  dep_data* dep;
  loop* next;
};
//

struct loop_data
{
 std::string lb,ub,loop_variable,step;
 int loop_number;
  loop_data* next;
};
struct Phi_Values
{
    char *loop_index;
    int phi_val;
    struct Phi_Values *next;
};
struct ReferencePair
{
    struct DDV *ddv;
    struct ReferencePair *next;
};

struct DDV
{
    struct DDV_Values *ddv_values;
    struct DDV *next;
};

struct DDV_Values
{
    int value;
    struct DDV_Values *next;
};
extern struct ReferencePair *RefPair;
extern struct DDV *DDVvector;
extern int noOfNestedLoops;
extern Phi_Values* lambda_var;
extern loop_data* head_loop;
extern loop* intersect_RAW;
extern loop* intersect_WAW;
extern loop* head;
extern loop* intersect_RAW_shrinking;
extern int Total_Phi;
extern char DependencyExists;
extern char AffineKernel;
extern std::string loop_id_string;
extern char VariableDependenceDist;
extern std::string op;
extern std::string rel_op;
extern int b_val;
extern char* upper;
#endif
