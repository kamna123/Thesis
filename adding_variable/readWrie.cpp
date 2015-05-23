/*
 *  * Call Qing's side effect analysis
 *  by Liao, 2/26/2009
 *  */
#include "rose.h"
 #include "readWrie.hpp"
 #include "dependency.h"
#include <iostream>
#include <set>
 #include "readWrie.h"
 #include "ds.hpp"

using namespace std;
using namespace SageInterface;
using namespace SageBuilder;
/*class visitorTraversal : public AstSimpleProcessing
{
    public:
       virtual void visit(SgNode* n);
};*/

void setRhsOperand1(SgExpression* target, SgExpression* rhs)
{

     bool haslhs = false;
     SgVarArgCopyOp* varargcopy = isSgVarArgCopyOp(target);
     SgVarArgStartOp* varargstart = isSgVarArgStartOp(target);
     SgBinaryOp* binary = isSgBinaryOp(target);
        if (varargcopy!=NULL)
           {
           varargcopy->set_rhs_operand(rhs);
           if( varargcopy->get_lhs_operand()!=NULL) haslhs= true;
           }
       else if(varargstart!=NULL)
           {
           varargstart->set_rhs_operand(rhs);
           if( varargstart->get_lhs_operand()!=NULL) haslhs= true;
           }
      else if(binary!=NULL)
           {
           binary->set_rhs_operand(rhs);
           if( binary->get_lhs_operand()!=NULL) haslhs= true;
           }
      else
          {
          cout<<"SageInterface::setRhsOperand(): unhandled case for target expression of type "
           <<target->class_name()<<endl;
          ROSE_ASSERT(false);
          }
            rhs->set_parent(target);
            // only when both lhs and rhs are available, can we set lvalue
            if (haslhs)
               markLhsValues(target);
}
void setLoopLowerBound1(SgForStatement* forstmt, SgExpression* lb)
{

     if (forstmt != NULL)
        {
          // two cases: init_stmt is
          // SgExprStatement (assignment) like i=0;
          // SgVariableDeclaration int i =0 or
           Rose_STL_Container<SgNode* > testList = NodeQuery::querySubTree( *((forstmt->get_init_stmt()).begin()), V_SgAssignOp);
             if (testList.size()>0) // assignment statement
                {
                ROSE_ASSERT(testList.size()==1);// only handle the case of 1 statement, canonical form
                cout<<"abc"<<"\n";
                SgAssignOp * assignop = isSgAssignOp((*testList.begin()));
                  //ROSE_ASSERT(assignop);
                  //cout<<"dfg"<<assignop->get_rhs_operand()->get_lvalue();
                    if( assignop->get_rhs_operand()->get_lvalue()==0)
                        cout<<"def"<<"\n";
                        lb->set_lvalue(true);
                        assignop->set_rhs_operand(lb);
                        lb->set_parent(assignop);
                 }
        }
}

static SgExpression* SkipCasting (SgExpression* exp)
{
      SgCastExp* cast_exp = isSgCastExp(exp);
          if (cast_exp != NULL)
             {   
              SgExpression* operand = cast_exp->get_operand();
              assert(operand != 0);
              return SkipCasting(operand);
             }
         else
              return exp;
}
bool isIntExpression( SgExpression * exp) 
{
VariantT varT = exp->variantT();
switch (varT)
{
case V_SgIntVal:
return true;
case V_SgAddOp:
case V_SgSubtractOp:
case V_SgMultiplyOp:
case V_SgIntegerDivideOp:
case V_SgDivideOp:
if ( isIntExpression( isSgBinaryOp(exp)->get_lhs_operand() ) && isIntExpression( isSgBinaryOp(exp)->get_rhs_operand() ) )
return true;
else
return false;
default:
return false;
}
}

void replace_Expression_recursively(SgExpression** a,  SgInitializedName* ivarname,SgExpression* lbast,SgExpression* stepast1)
{
           if( isIntExpression(*a)) return ;
           SgVarRefExp* ref = isSgVarRefExp (*a);
         
             SgExpression* lhs=isSgBinaryOp(*a)->get_lhs_operand();
             
                    ref = isSgVarRefExp (lhs);  
     
        if(lhs!=NULL)
         {
                   if(ref!=NULL)
                    {
                      SgExpression *exp= buildVarRefExp("("+(ivarname)->unparseToString()+"*"+(stepast1)->unparseToString()+"+"+(lbast)->unparseToString()+")");
                                  replaceExpression(lhs,exp);

                    } 
                   else
                    
                     replace_Expression_recursively(&lhs,   ivarname, lbast, stepast1);
          }
                  SgExpression* rhs=isSgBinaryOp(*a)->get_rhs_operand();
           
             if(rhs!=NULL)
             {
                   SgVarRefExp* ref1 = isSgVarRefExp (rhs);  
                   if(ref1!=NULL)
                    {
                      SgExpression *exp= buildVarRefExp("("+(ivarname)->unparseToString()+"*"+(stepast1)->unparseToString()+"+"+(lbast)->unparseToString()+")");
                                  replaceExpression(rhs,exp);
                    } 
                   else
                     replace_Expression_recursively(&rhs,   ivarname, lbast, stepast1);
              }
}

void display1(loop_data* loop)
{
  while(loop)
  {
    cout<<"loop data"<<"\n";
     cout<<loop->lb<<" "<<loop->ub<<" "<<loop->loop_variable<<" "<<loop->step<<"\n";
     loop=loop->next;
  }
}


void visit1(SgNode* n)
{
     vector<SgNode*> readRefs;
     vector<SgNode*> writeRefs;
     vector<SgNode*>:: iterator itr;
     SgExpression* rhs;
     SgExpression* lhs;
     SgExpression* temp;
     SgForStatement* a=isSgForStatement(n);
     SgBasicBlock *block = isSgBasicBlock (n);
     SgExpression* ivarast=NULL, *lbast=NULL, *ubast=NULL, *stepast=NULL;
     if(a!=NULL)
     {
       SageInterface::normalizeForLoopInitDeclaration(a);
       bool k=forLoopNormalization(a);
       //cout<<"k= "<<k<<endl;
       SgScopeStatement* scope=a->get_scope();
       SgStatementPtrList & init=a->get_init_stmt();
       SgStatement* init1 = init.front();
       SgInitializedName* ivarname=NULL;
       loop_data* node=new loop_data;
       node->next=NULL;
      if(head_loop==NULL)
      {
         head_loop=node;
      }
            if (isAssignmentStatement(init1, &ivarast, &lbast))
             {
                SgVarRefExp* var = isSgVarRefExp(ivarast);
                  if (var)
                   {
                     //cout<<"a"<<"\n";
                     ivarname = var->get_symbol()->get_declaration();
                     cout<<" loop lower bound= "<<(lbast)->unparseToString()<<"\n"; 
                     cout<<" loop variable= "<<(ivarname)->unparseToString()<<"\n";
                   }
             }          
           SgBinaryOp* test = isSgBinaryOp(a->get_test_expr()); 
           //SgBinaryOp* test1 = isSgBinaryOp(test->get_rhs_operand());  
           //cout<<" loop operator= "<<(testvar)->unparseToString()<<"\n";
           cout<<" loop test= "<<(test)->unparseToString()<<"\n";
            switch (test->variantT()) 
               {
               case V_SgLessOrEqualOp:
                 cout<<"less than equal"<<"\n";
                 break;
               default :
                 break;
               }
            ubast = test->get_rhs_operand();
            cout<<" loop upper bound= "<<(ubast)->unparseToString()<<"\n";  
            SgExpression* incr = a->get_increment();
            Sg_File_Info* sourceLocation = Sg_File_Info::generateDefaultFileInfoForTransformationNode(); 
            SgBinaryOp* test1 = isSgBinaryOp(test->get_rhs_operand());  
            cout<<" loop increment= "<<(incr)->unparseToString()<<"\n";
            stepast=isSgBinaryOp(incr)->get_rhs_operand();
            string ab=(stepast)->unparseToString();
            cout<<"string "<<ab[3]<<"\n";
            cout<<" loop stepast= "<<(stepast)->unparseToString()<<"\n";
            SgExpression*  stepast1=isSgBinaryOp(stepast)->get_rhs_operand();
            //SgVarRefExp*    stepast1=isSgVarRefExp(isSgBinaryOp(stepast)->get_rhs_operand());
            cout<<" loop stepast1= "<<(stepast1)->unparseToString()<<"\n";
            //stepast1=isSgBinaryOp(stepast)->get_lhs_operand();  
            /*cout<<" loop stepast2= "<<(stepast1)->unparseToString()<<"\n";
              stepast1=isSgBinaryOp(stepast);
              cout<<" loop stepast3= "<<(stepast1)->unparseToString()<<"\n";*/
              //SgExpression * init_exp = buildIntVal(0); 
              //SgExprStatement* exp=buildAssignStatement(buildVarRefExp((ivarname)->unparseToString()),buildIntVal(0));
                SgExpression * init_exp2 = buildAssignOp();
                setLhsOperand(init_exp2,buildVarRefExp((ivarname)->unparseToString()));
                setRhsOperand(init_exp2,buildIntVal(0));
                SgName name =(ivarname)->unparseToString();
               //SgVariableDeclaration *lower_decl =buildVariableDeclaration ("0", buildIntType ());
               //prependStatement (lower_decl, scope);
               //buildVarRefExp("0", scope);
                 setLoopLowerBound1(a,  buildVarRefExp("0", scope));
               /* node->lb="0";
                node->ub="("+(ubast)->unparseToString()+"-"+(lbast)->unparseToString()+")"+"/"+(stepast1)->unparseToString();
                node->loop_variable=(ivarname)->unparseToString();
                node->step="1";*/
                 setLoopUpperBound(a,  buildVarRefExp("("+(ubast)->unparseToString()+"-"+(lbast)->unparseToString()+")"+"/"+(stepast1)->unparseToString(),scope));
                 setLoopStride(a,buildVarRefExp("1",scope));
        

         SageInterface::collectReadWriteRefs(scope, readRefs, writeRefs);
         for (itr=readRefs.begin();itr!=readRefs.end();itr++)
           {
                if(isSgBinaryOp(*itr)!=NULL)
                {
                   rhs = isSgBinaryOp(*itr)->get_rhs_operand();
                   lhs=  isSgBinaryOp(*itr)->get_lhs_operand();
                    SgExpression* rhs1=rhs;
                    SgVarRefExp* ref = isSgVarRefExp (rhs);
                  if(ref!=NULL)
                  {
                  
                   SgExpression *exp= buildVarRefExp("("+(ivarname)->unparseToString()+"*"+(stepast1)->unparseToString()+"+"+(lbast)->unparseToString()+")");
                   
               //    int k=atoi(exp->unparseToString()) ;
                   replaceExpression(rhs,exp);
                   }
                   else
                   { 
                   replace_Expression_recursively(&rhs,  ivarname,lbast, stepast1);
                   }
                    cout<<"read Ref "<<(lhs)->unparseToString()<<"["<<(rhs)->unparseToString()<<"]"<<endl;
                }
              }
           // cout<<"read ref:"<<(*itr)->unparseToString()<<endl; 
           
         for (itr=writeRefs.begin();itr!=writeRefs.end();itr++)
           {
              if(isSgBinaryOp(*itr)!=NULL)
              {
                rhs = isSgBinaryOp(*itr)->get_rhs_operand();
                SgExpression* rhs1=rhs;
                lhs=  isSgBinaryOp(*itr)->get_lhs_operand();
                
                SgVarRefExp* ref = isSgVarRefExp (rhs);
                  if(ref!=NULL)
                  {  
                   SgExpression *exp= buildVarRefExp("("+(ivarname)->unparseToString()+"*"+(stepast1)->unparseToString()+"+"+(lbast)->unparseToString()+")");
                
                //cout<< expr->toLaTeX()<<endl;
		//string a= expr->toLaTeX();
                //cout<<a<<endl;
                   replaceExpression(rhs,exp);
                   }
                   else
                  { 
                   replace_Expression_recursively(&rhs,  ivarname,lbast, stepast1);
                 /* string line=rhs->unparseToString();
                    line.erase(remove(line.begin(), line.end(),' '),line.end());
             //  cout<<line<<endl;
	
		ExpressionObject *expr = ExpressionObject::parse(line, false);
		
		expr = expr->optimize();
                  rhs=buildVarRefExp(line);
                //cout<< expr->toLaTeX()<<endl;
		//string a= expr->toLaTeX();
                //cout<<a<<endl;*/
                  
                   }
              //    cout<<"rhs "<<rhs->unparseToString();
                 cout<<"write Ref "<<(lhs)->unparseToString()<<"["<<(rhs)->unparseToString()<<"]"<<endl;
              }
           }
               /*  if(rhs!=NULL)
                 {
                     SgExpression *exp1=isSgBinaryOp(rhs);
                     if(exp1==NULL)
                     {
                     SgExpression *exp= buildVarRefExp((ivarname)->unparseToString()+"*"+(stepast1)->unparseToString()+"+"+(lbast)->unparseToString());
                     lhs=  isSgBinaryOp(*itr)->get_lhs_operand();
                  
                     replaceExpression(rhs,exp);
                     rhs=exp;
                 }
                 else
                 {
                   SgExpression *exp= rhs;
                    setLhsOperand(init_exp2,rhs);
                    setRhsOperand(init_exp2,buildVarRefExp((lbast)->unparseToString()))
                    setLhsOperand(exp,buildVarRefExp((ivarname)->unparseToString()+"*"+(stepast1)->unparseToString()+"+"+(lbast)->unparseToString()));
                    rhs=exp;
                    replaceExpression(rhs,exp);
                  }
                   cout<<"write Ref "<<(lhs)->unparseToString()<<"["<<(rhs)->unparseToString()<<"]"<<endl;  
                 }
              }
           // cout<<"read ref:"<<(*itr)->unparseToString()<<endl; 
           }*/
        }
}
/*int main(int argc, char * argv[])
{
  SgProject *project = frontend (argc, argv);
 /* SgFunctionDeclaration* func = SageInterface::findMain(project);
  ROSE_ASSERT(func != NULL);
  set<SgInitializedName*> readNames, writeNames;
  if (!SageInterface::collectReadWriteVariables(func,readNames,writeNames))
  {
    ROSE_ASSERT(false);
  }
  set<SgInitializedName*>::iterator iter;
  for (iter=readNames.begin();iter!=readNames.end();iter++)
       cout<<"read variable:"<<(*iter)->unparseToString()<<endl;
  /* i, j, a, b
   */
 // ROSE_ASSERT(writeNames.size() ==4);
 /* for (iter=writeNames.begin();iter!=writeNames.end();iter++)
       cout<<"written variable:"<<(*iter)->unparseToString()<<endl;
  // read only variables  
  set<SgInitializedName*> readOnlyVars;
  SageInterface::collectReadOnlyVariables(func,readOnlyVars);
  for (iter=readOnlyVars.begin();iter!=readOnlyVars.end();iter++)
      cout<<"read-only variable:"<<(*iter)->unparseToString()<<endl;
   SgFunctionDefinition *defn = func->get_definition();
   Rose_STL_Container<SgNode*> arrayAccess = NodeQuery::querySubTree(defn,V_SgArrayType);
   vector<SgNode*> readRefs;
   vector<SgNode*> writeRefs;
   vector<SgNode*>:: iterator a;
  
    /*Rose_STL_Container<SgStatement*> stmts= NodeQuery::querySubTree(func,V_SgStatement);
   for ( Rose_STL_Container<SgStatement*>::iterator i=stmts.begin();i!=stmts.end();i++)
   {
         // cout<<"abc";
          SageInterface::collectReadWriteRefs(*i, readRefs, writeRefs);
             for (a=readRefs.begin();a!=readRefs.end();a++)
            cout<<"read ref:"<<(*a)->unparseToString()<<endl;  
   }*/
  
  /* for (Rose_STL_Container<SgNode*>::iterator iter = arrayAccess.begin(); iter!= arrayAccess.end(); iter++ ) 
  {
     // SgExprListExp* dims = (*iter)->get_dim_info();
        cout<<"array access pattern :"<<(*iter)->unparseToString()<<endl;
  }
 Rose_STL_Container<SgNode*> forLoops = NodeQuery::querySubTree(defn,V_SgForStatement);
  for(Rose_STL_Container<SgNode*>::iterator iter = forLoops.begin(); iter!= forLoops.end(); iter++ )
   {
         printf ("Found a SgForStatement \n");
             /*  Rose_STL_Container<SgNode*> expr = NodeQuery::querySubTree(defn,V_SgStatement);
              for(Rose_STL_Container<SgNode*>::iterator iter = expr.begin(); iter!= expr.end(); iter++ )
                {
                  cout<<"adsd"<<(*iter)->unparseToString()<<endl; 
                SageInterface::collectReadWriteRefs(expr, readRefs, writeRefs); 
                 }
              for (a=readRefs.begin();a!=readRefs.end();a++)
               cout<<"read ref:"<<(*a)->unparseToString()<<endl; */
   /*  SgExpression* init_exp=(buildVarRefExp("a"));
     Rose_STL_Container<SgNode*> pntrArrRefList =  NodeQuery::querySubTree(defn, V_SgPntrArrRefExp);
     Rose_STL_Container<SgNode*>::iterator iter1;
   for(iter1 = pntrArrRefList.begin(); iter1 != pntrArrRefList.end(); ++iter1) 
   {
    SgExpression* rhs = isSgBinaryOp(*iter1)->get_rhs_operand();
     cout<<"SgExpression"<<(rhs)->unparseToString()<<endl;
   }
  }*/
  // run all tests
  //AstTests::runAllTests(project);
/* visitorTraversal ae;
  ae.traverseInputFiles(project,preorder);
  display(head_loop);
  // Generate source code from AST and call the vendor's compiler
  return backend(project);
}*/

