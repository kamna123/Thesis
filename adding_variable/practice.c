#include "rose.h"
#include "NameGenerator.hh" 
using namespace std;
using namespace SageBuilder;
using namespace SageInterface;
using namespace OmpSupport;
int main(int argc, char * argv[])
{

 SgFunctionParameterTypeList* param_type_list;
SgProject *project = frontend (argc, argv);

std::vector<SgNode*> functionCalls = NodeQuery::querySubTree (project,V_SgFunctionCallExp);
    SgSourceFile* sourceFile = isSgSourceFile(project->get_fileList()[0]);
     ROSE_ASSERT(sourceFile != NULL);
     SgGlobal* globalScope = sourceFile->get_globalScope();
     SgFunctionDeclaration* mainDecl = findMain(project);
SgFunctionDefinition* mainDef = mainDecl->get_definition();
    SgBasicBlock* main_body = mainDef->get_body();
pushScopeStack(main_body);
   SgGlobal* gscope = getGlobalScope(mainDef);
SgStatement* laststmt;
       for (unsigned long i = 0; i < functionCalls.size(); i++)
        {
            SgFunctionCallExp* functionCallExp = isSgFunctionCallExp(functionCalls[i]);
            SgExpression *function = functionCallExp->get_function();
        //    printf("a : %s\n",functionCallExp->get_name().str());
          ROSE_ASSERT(functionCallExp != NULL);
            SgFunctionRefExp* functionRefExp = isSgFunctionRefExp(functionCallExp->get_function());
               if (functionRefExp != NULL)
             {
               SgFunctionSymbol* functionSymbol = functionRefExp->get_symbol();
             
              if (functionSymbol != NULL )
              {
               SgFunctionDeclaration *functionDeclaration = functionSymbol->get_declaration();
              SgName functionName = functionSymbol->get_name();
             SgFunctionType* type=functionDeclaration->get_type();
                printf ("Function being called: %s \n",functionName.str());
               //cout<<functionName.str();
               cout<<"type"<<"\n";
             //   SgFunctionType* fn_type = functionDeclaration->get_type();
                  param_type_list = type->get_argument_list();
                SgTypePtrList& type_list = param_type_list->get_arguments();

               cout<<type->get_return_type()->unparseToString();
       SgTypePtrList::iterator i = type_list.begin();  
       SgExprListExp* exp_list_exp=buildExprListExp();
      
       SgInitializedNamePtrList& argList = functionDeclaration->get_args();
       SgInitializedNamePtrList:: iterator j=argList.begin();
         while(j!=argList.end() && i!=type_list.end())
        {     
             SgInitializedName* dev_name=(*j);
             string s=dev_name->get_name().str();
              SgName name="d_"+s;
             SgVarRefExp* v_ref=buildVarRefExp(SgName(name));
               exp_list_exp->append_expression(v_ref);
              cout<<"parameter "<<"\n";
               cout<<(*i++)->unparseToString()<<"\n";
               cout<<"name"<<"\n";
               cout<<(*j++)->unparseToString()<<"\n";

         }
        
          SgExprStatement *func_call_stmt = buildFunctionCallStmt(functionName+"<<<N,M>>>",buildVoidType(),exp_list_exp,gscope);
         laststmt = getLastStatement(topScopeStack());
       insertStatementBefore(laststmt,func_call_stmt);
            //   printf ("type of Function being called: %s \n",type.unparseToString());
          }}

        }

         SgInitializedName* arg1 = buildInitializedName(SgName("512"), buildIntType());
 // SgInitializedName* arg2 = buildInitializedName(SgName("BLOCKDIM_Y"), buildIntType());

  SgType* dim3_t = buildOpaqueType("dim3", globalScope);

 /* SgExprListExp* exprList = buildExprListExp();
  //appendArg(exprList, arg1);
  //ppendArg(exprList, arg2);

  SgFunctionParameterList * paraList = buildFunctionParameterList();
  appendArg(paraList, arg1);
  appendArg(paraList, arg2);

  SgFunctionDeclaration * funcdecl = buildNondefiningFunctionDeclaration
  ("threads", dim3_t, paraList);*/
 SgExprListExp* mpi_comm_rank_args =buildExprListExp(buildVarRefExp(SgName("512"),main_body));
    SgExprStatement* callStmt_1 = buildFunctionCallStmt(SgName("dim3 _threads"),dim3_t,mpi_comm_rank_args,gscope);

   laststmt = getLastStatement(topScopeStack());
  insertStatementBefore(laststmt,callStmt_1);
   //prependStatement(funcdecl);
  
                   //replaceExpression(rhs,exp);
return backend(project);
}
