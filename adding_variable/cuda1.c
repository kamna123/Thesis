#include "rose.h"
using namespace std;
using namespace SageBuilder;
using namespace SageInterface;
int main(int argc, char * argv[])
{
SgProject *project = frontend (argc, argv);
Rose_STL_Container<SgInitializedName*> globalVariableList;
 SgSourceFile* sourceFile = isSgSourceFile(project->get_fileList()[0]);
     ROSE_ASSERT(sourceFile != NULL);
     SgGlobal* globalScope = sourceFile->get_globalScope();
    Rose_STL_Container<SgDeclarationStatement*>::iterator i = globalScope->get_declarations().begin();
 while(i != globalScope->get_declarations().end())
{
SgVariableDeclaration *variableDeclaration = isSgVariableDeclaration(*i);
if (variableDeclaration != NULL)
{
Rose_STL_Container<SgInitializedName*> & variableList = variableDeclaration->get_variables();
Rose_STL_Container<SgInitializedName*>::iterator var = variableList.begin();
while(var != variableList.end())
{
globalVariableList.push_back(*var);
printf ("Found a SgInitializedName = %s \n",(*var)->get_name().str());
var++;
}
printf ("Found a SgInitializedName = %s \n",(*var)->get_name().str());
}
i++;
}
}
