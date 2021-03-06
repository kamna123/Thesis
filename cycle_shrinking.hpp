#ifndef CYCLE_SHRINKING
#define CYCLE_SHRINKING
#include "extShrinking.hpp"
struct Phi_Values *Simple_Loops_Code_Gen(loop* write,SgNode* loop,int loop_number,std::set<std::string> var);
struct Phi_Values *find_phi_values(std::string dep_size,struct Phi_Values *lambda,std::string loop_id_string);
void CycleShrinking( char *shrinking,loop* write,SgNode* n,int loop_number,std::set<std::string> var);
#endif