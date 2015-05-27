
#include "rose.h"
#include "ds.hpp"
#include "CodeGen_Cycle_Shrink.hpp"
#include "extShrinking.hpp"
#include <iostream>
#include <set>
#include <vector>
#include <iterator>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <cstdio>
#include <cstdlib>
#include <fstream>
using namespace std;
using namespace SageInterface;
using namespace SageBuilder;
struct loop_var
{
    string data_type;
    int size;
    string name;
};
    map<string ,loop_var > mymap;


int count1=0;
void var_loop(SgNode* forloop,string loop_id)
{

    mymap.clear();
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
                if((a)->unparseToString().compare(loop_id) && arrT)
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

void  SimpleSelective_kernel_declaration_DEPENDENCY(SgNode* forloop,string loop_id,int i)
{

    
    outputfile<< "__global__ void _AFFINE_KERNEL_"<<i<<"(";
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
    for(int i=0; i<Total_Phi; i++)
        outputfile<<"int ,";
    outputfile<<"int ,";//for lower limit
    outputfile<<"int ,";//for upper limit
    outputfile<<"int );"<<endl<<endl;//for cuda tile
}
void cuda_kernel_declaration_NO_DEPENDENCY(int i)
{
   // outputfile<<"#define _NTHREAD 512"<<endl<<"#define _NBLOCK 65535"<<endl<<"#include<cuda.h>"<<endl<<endl;
   outputfile<< "__global__ void _AFFINE_KERNEL_"<<i<<"(";
    std::map<string ,loop_var >::iterator it;
    for (it=mymap.begin(); it!=mymap.end(); ++it)
    {
        outputfile<<it->second.data_type;
        outputfile<<"*";
        outputfile<<" ";
        outputfile<<",";
        outputfile<<"int ,";
    }
   

    outputfile<<"int ,";//for lower limit
    outputfile<<"int ,";//for upper limit
    outputfile<<"int );"<<endl<<endl;//for cuda tile
}
void ExtendedShrinking_kernel_declaration_DEPENDENCY(int i)
{
   // outputfile<<"#define _NTHREAD 512"<<endl<<"#define _NBLOCK 65535"<<endl<<"#include<cuda.h>"<<endl<<endl;
    outputfile<< "__global__ void _AFFINE_KERNEL_"<<i<<"(";
    std::map<string ,loop_var >::iterator it;
    for (it=mymap.begin(); it!=mymap.end(); ++it)
    {
        outputfile<<it->second.data_type;
        outputfile<<"*";
        outputfile<<" ";
        outputfile<<",";
        outputfile<<"int ,";
    }
   

    outputfile<<"int ,";//for lower limit
    outputfile<<"int ,";//for upper limit
    outputfile<<"int );"<<endl<<endl<<"#define MIN(a,b) (((a)<(b))?(a):(b))"<<endl<<"#include<cuda.h>"<<endl;//for cuda tile
}
void simple_loop_shrinking_AFFINE(SgNode* forloop,string loop_id,int i)
{
    std::map<string ,loop_var >::iterator it;
    string loop=process(forloop->unparseToString());
    //cout<<"for loop is "<<loop;
   
    int x=1,j,temp_size=1,id_max=0;
    int max_array_size=1;   //contains the array with maximum size like 'a' for declaration like int a[20][30],b[2][10][10]
    int max_dimension_size=1;
    int max_size,sz;
    outputfile<<endl<<"\t#ifdef DATASET"<<endl<<"\t\tchar* outfile = (char*)malloc(sizeof(char)*(strlen(readfile)+50));"<<endl<<"\t\tstrcpy(outfile, readfile);"<<endl<<"\t\tstrcat(outfile, \".data\");"<<endl<<"\t\tFILE* fp;"<<endl<<"\t\tfp = fopen(outfile, \"a\");"<<endl<<"\t#endif"<<endl;
    outputfile<<endl<<"\t#ifdef TIME"<<endl<<"\t\tstruct timespec start_"<<i<<", end_"<<i<<", mid_start_"<<i<<", mid_end_"<<i<<";"<<endl<<"\t\tdouble runTime_"<<i<<", pre_time_"<<i<<", post_time_"<<i<<", computeTime_"<<i<<";"<<endl<<"\t#endif"<<endl;
    for (it=mymap.begin(); it!=mymap.end(); ++it)
    {
        temp_size=1;
        outputfile<< "\t"<<it->second.data_type;
        outputfile<<" _SZ_"<<(it->second.name)<<"_"<<i<<" = " ;
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
    outputfile<<endl<<"\t#ifdef TIME"<<endl<<"\t\tclock_gettime(CLOCK_MONOTONIC, &start_"<<i<<");"<<endl<<"\t#endif"<<endl;
    outputfile<<endl<<"\t// ----------Allocating memory to Kernel Variable and copying them on device----------"<<endl;
    for (it=mymap.begin(); it!=mymap.end(); ++it)
    {
        outputfile<< "\t"<<it->second.data_type;
        outputfile<<"*_DEV_"<<(it->second.name)<<"_"<<i<<";"<<endl;
        outputfile<<"\tcudaMalloc((void**) &_DEV_"<<(it->second.name)<<"_"<<i<<","<<"sizeof(";
        outputfile<<it->second.data_type;
        outputfile<< ")";
        sz = it->second.size;
        x = 1;
       // i=1;
        outputfile<< " *_SZ_"<<it->second.name<<"_"<<i;
        outputfile<< ");"<<endl;
        outputfile<<"\tcudaMemcpy(_DEV_"<<it->second.name<<"_"<<i<<","<<it->second.name<< ","<<"sizeof(";
        outputfile<<it->second.data_type;
        outputfile<< ")";
        sz = it->second.size;
        x = 1;
        outputfile<<" *_SZ_"<<it->second.name<<"_"<<i;
        outputfile<< ", cudaMemcpyHostToDevice);"<<endl;
    }
    outputfile<<"\tint _NUM_THREADS_"<<i<< "= "<< max_array_size<<";"<<endl;
    outputfile<<"\tfloat _NUM_BLOCKS_"<<i<<"=1;"<<endl<<"\tint _NUM_TILE_"<<i<<"=1;"<<endl;
    outputfile<<"\tdim3 _THREADS_"<<i<<"(512);"<<endl<<"\tdim3 _BLOCKS_"<<i<<"(1);"<<endl;
    outputfile<< "\tif(_NUM_THREADS_"<<i<< " < _NTHREAD)"<<endl;
    if(id_max==1)
        outputfile<<"\t{"<<endl<<"\t\t_THREADS_"<<i<< ".x=_NUM_THREADS_"<<i<< ";"<<endl<<"\t}"<<endl;
    outputfile<< "\telse {"<<endl;
    if(id_max==1)
        outputfile<< "\t\t _THREADS_"<<i<< ".x=_NTHREAD;"<<endl<<"\t\t_NUM_BLOCKS_"<<i<< "=(_NUM_THREADS_"<<i<< " % _NTHREAD == 0)?(_NUM_THREADS_"<<i<< "/_NTHREAD):((_NUM_THREADS_"<<i<< "/_NTHREAD)+1);"<<endl<<"\t\tif(_NUM_BLOCKS_"<<i<< "<_NBLOCK)"<<endl<<"\t\t\t_BLOCKS_"<<i<< ".x=_NUM_BLOCKS_"<<i<< ";"<<endl<<"\t\telse {"<<endl<<"\t\t\t_BLOCKS_"<<i<< ".x=_NBLOCK;"<<endl<<"\t\t\tint temp_"<<i<< "=_NUM_BLOCKS_"<<i<< ";"<<endl<<"\t\t\t_NUM_TILE_"<<i<< "=(temp_"<<i<< " % _NBLOCK == 0)?(_NUM_BLOCKS_"<<i<< "/_NBLOCK):((_NUM_BLOCKS_"<<i<< "/_NBLOCK)+1);"<<endl<<"\t\t}"<<endl<<"\t}"<<endl;
    outputfile<<endl<<"\t#ifdef TIME"<<endl<<"\t\tclock_gettime(CLOCK_MONOTONIC, &mid_start_"<<i<<");"<<endl<<"\t#endif"<<endl<<endl;
    outputfile<<"\tint _CUDA_TILE_"<<i<< ";"<<endl;
    if(DependencyExists=='y')
    {

        struct Phi_Values *lambda_temp=lambda_var;
        outputfile<<"\tfor("<<loop_id<<"=0;"<<loop_id<<rel_op;
        outputfile<<b_val<<";"<<loop_id<<"+="<<lambda_temp->phi_val<<")"<<endl;
        lambda_temp=lambda_temp->next;
    }
    outputfile<<"\tfor(_CUDA_TILE_"<<i<< "=0;_CUDA_TILE_"<<i<< "<_NUM_TILE_"<<i<< ";_CUDA_TILE_"<<i<< "++)"<<endl<<"\t{";
    outputfile<<"\t\t_AFFINE_KERNEL_"<<i<<"<<<_BLOCKS_"<<i<<",_THREADS_"<<i<<">>>(";

    for (it=mymap.begin(); it!=mymap.end(); ++it)
    {
        outputfile <<" _DEV_";
        outputfile << it->first<<"_"<<i<<",";
        x=1;
      //  i=1;
        outputfile<<" _SZ_"<<it->first<<"_"<<i<<",";
    }
    if(DependencyExists=='y')
    {
        outputfile<<Total_Phi<<",";
        outputfile<<loop_id<<",";
    }
    outputfile<<"0,"<<b_val<<",";
    outputfile<<"_CUDA_TILE_"<<i<< ");"<<endl;
    outputfile<<"\t\tcudaDeviceSynchronize();"<<endl<<"\t}";
    outputfile<<endl<<"\t#ifdef TIME"<<endl<<"\t\tclock_gettime(CLOCK_MONOTONIC, &mid_end_"<<i<<");"<<endl<<"\t#endif"<<endl;
    for (it=mymap.begin(); it!=mymap.end(); ++it)
    {
        outputfile<<"\tcudaMemcpy("<<it->second.name<<", "<<"_DEV_"<<it->second.name<<"_"<<i<<","<<"sizeof(";
        outputfile<<it->second.data_type;
        outputfile<< ")";

        sz = it->second.size;
        x = 1;
       // i=1;
        outputfile<< " *_SZ_"<<it->second.name<<"_"<<i;
        outputfile<< ", cudaMemcpyDeviceToHost);"<<endl;
    }
    for (it=mymap.begin(); it!=mymap.end(); ++it)
    {
        outputfile<<"\tcudaFree(_DEV_"<<it->second.name<<"_"<<i<<");"<<endl;
    }
     outputfile<<endl<<"\t#ifdef TIME"<<endl<<"\t\tclock_gettime(CLOCK_MONOTONIC, &end_"<<i<<");"<<endl;
     outputfile<<"\t\tpre_time_"<<i<<" = (double) ((((&mid_start_"<<i<<")->tv_sec * 1000000000) + (&mid_start_"<<i<<")->tv_nsec) - (((&start_"<<i<<")->tv_sec * 1000000000) + (&start_"<<i<<")->tv_nsec)) / 1000000000;"<<endl<<"\t\tpost_time_"<<i<<" = (double) ((((&end_"<<i<<")->tv_sec * 1000000000) + (&end_"<<i<<")->tv_nsec) - (((&mid_end_"<<i<<")->tv_sec * 1000000000) + (&mid_end_"<<i<<")->tv_nsec)) / 1000000000;"<<endl<<"\t\tcomputeTime_"<<i<<" = (double) ((((&mid_end_"<<i<<")->tv_sec * 1000000000) + (&mid_end_"<<i<<")->tv_nsec) - (((&mid_start_"<<i<<")->tv_sec * 1000000000) + (&mid_start_"<<i<<")->tv_nsec)) / 1000000000;"<<endl<<"\t\trunTime_"<<i<<" = (double) ((((&end_"<<i<<")->tv_sec * 1000000000) + (&end_"<<i<<")->tv_nsec) - (((&start_"<<i<<")->tv_sec * 1000000000) + (&start_"<<i<<")->tv_nsec)) / 1000000000;"<<endl<<"\t#endif"<<endl<<endl;
  outputfile<<"\t#ifdef DATASET"<<endl<<"\t\tfprintf(fp,\"%%d,%%d,%%d,%%d,%%d,%%.14f,%%.14f,%%.14f,%%.14f,%%d\\n\",N,_NTHREAD*_NBLOCK,_THREADS_"<<i<<".x,_BLOCKS_"<<i<<".x,data,pre_time_"<<i<<",computeTime_"<<i<<",post_time_"<<i<<",runTime_"<<i<<",_CUDA_TILE_"<<i<<");"<<endl<<"\t\tfclose(fp);"<<endl<<"\t\tfclose(f);"<<endl<<"\t#else"<<endl<<"\t#ifdef TIME"<<endl<<"\t\tprintf(\"Runtime:%%f\\n\",runTime_"<<i<<");"<<endl<<"\t#endif"<<endl<<"\t#endif"<<endl;
    
}
void cuda_kernel_call_NO_DEPENDENCY(SgNode* forloop,string loop_id,int i)
{
    std::map<string ,loop_var >::iterator it;
    string loop=process(forloop->unparseToString());
    cout<<"for loop is "<<loop;

    int x=1,j,temp_size=1,id_max=0;
    int max_array_size=1;   //contains the array with maximum size like 'a' for declaration like int a[20][30],b[2][10][10]
    int max_dimension_size=1;
    int max_size,sz;
        outputfile<<endl<<"\t#ifdef DATASET"<<endl<<"\t\tchar* outfile = (char*)malloc(sizeof(char)*(strlen(readfile)+50));"<<endl<<"\t\tstrcpy(outfile, readfile);"<<endl<<"\t\tstrcat(outfile, \".data\");"<<endl<<"\t\tFILE* fp;"<<endl<<"\t\tfp = fopen(outfile, \"a\");"<<endl<<"\t#endif"<<endl;
    outputfile<<endl<<"\t#ifdef TIME"<<endl<<"\t\tstruct timespec start_"<<i<<", end_"<<i<<", mid_start_"<<i<<", mid_end_"<<i<<";"<<endl<<"\t\tdouble runTime_"<<i<<", pre_time_"<<i<<", post_time_"<<i<<", computeTime_"<<i<<";"<<endl<<"\t#endif"<<endl;
    for (it=mymap.begin(); it!=mymap.end(); ++it)
    {
        temp_size=1;
        outputfile<< "\t"<<it->second.data_type;
        outputfile<<" _SZ_"<<(it->second.name)<<"_"<<i<<" = " ;
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
    outputfile<<endl<<"\t#ifdef TIME"<<endl<<"\t\tclock_gettime(CLOCK_MONOTONIC, &start_"<<i<<");"<<endl<<"\t#endif"<<endl;
    outputfile<<endl<<"\t// ----------Allocating memory to Kernel Variable and copying them on device----------"<<endl;
    for (it=mymap.begin(); it!=mymap.end(); ++it)
    {
        outputfile<< "\t"<<it->second.data_type;
        outputfile<<" *_DEV_"<<(it->second.name)<<"_"<<i<<";"<<endl;
        outputfile<<"\tcudaMalloc((void**) &_DEV_"<<(it->second.name)<<"_"<<i<<","<<"sizeof(";
        outputfile<<it->second.data_type;
        outputfile<< ")";
        sz = it->second.size;
        x = 1;
        //i=1;
        outputfile<< " *_SZ_"<<it->second.name<<"_"<<i;
        outputfile<< ");"<<endl;

        outputfile<<"\tcudaMemcpy(_DEV_"<<it->second.name<<"_"<<i<<","<<it->second.name<< ","<<"sizeof(";
        outputfile<<it->second.data_type;
        outputfile<< ")";
        sz = it->second.size;
        x = 1;
        outputfile<<"*_SZ_"<<it->second.name<<"_"<<i;
        outputfile<< ", cudaMemcpyHostToDevice);"<<endl;
    }
    outputfile<<"\tint _NUM_THREADS_"<<i<< "= "<< max_array_size<<";"<<endl;
    outputfile<<"\tfloat _NUM_BLOCKS_"<<i<< "=1;"<<endl<<"\tint _NUM_TILE_"<<i<< "=1;"<<endl;
    outputfile<<"\tdim3 _THREADS_"<<i<< "(512);"<<endl<<"\tdim3 _BLOCKS_"<<i<< "(1);"<<endl;
    outputfile<< "\tif(_NUM_THREADS_"<<i<< " < _NTHREAD)"<<endl;
    if(id_max==1)
        outputfile<<"\t{"<<endl<<"\t\t_THREADS_"<<i<< ".x=_NUM_THREADS_"<<i<< ";"<<endl<<"\t}"<<endl;
    outputfile<< "\telse {"<<endl;
    if(id_max==1)
        outputfile<< "\t\t _THREADS_"<<i<< ".x=_NTHREAD;"<<endl<<"\t\t_NUM_BLOCKS_"<<i<< "=(_NUM_THREADS_"<<i<< " % _NTHREAD == 0)?(_NUM_THREADS_"<<i<< "/_NTHREAD):((_NUM_THREADS_"<<i<< "/_NTHREAD)+1);"<<endl<<"\t\tif(_NUM_BLOCKS_"<<i<< "<_NBLOCK)"<<endl<<"\t\t\t_BLOCKS_"<<i<< ".x=_NUM_BLOCKS_"<<i<< ";"<<endl<<"\t\telse {"<<endl<<"\t\t\t_BLOCKS_"<<i<< ".x=_NBLOCK;"<<endl<<"\t\t\tint temp_"<<i<< "=_NUM_BLOCKS_"<<i<< ";"<<endl<<"\t\t\t_NUM_TILE_"<<i<< "=(temp_"<<i<< " % _NBLOCK == 0)?(_NUM_BLOCKS_"<<i<< "/_NBLOCK):((_NUM_BLOCKS_"<<i<< "/_NBLOCK)+1);"<<endl<<"\t\t}"<<endl<<"\t}"<<endl;
    outputfile<<endl<<"\t#ifdef TIME"<<endl<<"\t\tclock_gettime(CLOCK_MONOTONIC, &mid_start_"<<i<<");"<<endl<<"\t#endif"<<endl<<endl;
    outputfile<<"\tint _CUDA_TILE_"<<i<< ";"<<endl;
    outputfile<<"\tfor(_CUDA_TILE_"<<i<< "=0;_CUDA_TILE_"<<i<< "<_NUM_TILE_"<<i<< ";_CUDA_TILE_"<<i<< "++)"<<endl<<"\t{"<<endl;
    outputfile<<"\t\t_AFFINE_KERNEL_"<<i<<"<<<_BLOCKS_"<<i<< ",_THREADS_"<<i<< ">>>(";
    for (it=mymap.begin(); it!=mymap.end(); ++it)
    {

        outputfile <<" _DEV_";
        outputfile << it->first<<"_"<<i<<",";
        x=1;
       // i=1;
        outputfile<<" _SZ_"<<it->first<<"_"<<i<<",";
    }
    outputfile<<"0,"<<b_val<<", ";
    outputfile<<"_CUDA_TILE_"<<i<< ");"<<endl;
    outputfile<<"\t\tcudaDeviceSynchronize();"<<endl<<"\t}"<<endl;
    outputfile<<endl<<"\t#ifdef TIME"<<endl<<"\t\tclock_gettime(CLOCK_MONOTONIC, &mid_end_"<<i<<");"<<endl<<"\t#endif"<<endl;
    for (it=mymap.begin(); it!=mymap.end(); ++it)
    {

        outputfile<<"\tcudaMemcpy("<<it->second.name<<", "<<"_DEV_"<<it->second.name<<"_"<<i<<","<<"sizeof(";
        outputfile<<it->second.data_type;
        outputfile<< ")";

        sz = it->second.size;
        x = 1;
      //  i=1;
        outputfile<< " *_SZ_"<<it->second.name<<"_"<<i;
        outputfile<< ", cudaMemcpyDeviceToHost);"<<endl;
    }
    for (it=mymap.begin(); it!=mymap.end(); ++it)
    {
        outputfile<<"\tcudaFree(_DEV_"<<it->second.name<<"_"<<i<<");"<<endl;
    }
    outputfile<<endl<<"\t#ifdef TIME"<<endl<<"\t\tclock_gettime(CLOCK_MONOTONIC, &end_"<<i<<");"<<endl<<endl;
     outputfile<<"\t\tpre_time_"<<i<<" = (double) ((((&mid_start_"<<i<<")->tv_sec * 1000000000) + (&mid_start_"<<i<<")->tv_nsec) - (((&start_"<<i<<")->tv_sec * 1000000000) + (&start_"<<i<<")->tv_nsec)) / 1000000000;"<<endl<<"\t\tpost_time_"<<i<<" = (double) ((((&end_"<<i<<")->tv_sec * 1000000000) + (&end_"<<i<<")->tv_nsec) - (((&mid_end_"<<i<<")->tv_sec * 1000000000) + (&mid_end_"<<i<<")->tv_nsec)) / 1000000000;"<<endl<<"\t\tcomputeTime_"<<i<<" = (double) ((((&mid_end_"<<i<<")->tv_sec * 1000000000) + (&mid_end_"<<i<<")->tv_nsec) - (((&mid_start_"<<i<<")->tv_sec * 1000000000) + (&mid_start_"<<i<<")->tv_nsec)) / 1000000000;"<<endl<<"\t\trunTime_"<<i<<" = (double) ((((&end_"<<i<<")->tv_sec * 1000000000) + (&end_"<<i<<")->tv_nsec) - (((&start_"<<i<<")->tv_sec * 1000000000) + (&start_"<<i<<")->tv_nsec)) / 1000000000;"<<endl<<"\t#endif"<<endl<<endl;
  outputfile<<"\t#ifdef DATASET"<<endl<<"\t\tfprintf(fp,\"%%d,%%d,%%d,%%d,%%d,%%.14f,%%.14f,%%.14f,%%.14f,%%d\\n\",N,_NTHREAD*_NBLOCK,_THREADS_"<<i<<".x,_BLOCKS_"<<i<<".x,data,pre_time_"<<i<<",computeTime_"<<i<<",post_time_"<<i<<",runTime_"<<i<<",_CUDA_TILE_"<<i<<");"<<endl<<"\t\tfclose(fp);"<<endl<<"\t\tfclose(f);"<<endl<<"\t#else"<<endl<<"\t#ifdef TIME"<<endl<<"\t\tprintf(\"Runtime:%%f\\n\",runTime_"<<i<<");"<<endl<<"\t#endif"<<endl<<"\t#endif"<<endl;
}
void extCS_ConstantDistance_AFFINE(string loop_id,SgNode* forloop,int i)
{
    
    std::map<string ,loop_var >::iterator it;
    string loop=process(forloop->unparseToString());
// cout<<"for loop is "<<loop;
     noOfNestedLoops=1;
    int x=1,j,temp_size=1,id_max=0;
    int max_array_size=1;   //contains the array with maximum size like 'a' for declaration like int a[20][30],b[2][10][10]
    int max_dimension_size=1;
    int max_size,sz;
     outputfile<<endl<<"\t#ifdef DATASET"<<endl<<"\t\tchar* outfile = (char*)malloc(sizeof(char)*(strlen(readfile)+50));"<<endl<<"\t\tstrcpy(outfile, readfile);"<<endl<<"\t\tstrcat(outfile, \".data\");"<<endl<<"\t\tFILE* fp;"<<endl<<"\t\tfp = fopen(outfile, \"a\");"<<endl<<"\t#endif"<<endl;
    outputfile<<endl<<"\t#ifdef TIME"<<endl<<"\t\tstruct timespec start_"<<i<<", end_"<<i<<", mid_start_"<<i<<", mid_end_"<<i<<";"<<endl<<"\t\tdouble runTime_"<<i<<", pre_time_"<<i<<", post_time_"<<i<<", computeTime_"<<i<<";"<<endl<<"\t#endif"<<endl;
    for (it=mymap.begin(); it!=mymap.end(); ++it)
    {
        temp_size=1;
        outputfile<< "\t"<<it->second.data_type;
        outputfile<<" _SZ_"<<(it->second.name)<<"_"<<i<<" = " ;
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
    outputfile<<endl<<"\t#ifdef TIME"<<endl<<"\t\tclock_gettime(CLOCK_MONOTONIC, &start_"<<i<<");"<<endl<<"\t#endif"<<endl;
    outputfile<<endl<<"\t// ----------Allocating memory to Kernel Variable and copying them on device----------"<<endl;
    for (it=mymap.begin(); it!=mymap.end(); ++it)
    {
        outputfile<< "\t"<<it->second.data_type;
        outputfile<<" *_DEV_"<<(it->second.name)<<"_"<<i<<";"<<endl;
        outputfile<<"\tcudaMalloc((void**) &_DEV_"<<(it->second.name)<<"_"<<i<<","<<"sizeof(";
        outputfile<<it->second.data_type;
        outputfile<< ")";
        sz = it->second.size;
        x = 1;
      
        outputfile<< " *_SZ_"<<it->second.name<<"_"<<i;
        outputfile<< ");"<<endl;

        outputfile<<"\tcudaMemcpy(_DEV_"<<it->second.name<<"_"<<i<<","<<it->second.name<< ","<<"sizeof(";
        outputfile<<it->second.data_type;
        outputfile<< ")";
        sz = it->second.size;
        x = 1;
        outputfile<<" *_SZ_"<<it->second.name<<"_"<<i;
        outputfile<< ", cudaMemcpyHostToDevice);"<<endl;
    }
    outputfile<<"\tint _NUM_THREADS_"<<i<< " = "<< max_array_size<<";"<<endl;
    outputfile<<"\tfloat _NUM_BLOCKS_"<<i<< "=1;"<<endl<<"\tint _NUM_TILE_"<<i<< "=1;"<<endl;
    outputfile<<"\tdim3 _THREADS_"<<i<< "(512);"<<endl<<"\tdim3 _BLOCKS_"<<i<< "(1);"<<endl;
    outputfile<< "\tif(_NUM_THREADS_"<<i<< " < _NTHREAD)"<<endl;
    if(id_max==1)
        outputfile<<"\t{"<<endl<<"\t\t_THREADS_"<<i<< ".x=_NUM_THREADS_"<<i<< ";"<<endl<<"\t}"<<endl;
    outputfile<< "\telse {"<<endl;
    if(id_max==1)
        outputfile<< "\t\t _THREADS_"<<i<< ".x=_NTHREAD;"<<endl<<"\t\t_NUM_BLOCKS_"<<i<< "=(_NUM_THREADS_"<<i<< " % _NTHREAD == 0)?(_NUM_THREADS_"<<i<< "/_NTHREAD):((_NUM_THREADS_"<<i<< "/_NTHREAD)+1);"<<endl<<"\t\tif(_NUM_BLOCKS_"<<i<< "<_NBLOCK)"<<endl<<"\t\t\t_BLOCKS_"<<i<< ".x=_NUM_BLOCKS_"<<i<< ";"<<endl<<"\t\telse {"<<endl<<"\t\t\t_BLOCKS_"<<i<< ".x=_NBLOCK;"<<endl<<"\t\t\tint temp_"<<i<< "=_NUM_BLOCKS_"<<i<< ";"<<endl<<"\t\t\t_NUM_TILE_"<<i<< "=(temp_"<<i<< " % _NBLOCK == 0)?(_NUM_BLOCKS_"<<i<< "/_NBLOCK):((_NUM_BLOCKS_"<<i<< "/_NBLOCK)+1);"<<endl<<"\t\t}"<<endl<<"\t}"<<endl;
    struct Phi_Values *lambda,*lambda_temp;
    outputfile<<"\tint ID_1_"<<i<< ", ID_2_"<<i<< ", START["<<id_max<<"];"<<endl;
     outputfile<<endl<<"\t#ifdef TIME"<<endl<<"\t\tclock_gettime(CLOCK_MONOTONIC, &mid_start_"<<i<<");"<<endl<<"\t#endif"<<endl<<endl;
    outputfile<<"\tint _CUDA_TILE_"<<i<< ";"<<endl;
    outputfile<<"\tint Phi_"<<i<< "["<<noOfNestedLoops<<"]={";
    lambda=lambda_var;
    while(lambda)
    {
        outputfile<<lambda->phi_val;
        lambda=lambda->next;
        if(lambda)  outputfile<<", ";
        else    outputfile<<"};"<<endl;
    }

    outputfile<<"\tint loopUpperLimits_"<<i<< "["<<noOfNestedLoops<<"]={";
    outputfile<<b_val;
    outputfile<<"};"<<endl;
    outputfile<<"\tfor(ID_1_"<<i<< "=1;ID_1_"<<i<< "<=";
    lambda=lambda_var;
    int minCount=0;
    outputfile<<b_val<<"/"<<lambda->phi_val;
    while(minCount--)
        outputfile<<")";
    lambda=lambda->next;
    outputfile<<"+1;ID_1_"<<i<< "++)"<<endl<<"\t{"<<endl;
    outputfile<<"\t\tfor(ID_2_"<<i<< "=0;ID_2_"<<i<< "<"<<noOfNestedLoops<<";ID_2_"<<i<< "++)"<<endl<<"\t\t{"<<endl;
    outputfile<<"\t\t\tif(Phi_"<<i<< "[ID_2_"<<i<< "]>=0)"<<endl<<"\t\t\t\tSTART[ID_2_"<<i<< "]=(ID_1_"<<i<< "-1)*Phi_"<<i<< "[ID_2_"<<i<< "];"<<endl<<"\t\t\telse"<<endl<<"\t\t\t\tSTART[ID_2_"<<i<< "]=loopUpperLimits_"<<i<< "[ID_2_"<<i<< "]+(ID_1_"<<i<< "-1)*Phi_"<<i<< "[ID_2_"<<i<< "];"<<endl;
    outputfile<<"\t\t}"<<endl;
    int r=0;
    noOfNestedLoops=1;
    lambda=lambda_var;
    outputfile<<"\tfor(_CUDA_TILE_"<<i<< "=0;_CUDA_TILE_"<<i<< "<_NUM_TILE_"<<i<< ";_CUDA_TILE_"<<i<< "++)"<<endl<<"\t{"<<endl;
    outputfile<<"\t\t_AFFINE_KERNEL_"<<i<<"<<<_BLOCKS_"<<i<<",_THREADS_"<<i<<">>>(";
    while(r<noOfNestedLoops)
    {
        for (it=mymap.begin(); it!=mymap.end(); ++it)
        {
            outputfile <<" _DEV_";
            outputfile << it->first<<"_"<<i<<",";
            x=1;
           // i=1;
            outputfile<<" _SZ_"<<it->first<<"_"<<i<<",";
        }
        lambda_temp=lambda_var;
        int z=0;
        while(z<noOfNestedLoops)
        {
            if(z<r)
                outputfile<<"START["<<i<<"]+"<<lambda_temp->phi_val<<", "<<b_val<<", ";
            else if(z>r)
                outputfile<<"START["<<i<<"],"<<b_val<<", "<<endl;
            else
                outputfile<<"START["<<r<<"], MIN(START["<<r<<"]+"<<lambda_temp->phi_val<<", "<<b_val<<"), ";
            lambda_temp=lambda_temp->next;
            z++;
        }
        outputfile<<"_CUDA_TILE_"<<i<< ");"<<endl;
        outputfile<<"\t\t\tcudaDeviceSynchronize();"<<endl<<"\t}"<<endl;
        lambda=lambda->next;
        r++;
    }
    outputfile<<"\t}"<<endl;
    outputfile<<endl<<"\t#ifdef TIME"<<endl<<"\t\tclock_gettime(CLOCK_MONOTONIC, &mid_end_"<<i<<");"<<endl<<"\t#endif"<<endl;
    for(it=mymap.begin(); it!=mymap.end(); ++it)
    {
        outputfile<<"\tcudaMemcpy("<<it->second.name<<", "<<"_DEV_"<<it->second.name<<"_"<<i<<","<<"sizeof(";
        outputfile<<it->second.data_type;
        outputfile<< ")";
        sz = it->second.size;
        x = 1;
      //  i=1;
        outputfile<< " *_SZ_"<<it->second.name<<"_"<<i;
        outputfile<< ", cudaMemcpyDeviceToHost);"<<endl;
    }
    for (it=mymap.begin(); it!=mymap.end(); ++it)
    {
        outputfile<<"\tcudaFree(_DEV_"<<it->second.name<<"_"<<i<<");"<<endl;
    }
    outputfile<<endl<<"\t#ifdef TIME"<<endl<<"\t\tclock_gettime(CLOCK_MONOTONIC, &end_"<<i<<");"<<endl;
     outputfile<<"\t\tpre_time_"<<i<<" = (double) ((((&mid_start_"<<i<<")->tv_sec * 1000000000) + (&mid_start_"<<i<<")->tv_nsec) - (((&start_"<<i<<")->tv_sec * 1000000000) + (&start_"<<i<<")->tv_nsec)) / 1000000000;"<<endl<<"\t\tpost_time_"<<i<<" = (double) ((((&end_"<<i<<")->tv_sec * 1000000000) + (&end_"<<i<<")->tv_nsec) - (((&mid_end_"<<i<<")->tv_sec * 1000000000) + (&mid_end_"<<i<<")->tv_nsec)) / 1000000000;"<<endl<<"\t\tcomputeTime_"<<i<<" = (double) ((((&mid_end_"<<i<<")->tv_sec * 1000000000) + (&mid_end_"<<i<<")->tv_nsec) - (((&mid_start_"<<i<<")->tv_sec * 1000000000) + (&mid_start_"<<i<<")->tv_nsec)) / 1000000000;"<<endl<<"\t\trunTime_"<<i<<" = (double) ((((&end_"<<i<<")->tv_sec * 1000000000) + (&end_"<<i<<")->tv_nsec) - (((&start_"<<i<<")->tv_sec * 1000000000) + (&start_"<<i<<")->tv_nsec)) / 1000000000;"<<endl<<"\t#endif"<<endl<<endl;
  outputfile<<"\t#ifdef DATASET"<<endl<<"\t\tfprintf(fp,\"%%d,%%d,%%d,%%d,%%d,%%.14f,%%.14f,%%.14f,%%.14f,%%d\\n\",N,_NTHREAD*_NBLOCK,_THREADS_"<<i<<".x,_BLOCKS_"<<i<<".x,data,pre_time_"<<i<<",computeTime_"<<i<<",post_time_"<<i<<",runTime_"<<i<<",_CUDA_TILE_"<<i<<");"<<endl<<"\t\tfclose(fp);"<<endl<<"\t\tfclose(f);"<<endl<<"\t#else"<<endl<<"\t#ifdef TIME"<<endl<<"\t\tprintf(\"Runtime:%%f\\n\",runTime_"<<i<<");"<<endl<<"\t#endif"<<endl<<"\t#endif"<<endl;

}
void extCS_VariableDistance_AFFINE(string loop_id,SgNode* forloop,int i)
{
  
    std::map<string ,loop_var >::iterator it;
    string loop=process(forloop->unparseToString());
    //cout<<"for loop is "<<loop;

    int x=1,j,temp_size=1,id_max=0;
    int max_array_size=1;   //contains the array with maximum size like 'a' for declaration like int a[20][30],b[2][10][10]
    int max_dimension_size=1;
    int max_size,sz;
     outputfile<<endl<<"\t#ifdef DATASET"<<endl<<"\t\tchar* outfile = (char*)malloc(sizeof(char)*(strlen(readfile)+50));"<<endl<<"\t\tstrcpy(outfile, readfile);"<<endl<<"\t\tstrcat(outfile, \".data\");"<<endl<<"\t\tFILE* fp;"<<endl<<"\t\tfp = fopen(outfile, \"a\");"<<endl<<"\t#endif"<<endl;
    outputfile<<endl<<"\t#ifdef TIME"<<endl<<"\t\tstruct timespec start_"<<i<<", end_"<<i<<", mid_start_"<<i<<", mid_end_"<<i<<";"<<endl<<"\t\tdouble runTime_"<<i<<", pre_time_"<<i<<", post_time_"<<i<<", computeTime_"<<i<<";"<<endl<<"\t#endif"<<endl;
    for (it=mymap.begin(); it!=mymap.end(); ++it)
    {
        temp_size=1;
        outputfile<< "\t"<<it->second.data_type;
        outputfile<<" _SZ_"<<(it->second.name)<<"_"<<i<<" = " ;
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
    outputfile<<endl<<"\t#ifdef TIME"<<endl<<"\t\tclock_gettime(CLOCK_MONOTONIC, &start_"<<i<<");"<<endl<<"\t#endif"<<endl;
    outputfile<<endl<<"\t// ----------Allocating memory to Kernel Variable and copying them on device----------"<<endl;
    for (it=mymap.begin(); it!=mymap.end(); ++it)
    {
        outputfile<< "\t"<<it->second.data_type;
        outputfile<<" *_DEV_"<<(it->second.name)<<"_"<<i<<";"<<endl;
        outputfile<<"\tcudaMalloc((void**) &_DEV_"<<(it->second.name)<<"_"<<i<<","<<"sizeof(";
        outputfile<<it->second.data_type;
        outputfile<< ")";
        sz = it->second.size;
        x = 1;
      //  i=1;
        outputfile<< " *_SZ_"<<it->second.name<<"_"<<i;
        outputfile<< ");"<<endl;

        outputfile<<"\tcudaMemcpy(_DEV_"<<it->second.name<<"_"<<i<<","<<it->second.name<< ","<<"sizeof(";
        outputfile<<it->second.data_type;
        outputfile<< ")";
        sz = it->second.size;
        x = 1;
        outputfile<<" *_SZ_"<<it->second.name<<"_"<<i;
        outputfile<< ", cudaMemcpyHostToDevice);"<<endl;
    }
    outputfile<<"\tint _NUM_THREADS_"<<i<< " = "<< max_array_size<<";"<<endl;
    outputfile<<"\tfloat _NUM_BLOCKS_"<<i<< "=1;"<<endl<<"\tint _NUM_TILE_"<<i<< "=1;"<<endl;
    outputfile<<"\tdim3 _THREADS_"<<i<< "(512);"<<endl<<"\tdim3 _BLOCKS_"<<i<< "(1);"<<endl;
    outputfile<< "\tif(_NUM_THREADS_"<<i<< " < _NTHREAD)"<<endl;
    if(id_max==1)
        outputfile<<"\t{"<<endl<<"\t\t_THREADS_"<<i<< ".x=_NUM_THREADS_"<<i<< ";"<<endl<<"\t}"<<endl;
    outputfile<< "\telse {"<<endl;
    if(id_max==1)
        outputfile<< "\t\t _THREADS_"<<i<< ".x=_NTHREAD;"<<endl<<"\t\t_NUM_BLOCKS_"<<i<< "=(_NUM_THREADS_"<<i<< " % _NTHREAD == 0)?(_NUM_THREADS_"<<i<< "/_NTHREAD):((_NUM_THREADS_"<<i<< "/_NTHREAD)+1);"<<endl<<"\t\tif(_NUM_BLOCKS_"<<i<< "<_NBLOCK)"<<endl<<"\t\t\t_BLOCKS_"<<i<< ".x=_NUM_BLOCKS_"<<i<< ";"<<endl<<"\t\telse {"<<endl<<"\t\t\t_BLOCKS_"<<i<< ".x=_NBLOCK;"<<endl<<"\t\t\tint temp_"<<i<< "=_NUM_BLOCKS_"<<i<< ";"<<endl<<"\t\t\t_NUM_TILE_"<<i<< "=(temp_"<<i<< " % _NBLOCK == 0)?(_NUM_BLOCKS_"<<i<< "/_NBLOCK):((_NUM_BLOCKS_"<<i<< "/_NBLOCK)+1);"<<endl<<"\t\t}"<<endl<<"\t}"<<endl;
     outputfile<<endl<<"\t#ifdef TIME"<<endl<<"\t\tclock_gettime(CLOCK_MONOTONIC, &mid_start_"<<i<<");"<<endl<<"\t#endif"<<endl<<endl;
    outputfile<<"\tint _CUDA_TILE_"<<i<< ";"<<endl<<"\tint ";
    int temp=1;
    while(temp<=noOfNestedLoops)
    {
        outputfile<<"ID_"<<temp<<"_"<<i<<"=0, next_ID_"<<temp<<"_"<<i;
        if(temp<noOfNestedLoops)    outputfile<<", ";
        else    outputfile<<";"<<endl;
        temp++;
    }
    outputfile<<"\twhile(";
    temp=1;

    outputfile<<"(ID_"<<temp<<"_"<<i<<"<"<<b_val<<")";
    if(temp<noOfNestedLoops)    outputfile<<"&&";
    else    outputfile<<")"<<endl<<"\t{"<<endl;
    temp++;

    temp=1;
    int count,minCount=0;
    struct ReferencePair *refPairTemp;
    struct DDV *DDVtemp;
    struct DDV_Values *DDVtempValues;
    outputfile<<"\t\tnext_ID_"<<temp<<"_"<<i<<" = ";
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
            if(DDVtempValues->next==NULL)   outputfile<<")/("<<DDVtempValues->value<<"))";
            else
            {
                outputfile<<"+("<<DDVtempValues->value<<")*ID_"<<count<<"_"<<i;
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
        outputfile<<"\tfor(_CUDA_TILE_"<<i<< "=0;_CUDA_TILE_"<<i<< "<_NUM_TILE_"<<i<< ";_CUDA_TILE_"<<i<< "++)"<<endl<<"\t{"<<endl;
        outputfile<<"\t\t_AFFINE_KERNEL_"<<i<<"<<<_BLOCKS_"<<i<<",_THREADS_"<<i<<">>>(";
        for (it=mymap.begin(); it!=mymap.end(); ++it)
        {
            outputfile <<" _DEV_";
            outputfile << it->first<<"_"<<i<<",";
            x=1;
           // i=1;
            outputfile<<" _SZ_"<<it->first<<"_"<<i<<",";
        }
        outputfile<<"ID_1_"<<i<< ", MIN(next_ID_1_"<<i<< ","<<b_val<<"), _CUDA_TILE_"<<i<< ");"<<endl;
        outputfile<<"\t\t\tcudaDeviceSynchronize();"<<endl<<"\t\t}"<<endl;
        outputfile<<"\tfor(_CUDA_TILE_"<<i<< "=0;_CUDA_TILE_"<<i<< "<_NUM_TILE_"<<i<< ";_CUDA_TILE_"<<i<< "++)"<<endl<<"\t{"<<endl;
        outputfile<<"\t\t_AFFINE_KERNEL_"<<i<<"<<<_BLOCKS_"<<i<<",_THREADS_"<<i<<">>>(";
        for (it=mymap.begin(); it!=mymap.end(); ++it)
        {
            outputfile <<" _DEV_";
            outputfile << it->first<<"_"<<i<<",";
            x=1;
           // i=1;
            outputfile<<" _SZ_"<<it->first<<"_"<<i<<",";
        }
        outputfile<<"next_ID_1_"<<i<< ", "<<b_val<<", _CUDA_TILE_"<<i<< ");"<<endl;
        outputfile<<"\t\t\tcudaDeviceSynchronize();"<<endl<<"\t\t}"<<endl;
    }
    temp=1;
    while(temp<=noOfNestedLoops)
    {
        outputfile<<"\t\tID_"<<temp<<"_"<<i<<"=next_ID_"<<temp<<"_"<<i<<";"<<endl;
        temp++;
    }
    outputfile<<"\t}"<<endl;
    outputfile<<endl<<"\t#ifdef TIME"<<endl<<"\t\tclock_gettime(CLOCK_MONOTONIC, &mid_end_"<<i<<");"<<endl<<"\t#endif"<<endl;
    for (it=mymap.begin(); it!=mymap.end(); ++it)
    {

        outputfile<<"\tcudaMemcpy("<<it->second.name<<", "<<"_DEV_"<<it->second.name<<"_"<<i<<","<<"sizeof(";
        outputfile<<it->second.data_type;
        outputfile<< ")";
        sz = it->second.size;
        x = 1;
      //  i=1;
        outputfile<< " *_SZ_"<<it->second.name<<"_"<<i;
        outputfile<< ", cudaMemcpyDeviceToHost);"<<endl;
    }
    for (it=mymap.begin(); it!=mymap.end(); ++it)
    {
        outputfile<<"\tcudaFree(_DEV_"<<it->second.name<<"_"<<i<<");"<<endl;
    }
    outputfile<<endl<<"\t#ifdef TIME"<<endl<<"\t\tclock_gettime(CLOCK_MONOTONIC, &end_"<<i<<");"<<endl;
     outputfile<<"\t\tpre_time_"<<i<<" = (double) ((((&mid_start_"<<i<<")->tv_sec * 1000000000) + (&mid_start_"<<i<<")->tv_nsec) - (((&start_"<<i<<")->tv_sec * 1000000000) + (&start_"<<i<<")->tv_nsec)) / 1000000000;"<<endl<<"\t\tpost_time_"<<i<<" = (double) ((((&end_"<<i<<")->tv_sec * 1000000000) + (&end_"<<i<<")->tv_nsec) - (((&mid_end_"<<i<<")->tv_sec * 1000000000) + (&mid_end_"<<i<<")->tv_nsec)) / 1000000000;"<<endl<<"\t\tcomputeTime_"<<i<<" = (double) ((((&mid_end_"<<i<<")->tv_sec * 1000000000) + (&mid_end_"<<i<<")->tv_nsec) - (((&mid_start_"<<i<<")->tv_sec * 1000000000) + (&mid_start_"<<i<<")->tv_nsec)) / 1000000000;"<<endl<<"\t\trunTime_"<<i<<" = (double) ((((&end_"<<i<<")->tv_sec * 1000000000) + (&end_"<<i<<")->tv_nsec) - (((&start_"<<i<<")->tv_sec * 1000000000) + (&start_"<<i<<")->tv_nsec)) / 1000000000;"<<endl<<"\t#endif"<<endl<<endl;
  outputfile<<"\t#ifdef DATASET"<<endl<<"\t\tfprintf(fp,\"%%d,%%d,%%d,%%d,%%d,%%.14f,%%.14f,%%.14f,%%.14f,%%d\\n\",N,_NTHREAD*_NBLOCK,_THREADS_"<<i<<".x,_BLOCKS_"<<i<<".x,data,pre_time_"<<i<<",computeTime_"<<i<<",post_time_"<<i<<",runTime_"<<i<<",_CUDA_TILE_"<<i<<");"<<endl<<"\t\tfclose(fp);"<<endl<<"\t\tfclose(f);"<<endl<<"\t#else"<<endl<<"\t#ifdef TIME"<<endl<<"\t\tprintf(\"Runtime:%%f\\n\",runTime_"<<i<<");"<<endl<<"\t#endif"<<endl<<"\t#endif"<<endl;


}
/***********************************  KERNEL DEFINITION CODE GENERATION ********************************************************/

//Function for kernel definition if dependency exists
void SimpleSelective_kernel_definition_DEPENDENCY(char *shrinking_type,string loop_id,SgNode* forloop,SgFunctionDefinition *defn,int i)
{
    int x;
    std::map<string ,loop_var >::iterator it;
    string loop=process(forloop->unparseToString());
    cout<<"for loop is "<<loop;
    outputfile<<"\n\n__global__ void _AFFINE_KERNEL_"<<i<<"(";
    for (it=mymap.begin(); it!=mymap.end(); ++it)
    {
        outputfile<<it->second.data_type;
        outputfile<<"*";
        outputfile<<" ";
        outputfile<<it->second.name <<",";
       
        outputfile<<"int ";
        outputfile<< " _SZ_"<<it->second.name<<"_"<<i<<",";
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
void cuda_kernel_definition_NO_DEPENDENCY(string loop_id,SgNode* forloop,SgFunctionDefinition *defn,int i)
{
    int x;
    std::map<string ,loop_var >::iterator it;
    string loop=process(forloop->unparseToString());
    cout<<"for loop is "<<loop;
    outputfile<<"\n\n__global__ void _AFFINE_KERNEL_"<<i<<"(";
    for (it=mymap.begin(); it!=mymap.end(); ++it)
    {
        outputfile<<it->second.data_type;
        outputfile<<"*";
        outputfile<<" ";
        outputfile<<it->second.name<<",";
        
        outputfile<<"int ";
        outputfile<< " _SZ_"<<it->second.name<<"_"<<i<<",";
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
    outputfile<<"}"<<endl<<endl;
}
void ExtendedShrinking_kernel_definition_DEPENDENCY(string loop_id,SgNode* forloop,SgFunctionDefinition *defn,int i)
{
    int x;
    std::map<string ,loop_var >::iterator it;
    string loop=process(forloop->unparseToString());
    cout<<"for loop is "<<loop;
     outputfile<<"\n\n__global__ void _AFFINE_KERNEL_"<<i<<"(";
    for (it=mymap.begin(); it!=mymap.end(); ++it)
    {
        outputfile<<it->second.data_type;
        outputfile<<"*";
        outputfile<<" ";
        outputfile<<it->second.name<<",";
        
        outputfile<<"int ";
        outputfile<< " _SZ_"<<it->second.name<<"_"<<i<<",";
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
    outputfile<<"}"<<endl<<endl;
}
