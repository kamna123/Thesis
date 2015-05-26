#ifndef CODEGEN_CYCLE_SHRINK
#define CODEGEN_CYCLE_SHRINK
void var_loop(SgNode* forloop,std::string loop_id);
std::string process(std::string const& s);
void  SimpleSelective_kernel_declaration_DEPENDENCY(SgNode* forloop,std::string loop_id,int i);
void cuda_kernel_declaration_NO_DEPENDENCY(int i);
void ExtendedShrinking_kernel_declaration_DEPENDENCY(int i);
void simple_loop_shrinking_AFFINE(SgNode* forloop,std::string loop_id,int i);
void cuda_kernel_call_NO_DEPENDENCY(SgNode* forloop,std::string loop_id,int i);
void extCS_ConstantDistance_AFFINE(std::string loop_id,SgNode* forloop,int i);
void extCS_VariableDistance_AFFINE(std::string loop_id,SgNode* forloop,int i);
void SimpleSelective_kernel_definition_DEPENDENCY(char *shrinking_type,std::string loop_id,SgNode* forloop,SgFunctionDefinition *defn,int i);
void cuda_kernel_definition_NO_DEPENDENCY(std::string loop_id,SgNode* forloop,SgFunctionDefinition *defn,int i);
void ExtendedShrinking_kernel_definition_DEPENDENCY(std::string loop_id,SgNode* forloop,SgFunctionDefinition *defn,int i);

#endif
