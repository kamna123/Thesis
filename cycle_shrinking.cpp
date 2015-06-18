
#include "rose.h"
#include "ds.hpp"
#include "cycle_shrinking.hpp"
#include "extShrinking.hpp"
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
struct Phi_Values *find_phi_values(string dep_string,struct Phi_Values *lambda,string loop_id_string)
{

    struct Phi_Values *phi_value,phi_value_temp,*lambda_temp;
    int flag=1,j;
    while(lambda!=NULL)
    {
        if(flag)
        {
            phi_value=(struct Phi_Values*)malloc(sizeof(struct Phi_Values));
            phi_value->loop_index=lambda->loop_index;
            phi_value->phi_val=lambda->phi_val;
            phi_value->next=NULL;
            lambda_temp=phi_value;
            flag=0;
        }
        else
        {
            lambda_temp->next=(struct Phi_Values*)malloc(sizeof(struct Phi_Values));
            lambda_temp->next->loop_index=lambda->loop_index;
            lambda_temp->next->phi_val=lambda->phi_val;
            lambda_temp->next->next=NULL;
            lambda_temp=lambda_temp->next;
        }
        lambda=lambda->next;
    }
//cout<<"dep_ size = "<<dep_string<<endl;
    int constt=0,var,sign=1;
    string loop_id;
    lambda_temp=phi_value;
    for(j=0; dep_string[j];)
    {
        stringstream ss;
        string s;
        if(isdigit(dep_string[j])==1)
        {
            while(isdigit(dep_string[j])==1 && dep_string[j])
            {
                ss<<dep_string[j] ;
                j++;
            }
            ss>>s;
        }
        else
        {
            ss<<dep_string[j] ;
            ss>>s;
            j++;
        }
        j--;
        /// cout<<"string in coef and j "<<s<<" "<<j<<endl;
        if(!loop_id_string.compare(s))

        {
            // cout<<"-----cond 1-----"<<endl;
            loop_id=s;
            stringstream a;
            string b;
            a<<dep_string[j+1];
            a>>b;
            if(!b.compare("*") && dep_string[j+1]!='\0')
                //  {cout<<"-----cond 2-----"<<endl;}
                j=j+2;
        }
        else if(!(s.compare("*")));//{cout<<"-----cond 3-----"<<endl;}
        else if(!(s.compare("+")))
        {
            //cout<<"-----cond 4-----"<<endl;
            sign=1;
        }
        else if(!(s.compare("-")))
        {
            //cout<<"-----cond 5-----"<<endl;
            sign=-1;
        }
        else
        {
            //cout<<"-----cond 6-----"<<endl;
            const char *cstr = s.c_str();
            var=atoi(cstr);
            stringstream a;
            string b;
            a<<dep_string[j+1];
            a>>b;
            if((b.compare("*") &&  dep_string[j+1]!='\0') || dep_string[j+1]=='\0')
            {
                //  cout<<"b is "<<b<<" "<<"dep_string[j+1 ]= "<<dep_string[j+1]<<endl;
                // cout<<"-----cond 7-----"<<endl;
                constt=constt+(var*sign);
            }

        }
        j++;

    }
    while(lambda_temp!=NULL)
    {
        const char *cstr = loop_id_string.c_str();
        if(!strcmp(cstr,lambda_temp->loop_index))
            lambda_temp->phi_val=constt;
        lambda_temp=lambda_temp->next;
    }
    return phi_value;
}
struct Phi_Values *Simple_Loops_Code_Gen(loop* write,SgNode* n,int loop_number,set<string> var)
{
    struct Phi_Values *lambda,*lambda_temp,*read_phi_values,*write_phi_values,*write_phi_values_temp;
    int flag=1;
    SgForStatement* ab=isSgForStatement(n);
    SgExpression* ivarast=NULL, *lbast=NULL, *ubast=NULL, *stepast=NULL;
    SgStatementPtrList & init=ab->get_init_stmt();
    SgStatement* init1 = init.front();
    SgInitializedName* ivarname=NULL;
    if(isAssignmentStatement(init1, &ivarast, &lbast))
    {
        SgVarRefExp* var = isSgVarRefExp(ivarast);
        if (var)
        {
            ivarname = var->get_symbol()->get_declaration();
        }
    }
    string loop_id_string=(ivarname)->unparseToString();
    char* loop_id = strdup(loop_id_string.c_str());
    if(flag)
    {
        lambda=(struct Phi_Values*)malloc(sizeof(struct Phi_Values));
        lambda->loop_index=loop_id;
        //printf(" lambda->loop_index = %s \n", lambda->loop_index);
        //printf(" \n");
        lambda->phi_val=0;
        lambda->next=NULL;
        lambda_temp=lambda;
        flag=0;
    }
    else
    {
        lambda_temp->next=(struct Phi_Values*)malloc(sizeof(struct Phi_Values));
        lambda_temp->next->loop_index=loop_id;
        lambda_temp->next->phi_val=0;
        lambda_temp->next->next=NULL;
        lambda_temp=lambda_temp->next;
    }

    Total_Phi++;
    dep_data* dep=write->dep;
    int constt=0;
    // cout<<"in sgnode"<<write->dep->write_ref->unparseToString();
    while(dep)
    {
       // cout<<"-------------------in dep ---------------"<<endl;
        SgExpression* rhs_read;
        SgExpression* rhs_write;
        rhs_read = isSgBinaryOp(dep->read_ref[0])->get_rhs_operand();
        rhs_write = isSgBinaryOp(dep->write_ref[0])->get_rhs_operand();
        string write_size=rhs_write->unparseToString();
        string read_size=rhs_read->unparseToString();
        //    cout<<"write_size in cycle"<<write_size<<endl;
        // cout<<"read_size in cycle"<<read_size<<endl;
        write_phi_values=find_phi_values(write_size,lambda,loop_id_string);
        //  printf("write_phi_values = %d\n",write_phi_values->phi_val);
        //    printf("lambda_write_phi_values = %d\n",lambda->phi_val);
        read_phi_values=find_phi_values(read_size,lambda,loop_id_string);

        //   printf("read_phi_values = %d\n",read_phi_values->phi_val);
        //  printf("lambda_read_phi_values = %d\n",lambda->phi_val);
        lambda_temp=lambda;
        write_phi_values_temp=write_phi_values;

        while(read_phi_values!=NULL)
        {
            constt=abs((read_phi_values->phi_val)-(write_phi_values_temp->phi_val));
            //  printf("in read_phi_values=%d,%s: %d,%s %d\n",constt,read_phi_values->loop_index,read_phi_values->phi_val,write_phi_values->loop_index,write_phi_values->phi_val);
            lambda_temp->phi_val=(lambda_temp->phi_val==0||lambda_temp->phi_val>constt)?constt:lambda_temp->phi_val;
            read_phi_values=read_phi_values->next;
            write_phi_values_temp=write_phi_values_temp->next;
            lambda_temp=lambda_temp->next;
        }
        dep=dep->next;

    }
    lambda_temp=lambda;
    cout<<"-------------------- Reduction Factor (Lambda): <";
    while(lambda_temp!=NULL)
    {
        // cout<<"in lembda_temp"<<endl;
        //printf( "phi value: %s, %d\n",lambda_temp->loop_index,lambda_temp->phi_val);
        cout<<lambda_temp->phi_val;
        lambda_temp=lambda_temp->next;
        if(lambda_temp)
            cout<<","<<endl;
    }
    cout<< ">"<<endl;
    cout<<"-------------------- total phi: <"<<Total_Phi<<endl;
    return lambda;
}
void CycleShrinking( char *shrinking,loop* write,SgNode* n,int loop_number,set<string> var)
{
    if(VariableDependenceDist=='n')
    {
        if((!strcmp(shrinking,"simple")))

        {
            lambda_var=Simple_Loops_Code_Gen(write, n,loop_number, var);
            printf("-------------------total phi=  %d-------------------------\n",Total_Phi);
        }

        else if(!strcmp(shrinking,"extShrinking1"))
        {
            lambda_var=Simple_Loops_Code_Gen(write, n,loop_number, var);
            printf("-------------------total phi=  %d-------------------------\n",Total_Phi);
        }
        //extCS_ConstantDistance_Lambda(read_var,write_var,loop_index_new,stmt_var);
        else
        {
            cout<< "Oops!! Wrong input. Please give simple or extShrinking1 as input"<<endl;
            exit(0);
        }
    }
    else
    {
        if(!strcmp(shrinking,"extShrinking2"))
        {
            cout<<"ext shrinking applied on Single nested loop\n";
            extCS_VariableDistance_Lambda( write,n,loop_number,var);
            printf("-------------------total phi=  %d-------------------------\n",Total_Phi);
        }
        else
        {
            cout<< "Oops!! Code Generation for Variable Dependence Distance can only happen through Extended Cycle Shrinking \n";
            exit(0);
        }

    }
}