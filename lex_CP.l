/*

	Analizador Léxico do ComboPascal

	Tokens sugeridos:

	PLUS, MINUS, MULT, DIVINT, DIVREAL, IDENTIFIER, LPAR, RPAR, LCOL, RCOL, LKEY, RKEY, QUOT, QUOTSIMPLE, EXPUN, INT, DOUBLE, 
	BOOLEAN, STRING, CHAR, CONST, REPEAT, IF, ELSE, THEN, AND, OR, LTOP, GTOP, LTOEO, GTOEO, NEO, OF, DO, TO, VAR, BEGIN, END, 
	FOR, NIL, SEP, FSO, SC, AO, NL, TRUEE, FALSEE

*/

%{

	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include "teste.hpp"

	extern int yyparse();
	
%}

%option noyywrap nodefault

%%

"+" 				{ return PLUS; }
"-" 				{ return MINUS; }
"*" 				{ printf("multiplicacao"); return MULT; }
"/" 				{ return DIVREAL; }
"DIV" 				{ return DIVINT; }
"exp" 				{ return EXP; }
"log" 				{ return LOG2; }
"(" 				{ return LPAR; }
")" 				{ return RPAR; }
"[" 				{ return LCOL; }
"]" 				{ return RCOL; }
"{" 				{ return LKEY; }
"}" 				{ return RKEY; }
","					{ return SEP; }
"." 				{ return DOT; }
":"					{ printf(":"); return DP; }
";" 				{ printf(";\n"); return SC; }
"=" 				{ return EQ; }
"\""				{ return DIV; }
"'" 				{ return QUOTSIMPLE; }
"integer" 			{ printf("integer"); return INTEGER; }
"real" 				{ return REAL; }
"boolean" 			{ return BOOLEAN; }
"string" 			{ return STRING; }
"char" 				{ return CHAR; }
"const" 			{ return CONST; }
"true" 				{ return TRUEE; }
"false" 			{ return FALSEE; }
"repeat" 			{ return REPEAT; }
"if" 				{ return IF; }
"else" 				{ return ELSE; }
"then" 				{ return THEN; }
"and" 				{ return AND; }
"or" 				{ return OR; }
"<" 				{ return LTOP; }
">" 				{ return GTOP; }
"<=" 				{ return LTOEO; }
">=" 				{ return GTOEO; }
"<>" 				{ return NEO; }
"of" 				{ return OF; }
"do" 				{ return DO; }
"to" 				{ return TO; }
"var" 				{ printf("var\n"); return VAR; }
"begin" 			{ printf("begin\n"); return BEG; }
"end." 				{ printf("end.\n"); return ENDFIM; }
"for" 				{ return FOR; }
"nil" 				{ return NIL; }
"program"			{ printf("\nprogram "); return PROGRAM; }

[A-Za-z_\$][A-Za-z_\$0-9]* { yylval.str_val = strdup(yytext); printf("%s", yylval.str_val); return IDENTIFIER;}
[0-9]+ 					   { yylval.int_val = atoi(yytext); return INT_VALUE;}
[0-9]+\.[0-9]+             { yylval.double_val = atof(yytext); return DOUBLE_VALUE;}
"\n"					   {}
[\n\r\t ]				   {}
.						   { printf("\nCaractere invalido: %s\n", yytext); exit(1); }

%%

int main(int argc, char **argv){
		
	yyin = fopen (argv[1], "r"); //Arquivo de entrada
	
	if(argc != 2){
		printf("Passe como parametro o nome do arquivo\n\n");
		return 1;
	}

	if(yyparse()){
		//printf("\nParser Error!!\n");
		return 2;
	}

	return 0;
}	