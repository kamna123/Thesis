#include "rose.h"
using namespace std;
using namespace SageBuilder;
using namespace SageInterface;
struct a
{
  SgName name;
   SgName org;
  SgScopeStatement* scope;
  SgType* type;
};
struct a node[100];
 int i=0;
void setOutputFileName(SgFile* cur_file)
{
  ROSE_ASSERT(cur_file);
  string orig_name = cur_file->get_file_info()->get_filenameString();

  string file_suffix = StringUtility::fileNameSuffix(orig_name);

 // if (CommandlineProcessing::isCFileNameSuffix(file_suffix))
    {
      orig_name = StringUtility::stripPathFromFileName(orig_name);
      string naked_name = StringUtility::stripFileSuffixFromFileName(orig_name);
      cur_file->set_unparse_output_filename(naked_name+".cu");
      string output_name =  cur_file->get_unparse_output_filename();
      cout<<"output file name is :"<<output_name<<endl;                                                                                                     
    }
}
int insertHeaders(SgProject* project)
{

  //cout << "  INFO:Mint: Inserting runtime header cutil.h" << endl << endl ;

  Rose_STL_Container<SgNode*> globalScopeList = NodeQuery::querySubTree (project,V_SgGlobal);

  for (Rose_STL_Container<SgNode*>::iterator i = globalScopeList.begin(); i != globalScopeList.end(); i++)
    {
      SgGlobal* globalscope = isSgGlobal(*i);
      ROSE_ASSERT (globalscope != NULL);
      insertHeader("cutil.h",PreprocessingInfo::after,false,globalscope);
    }
  return 0; //assume always successful currently                                                                                             
}
class visitorTraversal : public AstSimpleProcessing
{
public:
void visit(SgNode* n);
};
/*void visitorTraversal::visit(SgNode* n)
{
// The "volatile" madifier is in the type of the SgInitializedName
 //Sg_File_Info* sourceLocation = Sg_File_Info::generateDefaultFileInfoForTransformationNode();
SgInitializedName* initializedName = isSgInitializedName(n);
SgFunctionDeclaration* mainDecl = findMain(n);
SgFunctionDefinition* mainDef = mainDecl->get_definition();
SgBasicBlock* main_body = mainDef->get_body();
if (initializedName != NULL )
{
printf ("Found a SgInitializedName = %s \n",initializedName->get_name().str());
SgScopeStatement* scope=initializedName->get_scope();
 //if(scope!=NULL )
{
string s=initializedName->get_name().str();
SgName name=s;
node[i].name="d_"+name;
node[i].org=name;
SgType* type = initializedName->get_type();
node[i].type=type;

node[i].scope=scope;
printf ("Found a Scope = %s \n",scope->class_name().c_str());
//SgVariableDeclaration* variableDeclaration =buildVariableDeclaration(name,buildPointerType(type));
 
//prependStatement (variableDeclaration,scope) ;
//printf (" initializedName: type = %p = %s \n",type,type->class_name().c_str());
i++;
}
}
}*/
// Note that the "volatile" madifier is not in the SgVariableDeclaration nor the SgVariableDefinition


// must have argc and argv here!!
int main(int argc, char * argv[])
{
SgFunctionParameterTypeList* param_type_list;
SgProject *project = frontend (argc, argv);
  SgSourceFile* file = isSgSourceFile(project->get_fileList()[0]);
setOutputFileName(isSgFile(file));
SgFunctionDeclaration* mainFunc= findMain(project);//mainDecl is practice
 SgFunctionDefinition* mainDef = mainFunc->get_definition();
  SgBasicBlock* body= mainFunc->get_definition()->get_body();
 SgBasicBlock* main_body = mainDef->get_body();
  pushScopeStack(body);
  SgStatement* laststmt = getLastStatement(topScopeStack());
/*visitorTraversal myvisitor;
myvisitor.traverseInputFiles(project,preorder);*/
int k=0;
std::vector<SgNode*> functionCalls = NodeQuery::querySubTree (project,V_SgFunctionCallExp);
    SgSourceFile* sourceFile = isSgSourceFile(project->get_fileList()[0]);
     ROSE_ASSERT(sourceFile != NULL);
     SgGlobal* globalScope = sourceFile->get_globalScope();
     SgGlobal* gscope = getGlobalScope(mainDef);
      if(gscope!=NULL)
    {
    Rose_STL_Container<SgNode*> varDefList = NodeQuery::querySubTree (project,V_SgVariableDeclaration);

         for (Rose_STL_Container<SgNode*>::iterator i = varDefList.begin(); i != varDefList.end(); i++)
         {
         SgVariableDeclaration* varDef = isSgVariableDeclaration(*i);
         SgInitializedName* initializedName = getFirstInitializedName(varDef);
         SgScopeStatement* scope=initializedName->get_scope();
          string s=initializedName->get_name().str();
          SgType* type = initializedName->get_type();
           SgVariableDeclaration* variableDeclaration =buildVariableDeclaration("crink_"+s,buildPointerType(type));
           node[k].name="crink_"+s;
           node[k].scope=scope;
           node[k].type=type;
           k++;
          laststmt = getLastStatement(scope);
       insertStatementBefore(laststmt,variableDeclaration);
        SgExprListExp* mpi_comm_rank_args =buildExprListExp(buildVarRefExp(SgName("(void**)& crink_"+s),main_body), buildExprListExp  (buildVarRefExp(SgName("size"), main_body)));
    SgExprStatement* callStmt_1 = buildFunctionCallStmt(SgName("cudaMalloc"),buildVoidType(),mpi_comm_rank_args,gscope);
    // Prepend in the reverse order so that the variable declarations come first

  insertStatementBefore(laststmt,callStmt_1);
         SgExprListExp* mpi_comm_rank_args1 =buildExprListExp(buildVarRefExp(SgName("crink_"+s),main_body), buildExprListExp(buildVarRefExp(SgName("&"+s), main_body)),buildExprListExp(buildVarRefExp(SgName("size"), main_body)),buildExprListExp(buildVarRefExp(SgName("CudaMemcpyHostToDevice"), main_body)));
    SgExprStatement* callStmt_2 = buildFunctionCallStmt(SgName("cudaMemcpy"),buildVoidType(),mpi_comm_rank_args1,gscope);
    // Prepend in the reverse order so that the variable declarations come first
 // prependStatement(callStmt_2,main_body);
 laststmt = getLastStatement(topScopeStack());
 insertStatementBefore(laststmt,callStmt_2);
         }

    }
       for (unsigned long i = 0; i < functionCalls.size(); i++)
        {
            SgFunctionCallExp* functionCallExp = isSgFunctionCallExp(functionCalls[i]);
          ROSE_ASSERT(functionCallExp != NULL);
           
            SgFunctionRefExp* functionRefExp = isSgFunctionRefExp(functionCallExp->get_function());
               if (functionRefExp != NULL)
             {
               SgFunctionSymbol* functionSymbol = functionRefExp->get_symbol();
             
              if (functionSymbol != NULL )
              {
          SgFunctionDeclaration *functionDeclaration = functionSymbol->get_declaration();
           SgGlobal* globalScope = getGlobalScope(functionDeclaration);
              SgName functionName = functionSymbol->get_name();
             SgFunctionType* type=functionDeclaration->get_type();
               SgExpressionPtrList args = functionCallExp->get_args()->get_expressions();
                printf ("Function being called: %s \n",functionName.str());
                    cout<<"type"<<"\n";
             //   SgFunctionType* fn_type = functionDeclaration->get_type();
                  param_type_list = type->get_argument_list();
                SgTypePtrList& type_list = param_type_list->get_arguments();

               cout<<type->get_return_type()->unparseToString();
               string fun_return_type=type->get_return_type()->unparseToString();
       SgTypePtrList::iterator i = type_list.begin();  
       SgExprListExp* exp_list_exp=buildExprListExp();
      
       SgInitializedNamePtrList& argList = functionDeclaration->get_args();
       SgInitializedNamePtrList:: iterator j=argList.begin();
       SgExprStatement* callStmt_2;
       SgFunctionParameterList* parameterList = buildFunctionParameterList();
         SgExpressionPtrList::iterator itA=args.begin();
         while(itA!=args.end() && i!=type_list.end() && j!=argList.end())
        {     
            SgInitializedName* dev_name=(*j);
            SgName s1=dev_name->get_name().str();
             string s=(*itA)->unparseToString();
              SgName name="crink_"+s;
             SgVarRefExp* v_ref=buildVarRefExp(SgName(name));
               exp_list_exp->append_expression(v_ref);
               SgReferenceType *ref_type = buildReferenceType(*i);
           SgInitializedName *var1_init_name = buildInitializedName(s1, ref_type);
             appendArg(parameterList,var1_init_name);
              cout<<"parameter "<<"\n";
               cout<<(*i++)->unparseToString()<<"\n";
               cout<<"name"<<"\n";
               cout<<(*itA++)->unparseToString()<<"\n";
               (*j)++;
               if(itA==args.end())
                     {
                          SgExprListExp* mpi_comm_rank_args1 =buildExprListExp(buildVarRefExp(SgName("&"+s),main_body), buildExprListExp(buildVarRefExp(SgName("crink_"+s), main_body)),buildExprListExp(buildVarRefExp(SgName("size"), main_body)),buildExprListExp(buildVarRefExp(SgName("CudaMemcpyDeviceToHost"), main_body)));
    callStmt_2 = buildFunctionCallStmt(SgName("cudaMemcpy"),buildVoidType(),mpi_comm_rank_args1,gscope);
    // Prepend in the reverse order so that the variable declarations come first
  //prependStatement(callStmt_2,main_body);

                     }

         }
      SgType* dim3_t = buildOpaqueType("_global_", globalScope);
          SgFunctionDeclaration * func        = buildDefiningFunctionDeclaration 
                        (fun_return_type+" "+functionName, dim3_t, parameterList,globalScope);
             prependStatement(func,globalScope);
          SgExprStatement *func_call_stmt = buildFunctionCallStmt(functionName+"<<<1,1>>>",buildVoidType(),exp_list_exp,gscope);
         laststmt = getLastStatement(topScopeStack());
       insertStatementBefore(laststmt,func_call_stmt);
          laststmt = getLastStatement(topScopeStack());
        insertStatementBefore(laststmt,callStmt_2);
            //   printf ("type of Function being called: %s \n",type.unparseToString());
          }}

        }

        // SgInitializedName* arg1 = buildInitializedName(SgName("512"), buildIntType());
 // SgInitializedName* arg2 = buildInitializedName(SgName("BLOCKDIM_Y"), buildIntType());

 // SgType* dim3_t = buildOpaqueType("dim3", globalScope);

 /* SgExprListExp* exprList = buildExprListExp();
  //appendArg(exprList, arg1);
  //ppendArg(exprList, arg2);

  SgFunctionParameterList * paraList = buildFunctionParameterList();
  appendArg(paraList, arg1);
  appendArg(paraList, arg2);

  SgFunctionDeclaration * funcdecl = buildNondefiningFunctionDeclaration
  ("threads", dim3_t, paraList);*/
/* SgExprListExp* mpi_comm_rank_args =buildExprListExp(buildVarRefExp(SgName("512"),main_body));
    SgExprStatement* callStmt_1 = buildFunctionCallStmt(SgName("dim3 _threads"),dim3_t,mpi_comm_rank_args,gscope);

   laststmt = getLastStatement(topScopeStack());
  insertStatementBefore(laststmt,callStmt_1);
      


SgType* type=node[0].type;*/

//SgExpression * init_exp2 = buildSizeOfOp(type);
 //SgVariableDeclaration* decl2 = buildVariableDeclaration("size",buildIntType(),buildAssignInitializer(init_exp2));
 // bottomup: build operands first, create expression later on
 //  double result = 2 * (1 - gama * gama);
 //SgExpression * init_exp =  
   //         buildMultiplyOp(buildDoubleVal(2.0),buildSubtractOp(buildDoubleVal(1.0),  buildMultiplyOp (buildVarRefExp("gama"),buildVarRefExp("gama") )));
/*SgExpression * init_exp=(buildVarRefExp("dim3 _Threads(512)"));
 laststmt = getLastStatement(topScopeStack());
  insertStatementBefore(laststmt,init_exp);*/
//pushScopeStack(body);
 //popScopeStack();
int z;
for(z=0;z<k;z++)
{
      SgExprListExp* mpi_comm_rank_args1 =buildExprListExp(buildVarRefExp(SgName(node[z].name),main_body));
    SgExprStatement* callStmt_2 = buildFunctionCallStmt(SgName("cudaFree"),buildVoidType(),mpi_comm_rank_args1,gscope);
    // Prepend in the reverse order so that the variable declarations come first
 // prependStatement(callStmt_2,main_body);
 laststmt = getLastStatement(topScopeStack());
 insertStatementBefore(laststmt,callStmt_2);
}
/*for( z=0;z<i;z++)
  {
SgVariableDeclaration* variableDeclaration =buildVariableDeclaration(node[k].name,buildPointerType(node[k].type));
  laststmt = getLastStatement(topScopeStack());
   insertStatementBefore(laststmt,variableDeclaration);
//prependStatement (variableDeclaration,node[k].scope) ;
type=node[k].type;
k++;
}*/
k=0;

/*SgFunctionDeclaration* mainDecl = findMain(project);
SgFunctionDefinition* mainDef = mainDecl->get_definition();
    SgBasicBlock* main_body = mainDef->get_body();
pushScopeStack(main_body);
   SgGlobal* gscope = getGlobalScope(mainDef);*/
 
  // insertStatementBefore(laststmt,decl2);


/*for(z=0;z<k;z++)
{
    if(main_body)
{

    SgExprListExp* mpi_comm_rank_args =buildExprListExp(buildVarRefExp(SgName("(void**)&"+node[k].name),main_body), buildExprListExp(buildVarRefExp(SgName("size"), main_body)));
    SgExprStatement* callStmt_1 = buildFunctionCallStmt(SgName("cudaMalloc"),buildVoidType(),mpi_comm_rank_args,gscope);
    // Prepend in the reverse order so that the variable declarations come first
laststmt = getLastStatement(topScopeStack());
  insertStatementBefore(laststmt,callStmt_1);
 k++; 
}
}*/
pushScopeStack(main_body);

/*k=0;
for(z=0;z<k;z++)
{
    if(main_body)
{
   SgExprListExp* mpi_comm_rank_args1 =buildExprListExp(buildVarRefExp(SgName(node[k].name),main_body), buildExprListExp(buildVarRefExp(SgName("&"+node[k].org), main_body)),buildExprListExp(buildVarRefExp(SgName("size"), main_body)),buildExprListExp(buildVarRefExp(SgName("CudaMemcpyHostToDevice"), main_body)));
    SgExprStatement* callStmt_2 = buildFunctionCallStmt(SgName("cudaMemcpy"),buildVoidType(),mpi_comm_rank_args1,gscope);
    // Prepend in the reverse order so that the variable declarations come first
 // prependStatement(callStmt_2,main_body);
 laststmt = getLastStatement(topScopeStack());
 insertStatementBefore(laststmt,callStmt_2);
k++;  
}
}*/
 





















return backend(project);
}

