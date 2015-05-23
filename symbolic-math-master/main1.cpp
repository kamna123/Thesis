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
	
	
	string line="(2 * (i*2+5)) - 1";
        line.erase(remove(line.begin(), line.end(),' '),line.end());
        cout<<line<<endl;
	
		ExpressionObject *expr = ExpressionObject::parse(line, false);
		
		expr = expr->optimize();
                //cout<< expr->toLaTeX()<<endl;
		string a= expr->toLaTeX();
                cout<<a<<endl;
	
	
	 
	return 0;
}
