// Brian Reavis
// COSC2030
// 11/17/2010
// Symbolic Function Differentiator

#include <stdio.h>
#include <iostream>
#include <fstream>
#include "expr.h"
using namespace std;

int main(){
	string line="(10-(j+1))";
              line.erase(remove(line.begin(), line.end(),' '),line.end());
	ExpressionObject *expr = ExpressionObject::parse(line,false);
	 expr = expr->optimize();
          string s=expr->toLaTeX();
	 cout<<"string  = "<<s<<endl;
	return 0;
}
