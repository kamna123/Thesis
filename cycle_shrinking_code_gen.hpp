#ifndef CYCLE_SHRINKING_CODE_GEN
#define CYCLE_SHRINKING_CODE_GEN
void setOutputFileName(SgFile* cur_file);
void visit(SgNode* n);
void var_loop(SgNode* forloop,std::string loop_id);
std::string process(std::string const& s);
void  SimpleSelective_kernel_declaration_DEPENDENCY(SgNode* forloop,std::string loop_id);
void simple_loop_shrinking_AFFINE(SgNode* forloop,std::string loop_id);
#endif