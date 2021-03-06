
#include "rose.h"
#include "dependency.h"
#include "ds.hpp"
#include "gcd_banerjee.hpp"
#include "CodeGen_Cycle_Shrink.hpp"
#include "new_loop_normalization.hpp"
#include "cycle_shrinking.hpp"
#include "CodeGen_Affinekernal_Interface.hpp"
#include "Dependence_Testing_Interface.hpp"
#include "readWrie.h"
#include "extShrinking.hpp"
#include "affinec.hpp"
#include <iostream>
#include <set>
#include <vector>
#include <iterator>
#include <algorithm>
#include <stdarg.h>
#include <getopt.h>
using namespace std;
using namespace SageInterface;
using namespace SageBuilder;
int Total_Phi=0;
char DependencyExists='n';
int noOfNestedLoops=0;
std::string op;
std::string rel_op;
int b_val;
char* upper;
char VariableDependenceDist='n';
struct ReferencePair *RefPair=NULL;
struct DDV *DDVvector=NULL;
Phi_Values* lambda_var=NULL;
ofstream outputfile;
ifstream inputfile;
ofstream outputfile1;
set<string> var;
class visitorTraversal : public AstSimpleProcessing
{
public:
    virtual void visit(SgNode* n);
};
void visitorTraversal::visit(SgNode* n)
{
    SgVariableDeclaration* forLoop=isSgVariableDeclaration(n);
    if(forLoop)
    {
        SgInitializedNamePtrList ptrList = forLoop->get_variables();
        SgInitializedNamePtrList::const_iterator i;
        for(i=ptrList.begin(); i!=ptrList.end(); i++)
        {
            // cout<<" val "<<(*i)->unparseToString()<<endl;
            var.insert((*i)->unparseToString());
        }

    }
}
loop_data* head_loop=NULL;
loop* intersect_RAW=NULL;
loop* intersect_WAW=NULL;
loop* intersect_RAW_shrinking=NULL;
loop* head=NULL;
char var_dep_dist[100];
char dep_exists[100];
ifstream fin;
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
void display_start(int startLine)
{
    int i=1;
    char c;
    while(!fin.eof() && i<startLine  )
    {

        fin.get(c);
        //  cout<<"i = "<<i<<"startLine = "<<startLine<<"c= "<<c<<endl;
        if(c=='\n')
        {
            i++;
            outputfile<<endl;
        }
        else
            outputfile<<c;
    }
}
void display_mid(int startLine_pre,int endline_pre,int startLine)
{
    int i=startLine_pre;
    int k=endline_pre;
    char c;
    while(i<=k && !fin.eof())
    {
        //   cout<<"k = "<<k<<"c = "<<c<< "i= "<<i<<endl;
        fin.get(c);
        if(c=='\n')
        {
            i++;
            if(i>k) break;
        }
    }
    while(!fin.eof() && i<startLine)
    {

        fin.get(c);
        //   cout<<"i in inner loop "<<i<<"c= "<<c<<endl;
        if(c=='\n')
        {
            i++;
            outputfile<<endl;
        }
        else outputfile<<c;
    }
}
void end(int i,int k)
{
    char c;
    while(i<=k && !fin.eof())
    {
        // cout<<"k = "<<k<<"c = "<<c<< "i= "<<i<<endl;
        fin.get(c);
        if(c=='\n')
        {
            i++;
            if(i>k) break;
        }
    }
    while(!fin.eof() )
    {

        fin.get(c);
        //  cout<<"i in inner loop "<<i<<"c= "<<c<<endl;
        if(c=='\n')
        {
            i++;
            outputfile<<endl;
        }
        else outputfile<<c;
    }
}
static int loop_num=0;
static int var_dep_dist_count=0;
static void getArrayDimensionSizes(const SgArrayType* array_type, std::vector<SgExpression*>& result)
{
ROSE_ASSERT (array_type != NULL);
const SgType* cur_type = array_type;
do
{
ROSE_ASSERT (isSgArrayType(cur_type) != NULL);
SgExpression* index_exp = isSgArrayType(cur_type)->get_index();
result.push_back(index_exp); // could be NULL, especially for the first dimension
cur_type = isSgArrayType(cur_type)->get_base_type();
}
while (isSgArrayType(cur_type));
}
int main(int argc, char * argv[])
{
    /* cout<<"abc";
      int q=argc;
      cout<<argc<<endl;
       while(q)
       {
         cout<<"arg "<<argv[--q]<<endl;

       }*/

    char* outfile;
    char* infile, *fileName;
    char *dependence_test,*shrinking,*verbosity_no;
    SgProject *project = frontend (argc, argv);
    SgFunctionDeclaration* func = SageInterface::findMain(project);
    SgSourceFile* file = isSgSourceFile((*project)[0]);
    //  cout<<"file = "<<file->getFileName();
    const char* file_name=(file->getFileName()).c_str();
    shrinking = (char*)malloc(sizeof(char)*20);
    dependence_test= (char*)malloc(sizeof(char)*20);
    vector<string> argvList(argv, argv+argc);

    if ( CommandlineProcessing::isOption(argvList,"-test:","(gcd|banerjee)",false)  )
    {
        //  cout<<"------------test--------------"<<endl;
        char * S = new char[argvList[3].length() + 1];
        std::strcpy(S,argvList[3].c_str());
        dependence_test=strstr(S,":");
        dependence_test=dependence_test+1;
        //cout<<"test= "<<dependence_test<<endl;
    }
    if ( CommandlineProcessing::isOption(argvList,"-shrink:","(simple|extShrinking1|extShrinking2)",false)  )
    {
        //  cout<<"------------test1--------------"<<endl;
        char * S = new char[argvList[4].length() + 1];
        std::strcpy(S,argvList[4].c_str());
        shrinking=strstr(S,":");
        shrinking=shrinking+1;
       // cout<<"shrinking= "<<shrinking<<endl;
    }
    fin.open(file_name,ios::in);



    infile = (char*)malloc(sizeof(char)*50);
    fileName = (char*)malloc(sizeof(char)*50);
    strcpy(infile,"input/");
    outfile = (char*)malloc(sizeof(char)*50);
    //shrinking=arg[4];
    // dependence_test=arg[3];
    strcpy(outfile,"output/");
    //  strcpy(dependence_test, "gcd");
    //  strcpy(shrinking, "simple");

    inputfile.open(file_name, ifstream::in);
    string file_name_output=strcat(strdup(file_name),"u");
    //  cout<<"output file "<<file_name_output<<endl;
    outputfile.open(strcat(strdup(file_name),"u"), ios::out );
    outputfile1.open(strcat(strdup(file_name),"u1"), ios::out );

    outputfile<<"#ifndef DATASET"<<endl<<"\t#define _NTHREAD 512"<<endl<<"\t#define _NBLOCK 65535"<<endl<<"#endif"<<endl<<endl;
    outputfile<<"#include<cuda.h>"<<endl<<"#include<time.h>"<<endl;
    string line;
    /* ifstream myfile ("config.txt");
     int time=0;
     if (myfile.is_open())
     {
         while (! myfile.eof() )
         {
             getline (myfile,line);
             char *cstr = new char[line.length() + 1];
             strcpy(cstr, line.c_str());

             if(time==0)
             {
                 dependence_test=cstr;
             }
             if(time==1)
             {
                 shrinking=cstr;
             }
             time++;

         }
     }*/
    //  cout<<"shrinking "<<shrinking<<endl;
    //  cout<<"dep "<<dependence_test<<endl;
         int multi_dim=0;
    vector<SgNode*> readRefs;
    vector<SgNode*> writeRefs;
    vector<SgNode*>:: iterator itr;
    string newFilename_output = "new_source_file.c";
    // outputfile.open (newFilename_output.c_str(), ios::out );

    // visitorTraversal ae;
    //ae.traverseInputFiles(project,preorder);
    // display1(head_loop);*/

    // set<string> :: iterator i;
    if(func)
        SgFunctionDefinition *defn = func->get_definition();

    /* set<SgInitializedName*> readNames, writeNames;
     if (!SageInterface::collectReadWriteVariables(func,readNames,writeNames))
     {
         ROSE_ASSERT(false);
     }
     set<SgInitializedName*>::iterator iter;
     for (iter=readNames.begin(); iter!=readNames.end(); iter++)
     {
          cout<<"read variable:"<<(*iter)->unparseToString()<<endl;
         var.insert((*iter)->unparseToString());
     }

    // ROSE_ASSERT(writeNames.size() ==4);

     for (iter=writeNames.begin(); iter!=writeNames.end(); iter++)
     {
           cout<<"written variable:"<<(*iter)->unparseToString()<<endl;
         var.insert((*iter)->unparseToString());
     }*/

    //for(ij=var.begin();ij!=var.end();ij+)
    // cout<<" vars are "<<*ij <<endl;
    Rose_STL_Container<SgNode*> nodeList= NodeQuery::querySubTree(project, V_SgFunctionDefinition);
    Rose_STL_Container<SgNode*>::const_iterator i = nodeList.begin();
    int k,f;
    // char c;
    int endline=0 ;
    int startLine;
    int m=0;
    int count1=0;
    for (; i!=nodeList.end(); ++i)
    {

        head_loop=NULL;
        intersect_RAW=NULL;
        intersect_WAW=NULL;
        intersect_RAW_shrinking=NULL;
        head=NULL;

        SgFunctionDefinition* defn=isSgFunctionDefinition(*i);
        //  visitorTraversal ae;
        // ae.traverseInputFiles(defn,preorder);
        set<string> :: iterator jk;

        Rose_STL_Container<SgNode*> loopvar= NodeQuery::querySubTree(*i, V_SgVariableDeclaration);
        Rose_STL_Container<SgNode*>::const_iterator ijk = loopvar.begin();

        for(; ijk!=loopvar.end(); ijk++)
        {
            SgVariableDeclaration* a=isSgVariableDeclaration(*ijk);
            SgInitializedNamePtrList ptrList = (a)->get_variables();
            SgInitializedNamePtrList::const_iterator j;
            for(j=ptrList.begin(); j!=ptrList.end(); j++)
            {
                //   cout<<" val "<<(*j)->unparseToString()<<endl;
                var.insert((*j)->unparseToString());
            }

        }

      //  for(jk=var.begin(); jk!=var.end(); jk++)
            //   cout<<"var = "<<(*jk)<<endl;
         //   cout<<"--------------------------found function---------------------"<<endl;

        Rose_STL_Container<SgNode*> forLoops = NodeQuery::querySubTree(defn,V_SgForStatement);
        
        for(Rose_STL_Container<SgNode*>::iterator iter = forLoops.begin(); iter!= forLoops.end(); iter++ )
        {
        multi_dim=0;
          SgForStatement* forLoop=isSgForStatement(*iter);
          std::vector<SgForStatement* > loops= SageInterface::querySubTree<SgForStatement>(forLoop,V_SgForStatement);
           SgBasicBlock* loopBody = isSgBasicBlock((forLoop)->get_loop_body());
         //  list<SgNode*> forList = NodeQuery::querySubTree( *iter, V_SgForStatement );
           SgStatementPtrList &init = forLoop->get_init_stmt();
           size_t loop_nest=loops.size();
          // cout<<"size = "<<loop_nest<<endl;
           
           Rose_STL_Container<SgNode*> arrayAccess = NodeQuery::querySubTree(forLoop,V_SgVarRefExp);
             for (Rose_STL_Container<SgNode*>::iterator iter = arrayAccess.begin(); iter!= arrayAccess.end(); iter++ )
{
  SgVarRefExp* a=isSgVarRefExp(*iter);
 // cout<<"var reaf "<<(*iter)->unparseToString()<<endl;
  SgArrayType* b=isSgArrayType(a->get_type());
 if(b)
 {int dim=getDimensionCount(b); 
 // cout<<"a = "<<b->unparseToString()<<endl;
  //cout<<"dim = "<<getDimensionCount(b)<<endl;
  if(dim>=2)
    multi_dim=1;
}
    
}
 
 

           if(loops.size()==1 && multi_dim==0)
           {

            cout<<"------------------loop normalization ---------------------------"<<endl;
            loop_normalization(*iter,var);
           cout<<"VariableDependenceDist during normalization "<<VariableDependenceDist<<endl;
            var_dep_dist[var_dep_dist_count++]=VariableDependenceDist;
           VariableDependenceDist='n';
            //  cout<<"after normalization "<<(*iter)->unparseToString();
          }
          else
           {// cout<<(*iter)->unparseToString()<<endl;
            while(loop_nest!=1){ iter++; loop_nest--;}}
         

        }
        cout<<"-----------done with normalization----------"<<endl;
       for(Rose_STL_Container<SgNode*>::iterator iter = forLoops.begin(); iter!= forLoops.end(); iter++ )
        {
            // printf ("Found a SgForStatement \n");
            // abc(*iter);

 multi_dim=0;
            // printf ("Found a SgForStatement \n");
          SgForStatement* forLoop=isSgForStatement(*iter);
          std::vector<SgForStatement* > loops= SageInterface::querySubTree<SgForStatement>(forLoop,V_SgForStatement);
           SgBasicBlock* loopBody = isSgBasicBlock((forLoop)->get_loop_body());
         //  list<SgNode*> forList = NodeQuery::querySubTree( *iter, V_SgForStatement );
          
           size_t loop_nest=loops.size();
          // cout<<"size = "<<loop_nest<<endl;
            Rose_STL_Container<SgNode*> arrayAccess = NodeQuery::querySubTree(forLoop,V_SgVarRefExp);
             for (Rose_STL_Container<SgNode*>::iterator iter = arrayAccess.begin(); iter!= arrayAccess.end(); iter++ )
{
  SgVarRefExp* a=isSgVarRefExp(*iter);
 // cout<<"var reaf "<<(*iter)->unparseToString()<<endl;
  SgArrayType* b=isSgArrayType(a->get_type());
 if(b)
 {int dim=getDimensionCount(b);  
 // cout<<"a = "<<b->unparseToString()<<endl;
 // cout<<"dim = "<<getDimensionCount(b)<<endl;
  if(dim>=2)
    multi_dim=1;
}
    
}
           if(loops.size()==1 && multi_dim==0)
           {
             SgForStatement* forLoop=isSgForStatement(*iter);
           SgBasicBlock* loopBody = isSgBasicBlock((forLoop)->get_loop_body());
          
            ref_function(*iter,defn);
          }
          else
          {
            while(loop_nest!=1)
            {
              iter++; loop_nest--;
            }
            // ref_function1(*iter,defn);
          }

        }


      //  cout<<"display head"<<endl;
        if(head)
       {// display(head);

        calculate_intersection_RAW(head);
      //  cout<<"after intersection  RAW"<<"\n";
      //  display(intersect_RAW);
        calculate_intersection_WAW(head);
      //  cout<<"after intersection  WAW"<<"\n";
       // display(intersect_WAW);
        calculate_intersection_RAW_for_srinking(head);
     //   cout<<"after intersection  RAW for cycle shrinking"<<"\n";
     //   display(intersect_RAW_shrinking);
      }


        for(Rose_STL_Container<SgNode*>::iterator iter = forLoops.begin(); iter!= forLoops.end(); iter++ )
        {
          multi_dim=0;
           SgForStatement* forLoop=isSgForStatement(*iter);
          std::vector<SgForStatement* > loops= SageInterface::querySubTree<SgForStatement>(forLoop,V_SgForStatement);
           SgBasicBlock* loopBody = isSgBasicBlock((forLoop)->get_loop_body());
         //  list<SgNode*> forList = NodeQuery::querySubTree( *iter, V_SgForStatement );
          
           size_t loop_nest=loops.size();
          // cout<<"size = "<<loop_nest<<endl;
            Rose_STL_Container<SgNode*> arrayAccess = NodeQuery::querySubTree(forLoop,V_SgVarRefExp);
             for (Rose_STL_Container<SgNode*>::iterator iter = arrayAccess.begin(); iter!= arrayAccess.end(); iter++ )
{
  SgVarRefExp* a=isSgVarRefExp(*iter);
 // cout<<"var reaf "<<(*iter)->unparseToString()<<endl;
  SgArrayType* b=isSgArrayType(a->get_type());
 if(b)
 {int dim=getDimensionCount(b); 
 // cout<<"a = "<<b->unparseToString()<<endl;
 // cout<<"dim = "<<getDimensionCount(b)<<endl;
  if(dim>=2)
    multi_dim=1;
}
    
}
           if(loops.size()==1 && multi_dim==0)
           {
            m=endline;
            k=startLine;
            loop* temp=intersect_RAW;
            loop* temp1=intersect_RAW_shrinking;
            while(temp1->loop_number!=loop_num)
                temp1=temp1->next;


            while(temp->loop_number!=loop_num)
                temp=temp->next;
            SgForStatement* node=isSgForStatement(*iter);
//if(node) DeleteSgTree(node);
             SgBasicBlock* loopBody = isSgBasicBlock((node)->get_loop_body());
             if(loopBody)
             {
            Sg_File_Info * startInfo = node->get_startOfConstruct();
            Sg_File_Info * endInfo = node->get_endOfConstruct();
            if(startInfo && endInfo)
            {
                startLine = startInfo->get_line();
                endline = endInfo->get_line();
                int startCol= startInfo->get_col();
                int endCol=endInfo->get_col();
                if(loop_num==0)
                    display_start(startLine);
                else
                    display_mid(k,m,startLine);
// if at least one line is referenced then we can't delete it
//for(int i = startLine; i <= endline ; i++) {
                // cout<<"Start = "<<startLine<<"end = "<<endline<<endl;

            }
            SgExpression* ivarast=NULL, *lbast=NULL, *ubast=NULL;
            SgScopeStatement* scope=node->get_scope();
            SgStatementPtrList & init=node->get_init_stmt();
            SgStatement* init1 = init.front();
            SgInitializedName* ivarname=NULL;
            if (isAssignmentStatement(init1, &ivarast, &lbast))
            {
                SgVarRefExp* var = isSgVarRefExp(ivarast);
                if (var)
                {
                    //cout<<"a"<<"\n";
                    ivarname = var->get_symbol()->get_declaration();
                    //   cout<<" loop lower bound= "<<(lbast)->unparseToString()<<"\n";
                    string b=(lbast)->unparseToString();

                    //  cout<<" loop variable= "<<(ivarname)->unparseToString()<<"\n";
                    //  cout<<"a ="<<a<<endl;

                }
            }
            VariableDependenceDist=var_dep_dist[loop_num];
            Dependence_Testing_Interface(dependence_test, temp,*iter,loop_num);
            CycleShrinking( shrinking, temp1,*iter,loop_num, var);
            //Simple_Loops_Code_Gen(temp,*iter,m,var);

            //  cout<<"DependencyExists  1= "<<DependencyExists<<endl;
            //  cout<<"VariableDependenceDist "<<VariableDependenceDist<<endl;
            var_loop(*iter,"i");
            //    outputfile<<"--------------------------loop number ------------ "<<loop_num<<endl;
            cuda_kernel_declaration_AFFINE(shrinking,*iter,(ivarname)->unparseToString(),loop_num);
            cuda_kernel_call_AFFINE(shrinking,*iter,(ivarname)->unparseToString(),loop_num);

            cuda_kernel_definition_AFFINE(shrinking,(ivarname)->unparseToString(),*iter,defn,loop_num);
            DependencyExists='n';
            VariableDependenceDist='n';
            Total_Phi=0;
            RefPair=NULL;
            DDVvector=NULL;
            lambda_var=NULL;


            loop_num++;}}
            else
            {
               while(loop_nest!=1)
            {
              iter++; loop_nest--;
            }
            }

        }

        //   cout<<"i= "<<i<<endl;
//fprintf(out, "start ");
        /*  if(count1==0 && m==0)
          {
              while(!fin.eof() && i<startLine  )
              {

                  fin.get(c);
                  //  cout<<"i = "<<i<<"startLine = "<<startLine<<"c= "<<c<<endl;
                  if(c=='\n')
                  {
                      i++;
                      outputfile<<endl;
                  }
                  else
                      outputfile<<c;
              }
              count1++;
              m++;
              VariableDependenceDist=var_dep_dist[loop_num];
              Dependence_Testing_Interface(dependence_test, temp,*iter,loop_num);
              CycleShrinking( shrinking, temp1,*iter,loop_num, var);
              //Simple_Loops_Code_Gen(temp,*iter,m,var);

              cout<<"DependencyExists  1= "<<DependencyExists<<endl;
              cout<<"VariableDependenceDist "<<VariableDependenceDist<<endl;
              var_loop(*iter,"i");
              cuda_kernel_declaration_AFFINE(shrinking,*iter,"i",loop_num);
              cuda_kernel_call_AFFINE(shrinking,*iter,"i",loop_num);
              // cuda_kernel_definition_AFFINE(shrinking,"i",*iter,defn,loop_num);
              DependencyExists='n';
              VariableDependenceDist='n';
              Total_Phi=0;
              RefPair=NULL;
              DDVvector=NULL;
              lambda_var=NULL;

          }
          //   cout<<"for loop is "<<(*iter)->unparseToString()<<endl;
          else if(m!=0 && count1!=0)
          {
              i=f;

              while(i<=k && !fin.eof())
              {
                  //   cout<<"k = "<<k<<"c = "<<c<< "i= "<<i<<endl;
                  fin.get(c);
                  if(c=='\n')
                  {
                      i++;
                      if(i>k) break;
                  }
              }
              while(!fin.eof() && i<startLine)
              {

                  fin.get(c);
                  //   cout<<"i in inner loop "<<i<<"c= "<<c<<endl;
                  if(c=='\n')
                  {
                      i++;
                      outputfile<<endl;
                  }
                  else outputfile<<c;
              }

              VariableDependenceDist=var_dep_dist[loop_num];
              Dependence_Testing_Interface(dependence_test, temp,*iter,loop_num);
              CycleShrinking( shrinking, temp1,*iter,loop_num, var);

              cout<<"DependencyExists 2 = "<<DependencyExists<<endl;
              cout<<"VariableDependenceDist "<<VariableDependenceDist<<endl;
              //Simple_Loops_Code_Gen(temp,*iter,m,var);
              var_loop(*iter,"i");
              cuda_kernel_declaration_AFFINE(shrinking,*iter,"i",loop_num);
              cuda_kernel_call_AFFINE(shrinking,*iter,"i",loop_num);
              // cuda_kernel_definition_AFFINE(shrinking,"i",*iter,defn,loop_num);
              DependencyExists='n';
              Total_Phi=0;
              VariableDependenceDist='n';
              RefPair=NULL;
              DDVvector=NULL;
              lambda_var=NULL;

          }



        }

        k=endline;
        f=startLine;
        loop_num++;
        }*/
        // i=f;

     var.clear();
    }

    /* loop_num=0;
     for(Rose_STL_Container<SgNode*>::iterator iter = forLoops.begin(); iter!= forLoops.end(); iter++ )
     {


         loop* temp=intersect_RAW;
         loop* temp1=intersect_RAW_shrinking;
         while(temp1->loop_number!=loop_num)
             temp1=temp1->next;


         while(temp->loop_number!=loop_num)
             temp=temp->next;

         VariableDependenceDist=var_dep_dist[loop_num];
         Dependence_Testing_Interface(dependence_test, temp,*iter,loop_num);
         CycleShrinking( shrinking, temp1,*iter,loop_num, var);
         //  cout<<"DependencyExists = "<<DependencyExists<<endl;
         // cout<<"VariableDependenceDist "<<var_dep_dist[loop_num]<<endl;
         //Simple_Loops_Code_Gen(temp,*iter,m,var);
         var_loop(*iter,"i");
         // cuda_kernel_declaration_AFFINE(shrinking,*iter,"i",loop_num);
         // cuda_kernel_call_AFFINE(shrinking,*iter,"i",loop_num);
         cout<<"DependencyExists code generatiopn= "<<DependencyExists<<endl;
         cout<<"VariableDependenceDist "<<VariableDependenceDist<<endl;
         cuda_kernel_definition_AFFINE(shrinking,"i",*iter,defn,loop_num);
         DependencyExists='n';
         Total_Phi=0;
         VariableDependenceDist='n';
         RefPair=NULL;
         DDVvector=NULL;
         lambda_var=NULL;

         loop_num++;
     }*/
    /* for(Rose_STL_Container<SgNode*>::iterator iter = forLoops.begin(); iter!= forLoops.end(); iter++ )
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
     }*/
//   m=0;

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
    end(startLine,endline);
    std::ofstream pt;
    std::ifstream ab;
    pt.open(strcat(strdup(file_name),"u"),ios::app);
    ab.open(strcat(strdup(file_name),"u1"),ios::in);
    char c;
    while(!ab.eof() )
    {

        ab.get(c);
        //cout<<"char is "<<c<<endl;
        //  cout<<"i in inner loop "<<i<<"c= "<<c<<endl;
        if(c=='\n')
        {

            //  i++;
            outputfile<<endl;
        }
        else outputfile<<c;
    }
    remove(strcat(strdup(file_name),"u1"));
    return backend(project);
}
