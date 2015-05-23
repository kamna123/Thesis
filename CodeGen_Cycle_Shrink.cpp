
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
using namespace SageBuilder
    map<string ,loop_var > mymap;
string newFilename_output = "new_source_file.c";
ofstream outputfile(newFilename_output.c_str(),ios::out);
static int count1=0;
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
                int flag=0;
                if((a)->unparseToString().compare(loop_id))
                {
                    mymap[a->unparseToString()].data_type=token;
                    mymap[a->unparseToString()].name=a->unparseToString();
                    mymap[a->unparseToString()].size=getArrayElementCount(arrT);
                    flag=1;
                }

            }
        }
    }
    /*std::cout << "mymap contains:\n";
    for (it=mymap.begin(); it!=mymap.end(); ++it)
      std::cout << it->first << " =" << it->second.name<<it->second.data_type<<it->second.size<<'\n';*/
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
void display_program( SgFunctionDefinition *defn  )
{
    Rose_STL_Container<SgNode*> forLoops = NodeQuery::querySubTree(defn,V_SgForStatement);
    for(Rose_STL_Container<SgNode*>::iterator iter = forLoops.begin(); iter!= forLoops.end(); iter++ )
    {
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
            //cout<<"Start = "<<startLine<<"end = "<<endline<<endl;
            i=1;

            // cout<<"i= "<<i<<endl;
            //fprintf(out, "start ");
            if(count1==0)
            {
                while(!fin.eof() && i<startLine  )
                {
                    fin.get(c);
                    // cout<<"i = "<<i<<"startLine = "<<startLine<<"c= "<<c<<endl;
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
                    //cout<<"k = "<<k<<"c = "<<c<< "i= "<<i<<endl;
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
                    // cout<<"i in inner loop "<<i<<"c= "<<c<<endl;
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
        //cout<<"k = "<<k<<"c = "<<c<< "i= "<<i<<endl;
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
        // cout<<"i in inner loop "<<i<<"c= "<<c<<endl;
        if(c=='\n')
        {
            i++;
            outfile<<endl;
        }
        else outfile<<c;
    }

}
void  SimpleSelective_kernel_declaration_DEPENDENCY(SgNode* forloop,string loop_id)
{

    outputfile<<"#define _NTHREAD 512"<<endl<<"#define _NBLOCK 65535"<<endl<<"#include<cuda.h>"<<endl<<endl;
    outputfile<< "__global__ void _AFFINE_KERNEL(";
    std::map<string ,loop_var >::iterator it;
    for (it=mymap.begin(); it!=mymap.end(); ++it)
    {
        outputfile<<it->second.data_type;
        outputfile<<"*";
        outputfile<<" ";
        outputfile<<",";
        outputfile<<"int ,";
    }
    outputfile<<"int ,";
    for(i=0; i<Total_Phi; i++)
        outputfile<<"int ,";
    outputfile<<"int ,";//for lower limit
    outputfile<<"int ,";//for upper limit
    outputfile<<"int );"<<endl<<endl;//for cuda tile
}
void cuda_kernel_declaration_NO_DEPENDENCY()
{
    outputfile<<"#define _NTHREAD 512"<<endl<<"#define _NBLOCK 65535"<<endl<<"#include<cuda.h>"<<endl<<endl;
    outputfile<< "__global__ void _AFFINE_KERNEL(";
    std::map<string ,loop_var >::iterator it;
    for (it=mymap.begin(); it!=mymap.end(); ++it)
    {
        outputfile<<it->second.data_type;
        outputfile<<"*";
        outputfile<<" ";
        outputfile<<",";
        outputfile<<"int ,";
    }
    outputfile<<"int ,";

    outputfile<<"int ,";//for lower limit
    outputfile<<"int ,";//for upper limit
    outputfile<<"int );"<<endl<<endl;//for cuda tile
}
void ExtendedShrinking_kernel_declaration_DEPENDENCY()
{
    outputfile<<"#define _NTHREAD 512"<<endl<<"#define _NBLOCK 65535"<<endl<<"#include<cuda.h>"<<endl<<endl;
    outputfile<< "__global__ void _AFFINE_KERNEL(";
    std::map<string ,loop_var >::iterator it;
    for (it=mymap.begin(); it!=mymap.end(); ++it)
    {
        outputfile<<it->second.data_type;
        outputfile<<"*";
        outputfile<<" ";
        outputfile<<",";
        outputfile<<"int ,";
    }
    outputfile<<"int ,";

    outputfile<<"int ,";//for lower limit
    outputfile<<"int ,";//for upper limit
    outputfile<<"int );"<<endl<<endl<<"#define MIN(a,b) (((a)<(b))?(a):(b))"<<endl<<"#include<cuda.h>"<<endl;//for cuda tile
}
void simple_loop_shrinking_AFFINE(SgNode* forloop,string loop_id)
{
    std::map<string ,loop_var >::iterator it;
    string loop=process(forloop->unparseToString());
    //cout<<"for loop is "<<loop;

    int i=1,x=1,j,temp_size=1,id_max=0;
    int max_array_size=1;   //contains the array with maximum size like 'a' for declaration like int a[20][30],b[2][10][10]
    int max_dimension_size=1;
    int max_size,sz;
    for (it=mymap.begin(); it!=mymap.end(); ++it)
    {
        temp_size=1;
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
            //printf("in id max\n");
        }
        //  printf("max_array_size=%d",max_array_size);
        //printf( "id_max: %d\n",id_max);
    }
    sz=max_size;
    temp_size=sz;
    // printf("sz=%d\n",temp_size);
    max_dimension_size=(temp_size>max_dimension_size)?temp_size:max_dimension_size;
    //printf("max_dim_size=%d\n",max_dimension_size);
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
    outputfile<< "\telse {"<<endl;
    if(id_max==1)
        outputfile<< "\t\t _THREADS.x=_NTHREAD;"<<endl<<"\t\t_NUM_BLOCKS=(_NUM_THREADS % _NTHREAD == 0)?(_NUM_THREADS/_NTHREAD):((_NUM_THREADS/_NTHREAD)+1);"<<endl<<"\t\tif(_NUM_BLOCKS<_NBLOCK)"<<endl<<"\t\t\t_BLOCKS.x=_NUM_BLOCKS;"<<endl<<"\t\telse {"<<endl<<"\t\t\t_BLOCKS.x=_NBLOCK;"<<endl<<"\t\t\tint temp=_NUM_BLOCKS;"<<endl<<"\t\t\t_NUM_TILE=(temp % _NBLOCK == 0)?(_NUM_BLOCKS/_NBLOCK):((_NUM_BLOCKS/_NBLOCK)+1);"<<endl<<"\t\t}"<<endl<<"\t}"<<endl;
    outputfile<<"\tint _CUDA_TILE;"<<endl;
    if(DependencyExists=='y')
    {

        struct Phi_Values *lambda_temp=lambda_var;
        outputfile<<"\tfor("<<loop_id<<"=0;"<<loop_id<<rel_op;
        outputfile<<b_val<<";"<<loop_id<<"+="<<lambda_temp->phi_val<<endl;
        lambda_temp=lambda_temp->next;
    }
    outputfile<<"\tfor(_CUDA_TILE=0;_CUDA_TILE<_NUM_TILE;_CUDA_TILE++)"<<endl<<"\t{";
    outputfile<<"\t\t_AFFINE_KERNEL<<<_BLOCKS,_THREADS>>>(";

    for (it=mymap.begin(); it!=mymap.end(); ++it)
    {
        outputfile <<"_DEV_";
        outputfile << it->first;
        x=1;
        i=1;
        outputfile<<"_SZ_"<<it->first<<"_"<<i;
    }
    if(DependencyExists=='y')
    {
        outputfile<<Total_Phi<<",";
        outputfile<<loop_id<<",";
    }
    outputfile<<"0,"<<b_val<<",";
    outputfile<<"_CUDA_TILE);"<<endl;
    outputfile<<"\t\tcudaDeviceSynchronize();"<<endl<<"\t}";
    for (it=mymap.begin(); it!=mymap.end(); ++it)
    {
        outputfile<<"\tcudaMemcpy("<<it->second.name<<", "<<"_DEV_"<<it->second.name<<","<<"sizeof(";
        outputfile<<it->second.data_type;
        outputfile<< ")";

        sz = it->second.size;
        x = 1;
        i=1;
        outputfile<< "*_SZ_"<<it->second.name<<"_"<<i;
        outputfile<< ", cudaMemcpyDeviceToHost);"<<endl;
    }
    for (it=mymap.begin(); it!=mymap.end(); ++it)
    {
        outputfile<<"\tcudaFree(_DEV_"<<it->second.name<<");"<<endl;
    }
}
void cuda_kernel_call_NO_DEPENDENCY(SgNode* forloop,string loop_id)
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
    outputfile<< "\telse {"<<endl;
    if(id_max==1)
        outputfile<< "\t\t _THREADS.x=_NTHREAD;"<<endl<<"\t\t_NUM_BLOCKS=(_NUM_THREADS % _NTHREAD == 0)?(_NUM_THREADS/_NTHREAD):((_NUM_THREADS/_NTHREAD)+1);"<<endl<<"\t\tif(_NUM_BLOCKS<_NBLOCK)"<<endl<<"\t\t\t_BLOCKS.x=_NUM_BLOCKS;"<<endl<<"\t\telse {"<<endl<<"\t\t\t_BLOCKS.x=_NBLOCK;"<<endl<<"\t\t\tint temp=_NUM_BLOCKS;"<<endl<<"\t\t\t_NUM_TILE=(temp % _NBLOCK == 0)?(_NUM_BLOCKS/_NBLOCK):((_NUM_BLOCKS/_NBLOCK)+1);"<<endl<<"\t\t}"<<endl<<"\t}"<<endl;
    outputfile<<"\tint _CUDA_TILE;"<<endl;
    outputfile<<"\tfor(_CUDA_TILE=0;_CUDA_TILE<_NUM_TILE;_CUDA_TILE++)"<<endl<<"\t{"<<endl;
    outputfile<<"\t\t_AFFINE_KERNEL<<<_BLOCKS,_THREADS>>>(";
    for (it=mymap.begin(); it!=mymap.end(); ++it)
    {

        outputfile <<"_DEV_";
        outputfile << it->first;
        x=1;
        i=1;
        outputfile<<"_SZ_"<<it->first<<"_"<<i;
    }

    for (it=mymap.begin(); it!=mymap.end(); ++it)
    {

        outputfile<<"\tcudaMemcpy("<<it->second.name<<", "<<"_DEV_"<<it->second.name<<","<<"sizeof(";
        outputfile<<it->second.data_type;
        outputfile<< ")";

        sz = it->second.size;
        x = 1;
        i=1;
        outputfile<< "*_SZ_"<<it->second.name<<"_"<<i;
        outputfile<< ", cudaMemcpyDeviceToHost);"<<endl;
    }
    for (it=mymap.begin(); it!=mymap.end(); ++it)
    {
        outputfile<<"\tcudaFree(_DEV_"<<it->second.name<<");"<<endl;
    }
}
void extCS_ConstantDistance_AFFINE(string loop_id,SgNode* forloop)
{
    int i,x,j,temp_size=1;
    int max_array_size=1;   //contains the array with maximum size like 'a' for declaration like int a[20][30],b[2][10][10]
    int max_dimension_size=1;
    std::map<string ,loop_var >::iterator it;
    string loop=process(forloop->unparseToString());
// cout<<"for loop is "<<loop;

    int i=1,x=1,j,temp_size=1,id_max=0;
    int max_array_size=1;   //contains the array with maximum size like 'a' for declaration like int a[20][30],b[2][10][10]
    int max_dimension_size=1;
    int max_size,sz;
    for (it=mymap.begin(); it!=mymap.end(); ++it)
    {
        temp_size=1;
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
    outputfile<< "\telse {"<<endl;
    if(id_max==1)
        outputfile<< "\t\t _THREADS.x=_NTHREAD;"<<endl<<"\t\t_NUM_BLOCKS=(_NUM_THREADS % _NTHREAD == 0)?(_NUM_THREADS/_NTHREAD):((_NUM_THREADS/_NTHREAD)+1);"<<endl<<"\t\tif(_NUM_BLOCKS<_NBLOCK)"<<endl<<"\t\t\t_BLOCKS.x=_NUM_BLOCKS;"<<endl<<"\t\telse {"<<endl<<"\t\t\t_BLOCKS.x=_NBLOCK;"<<endl<<"\t\t\tint temp=_NUM_BLOCKS;"<<endl<<"\t\t\t_NUM_TILE=(temp % _NBLOCK == 0)?(_NUM_BLOCKS/_NBLOCK):((_NUM_BLOCKS/_NBLOCK)+1);"<<endl<<"\t\t}"<<endl<<"\t}"<<endl;
    struct Phi_Values *lambda,*lambda_temp;
    outputfile<<"\tint ID_1, ID_2, START["<<id_max<<"];"<<endl;
    outputfile<<"\tint _CUDA_TILE;"<<endl;
    outputfile<<"\tint Phi["<<noOfNestedLoops<<"]={";
    lambda=lambda_var;
    while(lambda)
    {
        outputfile<<lambda->phi_val;
        lambda=lambda->next;
        if(lambda)  outputfile<<", ";
        else    outputfile<<"};"<<endl;
    }
    outputfile<<"\tint loopUpperLimits["<<noOfNestedLoops"]={";
    outputfile<<b_val;
    outputfile<<"};"<<endl;
    outputfile<<"\tfor(ID_1=1;ID_1<=";
    lambda=lambda_var;
    int minCount=0;
    outputfile<<b_val<<"/"<<lambda->phi_val;
    while(minCount--)
        outputfile<<")";
    lambda=lambda->next;
    outputfile<<"+1;ID_1++)"<<endl<<"\t{"<<endl;
    outputfile<<"\t\tfor(ID_2=0;ID_2<"<<noOfNestedLoops<<";ID_2++)"<<endl<<"\t\t{"<<endl;
    outputfile<<"\t\t\tif(Phi[ID_2]>=0)"<<endl<<"\t\t\t\tSTART[ID_2]=(ID_1-1)*Phi[ID_2];"<<endl<<"\t\t\telse"<<endl<<"\t\t\t\tSTART[ID_2]=loopUpperLimits[ID_2]+(ID_1-1)*Phi[ID_2];"<<endl;
    outputfile<<"\t\t}"<<endl;
    int r=0;
    lambda=lambda_var;
    outputfile<<"\tfor(_CUDA_TILE=0;_CUDA_TILE<_NUM_TILE;_CUDA_TILE++)"<<endl<<"\t{"<<endl;
    outputfile<<"\t\t_AFFINE_KERNEL<<<_BLOCKS,_THREADS>>>(";
    while(r<noOfNestedLoops)
    {
        for (it=mymap.begin(); it!=mymap.end(); ++it)
        {
            outputfile <<"_DEV_";
            outputfile << it->first;
            x=1;
            i=1;
            outputfile<<"_SZ_"<<it->first<<"_"<<i;
        }
        lambda_temp=lambda_var;
        i=0;
        while(i<noOfNestedLoops)
        {
            if(i<r)
                outputfile<<"START["<<i<<"]+"<<lambda_temp->phi_val<<", "<<b_val<<", ";
            else if(i>r)
                outputfile<<"START["<<i<<"],"<<b_val<<", "<<endl;
            else
                outputfile<<"START["<<r<<"], MIN(START["<<r<<"]+"<<lambda_temp->phi_val<<", "<<b_val<<"), ";
            lambda_temp=lambda_temp->next;
            i++;
        }
        outputfile<<"_CUDA_TILE);"<<endl;
        outputfile<<"\t\t\tcudaDeviceSynchronize();"<<endl<<"\t}"<<endl;
        lambda=lambda->next;
        r++;
    }
    outputfile<<"\t}"<<endl;
    for(it=mymap.begin(); it!=mymap.end(); ++it)
    {
        outputfile<<"\tcudaMemcpy("<<it->second.name<<", "<<"_DEV_"<<it->second.name<<","<<"sizeof(";
        outputfile<<it->second.data_type;
        outputfile<< ")";
        sz = it->second.size;
        x = 1;
        i=1;
        outputfile<< "*_SZ_"<<it->second.name<<"_"<<i;
        outputfile<< ", cudaMemcpyDeviceToHost);"<<endl;
    }
    for (it=mymap.begin(); it!=mymap.end(); ++it)
    {
        outputfile<<"\tcudaFree(_DEV_"<<it->second.name<<");"<<endl;
    }
}
void extCS_VariableDistance_AFFINE(string loop_id,SgNode* forloop)
{
    int i,x,j,temp_size=1;
    int max_array_size=1;   //contains the array with maximum size like 'a' for declaration like int a[20][30],b[2][10][10]
    int max_dimension_size=1;
    std::map<string ,loop_var >::iterator it;
    string loop=process(forloop->unparseToString());
    //cout<<"for loop is "<<loop;

    int i=1,x=1,j,temp_size=1,id_max=0;
    int max_array_size=1;   //contains the array with maximum size like 'a' for declaration like int a[20][30],b[2][10][10]
    int max_dimension_size=1;
    int max_size,sz;
    for (it=mymap.begin(); it!=mymap.end(); ++it)
    {
        temp_size=1;
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
    outputfile<< "\telse {"<<endl;
    if(id_max==1)
        outputfile<< "\t\t _THREADS.x=_NTHREAD;"<<endl<<"\t\t_NUM_BLOCKS=(_NUM_THREADS % _NTHREAD == 0)?(_NUM_THREADS/_NTHREAD):((_NUM_THREADS/_NTHREAD)+1);"<<endl<<"\t\tif(_NUM_BLOCKS<_NBLOCK)"<<endl<<"\t\t\t_BLOCKS.x=_NUM_BLOCKS;"<<endl<<"\t\telse {"<<endl<<"\t\t\t_BLOCKS.x=_NBLOCK;"<<endl<<"\t\t\tint temp=_NUM_BLOCKS;"<<endl<<"\t\t\t_NUM_TILE=(temp % _NBLOCK == 0)?(_NUM_BLOCKS/_NBLOCK):((_NUM_BLOCKS/_NBLOCK)+1);"<<endl<<"\t\t}"<<endl<<"\t}"<<endl;
    outputfile<<"\tint _CUDA_TILE;"<<endl;
    int temp=1;
    while(temp<=noOfNestedLoops)
    {
        outputfile<<"ID_"<<temp<<"=0, next_ID_"<<temp;
        if(temp<noOfNestedLoops)    outputfile<<", ";
        else    outputfile<<";"<<endl;
        temp++;
    }
    outputfile<<"\twhile(";
    temp=1;

    outputfile<<"(ID_"<<temp<<"<"<<b_val<<")";
    if(temp<noOfNestedLoops)    outputfile<<"&&";
    else    outputfile<<")"<<endl<<"\t{"<<endl;
    temp++;

    temp=1;
    int count,minCount=0;
    struct ReferencePair *refPairTemp;
    struct DDV *DDVtemp;
    struct DDV_Values *DDVtempValues;
    outputfile<<"\t\tnext_ID_"<<temp<<" = ";
    minCount=0;
    refPairTemp=RefPair;
    while(refPairTemp)
    {
        if(refPairTemp->next)
        {
            outputfile<<"MIN(";
            minCount++;
        }
        count=1;
        DDVtemp=refPairTemp->ddv;
        while(count!=temp)
        {
            count++;
            DDVtemp=DDVtemp->next;
        }
        outputfile<<"((("<<DDVtemp->ddv_values->value<<")";
        DDVtempValues=DDVtemp->ddv_values->next;
        count=1;
        while(DDVtempValues)
        {
            if(DDVtempValues->next==NULL)   outpufile<<")/("<<DDVtempValues->value<<"))";
            else
            {
                outputfile<<"+("<<DDVtempValues->value<<")*ID_"<<count;
                count++;
            }
            DDVtempValues=DDVtempValues->next;
        }
        refPairTemp=refPairTemp->next;
        if(refPairTemp) outputfile<<", ";
        else
            while(minCount--)
                outputfile<<")";
    }
    outputfile<<";"<<endl;
    temp++;
    if(noOfNestedLoops==1)
    {
        outputfile<<"\tfor(_CUDA_TILE=0;_CUDA_TILE<_NUM_TILE;_CUDA_TILE++)"<<endl<<"\t{"<<endl;
        outputfile<<"\t\t_AFFINE_KERNEL<<<_BLOCKS,_THREADS>>>(";
        for (it=mymap.begin(); it!=mymap.end(); ++it)
        {
            outputfile <<"_DEV_";
            outputfile << it->first;
            x=1;
            i=1;
            outputfile<<"_SZ_"<<it->first<<"_"<<i;
        }
        outputfile<<"ID_1, MIN(next_ID_1,"<<b_val<<"), _CUDA_TILE);"<<endl;
        outputfile<<"\t\t\tcudaDeviceSynchronize();"<<endl<<"\t\t}"<<endl;
        outputfile<<"\tfor(_CUDA_TILE=0;_CUDA_TILE<_NUM_TILE;_CUDA_TILE++)"<<endl<<"\t{"<<endl;
        outputfile<<"\t\t_AFFINE_KERNEL<<<_BLOCKS,_THREADS>>>(";
        for (it=mymap.begin(); it!=mymap.end(); ++it)
        {
            outputfile <<"_DEV_";
            outputfile << it->first;
            x=1;
            i=1;
            outputfile<<"_SZ_"<<it->first<<"_"<<i;
        }
        outputfile<<"next_ID_1, "<<b_val<<", _CUDA_TILE);"<<endl;
        outputfile<<"\t\t\tcudaDeviceSynchronize();"<<endl<<"\t\t}"<<endl;
    }
    temp=1;
    while(temp<=noOfNestedLoops)
    {
        outputfile<<"\t\tID_"<<temp<<"=next_ID_"<<temp<<";"<<endl;
        temp++;
    }
    outputfile<<"\t}"<<endl;
    for (it=mymap.begin(); it!=mymap.end(); ++it)
    {

        outputfile<<"\tcudaMemcpy("<<it->second.name<<", "<<"_DEV_"<<it->second.name<<","<<"sizeof(";
        outputfile<<it->second.data_type;
        outputfile<< ")";
        sz = it->second.size;
        x = 1;
        i=1;
        outputfile<< "*_SZ_"<<it->second.name<<"_"<<i;
        outputfile<< ", cudaMemcpyDeviceToHost);"<<endl;
    }
    for (it=mymap.begin(); it!=mymap.end(); ++it)
    {
        outputfile<<"\tcudaFree(_DEV_"<<it->second.name<<");"<<endl;
    }

}
/***********************************  KERNEL DEFINITION CODE GENERATION ********************************************************/

//Function for kernel definition if dependency exists
void SimpleSelective_kernel_definition_DEPENDENCY(char *shrinking_type,string loop_id,SgNode* forloop,SgFunctionDefinition *defn)
{
    int x,i;
    std::map<string ,loop_var >::iterator it;
    string loop=process(forloop->unparseToString());
    cout<<"for loop is "<<loop;
    outputfile<<"\n\n__global__ void _AFFINE_KERNEL(";
    for (it=mymap.begin(); it!=mymap.end(); ++it)
    {
        outputfile<<it->second.data_type;
        outputfile<<"*";
        outputfile<<" ";
        outputfile<<it->second.name;
        i=1;
        outputfile<<"int ";
        outputfile<< "_SZ_"<<it->second.name<<"_"<<i<<",";
    }
    outputfile<<"int phi_count, ";
    int temp=Total_Phi;
    outputfile<<"int CUDA_"<<loop_id<<"," ;
    outputfile<<"int CUDA_L_"<<loop_id<<","<<"int CUDA_U_"<<loop_id<<",";
    outputfile<<"int _CUDA_TILE)"<<endl<<"{"<<endl;
    outputfile<<"\tint "<< loop_id<<" = gridDim.x*blockDim.x*_CUDA_TILE + blockDim.x*blockIdx.x + threadIdx.x;"<<endl;
    int lambda_k=1;

    struct Phi_Values *lambda_temp=lambda_var;
    outputfile<<"\tif((CUDA_"<<loop_id<<"<="<<loop_id<<")&&("<<loop_id<<"<(CUDA_"<<loop_id<<"+"<<lambda_temp->phi_val<<"))&&("<<loop_id;
    outputfile<<rel_op;
    outputfile<<"CUDA_U_"<<loop_id<<")){"<<endl;
    if(lambda_temp->phi_val>=1)
        lambda_k=0;
    SgForStatement* forLoop=isSgForStatement(forloop);
    SgBasicBlock* loopBody = isSgBasicBlock(forLoop->get_loop_body());
    Rose_STL_Container<SgStatement*> forLoops = loopBody->get_statements();
    for(Rose_STL_Container<SgStatement*>::iterator iter = forLoops.begin(); iter!= forLoops.end(); iter++ )
    {
        outputfile<< (*iter)->unparseToString()<<"\n";
    }
    temp=Total_Phi;
    while(temp--)
    {
        outputfile<< "}";
    }
    outputfile<<"}"<<endl<<endl;
}
void cuda_kernel_definition_NO_DEPENDENCY(string loop_id,SgNode* forloop,SgFunctionDefinition *defn)
{
    int x,i;
    std::map<string ,loop_var >::iterator it;
    string loop=process(forloop->unparseToString());
    cout<<"for loop is "<<loop;
    outputfile<<"\n\n__global__ void _AFFINE_KERNEL(";
    for (it=mymap.begin(); it!=mymap.end(); ++it)
    {
        outputfile<<it->second.data_type;
        outputfile<<"*";
        outputfile<<" ";
        outputfile<<it->second.name;
        i=1;
        outputfile<<"int ";
        outputfile<< "_SZ_"<<it->second.name<<"_"<<i<<",";
    }
    outputfile<<"int CUDA_L_"<<loop_id<<","<<"int CUDA_U_"<<loop_id<<",";
    outputfile<<"int _CUDA_TILE)"<<endl<<"{"<<endl;
    outputfile<<"\tint "<< loop_id<<" = gridDim.x*blockDim.x*_CUDA_TILE + blockDim.x*blockIdx.x + threadIdx.x;"<<endl;
    struct Phi_Values *lambda_temp=lambda_var;

    outputfile<<"\tif((CUDA_L_"<<loop_id<<"<="<<loop_id<<")&&("<<loop_id<<"<=CUDA_U_"<<loop_id<<")){"<<endl;
    SgForStatement* forLoop=isSgForStatement(forloop);
    SgBasicBlock* loopBody = isSgBasicBlock(forLoop->get_loop_body());
    Rose_STL_Container<SgStatement*> forLoops = loopBody->get_statements();
    for(Rose_STL_Container<SgStatement*>::iterator iter = forLoops.begin(); iter!= forLoops.end(); iter++ )
    {
        outputfile<< (*iter)->unparseToString()<<"\n";
    }
    outputfile<<"}";
    outputfile<<"}"<endl<<endl;
}
void ExtendedShrinking_kernel_definition_DEPENDENCY(string loop_id,SgNode* forloop,SgFunctionDefinition *defn)
{
    int x,i;
    std::map<string ,loop_var >::iterator it;
    string loop=process(forloop->unparseToString());
    cout<<"for loop is "<<loop;
    outputfile<<"\n\n__global__ void _AFFINE_KERNEL(";
    for (it=mymap.begin(); it!=mymap.end(); ++it)
    {
        outputfile<<it->second.data_type;
        outputfile<<"*";
        outputfile<<" ";
        outputfile<<it->second.name;
        i=1;
        outputfile<<"int ";
        outputfile<< "_SZ_"<<it->second.name<<"_"<<i<<",";
    }
    outputfile<<"int CUDA_L_"<<loop_id<<","<<"int CUDA_U_"<<loop_id<<",";
    outputfile<<"int _CUDA_TILE)"<<endl<<"{"<<endl;
    outputfile<<"\tint "<< loop_id<<" = gridDim.x*blockDim.x*_CUDA_TILE + blockDim.x*blockIdx.x + threadIdx.x;"<<endl;
    struct Phi_Values *lambda_temp=lambda_var;

    outputfile<<"\tif((CUDA_L_"<<loop_id<<"<="<<loop_id<<")&&("<<loop_id<<"<=CUDA_U_"<<loop_id<<")){"<<endl;
    SgForStatement* forLoop=isSgForStatement(forloop);
    SgBasicBlock* loopBody = isSgBasicBlock(forLoop->get_loop_body());
    Rose_STL_Container<SgStatement*> forLoops = loopBody->get_statements();
    for(Rose_STL_Container<SgStatement*>::iterator iter = forLoops.begin(); iter!= forLoops.end(); iter++ )
    {
        outputfile<< (*iter)->unparseToString()<<"\n";
    }
    outputfile<<"}";
    outputfile<<"}"<endl<<endl;
}
