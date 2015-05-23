
#include "rose.h"
#include <sstream>
//#include "readWrie.hpp"
#include "ds.hpp"
#include "gcd_banerjee.hpp"
//#include "symbolic-math-master/expr.h"
using namespace std;
using namespace SageBuilder;
using namespace SageInterface;

int euclid_GCD(int a, int b)
{
    if(b == 0)
       return a;
    else
       return euclid_GCD(b, (a%b));
}
string find_corresponding_read_dep_var(SgExpression* write_string,loop* read)
{
	vector<SgNode*>::iterator i;
	SgExpression* lhs;
	SgExpression* rhs;
  dep_data* ab=read->dep;
  while(ab)
  {
	for(i=ab->read_ref.begin();i!=ab->read_ref.end();i++)
	{
        lhs=isSgBinaryOp(*i)->get_lhs_operand();
        rhs=isSgBinaryOp(*i)->get_rhs_operand();
        string a=lhs->unparseToString();
        string b=rhs->unparseToString();
		if(!(a.compare(write_string->unparseToString())))
			return (b);

	}
  ab=ab->next;
}
}
int positive_func(int x)
{
    int result=(x>0)?x:0;
    return result;
}

int negative_func(int x)
{
    int result=(x<0)?-x:0;
    return result;
}

string get_lower_bound(SgNode* n )
{
  SgForStatement* a=isSgForStatement(n);
  string lb;
   SgExpression* ivarast=NULL, *lbast=NULL, *ubast=NULL, *stepast=NULL;
   SgStatementPtrList & init=a->get_init_stmt();
       SgStatement* init1 = init.front();
        SgInitializedName* ivarname=NULL;
        if (isAssignmentStatement(init1, &ivarast, &lbast))
             {
                SgVarRefExp* var = isSgVarRefExp(ivarast);
                  if (var)
                   {
                     //cout<<"a"<<"\n";
                     ivarname = var->get_symbol()->get_declaration();
                    // cout<<" loop lower bound= "<<(lbast)->unparseToString()<<"\n"; 
                    lb=(ivarname)->unparseToString();
                   }
             }  
             return lb;        
}
string get_upper_bound(SgNode* n)
{
   SgForStatement* a=isSgForStatement(n);
   SgExpression* ubast=NULL;
     SgBinaryOp* test = isSgBinaryOp(a->get_test_expr()); 
     ubast=test->get_rhs_operand();
     return (ubast->unparseToString());
}
int fill_coeff_array(int *arr,string stmt_string,SgNode* loop_id)
{ 
  int coeff=1,constt=0,var=0,sign=1,j;
   string loop_id_string= get_lower_bound(loop_id);
  for(j=0;stmt_string[j];)
  {
                       stringstream ss;
                       string s;
                       if(isdigit(stmt_string[j])==1)
                       {
                       while(isdigit(stmt_string[j])==1 && stmt_string[j])
                       {ss<<stmt_string[j] ;j++;}
                       ss>>s;
                       }
                       else
                       {
                        ss<<stmt_string[j] ;
                        ss>>s;
                        j++;
                       }
                    //  cout<<"string in coef "<<s<<endl;
                        if(!loop_id_string.compare(s))
                         
                         {
                          arr[0]=coeff*sign;
                          coeff=1;
                         }
                        else if(!(s.compare("*")));
                        else if(!(s.compare("+")))
                           {
                            sign=1;
                           }
                           else if(!(s.compare("-")))
                           {
                            sign=-1;
                           }
                           else
                           {
                             const char *cstr = s.c_str();
                             var=atoi(cstr);
                             stringstream a;
                             string b;
                             a<<stmt_string[j];
                             a>>b;
                             if(b.compare("*") || stmt_string[j]=='\0')
                             {
                                constt=constt+(var*sign);
                             }
                             else
                             {
                                coeff=(var*sign);
                             }
                              
                           }
       // printf("constt=%d coeff=%d var=%d sign=%d\n",constt,coeff,var,sign);
  }
  return constt;
}
int banerjee(loop* write,SgNode* loop,int loop_number)
{
string write_size,read_size;
   int no_of_loops=1,i,c,d;
   int a_i[no_of_loops],b_i[no_of_loops],lower_limits[no_of_loops],upper_limits[no_of_loops];
    int a_neg[no_of_loops],a_pos[no_of_loops],b_neg[no_of_loops],b_pos[no_of_loops];
    int LB_less=0,UB_less=0,LB_greater=0,UB_greater=0,LB_equal=0,UB_equal=0,dep_exists=0,j;
    int dependency,dimension;
    
    i=0;
    string ub;
    //ub=get_upper_bound(loop);
    string lb=get_lower_bound(loop);
    string line=store_upper[loop_number];
   cout<<"----------upper bound ----------"<<line<<endl;
   // string line=ub;
   line.erase(remove(line.begin(), line.end(),')'),line.end());
   line.erase(remove(line.begin(), line.end(),'('),line.end());
      //  cout<<"line = "<<line<<endl;
  
  /*ExpressionObject *expr = ExpressionObject::parse(line, false);
    
                  expr = expr->optimize();*/
                  string s=line;
               // cout<<"string after simplification = "<<s<<endl;
    const char *c_lb= lb.c_str();
    const char *c_ub = s.c_str();
    lower_limits[i]=0;
    upper_limits[i]=atoi(c_ub);
   
    cout<<"upper_limits[i] = "<<upper_limits[i]<<endl;
   
     vector<SgNode*>::iterator itr;
    SgExpression* rhs;
    SgExpression* lhs;
     dep_data* ab=write->dep;
   while(ab)
   {

    for(itr=ab->write_ref.begin();itr!=ab->write_ref.end();itr++)
    {

           if(isSgBinaryOp(*itr)!=NULL)
                {
                   rhs = isSgBinaryOp(*itr)->get_rhs_operand();
                   lhs=  isSgBinaryOp(*itr)->get_lhs_operand();
               }
               
               string line=rhs->unparseToString();
              line.erase(remove(line.begin(), line.end(),')'),line.end());
              line.erase(remove(line.begin(), line.end(),'('),line.end());
            /*  ExpressionObject *expr = ExpressionObject::parse(line, false);
    
                  expr = expr->optimize();
                  string s=expr->toLaTeX();*/
                  rhs=buildVarRefExp(line);
                   cout<<"rhs read "<<(rhs)->unparseToString()<<endl;
               write_size=rhs->unparseToString();
               read_size=find_corresponding_read_dep_var(lhs,write);
               line=read_size;
               line.erase(remove(line.begin(), line.end(),')'),line.end());
               line.erase(remove(line.begin(), line.end(),'('),line.end());
            /*   expr = ExpressionObject::parse(line, false);
               expr = expr->optimize();*/
               read_size=line;
               cout<<"write_size "<<write_size<<"\n";
               cout<<"read size "<<read_size<<"\n";
                 dependency=0,dimension=0;
                if(write_size!="\0" || read_size!="\0")
                 {
                    a_i[i]=0;
                    b_i[i]=0;
                    c=fill_coeff_array(a_i,write_size,loop);
                     cout<<"c = "<<c<<endl;
                    d=fill_coeff_array(b_i,read_size,loop);
                   
                    cout<<"d = "<<d<<endl;
                    LB_less=0,UB_less=0,LB_greater=0,UB_greater=0,LB_equal=0,UB_equal=0;
                // Printing the obtained matrix
                    
            printf("Lower limits array\n");
           // for(i=0;i<no_of_loops;i++)
                printf("%d ",lower_limits[i]);
            printf("\n");
            printf("Upper limits array\n");
          //  for(i=0;i<no_of_loops;i++)
                printf("%d ",upper_limits[i]);
            printf("\n");
            printf("a_i array\n");
            //for(i=0;i<no_of_loops;i++)
                printf("%d ",a_i[i]);
            printf("\n");
            printf("b_i array\n");
           // for(i=0;i<no_of_loops;i++)
                printf("%d ",b_i[i]);
            printf("\nc=%d d=%d\n",c,d);
            //////////////////////////////////    
                a_neg[i]=(a_i[i]<0)?-a_i[i]:0;              //negative function of a_i[]
                a_pos[i]=(a_i[i]>0)?a_i[i]:0;               //positive function of a_i[]
                b_neg[i]=(b_i[i]<0)?-b_i[i]:0;              //negative function of b_i[]
                b_pos[i]=(b_i[i]>0)?b_i[i]:0;               //positive function of b_i[]
            
          
            
                LB_less+=(-1)*positive_func(a_neg[i]+b_i[i])*(upper_limits[i]-1)+(negative_func(a_neg[i]+b_i[i])+a_pos[i])*lower_limits[i]-b_i[i];
                UB_less+=positive_func(a_pos[i]-b_i[i])*(upper_limits[i]-1)+(negative_func(a_pos[i]-b_i[i])+a_neg[i])*lower_limits[i]-b_i[i];
                LB_equal+=(-1)*negative_func(a_i[i]-b_i[i])*upper_limits[i]+positive_func(a_i[i]-b_i[i])*lower_limits[i];
                UB_equal+=positive_func(a_i[i]-b_i[i])*upper_limits[i]-negative_func(a_i[i]-b_i[i])*lower_limits[i];
                LB_greater+=(-1)*negative_func(a_i[i]-b_pos[i])*(upper_limits[i]-1)+(positive_func(a_i[i]-b_pos[i])+b_neg[i])*lower_limits[i]+a_i[i];
                UB_greater+=positive_func(a_i[i]+b_neg[i])*(upper_limits[i]-1)-(negative_func(a_i[i]+b_neg[i])+b_pos[i])*lower_limits[i]+a_i[i];
        
                 int flag=0;
            if((d-c)>=LB_less&&(d-c)<=UB_less)
            {
                flag=1;
                //*less=1;
            }
            if((d-c)>=LB_greater&&(d-c)<=UB_greater)
            {
                flag=1;
                //*greater=1;
            }
            if((d-c)>=LB_equal&&(d-c)<=UB_equal)
            {
                flag=1;
                //*equal=1;
            }
            dependency=(flag==1)?dependency+1:dependency; 
            dimension++;
             printf( "dependency=%d dimension=%d flag=%d\n",dependency,dimension,flag);
         }
          dep_exists=(dependency==dimension)?1:dep_exists;

    }
     ab=ab->next;
   }
 if(dep_exists)      //dependency exist
        return 1;     
    else
        return 0;
}
void calculate_node(dep_data* node)
{
  int i=0;
  while(node)
  {
    i++;
    node=node->next;
  }
  cout<<"i= "<<i<<"\n";
}
int GCD_Test(loop* write,SgNode* loop)
{
	//cout<<"in gcd function";
    int a=0,b=0,c=0,d=0,var,sign=1,dependency=0,dimension=0,dep_exists=0;
    string loop_id_string= get_lower_bound(loop);
   // cout<<"loop_id_string = "<<loop_id_string;
    if(write->dep==NULL)
      return 0;
   // cout<<"loop id"<<loop_id_string<<"\n";
    string write_size,read_size;
    vector<SgNode*>::iterator i;
    SgExpression* rhs;
    SgExpression* lhs;
    dep_data* ab=write->dep;
    // cout<<"in sgnode"<<write->dep->write_ref->unparseToString();
    while(ab)
    {
       for(i=ab->write_ref.begin();i!=ab->write_ref.end();i++)
    {
          
             if(isSgBinaryOp(*i)!=NULL)
                {
                   rhs = isSgBinaryOp(*i)->get_rhs_operand();
                   lhs=  isSgBinaryOp(*i)->get_lhs_operand();
               }
               string line=rhs->unparseToString();
             line.erase(remove(line.begin(), line.end(),')'),line.end());
              line.erase(remove(line.begin(), line.end(),'('),line.end());
             //  cout<<line<<endl;
  
             /* ExpressionObject *expr = ExpressionObject::parse(line, false);
    
                  expr = expr->optimize();
                  string s=expr->toLaTeX();*/
                  rhs=buildVarRefExp(line);
                 //  cout<<"rhs read "<<(rhs)->unparseToString()<<endl;
               write_size=rhs->unparseToString();
               read_size=find_corresponding_read_dep_var(lhs,write);
               line=read_size;
              line.erase(remove(line.begin(), line.end(),')'),line.end());
              line.erase(remove(line.begin(), line.end(),'('),line.end());
              /* expr = ExpressionObject::parse(line, false);
               expr = expr->optimize();*/
               read_size=line;
               cout<<"write_size "<<write_size<<"\n";
               cout<<"read size "<<read_size<<"\n";
                 dependency=0,dimension=0;
                 int k;
                 if(write_size!="\0" || read_size!="\0")
                 {
                  a=0,b=0,c=0,d=0,var,sign=1;
                   int j;
                   for(j=0;write_size[j];)
                   {
                       stringstream ss;
                       string s;
                       if(isdigit(write_size[j])==1)
                       {
                       while(isdigit(write_size[j])==1 && write_size[j])
                       {ss<<write_size[j] ;j++;}
                       ss>>s;
                       }
                      
                       else
                       {
                        ss<<write_size[j] ;
                        ss>>s;
                        j++;
                       }
                      
                        if(!loop_id_string.compare(s))
                          a=(a==0)?1:a;
                        else if(!(s.compare("*")));
                        else if(!(s.compare("+")))
                           {
                            sign=1;
                           }
                           else if(!(s.compare("-")))
                           {
                            sign=-1;
                           }
                           else
                           {
                             const char *cstr = s.c_str();
                             var=atoi(cstr);
                              stringstream ab;
                             string b;
                             ab<<write_size[j];
                             ab>>b;
                             if(!b.compare("*") || write_size[j]=='\0')
                             {
                                c=c+(var*sign);
                             }
                             else
                             {
                                a=(a>0)?euclid_GCD(a,var):var;
                             }
                           }
                   }
                   sign=1;
                    for(j=0;read_size[j];j++)
                   {
                       stringstream ss;
                       string s;
                       ss<<read_size[j];
                       ss>>s;
                        if(!loop_id_string.compare(s))
                          b=(b==0)?1:b;
                        else if(!(s.compare("*")));
                        else if(!(s.compare("+")))
                           {
                            sign=1;
                           }
                           else if(!(s.compare("-")))
                           {
                            sign=-1;
                           }
                           else
                           {
                             const char *cstr = s.c_str();
                             var=atoi(cstr);
                             if(read_size[j+1]=='\0')
                             {
                                d=d+(var*sign);
                             }
                             else
                             {
                                b=(b>0)?euclid_GCD(b,var):var;
                             }
                           }
                   }
            if(a==0&&b==0)    var=1;
            else if(b==0)   var=a;
            else if(a==0)   var=b;
            else var=euclid_GCD(a,b);
            dependency=(((d-c)%var)==0)?dependency+1:dependency; 
            dimension++;
                 }
                  dep_exists=(dependency==dimension)?1:dep_exists;
                }
      ab=ab->next;
    }
     if(dep_exists)      //dependency exist
        return 1;     
    else
        return 0;
}
