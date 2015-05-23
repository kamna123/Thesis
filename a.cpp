// ROSE is a tool for building translators, this file is an example translator built with ROSE.
// Specifically it shows the analysis of a code to report all variable declarations in each block.

#include "rose.h"
#include <iostream>
#include <string>
#include <sstream>

#include <fstream>
class DeleteAST : public SgSimpleProcessing
{
public:
//! Required traversal function
    void visit (SgNode* node);
};
void
DeleteAST::visit(SgNode* node)
{
    delete node;
}
void DeleteSgTree( SgNode* root)
{
    DeleteAST deleteTree;
    deleteTree.traverse(root,postorder);
}

using namespace std;
using namespace SageBuilder;
using namespace SageInterface;
ofstream outfile("to.cpp");
SgProject* project;
int flag=0;
static int count1=0;
class visitorTraversal : public AstSimpleProcessing
{
public:
    virtual void visit(SgNode* n);
};
/*void visitorTraversal::visit(SgNode* n)
{
  SgVarRefExp* var = isSgVarRefExp(n);

  // cout<<"pos "<<var->get_file_info()->get_line()<<endl;
int k=0;
  if(var!=NULL)
  {
    SgArrayType *arrT = isSgArrayType(var->get_type());
   if(arrT)
   {  k=getArrayElementCount(arrT);
      cout<<k<<endl;
   SgName varName = var->get_symbol()->get_name();

   cout<<(&varName)->getString()<<endl; }
  }
}*/
/*void fdisplay_part1(){
	int i = 0;
	char c;
 //fprintf(out, "start ");
	while((c = fgetc(in)) != EOF && i<start_num) {
        if (c == '\n') {
        	i++;
        }
        fputc(c, out);

    }
//fprintf(out, "finish ");
}*/
void visitorTraversal::visit(SgNode* n)
{
    //Project* project = frontend(argc,argv);
//SgFunctionDeclaration* func = SageInterface::findMain(project);
    /* SgForStatement* func=isSgForStatement(n);
    if(func!=NULL){
    const Sg_File_Info *start = func->get_body()->get_startOfConstruct();
    		const Sg_File_Info *end = func->get_body()->get_endOfConstruct();
    		int lineS = start->get_line();
    		int lineE = end->get_line();}
      if(func!=NULL )
     { cout<<"pos "<<func->get_file_info()->get_line()<<endl; flag=1;}*/
    SgLocatedNode* locatedNode = isSgLocatedNode(n);
    SgVariableDeclaration* node=isSgVariableDeclaration(n);
    if(node!=NULL && locatedNode!=NULL )
    {
        cout<<node->unparseToString()<<endl;
        Sg_File_Info * startInfo = node->get_startOfConstruct();
        Sg_File_Info * endInfo = node->get_endOfConstruct();
        if(startInfo && endInfo)
        {
            int startLine = startInfo->get_line();
            int endline = endInfo->get_line();
// if at least one line is referenced then we can't delete it
//for(int i = startLine; i <= endline ; i++) {
            cout<<"Start = "<<startLine<<"end = "<<endline<<endl;


        }
    }

}

void another(SgNode* forloop)
{
    SgForStatement* loop=isSgForStatement(forloop);
    vector<SgExprStatement*> exprStmtList = querySubTree<SgExprStatement> (loop->get_loop_body(), V_SgExprStatement);
    for (vector<SgExprStatement*>::iterator iter = exprStmtList.begin(); iter!= exprStmtList.end(); iter++)
    {
        // cout<<"*iter = "<<((*iter))->unparseToString()<<endl;
        SgAssignOp *assignOp = isSgAssignOp((*iter)->get_expression());
        if (assignOp != NULL)
        {
            SgExpression* lhs = (assignOp->get_lhs_operand());
            SgExpression* rhs = (assignOp->get_rhs_operand());
            // assignOp=isSgAssignOp((lhs)->get_expression());
            // if(assignOp!=NULL)
            //lhs=assignOp->get_lhs_operand();
            cout<<"array = "<<(lhs)->unparseToString()<<endl;
            cout<<"array = "<<(rhs)->unparseToString()<<endl;
        }

    }

}
void ref_function(SgNode* for_loop,SgFunctionDefinition *defn )
{
    map<string ,string> mymap;
    std::map<string,string>::iterator it;

    SgForStatement* forLoop=isSgForStatement(for_loop);
    SgBasicBlock* loopBody = isSgBasicBlock(forLoop->get_loop_body());
    Rose_STL_Container<SgStatement*> forLoops = loopBody->get_statements();
    for(Rose_STL_Container<SgStatement*>::iterator iter = forLoops.begin(); iter!= forLoops.end(); iter++ )
    {
        SgScopeStatement* scope=(*iter)->get_scope();
        Rose_STL_Container<SgNode*> pntrArrRefList =  NodeQuery::querySubTree(scope, V_SgVarRefExp);
        Rose_STL_Container<SgNode*>::iterator iter1;
        for(iter1 = pntrArrRefList.begin(); iter1 != pntrArrRefList.end(); ++iter1)
        {
            SgVarRefExp* a=isSgVarRefExp(*iter1);

            if(a)
            {
                cout<<"SgExpression"<<(a)->unparseToString()<<endl;
                string type=(a)->get_type()->unparseToString();
                stringstream ss(type);
                string token;
                string buff;
                if(ss>>buff)
                    token=buff;
                cout<<token<<endl;
                mymap.insert(pair<string,string>((a)->unparseToString(),token));
            }

        }
    }
    for (it=mymap.begin(); it!=mymap.end(); ++it)
        std::cout << it->first << " => " << it->second << '\n';
}
void ref_function1(SgNode* for_loop,SgFunctionDefinition *defn )
{
    SgForStatement* forLoop=isSgForStatement(for_loop);
    SgBasicBlock* loopBody = isSgBasicBlock(forLoop->get_loop_body());
    Rose_STL_Container<SgStatement*> forLoops = loopBody->get_statements();
    for(Rose_STL_Container<SgStatement*>::iterator iter = forLoops.begin(); iter!= forLoops.end(); iter++ )
    {

        cout<<" statements are "<< (*iter)->unparseToString()<<"\n";
    }
}

int main ( int argc, char * argv[] )
{
    project = frontend(argc,argv);
    SgFunctionDeclaration* func = SageInterface::findMain(project);
    SgFunctionDefinition *defn = func->get_definition();
    SgSourceFile* file = isSgSourceFile((*project)[0]);
    cout<<"file = "<<file->getFileName();
    const char* file_name=(file->getFileName()).c_str();
    ifstream fin;
    fin.open(file_name,ios::in);

    int i=1,k,f;
    char c;
    int endline ;
    int startLine;
    Rose_STL_Container<SgNode*> forLoops = NodeQuery::querySubTree(defn,V_SgForStatement);
    for(Rose_STL_Container<SgNode*>::iterator iter = forLoops.begin(); iter!= forLoops.end(); iter++ )
    {
        ref_function1(*iter,defn);
        SgForStatement* node=isSgForStatement(*iter);
//if(node) DeleteSgTree(node);
        Sg_File_Info * startInfo = node->get_startOfConstruct();
        Sg_File_Info * endInfo = node->get_endOfConstruct();
        if(startInfo && endInfo)
        {
            startLine = startInfo->get_line();
            endline = endInfo->get_line();
            int startCol= startInfo->get_col();
            int endCol=endInfo->get_col();
// if at least one line is referenced then we can't delete it
//for(int i = startLine; i <= endline ; i++) {
            cout<<"Start = "<<startLine<<"end = "<<endline<<endl;



            i=1;

            cout<<"i= "<<i<<endl;
//fprintf(out, "start ");
            if(count1==0)
            {
                while(!fin.eof() && i<startLine  )
                {

                    fin.get(c);
                    cout<<"i = "<<i<<"startLine = "<<startLine<<"c= "<<c<<endl;
                    if(c=='\n')
                    {
                        i++;
                        outfile<<endl;
                    }
                    else
                        outfile<<c;
                }
                count1++;
            }
            else
            {
                i=f;

                while(i<=k && !fin.eof())
                {
                    cout<<"k = "<<k<<"c = "<<c<< "i= "<<i<<endl;
                    fin.get(c);
                    if(c=='\n')
                    {
                        i++;
                        if(i>k) break;
                    }
                }
                while(!fin.eof() && i<startLine)
                {

                    fin.get(c);
                    cout<<"i in inner loop "<<i<<"c= "<<c<<endl;
                    if(c=='\n')
                    {
                        i++;
                        outfile<<endl;
                    }
                    else outfile<<c;
                }
            }


        }

        k=endline;
        f=startLine;
    }
    i=f;
    while(i<=k && !fin.eof())
    {
        cout<<"k = "<<k<<"c = "<<c<< "i= "<<i<<endl;
        fin.get(c);
        if(c=='\n')
        {
            i++;
            if(i>k) break;
        }
    }
    while(!fin.eof() )
    {

        fin.get(c);
        cout<<"i in inner loop "<<i<<"c= "<<c<<endl;
        if(c=='\n')
        {
            i++;
            outfile<<endl;
        }
        else outfile<<c;
    }

    // visitorTraversal exampleTraversal;

    // Call the traversal starting at the project node of the AST
    // Traverse all header files and source file (the -rose:collectAllCommentsAndDirectives
    // commandline option controls if comments and CPP directives are separately extracted
    // from header files).
//exampleTraversal.traverse(project,preorder);



    /*Rose_STL_Container<SgNode*> arrayAccess = NodeQuery::querySubTree(defn,V_SgArrayType);
     std::string filename;
    for(int i = 0 ; i < project->numberOfFiles(); i++)
    {
    SgSourceFile* file = isSgSourceFile(&project->get_file(i));
    assert(file);
     std::cout << "Processing file " << file->getFileName() << std::endl;
    if( file != NULL)
    {
    filename = file->getFileName();
    filename = StringUtility::stripPathFromFileName(filename);
    filename = "tokens_" + filename;
    ofstream outfile(filename.c_str());
    outfile<<"-------------------------------------------------------------abc---------------------------------------------------------------"<<endl;
     std::cout << file->get_rawTokenStream().size() << " tokens!\n";
    for (SgSourceFile::LexTokenList::iterator i = file->get_rawTokenStream().begin(); i != file->get_rawTokenStream().end(); ++i)
    {
    std::cout <<"val "<< i->get_value().c_str();
    // std::cout.flush();
    const std::string& thisfile = i->get_position().get_file().c_str();
    if (thisfile.find("int main") != std::string::npos)
    {
    if (thisfile.length() == 0)
    {
    // boost::wave::token_id id = boost::wave::token_id(*i);
    // // King84 (2010.09.23): Hack because we had to insert some whitespace
    // if (id == boost::wave::T_NEWLINE || id == boost::wave::T_SPACE || id == boost::wave::T_RIGHTPAREN || id == boost::wave::T_LEFTPAREN)
    // outfile << i->get_value().c_str();
    }
    else
    outfile << i->get_value().c_str();
    if (i->get_value() == "int")
    {
    std::cout << "***** GOT A COMMA from file " << i->get_position().get_file().c_str() << "*****" << std::endl;
    }
    }
    }
    outfile.close();
    filename = file->getFileName();
    ROSE_ASSERT(filename != "");
    filename+=".out";
    filename = StringUtility::stripPathFromFileName(filename);
    //Output the macro diretives to the file
    ofstream myfile;
    myfile.open (filename.c_str());
    ROSE_ASSERT(myfile.is_open());
    std::cout << "Outputing to the file " << filename << std::endl;
    backend(project);



    }}*/return backend(project);
}

