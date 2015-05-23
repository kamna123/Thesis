/*#ifndef __OPENCL_FROM_LOOPS_HPP__
#define __OPENCL_FROM_LOOPS_HPP__*/
#include <vector>
#include <map>
#include <string>

/*#ifndef _VARIABLE_HPP_
#define _VARIABLE_HPP_*/

class SgStatement;
class SgForStatement;
class SgVariableSymbol;
class SgSourceFile;
class SgProject;
class SgInitializedName;
class SgType;
class SgVarRefExp;
class SgExpression;
class SgScopeStatement;
class SgFunctionDeclaration;
class SgExprStatement;
class RoseVariable 
{
protected:
SgInitializedName * p_var;
RoseVariable * p_base;
bool p_is_arrow;
public:
RoseVariable(SgInitializedName * var = NULL, RoseVariable * base = NULL, bool is_arrow = false);
RoseVariable(const RoseVariable & v);
~RoseVariable();
std::string getString() const;
bool is(SgInitializedName * var) const;
SgExpression * generate(SgScopeStatement * stmt) const;
RoseVariable & operator = (const RoseVariable & v);
SgInitializedName * getInitializedName() const;
friend bool operator == (const RoseVariable & v1, const RoseVariable & v2);
friend bool operator != (const RoseVariable & v1, const RoseVariable & v2);
friend bool operator < (const RoseVariable & v1, const RoseVariable & v2); // for std::map
};
bool operator == (const RoseVariable & v1, const RoseVariable & v2);
bool operator != (const RoseVariable & v1, const RoseVariable & v2);
bool operator < (const RoseVariable & v1, const RoseVariable & v2);
bool isConstant(const RoseVariable & v);
std::string toString(const RoseVariable & v);
RoseVariable constantLBL();

namespace PolyhedricDependency {
typedef enum {RaR, RaW, WaR, WaW} DependencyType;
/**
* \brief Represent a dependency between two statements of a SCoP.
*/
template <class Function, class Expression, class VariableLBL>
class Dependency {
protected:

/*const PolyhedricAnnotation::PolyhedralProgram<Function, Expression, VariableLBL> & p_polyhedral_program;
size_t p_from;
size_t p_to;
size_t p_from_pos;
size_t p_to_pos;
DependencyType p_type;
size_t p_variable;
Polyhedron p_dependency;
public:
Dependency(
const PolyhedricAnnotation::PolyhedralProgram<Function, Expression, VariableLBL> & polyhedral_program,
Expression * from,
Expression * to,
size_t from_pos,
size_t to_pos,
DependencyType type,
VariableLBL variable,
Polyhedron & dependency
);
Dependency(
const PolyhedricAnnotation::PolyhedralProgram<Function, Expression, VariableLBL> & polyhedral_program,
size_t from,
size_t to,
size_t from_pos,
size_t to_pos,
DependencyType type,
size_t variable,
Polyhedron & dependency
);

*/
size_t getFrom() const;
/**
* \return the statement wich it depends.
*/
size_t getTo() const;
/**
* \return the type of the dependency (RaR, RaW, WaR, WaW).
*/
DependencyType getType() const;
/**
* \return the variable which is involve.
*/
size_t getVariable() const;
/**
* \return the dependency polyhedron.
*/

};
}
namespace PolyhedricDependency {
typedef Dependency<SgFunctionDeclaration, SgExprStatement, RoseVariable> FunctionDependency;
}
enum AccessType {
in,
out,
inout,
unknown
};
struct Scalar {
Scalar(std::string name_);
std::string name;
SgType * type;
AccessType access_type;
};
struct Array {
Array(std::string name_);
std::string name;
SgType * base_type;
std::vector<unsigned> dimensions;
AccessType access_type;
SgVariableSymbol * associated_ocl_buffer;
};
struct AnalysisContainer {
AnalysisContainer();
bool polyhedral_analysis_success;
std::map<SgInitializedName *, Scalar> scalars;
std::map<SgInitializedName *, Array> arrays;
SgFunctionDeclaration * base_func;
std::vector<PolyhedricDependency::FunctionDependency *> * dependencies;
};


