
#include "rose.h"
#include "ds.hpp"
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
struct loop_var
{
    string name;
    string data_type;
    int size;
    loop_var* next;
};
loop_var* head_var=NULL;
map<string ,loop_var > mymap;
string newFilename_output = "new_source_file.c";
ofstream outputfile(newFilename_output.c_str(),ios::out);
class visitorTraversal : public AstSimpleProcessing
{
public:
    virtual void visit(SgNode* n);
};
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
void visitorTraversal::visit(SgNode* n)
{
    //  SgScopeStatement* scope =n->get_scope();
    // On each node look for any comments of CPP directives
    // if( isSgVariableDeclaration(n) && isSgGlobal(isSgVariableDeclaration(n)->get_parent()) != NULL)
    // {cout<<"abc"<<endl; outputfile<<n->unparseToString()<<endl;}
    SgLocatedNode* locatedNode = isSgLocatedNode(n);
    if (locatedNode != NULL)
    {
        AttachedPreprocessingInfoType* comments = locatedNode->getAttachedPreprocessingInfo();

        if (comments != NULL)
        {
            // printf ("Found attached comments (to IR node at %p of type: %s): \n",locatedNode,locatedNode->class_name().c_str());
            int counter = 0;
            AttachedPreprocessingInfoType::iterator i;
            for (i = comments->begin(); i != comments->end(); i++)
            {
                if(PreprocessingInfo::directiveTypeName((*i)->getTypeOfDirective()).compare("CpreprocessorIncludeDeclaration")==0)
                    /*  printf ("          Attached Comment #%d in file %s (relativePosition=%s): classification %s :\n%s\n",
                            counter++,(*i)->get_file_info()->get_filenameString().c_str(),
                            ((*i)->getRelativePosition() == PreprocessingInfo::before) ? "before" : "after",
                            PreprocessingInfo::directiveTypeName((*i)->getTypeOfDirective()).c_str(),
                            (*i)->getString().c_str());*/
                    outputfile<<(*i)->getString().c_str();
            }
        }
        /*else
         {
           printf ("No attached comments (at %p of type: %s): \n",locatedNode,locatedNode->sage_class_name());
         }*/
    }
    else
    {

    }


}

void var_loop(SgNode* forloop,string loop_id)
{

    std::map<string ,loop_var>::iterator it;

    SgForStatement* forLoop=isSgForStatement(forloop);
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
                //cout<<"SgExpression"<<(a)->unparseToString()<<endl;
                string type=(a)->get_type()->unparseToString();
                stringstream ss(type);
                string token;
                string buff;
                if(ss>>buff)
                    token=buff;
                int k;
                SgArrayType *arrT = isSgArrayType(a->get_type());
                if(arrT)
                {
                    k=getArrayElementCount(arrT);
                    cout<<k<<endl;
                    SgName varName = a->get_symbol()->get_name();

//  cout<<(&varName)->getString()<<endl; }
                    // cout<<token<<endl;
                    int flag=0;
                    if((a)->unparseToString().compare(loop_id) && arrT!=NULL)
                    {
                        //mymap.insert(pair<string,lo>(a->unparseToString(),token));
                        mymap[a->unparseToString()].data_type=token;
                        mymap[a->unparseToString()].name=a->unparseToString();
                        mymap[a->unparseToString()].size=getArrayElementCount(arrT);

                        flag=1;
                    }
                    //mymap.insert(make_pair(a->unparseToString(),make_pair(token,k)));
                    /* if(flag==1)
                      { loop_var* node=new loop_var;
                       node->next=NULL;
                        if(head_var==NULL)
                        {
                          head_var=node;
                          node->name=a->unparseToString();
                          node->data_type=token;
                          node->size=getArrayElementCount(arrT);
                        }
                        else
                        {
                          loop_var* temp=head_var;
                          while(temp->next)
                           temp=temp->next;
                         temp->next=node;
                          node->name=a->unparseToString();
                          node->data_type=token;
                          node->size=getArrayElementCount(arrT);
                        }
                        flag=0;
                      }*/
                    // mymap[a->unparseToString()]=make_pair(token,k);
                }
                //mymap.insert(pair<string ,pair<string,int> >((a)->unparseToString()),token,k);


            }

        }


        std::cout << "mymap contains:\n";
        for (it=mymap.begin(); it!=mymap.end(); ++it)
            std::cout << it->first << " =" << it->second.name<<it->second.data_type<<it->second.size<<'\n';
        /* loop_var* temp=head_var;
        while(temp)
        {
         cout<<"display "<<temp->name<<" "<<temp->size<<" "<<temp->data_type<<endl;
         temp=temp->next;
        }*/
    }
    std::string process(std::string const& s)
    {
        std::string::size_type pos = s.find(';');
        if (pos != std::string::npos)
        {
            return s.substr(0, pos);
        }
        else
        {
            return s;
        }
    }

    void  SimpleSelective_kernel_declaration_DEPENDENCY(SgNode* forloop,string loop_id)
    {

        outputfile<<"#define _NTHREAD 512"<<endl<<"#define _NBLOCK 65535"<<endl<<"#include<cuda.h>"<<endl<<endl;
        outputfile<< "__global__ void _AFFINE_KERNEL(";
        std::map<string ,loop_var >::iterator it;
        for (it=mymap.begin(); it!=mymap.end(); ++it)
        {
            cout<<"it->second.data_type "<<it->second.data_type<<endl;
            outputfile<<it->second.data_type;
            outputfile<<"*";
            outputfile<<" ";
            outputfile<<",";
            outputfile<<"int ,";
        }
        outputfile<<"int ,";
        for(i=0; i<Total_Phi; i++)

            outputfile<<"int );"<<endl<<endl;
    }


    void simple_loop_shrinking_AFFINE(SgNode* forloop,string loop_id)
    {
        std::map<string ,loop_var >::iterator it;
        string loop=process(forloop->unparseToString());
        cout<<"for loop is "<<loop;

        int i=1,x=1,j,temp_size=1,id_max=0;
        int max_array_size=1;   //contains the array with maximum size like 'a' for declaration like int a[20][30],b[2][10][10]
        int max_dimension_size=1;
        int max_size,sz;
        for (it=mymap.begin(); it!=mymap.end(); ++it)
        {
            temp_size=1;
            //for(i=x;i>0;i--)
            {

                outputfile<< "\t"<<it->second.data_type;

                outputfile<<"_SZ_"<<(it->second.name)<<"_"<<i<<" = " ;
                outputfile<<it->second.size;
                temp_size=it->second.size;
                outputfile<<";"<<endl;
                max_array_size=(temp_size>max_array_size)?temp_size:max_array_size;
                if(id_max<x)
                {
                    id_max=x;
                    max_size=it->second.size;
                    printf("in id max\n");
                }
                printf("max_array_size=%d",max_array_size);
                printf( "id_max: %d\n",id_max);


            }
        }
        sz=max_size;

        temp_size=sz;
        printf("sz=%d\n",temp_size);
        max_dimension_size=(temp_size>max_dimension_size)?temp_size:max_dimension_size;
        printf("max_dim_size=%d\n",max_dimension_size);
        int tempVar=id_max;
        printf("tempvar=%d\n",tempVar);
        max_array_size=1;
        while(tempVar)
        {
            max_array_size*=max_dimension_size;
            tempVar--;
        }
        for (it=mymap.begin(); it!=mymap.end(); ++it)
        {
            outputfile<< "\t"<<it->second.data_type;

            outputfile<<"*_DEV_"<<(it->second.name)<<";"<<endl;
            outputfile<<"\tcudaMalloc((void**) &_DEV_"<<(it->second.name)<<","<<"sizeof(";
            outputfile<<it->second.data_type;
            outputfile<< ")";
            sz = it->second.size;
            x = 1;

            i=1;
            outputfile<< "*_SZ_"<<it->second.name<<"_"<<i;
            outputfile<< ");"<<endl;

            outputfile<<"\tcudaMemcpy(_DEV_"<<it->second.name<<","<<it->second.name<< ","<<"sizeof(";
            outputfile<<it->second.data_type;
            outputfile<< ")";
            sz = it->second.size;
            x = 1;


            outputfile<<"*_SZ_"<<it->second.name<<"_"<<i;

            outputfile<< ", cudaMemcpyHostToDevice);"<<endl;



        }
        outputfile<<"\tint _NUM_THREADS = "<< max_array_size<<";"<<endl;
        outputfile<<"\tfloat _NUM_BLOCKS=1;"<<endl<<"\tint _NUM_TILE=1;"<<endl;
        outputfile<<"\tdim3 _THREADS(512);"<<endl<<"\tdim3 _BLOCKS(1);"<<endl;
        outputfile<< "\tif(_NUM_THREADS < _NTHREAD)"<<endl;
        if(id_max==1)
            outputfile<<"\t{"<<endl<<"\t\t_THREADS.x=_NUM_THREADS;"<<endl<<"\t}"<<endl;
        /*else if(id_max==2)
            fprintf(out, "\t{\n\t\t_THREADS.x=%d;\n\t\t_THREADS.y=%d;\n\t}\n",max_dimension_size,max_dimension_size);
        else
            fprintf(out, "\t{\n\t\t_THREADS.x=%d;\n\t\t_THREADS.y=%d;\n\t\t_THREADS.z=%d;\n\t}\n",max_dimension_size,max_dimension_size,max_dimension_size);*/

        outputfile<< "\telse {"<<endl;
        if(id_max==1)
            outputfile<< "\t\t _THREADS.x=_NTHREAD;"<<endl<<"\t\t_NUM_BLOCKS=(_NUM_THREADS % _NTHREAD == 0)?(_NUM_THREADS/_NTHREAD):((_NUM_THREADS/_NTHREAD)+1);"<<endl<<"\t\tif(_NUM_BLOCKS<_NBLOCK)"<<endl<<"\t\t\t_BLOCKS.x=_NUM_BLOCKS;"<<endl<<"\t\telse {"<<endl<<"\t\t\t_BLOCKS.x=_NBLOCK;"<<endl<<"\t\t\tint temp=_NUM_BLOCKS;"<<endl<<"\t\t\t_NUM_TILE=(temp % _NBLOCK == 0)?(_NUM_BLOCKS/_NBLOCK):((_NUM_BLOCKS/_NBLOCK)+1);"<<endl<<"\t\t}"<<endl<<"\t}"<<endl;
        /*else if(id_max==2)
            fprintf(out, "\t\t_NUM_BLOCKS=(_NUM_THREADS*1.0)/256;\n\t\t_BLOCKS.x=_BLOCKS.y=ceil(sqrt(_NUM_BLOCKS));\n\t\t_THREADS.x=_THREADS.y=ceil(sqrt(%d.0/(_BLOCKS.x*_BLOCKS.y)));\n\t\tint temp=_NUM_BLOCKS;\n\t\tif(_NUM_BLOCKS>_NBLOCK)\n\t\t\t_NUM_TILE=(temp %% _NBLOCK == 0)?(_NUM_BLOCKS/_NBLOCK):((_NUM_BLOCKS/_NBLOCK)+1);\n\t}\n",max_array_size);
        else
            fprintf(out, "\t\t_NUM_BLOCKS=(_NUM_THREADS*1.0)/512;\n\t\t_BLOCKS.x=_BLOCKS.y=_BLOCKS.z=ceil(cbrtf(_NUM_BLOCKS));\n\t\t_THREADS.x=_THREADS.y=_THREADS.z=ceil(cbrtf(%d.0/(_BLOCKS.x*_BLOCKS.y*_BLOCKS.z)));\n\t\tint temp=_NUM_BLOCKS;\n\t\tif(_NUM_BLOCKS>_NBLOCK)\n\t\t\t_NUM_TILE=(temp %% _NBLOCK == 0)?(_NUM_BLOCKS/_NBLOCK):((_NUM_BLOCKS/_NBLOCK)+1);\n\t}\n",max_array_size);*/

        outputfile<<"\tint _CUDA_TILE;"<<endl;
//for loop data insertion
        /*      if(DependencyExists=='y')
        {
        loop_index_temp = loop_index_new;
        struct Phi_Values *lambda_temp=lambda_var;
        while(loop_index_temp!=NULL)
        {
            fprintf(out, "\tfor(%s=%s;%s",loop_index_temp->loopIndex->string,loop_index_temp->L->string,loop_index_temp->loopIndex->string);
            int ch=loop_index_temp->relop;
            switch(ch)
            {
                case 1:fprintf(out, "<"); break;
                case 2:fprintf(out, ">"); break;
                case 3:fprintf(out, "<="); break;
                case 4:fprintf(out, ">="); break;
                default:fprintf(out, "wrong choice"); break;
            }
            fprintf(out, "%s;%s+=%d)\n",loop_index_temp->U->string,loop_index_temp->loopIndex->string,lambda_temp->phi_val);
            lambda_temp=lambda_temp->next;
            loop_index_temp=loop_index_temp->next;
        }
        }*/

        outputfile<<"\tfor(_CUDA_TILE=0;_CUDA_TILE<_NUM_TILE;_CUDA_TILE++)"<<endl<<"\t{";
        outputfile<<"\t\t_AFFINE_KERNEL<<<_BLOCKS,_THREADS>>>(";
        stmt_var_temp = stmt_var;
        for (it=mymap.begin(); it!=mymap.end(); ++it)
        {

            outputfile <<"_DEV_";
            outputfile << it->first;
            x=1;
            i=1;
            outputfile<<"_SZ_"<<it->first<<"_"<<i;

        }






    }
    int main(int argc, char * argv[])
    {
        SgProject *project = frontend (argc, argv);
        SgFunctionDeclaration* func = SageInterface::findMain(project);
        SgFunctionDefinition *defn = func->get_definition();
        SgFunctionParameterTypeList* param_type_list;
//SgProject *project = frontend (argc, argv);
        SgSourceFile*   file = isSgSourceFile(project->get_fileList()[0]);
//setOutputFileName(isSgFile(file));
//fprintf(file, "#define _NTHREAD 512\n#define _NBLOCK 65535\n#include<cuda.h>\n\n");
        Rose_STL_Container<SgNode*> forLoops = NodeQuery::querySubTree(defn,V_SgForStatement);
        for(Rose_STL_Container<SgNode*>::iterator iter = forLoops.begin(); iter!= forLoops.end(); iter++ )
        {
            SgExpression* ivarast=NULL, *lbast=NULL, *ubast=NULL, *stepast=NULL;
            SgForStatement* ab=isSgForStatement(*iter);
            SgStatementPtrList & init=(ab)->get_init_stmt();
            SgStatement* init1 = init.front();
            SgInitializedName* ivarname=NULL;
            visitorTraversal exampleTraversal;

            // Call the traversal starting at the project node of the AST
            // Traverse all header files and source file (the -rose:collectAllCommentsAndDirectives
            // commandline option controls if comments and CPP directives are separately extracted
            // from header files).
            exampleTraversal.traverse(project,preorder);
//fprintf(file,"int main () {");

            if (isAssignmentStatement(init1, &ivarast, &lbast))
            {
                SgVarRefExp* var = isSgVarRefExp(ivarast);
                if (var)
                {

                    ivarname = var->get_symbol()->get_declaration();
                }
            }
            string loop_id=(ivarname)->unparseToString();
            var_loop(*iter,loop_id);
            SimpleSelective_kernel_declaration_DEPENDENCY(*iter,loop_id);
            simple_loop_shrinking_AFFINE(*iter,loop_id);
        }

        return backend(project);
    }


