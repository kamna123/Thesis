#include "rose.h"
#include "ds.hpp"
#include "CodeGen_Affinekernal_Interface.hpp"
#include "CodeGen_Cycle_Shrink.hpp"
using namespace std;
void cuda_kernel_declaration_AFFINE(char *shrinking,SgNode* forloop,string loop_id,int loop_num)
{
    if((DependencyExists=='y')&&((!strcmp(shrinking,"extShrinking1"))||(!strcmp(shrinking,"extShrinking2"))))
    {
        // cout<<" 1 "<<endl;
        ExtendedShrinking_kernel_declaration_DEPENDENCY(loop_num);
    }
    else if((DependencyExists=='y')&&((!strcmp(shrinking,"simple"))||(!strcmp(shrinking,"selective"))))
    {
        //   cout<<" 2 "<<endl;
        SimpleSelective_kernel_declaration_DEPENDENCY( forloop,loop_id,loop_num);
    }
    else
    {
        // cout<<" 3 "<<endl;
        cuda_kernel_declaration_NO_DEPENDENCY(loop_num);
    }
}
void cuda_kernel_call_AFFINE(char *shrinking,SgNode* forloop,string loop_id,int i)
{
    if(DependencyExists=='n')
    {
        // cout<<" 4 "<<endl;
        cuda_kernel_call_NO_DEPENDENCY(forloop,loop_id, i);
    }
    else if(!strcmp(shrinking,"simple"))
    {
        // cout<<" 5 "<<endl;
        simple_loop_shrinking_AFFINE(forloop,loop_id,i);
    }
    else if(!strcmp(shrinking,"extShrinking1"))
    {
        //cout<<" 6 "<<endl;
        extCS_ConstantDistance_AFFINE(loop_id,forloop,i);
    }
    else
    {
        // cout<<" 7 "<<endl;
        extCS_VariableDistance_AFFINE(loop_id,forloop,i);
    }
}

//Function for kernel definition
void cuda_kernel_definition_AFFINE(char *shrinking_type,string loop_id,SgNode* forloop,SgFunctionDefinition *defn,int i)
{
    if(DependencyExists=='n')
    {
        // cout<<" 8 "<<endl;
        cuda_kernel_definition_NO_DEPENDENCY( loop_id, forloop, defn, i);
    }

    else if((!strcmp(shrinking_type,"simple"))||(!strcmp(shrinking_type,"selective")))
    {
        //  cout<<" 9 "<<endl;
        SimpleSelective_kernel_definition_DEPENDENCY(shrinking_type,loop_id, forloop, defn, i);
    }
    else if((!strcmp(shrinking_type,"extShrinking1"))||(!strcmp(shrinking_type,"extShrinking2")))
    {
        // cout<<" 10 "<<endl;
        ExtendedShrinking_kernel_definition_DEPENDENCY(loop_id, forloop, defn, i);
    }
}
