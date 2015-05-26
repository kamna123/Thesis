#ifndef CODEGEN_AFFINE_KERNEL_INTERFACE
#define CODEGEN_AFFINE_KERNEL_INTERFACE
#include "ds.hpp"
void cuda_kernel_declaration_AFFINE(char *shrinking,SgNode* forloop,std::string loop_id,int loop_num);
void cuda_kernel_call_AFFINE(char *shrinking,SgNode* forloop,std::string loop_id,int i);
void cuda_kernel_definition_AFFINE(char *shrinking_type,std::string loop_id,SgNode* forloop,SgFunctionDefinition *defn,int i);
#endif