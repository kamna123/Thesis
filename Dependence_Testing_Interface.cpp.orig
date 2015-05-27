#include "rose.h"

#include "ds.hpp"
#include "gcd_banerjee.hpp"
#include "Dependence_Testing_Interface.hpp"
using namespace std;
void Dependence_Testing_Interface(char *test_name, loop* write,SgNode* loop,int loop_number)
{
    int dependency_check=0;
    noOfNestedLoops=0;
    
    printf("test = %s\n",test_name );
    /******************************************/
    if(strcmp(test_name,"gcd")==0)
    {
	    if(GCD_Test(write, loop))
             //if(Omega_Test(read_var,write_var,loop_index_new,stmt_var))
             // if(Banerjee_Test(read,write,loop_id))
	    {
	        printf("\n-------------------- GCD Test Output: Dependency may exist\n");
	        DependencyExists='y';
	        }
    	else    
	        printf("\n-------------------- GCD Test Output: Dependency doesn't exist\n");
	        }
	else if(strcmp(test_name,"banerjee")==0)
    {
	  
        if(banerjee(write,loop,loop_number))
	    {
	        printf( "\n-------------------- Banerjee Test Output: Dependency may exist\n");
	        DependencyExists='y';
	        }
    	else
	        printf( "\n-------------------- Banerjee Test Output: Dependency doesn't exist\n");
	        }
        }