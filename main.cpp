#include <stdio.h>
#include "visitor.hpp"

extern int yyparse();
extern FILE *yyin;

int main(int argc, char ** argv){

	yyin = fopen (argv[1], "r");
	
	if(argc != 2){ 
		printf("Arquivo de entrada nao encontrado. Passe como parametro!"); 
		return 1; 
	}

	if(yyparse()){ 
		printf("Erro"); 
		return 1; 
	}

	Context::getContext().getProgram()->accept(new Interpreter());

	return 0;
}