
#include "rose.h"
#include "dependency.h"
#include "ds.hpp"
#include "gcd_banerjee.hpp"
#include "new_loop_normalization.hpp"
#include "readWrie.h"
#include <iostream>
#include <set>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;
using namespace SageInterface;
using namespace SageBuilder;

class visitorTraversal : public AstSimpleProcessing
{
    public:
       virtual void visit(SgNode* n);
};
loop_data* head_loop=NULL;
loop* intersect_RAW=NULL;
loop* intersect_WAW=NULL;
loop* head=NULL;
 ReferencePair *RefPair=NULL;
DDV *DDVvector=NULL;
int noOfNestedLoops=0;
void abc(SgNode* for_loop)
{
   SgForStatement* forLoop=isSgForStatement(for_loop);
    SgBasicBlock* loopBody = isSgBasicBlock(forLoop->get_loop_body());
    if(loopBody!=NULL)
    {    vector<SgNode*>:: iterator itr;
         Rose_STL_Container<SgStatement*> forLoops = loopBody->get_statements();
          for(Rose_STL_Container<SgStatement*>::iterator iter = forLoops.begin(); iter!= forLoops.end(); iter++ )
         {
           cout<<(*iter)->unparseToString()<<"\n"; 
         }
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
  /*  Rose_STL_Container<SgNode*> forLoops = NodeQuery::querySubTree(defn,V_SgForStatement);
    for(Rose_STL_Container<SgNode*>::iterator iter = forLoops.begin(); iter!= forLoops.end(); iter++ )
    {
        // printf ("Found a SgForStatement \n");
        // abc(*iter);
        
       ref_function(*iter,defn);//

/*         for(iter1 = pntrArrRefList.begin(); iter1 != pntrArrRefList.end(); ++iter1) 
         {

          if(a!=NULL)
          { cout<<"abc"<<"\n";  
            if(isAssignmentStatement(a,NULL,NULL))
              cout<<"found statement"<<"\n";
          }
          
          
     
         }
   
    }*/
          set<SgInitializedName*> readNames, writeNames;
  if (!SageInterface::collectReadWriteVariables(func,readNames,writeNames))
  {
    ROSE_ASSERT(false);
  }
  set<SgInitializedName*>::iterator iter;
  for (iter=readNames.begin();iter!=readNames.end();iter++)
  {
      // cout<<"read variable:"<<(*iter)->unparseToString()<<endl;
       var.insert((*iter)->unparseToString());
  }
  /* i, j, a, b
   */
 // ROSE_ASSERT(writeNames.size() ==4);

  for (iter=writeNames.begin();iter!=writeNames.end();iter++)
  {   //  cout<<"written variable:"<<(*iter)->unparseToString()<<endl;
        var.insert((*iter)->unparseToString());
}
   //for(i=var.begin();i!=var.end();i++)
  // cout<<" "<<*i ;
 Rose_STL_Container<SgNode*> forLoops = NodeQuery::querySubTree(defn,V_SgForStatement);
    for(Rose_STL_Container<SgNode*>::iterator iter = forLoops.begin(); iter!= forLoops.end(); iter++ )
    {
        loop_normalization(*iter,var);
   
    }
    for(Rose_STL_Container<SgNode*>::iterator iter = forLoops.begin(); iter!= forLoops.end(); iter++ )
    {
        // printf ("Found a SgForStatement \n");
        // abc(*iter);
        
      visit1(*iter);

/*         for(iter1 = pntrArrRefList.begin(); iter1 != pntrArrRefList.end(); ++iter1) 
         {

          if(a!=NULL)
          { cout<<"abc"<<"\n";  
            if(isAssignmentStatement(a,NULL,NULL))
              cout<<"found statement"<<"\n";
          }
          
          
     
         }*/
   
    }
  cout<<"display head"<<endl;
   display(head);  

/*calculate_intersection_RAW(head);
cout<<"after intersection  RAW"<<"\n";
display(intersect_RAW);
calculate_intersection_WAW(head);
cout<<"after intersection  WAW"<<"\n";
display(intersect_WAW);
/*int m=0;
 for(Rose_STL_Container<SgNode*>::iterator iter = forLoops.begin(); iter!= forLoops.end(); iter++ )
{
   loop* temp=intersect_RAW;
   while(temp->loop_number!=m)
      temp=temp->next;
int k= banerjee(temp,*iter);
if(k==1)
 cout<<"GCD dep may exists"<<endl;
else
cout<<"no dependency"<<endl;
m++;
}*/
 return backend(project);
 }
