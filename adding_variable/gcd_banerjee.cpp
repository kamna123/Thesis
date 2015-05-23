
#include "rose.h"
#include <sstream>
//#include "readWrie.hpp"
#include "ds.hpp"
#include "gcd_banerjee.hpp"
#include "symbolic-math-master/expr.h"
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
	for(i=read->dep->read_ref.begin();i!=read->dep->read_ref.end();i++)
	{
        lhs=isSgBinaryOp(*i)->get_lhs_operand();
        rhs=isSgBinaryOp(*i)->get_rhs_operand();
        string a=lhs->unparseToString();
        string b=rhs->unparseToString();
		if(!(a.compare(write_string->unparseToString())))
			return (b);
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
int banerjee(loop* write,SgNode* loop)
{
   string write_size,read_size;
   int no_of_loops=1,i,c,d;
   int a_i[no_of_loops],b_i[no_of_loops],lower_limits[no_of_loops],upper_limits[no_of_loops];
    int a_neg[no_of_loops],a_pos[no_of_loops],b_neg[no_of_loops],b_pos[no_of_loops];
    int LB_less=0,UB_less=0,LB_greater=0,UB_greater=0,LB_equal=0,UB_equal=0,dep_exists=0;
    int dependency,dimension;
    
    i=0;
    string ub=get_upper_bound(loop);
    string lb=get_lower_bound(loop);
    const char *c_lb= lb.c_str();
    const char *c_ub = ub.c_str();
    lower_limits[i]=atoi(c_lb);
    upper_limits[i]=atoi(c_ub);
    i++;
     vector<SgNode*>::iterator itr;
    SgExpression* rhs;
    SgExpression* lhs;
    for(itr=write->dep->write_ref.begin();itr!=write->dep->write_ref.end();itr++)
    {
           if(isSgBinaryOp(*itr)!=NULL)
                {
                   rhs = isSgBinaryOp(*itr)->get_rhs_operand();
                   lhs=  isSgBinaryOp(*itr)->get_lhs_operand();
               }
               string line=rhs->unparseToString();
              line.erase(remove(line.begin(), line.end(),')'),line.end());
               line.erase(remove(line.begin(), line.end(),'('),line.end());
             //  cout<<line<<endl;
  
           /*   ExpressionObject *expr = ExpressionObject::parse(line, false);
    
                  expr = expr->optimize();
                  string s=expr->toLaTeX();*/
                  rhs=buildVarRefExp(line);
                 //  cout<<"rhs read "<<(rhs)->unparseToString()<<endl;
               write_size=rhs->unparseToString();
               read_size=find_corresponding_read_dep_var(lhs,write);
               line=read_size;
                line.erase(remove(line.begin(), line.end(),')'),line.end());
               line.erase(remove(line.begin(), line.end(),'('),line.end());
             /*  expr = ExpressionObject::parse(line, false);
               expr = expr->optimize();
               read_size=expr->toLaTeX();*/
               read_size=line;
               cout<<"write_size "<<write_size<<"\n";
               cout<<"read size "<<read_size<<"\n";
    }

}

int GCD_Test(loop* write,SgNode* loop)
{
	//cout<<"in gcd function";
    int a=0,b=0,c=0,d=0,var,sign=1,dependency=0,dimension=0,dep_exists=0;
    string loop_id_string= get_lower_bound(loop);
    if(write->dep==NULL)
      return 0;
   // cout<<"loop id"<<loop_id_string<<"\n";
    string write_size,read_size;
    vector<SgNode*>::iterator i;
    SgExpression* rhs;
    SgExpression* lhs;
    // cout<<"in sgnode"<<write->dep->write_ref->unparseToString();
   for(i=write->dep->write_ref.begin();i!=write->dep->write_ref.end();i++)
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
	
	          	/*ExpressionObject *expr = ExpressionObject::parse(line, false);
		
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
               expr = expr->optimize();
               read_size=expr->toLaTeX();*/
               cout<<"write_size "<<write_size<<"\n";
               cout<<"read size "<<read_size<<"\n";
                 dependency=0,dimension=0;
                 int k;
                 if(write_size!="\0" || read_size!="\0")
                 {
                 	a=0,b=0,c=0,d=0,var,sign=1;
                 	 int j;
                   for(j=0;write_size[j];j++)
                   {
                       stringstream ss;
                       string s;
                       ss<<write_size[j];
                       ss>>s;
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
                             if(write_size[j+1]=='\0')
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
     if(dep_exists)      //dependency exist
        return 1;     
    else
        return 0;
}
