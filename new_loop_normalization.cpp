
#include "rose.h"
#include "ds.hpp"
#include "new_loop_normalization.hpp"

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
static int loop_number=0;

string store_upper[100];
void copy_into_struct(string a, StringNode** temp)
{
    StringNode* curr=(struct StringNode*)malloc(sizeof(struct StringNode));
    StringNode* temp1=curr;
    int j=0;
    while(a[j])
    {
        stringstream ss;
        string s;
        //cout<<"storing into struct"<<endl;
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

        char * S = new char[s.length() + 1];
        std::strcpy(S,s.c_str());
        curr->a=S;
        //  cout<<"s = "<<S<<endl;
        if(a[j])
        {
            curr->next=(struct StringNode*)malloc(sizeof(struct StringNode));
            curr=curr->next;
        }
        else
            curr->next=NULL;

    }
    *temp=temp1;

}
void display(StringNode* head)
{
    while(head)
    {
        cout<<" "<<head->a;
        head=head->next;
    }
}
string store(StringNode* head)
{
    string b;
    while(head)
    {
        string s(head->a);
        b.append(s);
        head=head->next;
    }
    return b;
}
void loop_normalization(SgNode* n,set<string> var)
{
    /* string abc="abcd";
     StringNode* head=NULL;
     copy_into_struct( abc,&head);
     cout<<"display head"<<endl;
     display(head);*/
    const char *a,*b,*c;
    int a_val=0,c_val=0,prev_val=1,sign=1,flag=0;
    SgForStatement* ab=isSgForStatement(n);
    SgBasicBlock *block = isSgBasicBlock (n);
    SgExpression* ivarast=NULL, *lbast=NULL, *ubast=NULL, *stepast=NULL;
    SgScopeStatement* scope=ab->get_scope();
    SgStatementPtrList & init=ab->get_init_stmt();
    SgStatement* init1 = init.front();
    SgInitializedName* ivarname=NULL;
    vector<SgNode*> reads;
    vector<SgNode*> writes;
    SgExpression* rhs;
    SgExpression* lhs;
    vector<SgNode*>:: iterator itr;
    char front[100];
    StringNode* prev=NULL;
    StringNode* last=NULL;
    StringNode* temp=NULL;
    StringNode* temp2=NULL;
    StringNode* temp3=NULL;
    StringNode* temp4=NULL;
    StringNode* curr=NULL;
    char VariableDependenceDist='n';
    if (isAssignmentStatement(init1, &ivarast, &lbast))
    {
        SgVarRefExp* var = isSgVarRefExp(ivarast);
        if (var)
        {
            //cout<<"a"<<"\n";
            ivarname = var->get_symbol()->get_declaration();
            //   cout<<" loop lower bound= "<<(lbast)->unparseToString()<<"\n";
            string b=(lbast)->unparseToString();
            a=b.c_str();
            //  cout<<" loop variable= "<<(ivarname)->unparseToString()<<"\n";
            //  cout<<"a ="<<a<<endl;
            a_val=atoi(a);

        }
    }
    string loop_id_string=(ivarname)->unparseToString();
    char* loop_id = strdup(loop_id_string.c_str());
    SgBinaryOp* test = isSgBinaryOp(ab->get_test_expr());
    ubast = test->get_rhs_operand();
    cout<<" loop upper bound= "<<(test)->unparseToString()<<"\n";
    string b1=(ubast)->unparseToString();
    b=b1.c_str();
    // cout<<"b ="<<b<<endl;
    SgExpression* incr = ab->get_increment();
    // cout<<" loop increment= "<<(incr)->unparseToString()<<"\n";
    stepast=isSgBinaryOp(incr)->get_rhs_operand();
    //    cout<<"stepast = "<<(stepast)->unparseToString()<<endl;
    SgExpression*  stepast1=isSgBinaryOp(stepast)->get_rhs_operand();
    string k=stepast->unparseToString();
    size_t found=k.find("+");
    //  string op;
    if(found!=string::npos)
        op="+";
    else
        op="-";
    ab->set_increment( buildVarRefExp((ivarname)->unparseToString()+"="+(ivarname)->unparseToString()+"+"+"1", scope));
    string b2=(stepast1)->unparseToString();
    c=b2.c_str();
    //  cout<<"c ="<<c<<endl;
    b_val=atoi(b);

    c_val=atoi(c);
    setLoopLowerBound(ab,  buildVarRefExp("0", scope));
    // setLoopUpperBound(a,  buildVarRefExp("("+(ubast)->unparseToString()+"-"+(lbast)->unparseToString()+")"+"/"+(stepast1)->unparseToString(),scope));
    setLoopStride(ab,buildVarRefExp("1",scope));


    SgBinaryOp* test1 = isSgBinaryOp(test->get_rhs_operand());
    //   cout<<" loop operator= "<<(testvar)->unparseToString()<<"\n";
    cout<<" loop test= "<<(test)->unparseToString()<<"\n";
    cout<<" op ="<<op<<endl;
    cout<<"b_val "<<b_val<<endl;
    cout<<"a_val "<<a_val<<endl;
    if(op.compare("+")==0)
    {
        //cout<<"true"<<endl;
        b_val=(b_val-a_val)/c_val;
    }
    else
        b_val=(a_val-b_val)/c_val;
    //  string rel_op;
    string loop_test;
    loop_test=test->unparseToString();
    if(loop_test.find(">")!=string::npos)
        rel_op="<";

    if(loop_test.find(">=")!=string::npos)
        rel_op="<=";

    if(loop_test.find("<")!=string::npos)
    {
        //cout<<"abc"<<endl;
        rel_op="<";
    }
    if(loop_test.find("<=")!=string::npos)
        rel_op="<=";
    cout<<"rel_op "<<rel_op<<endl;
    cout<<"b_val "<<b_val<<endl;
    stringstream ss;
    ss << b_val;
    string str = ss.str();
    store_upper[loop_number++]=str;
    ab->  set_test_expr(buildVarRefExp((ivarname)->unparseToString()+rel_op+str, scope)) ;
    //  setLoopUpperBound(ab,  buildVarRefExp(str,scope)
    //  test = isSgBinaryOp(ab->get_test_expr());
    // ubast = test->get_rhs_operand();


    string result;
    SgBasicBlock* loopBody = isSgBasicBlock(ab->get_loop_body());
    Rose_STL_Container<SgStatement*> forLoops = loopBody->get_statements();
    //    for(Rose_STL_Container<SgStatement*>::iterator iter = forLoops.begin(); iter!= forLoops.end(); iter++ )
    {
        //  SgScopeStatement* scope=(*iter)->get_scope();
        // cout<<" statements are "<< (*iter)->unparseToString()<<"\n";

        SageInterface::collectReadWriteRefs(ab, reads, writes);
        for (itr=reads.begin(); itr!=reads.end(); itr++)
        {
            if(isSgBinaryOp(*itr)!=NULL)
            {
                rhs = isSgBinaryOp(*itr)->get_rhs_operand();
                lhs=  isSgBinaryOp(*itr)->get_lhs_operand();
                string stmt_string2=rhs->unparseToString();
                stmt_string2.erase(remove(stmt_string2.begin(), stmt_string2.end(),')'),stmt_string2.end());
                stmt_string2.erase(remove(stmt_string2.begin(), stmt_string2.end(),'('),stmt_string2.end());
                stmt_string2.erase(remove(stmt_string2.begin(), stmt_string2.end(),' '),stmt_string2.end());
                //  cout<<"stmt_string2 "<<stmt_string2<<endl;
                prev=NULL;
                curr=NULL;
                last=NULL;
                temp=NULL;
                temp2=NULL;
                prev_val=1;
                sign=1;
                StringNode* stmt_string=NULL;
                copy_into_struct(stmt_string2,&stmt_string);
                temp2=stmt_string;
                display(stmt_string);
                int j=0;
                int occ=0;
                flag=0;
                while(stmt_string!=NULL)
                {
                    printf("stmt_size->a:%s\n",stmt_string->a);
                    while(stmt_string!=NULL && occ==0 && stmt_string->next!=NULL)
                    {
                        // cout<<stmt_string->a<<endl<<stmt_string->next->a<<endl<<stmt_string->next->next->a<<endl;
                        if(((strcmp(stmt_string->next->a,"*")==0) &&(stmt_string->next->next && strcmp(stmt_string->next->next->a,loop_id)==0) )||((strcmp(stmt_string->next->a,"*")==0) &&(strcmp(stmt_string->a,loop_id)==0) ))
                        {
                            cout<<"----------b---------"<<endl;
                            break;


                        }
                        else if(strcmp(stmt_string->a,loop_id)==0) break;
                        else
                        {
                            strcat (front,stmt_string->a);
                            cout<<"----------a---------"<<endl;
                            if(!strcmp(stmt_string->a,"+"))
                            {
                                sign=1;
                                printf("sign=1\n");
                            }
                            else if(!strcmp(stmt_string->a,"-"))
                            {
                                sign=-1;
                                printf("sign=-1\n");
                            }

                            stmt_string=stmt_string->next;
                        }
                        // cout<<"out of loop "<<endl;
                    }
                    occ=1;
                    cout<<":front"<<front<<endl;
                    if(!strcmp(stmt_string->a,"+"))
                    {
                        sign=1;
                        printf("sign=1\n");
                    }
                    else if(!strcmp(stmt_string->a,"-"))
                    {
                        sign=-1;
                        printf("sign=-1\n");
                    }
                    if(stmt_string->next&&(!strcmp(stmt_string->next->a,"*"))) //comes when stmt_string2 points to 2*i
                    {
                        printf("sign=*\n");
                        occ=1;
                        if((strcmp(stmt_string->a,loop_id))&&(strcmp(stmt_string->a,"*"))&&(strcmp(stmt_string->a,"+"))&&(strcmp(stmt_string->a,"-"))&&(!strcmp(stmt_string->next->next->a,loop_id)))
                        {

                            //   printf("stmt_string2->string= %s,loop_temp->loopIndex->string= %s,stmt_string2->next->next->string=%s\n",stmt_string->a,loop_id,stmt_string->next->next->a);
                            //     cout<<"----------1st cond----------"<<endl;
                            VariableDependenceDist='y';
                            prev_val=atoi(stmt_string->a);                     // pre_val: 2 (out of 2*i)
                            //    printf("prev_val = %d\n",prev_val);
                            if(a_val)
                            {
                                curr=(struct StringNode*)malloc(sizeof(struct StringNode));
                                curr->a=(char*)malloc(sizeof(char)*10);

                                sprintf(curr->a, "%d", a_val*prev_val);
                                //   printf("curr->a = %s\n",curr->a);
                                //create node curr with value 4*2
                                last=(struct StringNode*)malloc(sizeof(struct StringNode));
                                if(op.compare("+")==0)
                                {
                                    if (sign>0) last->a="+";
                                    else last->a="-";
                                }
                                else
                                {
                                    if(sign>0) last->a="-";
                                    else last->a="+";
                                }
                                // create node last with value '-'
                                curr->next=last;                                   // curr node will become '8'->'-'
                            }
                            stmt_string->a=(char*)malloc(sizeof(char)*10);
                            sprintf(stmt_string->a, "%d", c_val*prev_val); // update 2*i to 6*2*i
                            if(curr)
                                curr->next->next=stmt_string;
                            if(curr)
                            {
                                if(prev)
                                    prev->next=curr;
                                //else
                                //stmt_string=curr;
                            }
                            stmt_string=stmt_string->next->next;



                        }

                        else    if(!(strcmp(stmt_string->a,loop_id))&&(strcmp(stmt_string->next->next->a,"*"))&&(strcmp(stmt_string->next->next->a,"+"))&&(strcmp(stmt_string->next->next->a,"-"))&&(strcmp(stmt_string->next->next->a,loop_id)))
                        {
                            //   printf("stmt_string2->string= %s,loop_temp->loopIndex->string= %s,stmt_string2->next->next->string=%s\n",stmt_string->a,loop_id,stmt_string->next->next->a);
                            cout<<"----------2nd cond----------"<<endl;
                            VariableDependenceDist='y';
                            prev_val=atoi(stmt_string->next->next->a);                     // pre_val: 2 (out of 2*i)
                            //  printf("prev_val = %d\n",prev_val);
                            if(a_val)
                            {
                                curr=(struct StringNode*)malloc(sizeof(struct StringNode));
                                curr->a=(char*)malloc(sizeof(char)*10);

                                sprintf(curr->a, "%d", a_val*prev_val);
                                //    printf("curr->a = %s\n",curr->a);
                                //create node curr with value 4*2
                                last=(struct StringNode*)malloc(sizeof(struct StringNode));
                                if(op.compare("+")==0)
                                {
                                    if (sign>0) last->a="+";
                                    else last->a="-";
                                }
                                else
                                {
                                    if(sign>0) last->a="-";
                                    else last->a="+";
                                }
                                // create node last with value '-'
                                curr->next=last;                                   // curr node will become '8'->'-'
                            }
                            temp=(struct StringNode*)malloc(sizeof(struct StringNode));
                            temp->a=(char*)malloc(sizeof(char)*10);
                            sprintf(temp->a, "%d", c_val*prev_val);
                            //temp->size=NULL;
                            last=(struct StringNode*)malloc(sizeof(struct StringNode));
                            last->a="*";
                            //last->size=NULL;
                            temp->next=last;
                            //printf("%s, %s\n",temp->string,last->string);
                            if(curr)
                                curr->next->next=temp;
                            else
                                curr=temp;
                            if(curr)
                            {
                                if(prev)
                                    prev->next=curr;
                                // else
                                // stmt_string=curr;
                                last->next=stmt_string;
                            }
                            stmt_string->next=stmt_string->next->next->next;

                        }

                    }
                    else  if(!(strcmp(stmt_string->a,loop_id)))
                    {
                        occ=1;
                        cout<<"----------3rd cond----------"<<endl;
                        if(a_val)
                        {
                            curr=(struct StringNode*)malloc(sizeof(struct StringNode));
                            curr->a=(char*)malloc(sizeof(char)*10);
                            char buffer[100];
                            snprintf(buffer, sizeof(buffer), "%d", a_val);
                            curr->a=buffer;

                            //  cout<<"a = "<<buffer<<endl;
                            last=(struct StringNode*)malloc(sizeof(struct StringNode));
                            if(op.compare("+")==0)
                            {
                                if (sign>0) last->a="+";
                                else last->a="-";
                            }
                            else
                            {
                                if(sign>0) last->a="-";
                                else last->a="+";
                            }
                            // create node last with value '-'
                            curr->next=last;                                   // curr node will become '8'->'-'
                        }
                        if(c_val!=1)
                        {
                            temp=(struct StringNode*)malloc(sizeof(struct StringNode));
                            temp->a=(char*)malloc(sizeof(char)*10);
                            temp->a=strdup(c);
                            //temp->size=NULL;
                            last=(struct StringNode*)malloc(sizeof(struct StringNode));
                            last->a="*";
                            //last->size=NULL;
                            temp->next=last;
                            //  printf("%s, %s\n",temp->a,last->a);
                            if(curr)
                                curr->next->next=temp;
                            else
                                curr=temp;
                        }
                        if(curr)
                        {
                            if(prev)
                                prev->next=curr;
                            //  else
                            //   stmt_string=curr;
                            last->next=stmt_string;
                        }
                        //  stmt_string->next=stmt_string->next->next->next;

                    }
                    temp4=(struct StringNode*)malloc(sizeof(struct StringNode));
                    if(curr!=NULL && isdigit(front[0] ))
                    {
                        temp4->a=front;
                        cout<<"temp->a"<<temp4->a<<endl;
                        flag=1;
                        temp4->next=curr;
                        temp3=temp4;
                        cout<<"string is (curr!=NULL)"<<endl;
                        result=store(temp3);
                        cout<<result<<endl;
                        SgExpression* exp= buildVarRefExp(result);
                        replaceExpression(rhs,exp);
                    }
                    else if(curr!=NULL)
                    {
                        temp3=curr;
                        /* if(temp!=NULL)
                        {
                         cout<<"string is "<<endl;
                        display(temp3);
                         }*/
                    }

                    prev=stmt_string;

                    memset(&front[0], 0, sizeof(front));

                    curr=NULL;
                    last=NULL;

                    stmt_string=stmt_string->next;
                }
                if(flag==0)
                {
                    cout<<"string is "<<endl;
                    result=store(temp3);
                    SgExpression* exp= buildVarRefExp(result);
                    replaceExpression(rhs,exp);
                    cout<<result<<endl;
                    // display(temp3);
                }
                // result.clear();
            }
        }
        for (itr=writes.begin(); itr!=writes.end(); itr++)
        {
            if(isSgBinaryOp(*itr)!=NULL)
            {
                rhs = isSgBinaryOp(*itr)->get_rhs_operand();
                lhs=  isSgBinaryOp(*itr)->get_lhs_operand();
                string stmt_string2=rhs->unparseToString();
                stmt_string2.erase(remove(stmt_string2.begin(), stmt_string2.end(),')'),stmt_string2.end());
                stmt_string2.erase(remove(stmt_string2.begin(), stmt_string2.end(),'('),stmt_string2.end());
                stmt_string2.erase(remove(stmt_string2.begin(), stmt_string2.end(),' '),stmt_string2.end());
                //  cout<<"stmt_string2 "<<stmt_string2<<endl;
                prev=NULL;
                curr=NULL;
                last=NULL;
                temp=NULL;
                temp2=NULL;
                prev_val=1;
                sign=1;
                StringNode* stmt_string=NULL;
                copy_into_struct(stmt_string2,&stmt_string);
                temp2=stmt_string;
                display(stmt_string);
                int j=0;
                int occ=0;
                flag=0;
                while(stmt_string!=NULL)
                {
                    printf("stmt_size->a:%s\n",stmt_string->a);
                    while(stmt_string!=NULL && occ==0 && stmt_string->next!=NULL)
                    {
                        // cout<<stmt_string->a<<endl<<stmt_string->next->a<<endl<<stmt_string->next->next->a<<endl;
                        if(((strcmp(stmt_string->next->a,"*")==0) &&(stmt_string->next->next && strcmp(stmt_string->next->next->a,loop_id)==0) )||((strcmp(stmt_string->next->a,"*")==0) &&(strcmp(stmt_string->a,loop_id)==0) ))
                        {
                            cout<<"----------b---------"<<endl;
                            break;


                        }
                        else if(strcmp(stmt_string->a,loop_id)==0) break;
                        else
                        {
                            strcat (front,stmt_string->a);
                            cout<<"----------a---------"<<endl;
                            if(!strcmp(stmt_string->a,"+"))
                            {
                                sign=1;
                                printf("sign=1\n");
                            }
                            else if(!strcmp(stmt_string->a,"-"))
                            {
                                sign=-1;
                                printf("sign=-1\n");
                            }

                            stmt_string=stmt_string->next;
                        }
                        // cout<<"out of loop "<<endl;
                    }
                    occ=1;
                    cout<<":front"<<front<<endl;
                    if(!strcmp(stmt_string->a,"+"))
                    {
                        sign=1;
                        printf("sign=1\n");
                    }
                    else if(!strcmp(stmt_string->a,"-"))
                    {
                        sign=-1;
                        printf("sign=-1\n");
                    }
                    if(stmt_string->next&&(!strcmp(stmt_string->next->a,"*"))) //comes when stmt_string2 points to 2*i
                    {
                        printf("sign=*\n");
                        occ=1;
                        if((strcmp(stmt_string->a,loop_id))&&(strcmp(stmt_string->a,"*"))&&(strcmp(stmt_string->a,"+"))&&(strcmp(stmt_string->a,"-"))&&(!strcmp(stmt_string->next->next->a,loop_id)))
                        {

                            //   printf("stmt_string2->string= %s,loop_temp->loopIndex->string= %s,stmt_string2->next->next->string=%s\n",stmt_string->a,loop_id,stmt_string->next->next->a);
                            //     cout<<"----------1st cond----------"<<endl;
                            VariableDependenceDist='y';
                            prev_val=atoi(stmt_string->a);                     // pre_val: 2 (out of 2*i)
                            //    printf("prev_val = %d\n",prev_val);
                            if(a_val)
                            {
                                curr=(struct StringNode*)malloc(sizeof(struct StringNode));
                                curr->a=(char*)malloc(sizeof(char)*10);

                                sprintf(curr->a, "%d", a_val*prev_val);
                                //   printf("curr->a = %s\n",curr->a);
                                //create node curr with value 4*2
                                last=(struct StringNode*)malloc(sizeof(struct StringNode));
                                if(op.compare("+")==0)
                                {
                                    if (sign>0) last->a="+";
                                    else last->a="-";
                                }
                                else
                                {
                                    if(sign>0) last->a="-";
                                    else last->a="+";
                                }
                                // create node last with value '-'
                                curr->next=last;                                   // curr node will become '8'->'-'
                            }
                            stmt_string->a=(char*)malloc(sizeof(char)*10);
                            sprintf(stmt_string->a, "%d", c_val*prev_val); // update 2*i to 6*2*i
                            if(curr)
                                curr->next->next=stmt_string;
                            if(curr)
                            {
                                if(prev)
                                    prev->next=curr;
                                //else
                                //stmt_string=curr;
                            }
                            stmt_string=stmt_string->next->next;



                        }

                        else    if(!(strcmp(stmt_string->a,loop_id))&&(strcmp(stmt_string->next->next->a,"*"))&&(strcmp(stmt_string->next->next->a,"+"))&&(strcmp(stmt_string->next->next->a,"-"))&&(strcmp(stmt_string->next->next->a,loop_id)))
                        {
                            //   printf("stmt_string2->string= %s,loop_temp->loopIndex->string= %s,stmt_string2->next->next->string=%s\n",stmt_string->a,loop_id,stmt_string->next->next->a);
                            cout<<"----------2nd cond----------"<<endl;
                            VariableDependenceDist='y';
                            prev_val=atoi(stmt_string->next->next->a);                     // pre_val: 2 (out of 2*i)
                            //  printf("prev_val = %d\n",prev_val);
                            if(a_val)
                            {
                                curr=(struct StringNode*)malloc(sizeof(struct StringNode));
                                curr->a=(char*)malloc(sizeof(char)*10);

                                sprintf(curr->a, "%d", a_val*prev_val);
                                //    printf("curr->a = %s\n",curr->a);
                                //create node curr with value 4*2
                                last=(struct StringNode*)malloc(sizeof(struct StringNode));
                                if(op.compare("+")==0)
                                {
                                    if (sign>0) last->a="+";
                                    else last->a="-";
                                }
                                else
                                {
                                    if(sign>0) last->a="-";
                                    else last->a="+";
                                }
                                // create node last with value '-'
                                curr->next=last;                                   // curr node will become '8'->'-'
                            }
                            temp=(struct StringNode*)malloc(sizeof(struct StringNode));
                            temp->a=(char*)malloc(sizeof(char)*10);
                            sprintf(temp->a, "%d", c_val*prev_val);
                            //temp->size=NULL;
                            last=(struct StringNode*)malloc(sizeof(struct StringNode));
                            last->a="*";
                            //last->size=NULL;
                            temp->next=last;
                            //printf("%s, %s\n",temp->string,last->string);
                            if(curr)
                                curr->next->next=temp;
                            else
                                curr=temp;
                            if(curr)
                            {
                                if(prev)
                                    prev->next=curr;
                                // else
                                // stmt_string=curr;
                                last->next=stmt_string;
                            }
                            stmt_string->next=stmt_string->next->next->next;

                        }

                    }
                    else  if(!(strcmp(stmt_string->a,loop_id)))
                    {
                        occ=1;
                        //   cout<<"----------3rd cond----------"<<endl;
                        if(a_val)
                        {
                            curr=(struct StringNode*)malloc(sizeof(struct StringNode));
                            curr->a=(char*)malloc(sizeof(char)*10);
                            char buffer[100];
                            snprintf(buffer, sizeof(buffer), "%d", a_val);
                            curr->a=buffer;

                            //  cout<<"a = "<<buffer<<endl;
                            last=(struct StringNode*)malloc(sizeof(struct StringNode));
                            if(op.compare("+")==0)
                            {
                                if (sign>0) last->a="+";
                                else last->a="-";
                            }
                            else
                            {
                                if(sign>0) last->a="-";
                                else last->a="+";
                            }
                            // create node last with value '-'
                            curr->next=last;                                   // curr node will become '8'->'-'
                        }
                        if(c_val!=1)
                        {
                            temp=(struct StringNode*)malloc(sizeof(struct StringNode));
                            temp->a=(char*)malloc(sizeof(char)*10);
                            temp->a=strdup(c);
                            //temp->size=NULL;
                            last=(struct StringNode*)malloc(sizeof(struct StringNode));
                            last->a="*";
                            //last->size=NULL;
                            temp->next=last;
                            //  printf("%s, %s\n",temp->a,last->a);
                            if(curr)
                                curr->next->next=temp;
                            else
                                curr=temp;
                        }
                        if(curr)
                        {
                            if(prev)
                                prev->next=curr;
                            //  else
                            //   stmt_string=curr;
                            last->next=stmt_string;
                        }
                        //  stmt_string->next=stmt_string->next->next->next;

                    }
                    temp4=(struct StringNode*)malloc(sizeof(struct StringNode));
                    if(curr!=NULL && isdigit(front[0] ))
                    {
                        temp4->a=front;
                        cout<<"temp->a"<<temp4->a<<endl;
                        flag=1;
                        temp4->next=curr;
                        temp3=temp4;
                        cout<<"string is (curr!=NULL)"<<endl;
                        result=store(temp3);
                        cout<<result<<endl;
                        SgExpression* exp= buildVarRefExp(result);
                        replaceExpression(rhs,exp);
                    }
                    else if(curr!=NULL)
                    {
                        temp3=curr;
                        /* if(temp!=NULL)
                        {
                         cout<<"string is "<<endl;
                        display(temp3);
                         }*/
                    }

                    prev=stmt_string;

                    memset(&front[0], 0, sizeof(front));

                    curr=NULL;
                    last=NULL;

                    stmt_string=stmt_string->next;
                }
                if(flag==0)
                {
                    cout<<"string is "<<endl;
                    result=store(temp3);
                    SgExpression* exp= buildVarRefExp(result);
                    replaceExpression(rhs,exp);
                    cout<<result<<endl;
                    // display(temp3);
                }
                // result.clear();
            }
        }
    }

}

/*int main(int argc, char * argv[])
{
     set<string> var;
     set<string> :: iterator i;
    SgProject *project = frontend (argc, argv);
    SgFunctionDeclaration* func = SageInterface::findMain(project);
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
 Rose_STL_Container<SgNode*> forLoops = NodeQuery::querySubTree(defn,V_SgForStatement);
    for(Rose_STL_Container<SgNode*>::iterator iter = forLoops.begin(); iter!= forLoops.end(); iter++ )
    {
        loop_normalization(*iter,var);

    }
 return backend(project);
 }*/
