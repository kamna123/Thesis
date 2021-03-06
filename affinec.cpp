#include "rose.h"
#include "ds.hpp"
using namespace std;
using namespace SageBuilder;
using namespace SageInterface;
bool isIntegralType(SgType* type)
{
    if(
        isSgTypeInt(type) ||
        isSgTypeSignedInt(type) ||
        isSgTypeUnsignedInt(type) ||
        isSgTypeShort(type) ||
        isSgTypeSignedShort(type) ||
        isSgTypeUnsignedShort(type) ||
        isSgTypeLong(type) ||
        isSgTypeSignedLong(type) ||
        isSgTypeUnsignedLong(type) ||
        isSgTypeLongLong(type) ||
        isSgTypeSignedLongLong(type) ||
        isSgTypeUnsignedLongLong(type) ||
        isSgTypeChar(type) ||
        isSgTypeSignedChar(type) ||
        isSgTypeUnsignedChar(type)) return true  ;
    else
        return false;
}
bool isIntegralConstant(SgExpression* expr)
{
    if ( ! isIntegralType(expr->get_type())) return false;
    if (isSgValueExp(expr)) return true; // all subclasses of SgValueExp
    if (isSgMinusOp(expr))     return isIntegralConstant(isSgMinusOp(expr)->get_operand());
    if (isSgUnaryAddOp(expr))      return isIntegralConstant(isSgUnaryAddOp(expr)->get_operand());
    return false;
}
bool isPotentiallyAffine(SgExpression* expr)
{
    // "potentially" because we do not know the iterators and parameters
    // of the scop, so cannot check that it is affine ***in them***.
    if (isSgVarRefExp(expr)) return isIntegralType(expr->get_type());
    if (isIntegralConstant(expr)) return true;
    if (isSgBinaryOp(expr))
    {
        if (isSgSubtractOp(expr) || isSgAddOp(expr))
        {
            SgExpression* lhs = (isSgBinaryOp(expr))->get_lhs_operand();
            SgExpression* rhs = (isSgBinaryOp(expr))->get_rhs_operand();
            return (isPotentiallyAffine(lhs) && isPotentiallyAffine(rhs));
        }
        if (isSgMultiplyOp(expr))
        {
            SgExpression* lhs = (isSgBinaryOp(expr))->get_lhs_operand();
            SgExpression* rhs = (isSgBinaryOp(expr))->get_rhs_operand();
            if (isIntegralConstant(lhs))
                return isPotentiallyAffine(rhs);
            else if (isIntegralConstant(rhs))
                return isPotentiallyAffine(lhs);
        }
    }
    return false;
}

/*int main(int argc, char * argv[])
{

    SgProject *project = frontend (argc, argv);
    SgFunctionDeclaration* func = SageInterface::findMain(project);
    SgFunctionDefinition *defn = func->get_definition();
    Rose_STL_Container<SgNode*> forLoops = NodeQuery::querySubTree(defn,V_SgForStatement);
    for(Rose_STL_Container<SgNode*>::iterator iter = forLoops.begin(); iter!= forLoops.end(); iter++ )
    {
        printf ("Found a SgForStatement \n");
        // SgExpression* init_exp=(buildVarRefExp("a"));
        Rose_STL_Container<SgNode*> pntrArrRefList =  NodeQuery::querySubTree(defn, V_SgPntrArrRefExp);
        Rose_STL_Container<SgNode*>::iterator iter1;
        for(iter1 = pntrArrRefList.begin(); iter1 != pntrArrRefList.end(); ++iter1)
        {
            SgExpression* rhs = isSgBinaryOp(*iter1)->get_rhs_operand();
            cout<<"SgExpression"<<(rhs)->unparseToString()<<endl;
            bool k=isPotentiallyAffine(rhs);
            if(k==true)
            {
                cout<<"Affine "<<endl;

            }
            else
                cout<<"Not Affine"<<endl;

        }

    }
    return backend(project);
}*/
