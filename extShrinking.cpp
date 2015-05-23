#include "rose.h"
#include "ds.hpp"
#include <iostream>
#include <set>
#include <vector>
#include <iterator>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <cstdio>
#include <cstdlib>
using namespace std;
using namespace SageInterface;
using namespace SageBuilder;
void CalculateLambda(string a,int *lambda,string loop_id_string)
{
    int j=0;
    int constt,sign=1,index=1;
    //   string loop_id_string= get_lower_bound(loop_id);
    for(j=0; a[j]!='\0'; )
    {
        stringstream ss;
        string s;


        if(isdigit(a[j])==1)
        {
            while(isdigit(a[j])==1 && a[j])
            {
                ss<<a[j] ;
                j++;
            }
            ss>>s;
        }
        else

        {
            ss<<a[j] ;
            ss>>s;
            j++;
        }
        j--;
        cout<<"depstring is "<<s<<endl;
        if(!(s.compare("*")));
        else if(!(s.compare("+")))
        {
            sign=1;
        }
        else if(!(s.compare("-")))
        {
            sign=-1;
        }
        else  if(!loop_id_string.compare(s))
        {
            index=1;
            printf("index=%d\n",index);
            stringstream k,m;
            string b,c;
            k<<a[j+1];
            k>>b;
            m<<a[j+2];
            m>>c;
            if(b!="\0" && (!b.compare("*") ))
            {
                const char *cstr = c.c_str();
                int var=atoi(cstr);
                lambda[index]=sign*var;
                j=j+2;
            }
            else
            {
                lambda[index]=sign;
            }
        }
        else
        {
            const char *cstr = s.c_str();
            int   var=atoi(cstr);
            constt=sign*var;
            stringstream k,m;
            string b,c;
            k<<a[j+1];
            k>>b;
            m<<a[j+2];
            m>>c;
            if(b!="\0" && (!b.compare("*") ) && (!loop_id_string.compare(c)) )
            {
                index=1;
                printf("index 1=%d\n",index);
                lambda[index]=constt;
                j=j+2;
            }
            else
            {
                lambda[0]=lambda[0]+constt;

                printf(" value:%d, const=%d\n",lambda[0],constt);
            }
        }


        j++;
    }
}
void extCS_VariableDistance_Lambda(loop* write,SgNode* n,int loop_number,set<string> var)
{
    SgForStatement* ab=isSgForStatement(n);
    SgExpression* ivarast=NULL, *lbast=NULL, *ubast=NULL, *stepast=NULL;
    SgStatementPtrList & init=ab->get_init_stmt();
    SgStatement* init1 = init.front();
    SgInitializedName* ivarname=NULL;
    if (isAssignmentStatement(init1, &ivarast, &lbast))
    {
        SgVarRefExp* var = isSgVarRefExp(ivarast);
        if (var)
        {
            ivarname = var->get_symbol()->get_declaration();
        }
    }
    string loop_id_string=(ivarname)->unparseToString();
    char* loop_id = strdup(loop_id_string.c_str());
    char *readVar,*writeVar;

    struct ReferencePair *tailRefPair=NULL,*refPairTemp=NULL;
    struct DDV *tailDDV=NULL,*headDDV=NULL,*DDVtemp=NULL;
    struct DDV_Values *headDDVvalue=NULL,*tailDDVvalue=NULL,*DDVvaluesTemp=NULL;
    dep_data* dep=write->dep;
    int constt=0;
    // cout<<"in sgnode"<<write->dep->write_ref->unparseToString();
    while(dep)
    {
        SgExpression* rhs_read;
        SgExpression* rhs_write;
        rhs_read = isSgBinaryOp(dep->read_ref[0])->get_rhs_operand();
        rhs_write = isSgBinaryOp(dep->write_ref[0])->get_rhs_operand();
        string write_size=rhs_write->unparseToString();
        string read_size=rhs_read->unparseToString();
        cout<<"write size "<<write_size<<endl;
        cout<<"read size"<<read_size<<endl;
        refPairTemp=(struct ReferencePair*)malloc(sizeof(struct ReferencePair));
        refPairTemp->next=NULL;
        refPairTemp->ddv=NULL;
        if(tailRefPair)
        {
            tailRefPair->next=refPairTemp;
            tailRefPair=refPairTemp;
        }
        else
            RefPair=tailRefPair=refPairTemp;
        // loopTemp=loop_id;
        tailDDV=NULL;
        headDDV=NULL;
        noOfNestedLoops=0;
        //  while(loopTemp)
        {
            //printf(" In loop temp \n");
            //   printf(" readString->string= %s \n", readString->string);
            DDVtemp=(struct DDV*)malloc(sizeof(struct DDV));
            DDVtemp->ddv_values=NULL;
            DDVtemp->next=NULL;
            if(tailDDV)
            {
                tailDDV->next=DDVtemp;
                tailDDV=DDVtemp;
            }
            else
                DDVvector=headDDV=tailDDV=DDVtemp;
            noOfNestedLoops++;
            // loopTemp=loopTemp->next;
        }
        printf("  noOfNestedLoops=%d\n",  noOfNestedLoops);
        tailRefPair->ddv=headDDV;
        DDVtemp=headDDV;
        while(DDVtemp)
        {
            DDVvaluesTemp=(struct DDV_Values*)malloc(sizeof(struct DDV_Values));
            DDVvaluesTemp->value=0;
            DDVvaluesTemp->next=NULL;
            headDDVvalue=tailDDVvalue=DDVvaluesTemp;
            // loopTemp=loop_id;
            // while(loopTemp)
            {
                tailDDVvalue->next=(struct DDV_Values*)malloc(sizeof(struct DDV_Values));
                tailDDVvalue->next->value=0;
                tailDDVvalue->next->next=NULL;
                tailDDVvalue=tailDDVvalue->next;
                // loopTemp=loopTemp->next;
            }
            tailDDVvalue->next=(struct DDV_Values*)malloc(sizeof(struct DDV_Values));
            tailDDVvalue->next->value=0;
            tailDDVvalue->next->next=NULL;
            DDVtemp->ddv_values=headDDVvalue;
            DDVtemp=DDVtemp->next;
        }
        dep=dep->next;
    }
    /************************* calculating DDV **********************************/

    int Fvalue[noOfNestedLoops+2],Gvalue[noOfNestedLoops+2],temp;
    dep=write->dep;
    refPairTemp=RefPair;
    while(dep)
    {
        DDVtemp=refPairTemp->ddv;
        temp=1;
        SgExpression* rhs_read;
        SgExpression* rhs_write;
        rhs_read = isSgBinaryOp(dep->read_ref[0])->get_rhs_operand();
        rhs_write = isSgBinaryOp(dep->write_ref[0])->get_rhs_operand();
        string write_size=rhs_write->unparseToString();
        string read_size=rhs_read->unparseToString();
        cout<<"write size "<<write_size<<endl;
        cout<<"read size"<<read_size<<endl;
        int i;
        for( i=0; i<=(noOfNestedLoops+1); i++)
        {
            Fvalue[i]=0;
            Gvalue[i]=0;
        }
        CalculateLambda(rhs_read->unparseToString(),Gvalue,loop_id_string);
        CalculateLambda(rhs_write->unparseToString(),Fvalue,loop_id_string);
        //  cout<<"back "<<endl;
        printf("noOfNestedLoops=%d",noOfNestedLoops);
        Fvalue[noOfNestedLoops+1]=Gvalue[temp];
        for(i=0; i<=noOfNestedLoops; i++)
        {
            Fvalue[i]=Fvalue[i]-Gvalue[i] ;
            printf("fvalue[%d]=%d\n",i,Fvalue[i]);
        }
        DDVvaluesTemp=DDVtemp->ddv_values;
        i=0;
        while(DDVvaluesTemp)
        {
            DDVvaluesTemp->value=Fvalue[i++];
            printf(" DDVvaluesTemp->value=%d\n", DDVvaluesTemp->value);
            DDVvaluesTemp=DDVvaluesTemp->next;

        }
        temp++;
        DDVtemp=DDVtemp->next;

        refPairTemp=refPairTemp->next;
        //cout<<"loop "<<endl;
        dep=dep->next;

    }
    /*****************************************************************************************************************/

    // For printing the value of reference pair
    refPairTemp=RefPair;
    while(refPairTemp)
    {
        DDVtemp=refPairTemp->ddv;
        while(DDVtemp)
        {
            DDVvaluesTemp=DDVtemp->ddv_values;
            while(DDVvaluesTemp)
            {
                printf("3: %d\n",DDVvaluesTemp->value);
                DDVvaluesTemp=DDVvaluesTemp->next;
            }
            DDVtemp=DDVtemp->next;
        }
        refPairTemp=refPairTemp->next;
    }
}
/*int main(int argc, char * argv[])
{
     vector<SgNode*> readRefs;
     vector<SgNode*> writeRefs;
     vector<SgNode*>:: iterator itr;
    SgProject *project = frontend (argc, argv);
    SgFunctionDeclaration* func = SageInterface::findMain(project);

     set<string> var;
     set<string> :: iterator i;

   SgFunctionDefinition *defn = func->get_definition();

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

 // ROSE_ASSERT(writeNames.size() ==4);

  for (iter=writeNames.begin();iter!=writeNames.end();iter++)
  {   //  cout<<"written variable:"<<(*iter)->unparseToString()<<endl;
        var.insert((*iter)->unparseToString());
}
   //for(i=var.begin();i!=var.end();i++)
  // cout<<" "<<*i ;
int m=0;
 Rose_STL_Container<SgNode*> forLoops = NodeQuery::querySubTree(defn,V_SgForStatement);
    for(Rose_STL_Container<SgNode*>::iterator iter = forLoops.begin(); iter!= forLoops.end(); iter++ )
{
   loop* temp=intersect_RAW_shrinking;
     while(temp->loop_number!=m)
      temp=temp->next;
    cout<<"--------in loop ------------"<<endl;
extCS_VariableDistance_Lambda(temp,*iter,m,var);
 // temp=temp->next;
m++;
}
 return backend(project);
 }*/
