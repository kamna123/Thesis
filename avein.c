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
class visitorTraversal : public AstSimpleProcessing
{
public:
void visit(SgNode* n);
};
void visitorTraversal::visit(SgNode* n)
{
// The "volatile" madifier is in the type of the SgInitializedName
 //Sg_File_Info* sourceLocation = Sg_File_Info::generateDefaultFileInfoForTransformationNode();
SgInitializedName* initializedName = isSgInitializedName(n);
//SgBasicBlock* block=isSgBasicBlock(n);
if (initializedName != NULL )
{
printf ("Found a SgInitializedName = %s \n",initializedName->get_name().str());
string s=initializedName->get_name().str();
SgName name=s;
node[i].name="d_"+name;
node[i].org=name;
SgType* type = initializedName->get_type();
node[i].type=type;
SgScopeStatement* scope=initializedName->get_scope();
node[i].scope=scope;
printf ("Found a Scope = %s \n",scope->class_name().c_str());
//SgVariableDeclaration* variableDeclaration =buildVariableDeclaration(name,buildPointerType(type));
 
//prependStatement (variableDeclaration,scope) ;
//printf (" initializedName: type = %p = %s \n",type,type->class_name().c_str());
i++;
}
}
// Note that the "volatile" madifier is not in the SgVariableDeclaration nor the SgVariableDefinition


// must have argc and argv here!!
int main(int argc, char * argv[])
{
SgProject *project = frontend (argc, argv);
visitorTraversal myvisitor;
myvisitor.traverseInputFiles(project,preorder);
int k=0;
SgType* type=node[0].type;

SgExpression * init_exp2 = buildSizeOfOp(type);
 SgVariableDeclaration* decl2 = buildVariableDeclaration("size",buildIntType(),buildAssignInitializer(init_exp2));
SgFunctionDeclaration* mainFunc= findMain(project);

  SgBasicBlock* body= mainFunc->get_definition()->get_body();
  pushScopeStack(body);
  SgStatement* laststmt = getLastStatement(topScopeStack());
  insertStatementBefore(laststmt,decl2);
 popScopeStack();
for(int z=0;z<i;z++)
  {
SgVariableDeclaration* variableDeclaration =buildVariableDeclaration(node[k].name,buildPointerType(node[k].type));
prependStatement (variableDeclaration,node[k].scope) ;
type=node[k].type;


SgFunctionDeclaration* mainDecl = findMain(project);
 //if (mainDecl) 
{
//printf("BC");
   SgFunctionDefinition* mainDef = mainDecl->get_definition();
    SgBasicBlock* main_body = mainDef->get_body();
    if(main_body)
{
   SgGlobal* gscope = getGlobalScope(mainDef);
    SgExprListExp* mpi_comm_rank_args =buildExprListExp(buildVarRefExp(SgName("(void**)&"+node[k].name),main_body), buildExprListExp(buildVarRefExp(SgName("size"), main_body)));
    SgExprStatement* callStmt_1 = buildFunctionCallStmt(SgName("cudaMalloc"),buildVoidType(),mpi_comm_rank_args,gscope);
    // Prepend in the reverse order so that the variable declarations come first
  prependStatement(callStmt_1,main_body);
   SgExprListExp* mpi_comm_rank_args1 =buildExprListExp(buildVarRefExp(SgName(node[k].name),main_body), buildExprListExp(buildVarRefExp(SgName("&"+node[k].org), main_body)),buildExprListExp(buildVarRefExp(SgName("size"), main_body)),buildExprListExp(buildVarRefExp(SgName("CudaMemcpyHostToDevice"), main_body)));
    SgExprStatement* callStmt_2 = buildFunctionCallStmt(SgName("cudaMemcpy"),buildVoidType(),mpi_comm_rank_args1,gscope);
    // Prepend in the reverse order so that the variable declarations come first
  prependStatement(callStmt_2,main_body);
  
}
   
k++;
}}
return backend(project);
}

