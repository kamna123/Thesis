#ifndef READWRIE
#define READWRIE
#include <iostream>
#include "ds.hpp"
void setRhsOperand1(SgExpression* target, SgExpression* rhs);
void setLoopLowerBound1(SgForStatement* forstmt, SgExpression* lb);
static SgExpression* SkipCasting (SgExpression* exp);
bool isIntExpression( SgExpression * exp) ;
void replace_Expression_recursively(SgExpression** a,  SgInitializedName* ivarname,SgExpression* lbast,SgExpression* stepast1);
void display1(loop_data* loop);
void  visit1(SgNode* n);
#endif