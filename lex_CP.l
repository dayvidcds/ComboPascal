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
	#include "visitor.hpp"

	extern int yyparse();
	
%}

%option noyywrap nodefault

%%

"+" 				{ printf("+"); return PLUS; }
"-" 				{ printf("-"); return MINUS; }
"*" 				{ printf("*"); return MULT; }
"/" 				{ printf("/"); return DIVREAL; }
"DIV" 				{ return DIVINT; }
"exp" 				{ return EXP; }
"log" 				{ return LOG2; }
"(" 				{ printf("("); return LPAR; }
")" 				{ printf(")"); return RPAR; }
"[" 				{ return LCOL; }
"]" 				{ return RCOL; }
"{" 				{ return LKEY; }
"}" 				{ return RKEY; }
","					{ printf(", "); return SEP; }
"." 				{ return DOT; }
":"					{ printf(" : "); return DP; }
";" 				{ printf(";\n"); return SC; }
"=" 				{ return EQ; }
":=" 				{ printf(" := "); return EQATRIB; }
".."				{ return DIV; }
"'" 				{ return QUOTSIMPLE; }
"\""	 			{ printf("\""); return QUOTDOUBLE; }
"integer" 			{ printf("integer"); return INTEGER; }
"real" 				{ printf("real"); return REAL; }
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
"write" 			{ printf("write"); return WRITE; }

[A-Za-z_\$][A-Za-z_\$0-9]* { yylval.str_val = strdup(yytext); printf("%s", yylval.str_val); return IDENTIFIER; }
[0-9]+ 					   { yylval.int_val = atoi(yytext); printf("%i", yylval.int_val); return LITERAL_INT; }
[0-9]+\.[0-9]+             { yylval.double_val = atof(yytext); printf("%f", yylval.double_val); return LITERAL_REAL; }
"\n"					   {}
[\n\r\t ]				   {}
.						   { printf("\nCaractere invalido: %s\n", yytext); return 1; }

%%
	