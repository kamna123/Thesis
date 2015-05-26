#ifndef AFFINEC
#define AFFINEC
bool isIntegralType(SgType* type);
bool isIntegralConstant(SgExpression* expr);
bool isPotentiallyAffine(SgExpression* expr);
#endif