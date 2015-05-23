#ifndef DEPENDENCY
#define DEPENDENCY
#include "ds.hpp"

void display( loop* head);
void calculate_node(struct loop* node);
void calculate_intersection_RAW(struct loop* node);
void calculate_intersection_WAW(struct loop* node);
void ref_function(SgNode* for_loop,SgFunctionDefinition *defn );

#endif