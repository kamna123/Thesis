
#include "rose.h"
#include "dependency.h"
#include "ds.hpp"
#include "gcd_banerjee.hpp"
#include "new_loop_normalization.hpp"
#include "cycle_shrinking.hpp"
#include "readWrie.h"
#include "extShrinking.hpp"
#include <iostream>
#include <set>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;
using namespace SageInterface;
using namespace SageBuilder;
int Total_Phi=0;
char DependencyExists='n';
int noOfNestedLoops=0;
std::string op;
std::string rel_op;
int b_val;
struct ReferencePair *RefPair=NULL;
struct DDV *DDVvector=NULL;
class visitorTraversal : public AstSimpleProcessing
{
public:
    virtual void visit(SgNode* n);
};
loop_data* head_loop=NULL;
loop* intersect_RAW=NULL;
loop* intersect_WAW=NULL;
loop* intersect_RAW_shrinking=NULL;
loop* head=NULL;
/*void abc(SgNode* for_loop)
{ vector<SgNode*> reads;
   vector<SgNode*> writes;
   SgForStatement* forLoop=isSgForStatement(for_loop);
    SgBasicBlock* loopBody = isSgBasicBlock(forLoop->get_loop_body());
    if(loopBody!=NULL)
    {    vector<SgNode*>:: iterator itr;
       //  Rose_STL_Container<SgStatement*> forLoops = loopBody->get_statements();
        //  for(Rose_STL_Container<SgStatement*>::iterator iter = forLoops.begin(); iter!= forLoops.end(); iter++ )
         {
          // SgScopeStatement* scope=(*iter)->get_scope();


          SageInterface::collectReadWriteRefs(forLoop, reads, writes);
           for (itr=reads.begin();itr!=reads.end();itr++)
           {
              if(isSgBinaryOp(*itr)!=NULL)
                {
                 cout<<" read "<<(*itr)->unparseToString()<<endl;
                 }
         }

   }
}}*/
void ref_function1(SgNode* for_loop,SgFunctionDefinition *defn )
{
    SgForStatement* forLoop=isSgForStatement(for_loop);
    SgBasicBlock* loopBody = isSgBasicBlock(forLoop->get_loop_body());
    Rose_STL_Container<SgStatement*> forLoops = loopBody->get_statements();
    for(Rose_STL_Container<SgStatement*>::iterator iter = forLoops.begin(); iter!= forLoops.end(); iter++ )
    {

        cout<<" statements are "<< (*iter)->unparseToString()<<"\n";
    }
}

int main(int argc, char * argv[])
{
    vector<SgNode*> readRefs;
    vector<SgNode*> writeRefs;
    vector<SgNode*>:: iterator itr;
    SgProject *project = frontend (argc, argv);
    SgFunctionDeclaration* func = SageInterface::findMain(project);
    /*visitorTraversal ae;
    ae.traverseInputFiles(project,preorder);
     display1(head_loop);*/
    set<string> var;
    set<string> :: iterator i;

    SgFunctionDefinition *defn = func->get_definition();
    // Rose_STL_Container<SgNode*> forLoops = NodeQuery::querySubTree(defn,V_SgForStatement);
    /*   for(Rose_STL_Container<SgNode*>::iterator iter = forLoops.begin(); iter!= forLoops.end(); iter++ )
       {
          cout<<"found for statement "<<endl;
           abc(*iter);




       }*/
    set<SgInitializedName*> readNames, writeNames;
    if (!SageInterface::collectReadWriteVariables(func,readNames,writeNames))
    {
        ROSE_ASSERT(false);
    }
    set<SgInitializedName*>::iterator iter;
    for (iter=readNames.begin(); iter!=readNames.end(); iter++)
    {
        // cout<<"read variable:"<<(*iter)->unparseToString()<<endl;
        var.insert((*iter)->unparseToString());
    }

// ROSE_ASSERT(writeNames.size() ==4);

    for (iter=writeNames.begin(); iter!=writeNames.end(); iter++)
    {
        //   cout<<"written variable:"<<(*iter)->unparseToString()<<endl;
        var.insert((*iter)->unparseToString());
    }
    //for(i=var.begin();i!=var.end();i++)
    // cout<<" "<<*i ;
    Rose_STL_Container<SgNode*> forLoops = NodeQuery::querySubTree(defn,V_SgForStatement);
    for(Rose_STL_Container<SgNode*>::iterator iter = forLoops.begin(); iter!= forLoops.end(); iter++ )
    {
        cout<<"------------------loop normalization ---------------------------"<<endl;
        loop_normalization(*iter,var);
        cout<<"after normalization "<<(*iter)->unparseToString();

    }
    cout<<"-----------done with normalization----------"<<endl;
    for(Rose_STL_Container<SgNode*>::iterator iter = forLoops.begin(); iter!= forLoops.end(); iter++ )
    {
        // printf ("Found a SgForStatement \n");
        // abc(*iter);


        // printf ("Found a SgForStatement \n");


        ref_function(*iter,defn);
        ref_function1(*iter,defn);

    }


    cout<<"display head"<<endl;
    display(head);

    calculate_intersection_RAW(head);
    cout<<"after intersection  RAW"<<"\n";
    display(intersect_RAW);
    calculate_intersection_WAW(head);
    cout<<"after intersection  WAW"<<"\n";
    display(intersect_WAW);
    calculate_intersection_RAW_for_srinking(head);
    cout<<"after intersection  RAW for cycle shrinking"<<"\n";
    display(intersect_RAW_shrinking);
    int m=0;
    for(Rose_STL_Container<SgNode*>::iterator iter = forLoops.begin(); iter!= forLoops.end(); iter++ )
    {
        loop* temp=intersect_RAW;

        while(temp->loop_number!=m)
            temp=temp->next;
        // cout<<"--------in loop ------------"<<endl;
        int k= GCD_Test(temp,*iter);
//Simple_Loops_Code_Gen(temp,*iter,m,var);
        if(k==1)
        {
            cout<<"benerjee dep may exists"<<endl;
            DependencyExists='y';
        }
        else
        {
            cout<<"no dependency"<<endl;
            DependencyExists='n';
        }


        m++;
    }
    m=0;
    for(Rose_STL_Container<SgNode*>::iterator iter = forLoops.begin(); iter!= forLoops.end(); iter++ )
    {
        loop* temp=intersect_RAW_shrinking;
        while(temp->loop_number!=m)
            temp=temp->next;
        cout<<"--------in loop ------------"<<endl;
        Simple_Loops_Code_Gen(temp,*iter,m,var);
        extCS_VariableDistance_Lambda(temp,*iter,m,var);
        cout<<"Total_Phi "<<Total_Phi<<endl;
// temp=temp->next;
        Total_Phi=0;
        m++;
    }
    m=0;

    /*    for(Rose_STL_Container<SgNode*>::iterator iter = forLoops.begin(); iter!= forLoops.end(); iter++ )
    {
       loop* temp=intersect_RAW_shrinking;
         while(temp->loop_number!=m)
          temp=temp->next;
        cout<<"--------in loop next ------------"<<endl;
    extCS_VariableDistance_Lambda(temp,*iter,m,var);
     // temp=temp->next;
    m++;
    }*/
    return backend(project);
}
