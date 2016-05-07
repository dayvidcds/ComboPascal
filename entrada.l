%{

#include <stdio.h>
#include <string.h>
#include "teste.hpp"

%}

%option noyywrap nodefault

%%

"exp" {return EXP;}
"log" {return LOG2;}
"(" {return LPAR;}
")" {return RPAR;}
"*" {return MULT;}
"+" {return PLUS;}
"-" {return MINUS;}
"/" {return DIVINT;}
"=" {return AO;}
[0-9]+ {yylval.int_val = atoi(yytext);return LITERAL_INT;}
[A-Za-z_\$][A-Za-z_\$0-9]* { yylval.str_val = strdup(yytext); return IDENTIFIER;}
[0-9]+\.[0-9]+ { yylval.double_val = atof (yytext); return LITERAL_DOUBLE;}
\n {return LF;}
[\r\t ] {}
. {printf("Caractere invalido: %s",yytext);exit(1);}
	
%%
int main(int argc, char ** argv){
		
	yyin = fopen (argv[1],"r");
	
	if(argc != 2){
		printf("Tem que ter o nome do arquivo\n\n");
			return 1;
	}

	if(yyparse()){
		printf("Error!!\n");
		return 1;
	}

	return 0;
}