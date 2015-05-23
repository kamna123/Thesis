#include "rose.h"
using namespace std;
using namespace SageBuilder;
using namespace SageInterface;
using namespace OmpSupport;
void setOutputFileName(SgFile* cur_file)
{
  ROSE_ASSERT(cur_file);
  string orig_name = cur_file->get_file_info()->get_filenameString();

  string file_suffix = StringUtility::fileNameSuffix(orig_name);
cout<<"a===="<<file_suffix;
 // if (CommandlineProcessing::isCFileNameSuffix(file_suffix))
    {
      orig_name = StringUtility::stripPathFromFileName(orig_name);
       cout<<"orig"<<orig_name;
      string naked_name = StringUtility::stripFileSuffixFromFileName(orig_name);
      cur_file->set_unparse_output_filename("mint"+naked_name+".cu");
      string output_name =  cur_file->get_unparse_output_filename();
      cout<<"output file name is :"<<output_name<<endl;                                                                                                     
    }
}
int main(int argc, char * argv[])
{
SgFunctionParameterTypeList* param_type_list;
SgProject *project = frontend (argc, argv);
  SgSourceFile* file = isSgSourceFile(project->get_fileList()[0]);
  if(file!=NULL)
    cout<<"abc";
setOutputFileName(isSgFile(file));
 project->unparse();
     //return backend(project);

}
