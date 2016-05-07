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
"*" 				{ return MULT; }
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
"." 				{ return FSO; }
";" 				{ return SC; }
"=" 				{ return AO; }
"\""				{ return QUOT; }
"'" 				{ return QUOTSIMPLE; }
"integer" 			{ return INT; }
"real" 				{ return DOUBLE; }
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
"var" 				{ return VAR; }
"begin" 			{ return BEGIN; }
"end" 				{ return END; }
"for" 				{ return FOR; }
"nil" 				{ return NIL; }

[a-zA-Z_][a-zA-Z0-9_]* 				{ return IDENTIFIER; }
[-]?[0-9]+							{ return LITERAL_INT; }
[-]?[0-9]+[\.][0-9]+				{ return LITERAL_DOUBLE; }
"\n"								{ return NL; }
[\n\r\t ]							{}
.									{ printf("Caractere invalido: %s",yytext); exit(1); }

%%

int main(int argc, char **argv){
		
	yyin = fopen (argv[1], "r"); //Arquivo de entrada
	
	if(argc != 2){
		printf("Passe como parametro o nome do arquivo\n\n");
			return 1;
	}

	if(yyparse()){
		printf("Error!!\n");
		return 1;
	}
	return 0;
}	