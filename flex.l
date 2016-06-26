/*

	Analizador Léxico do ComboPascal

*/

%{
	#include "bison.hpp"
%}

%option noyywrap nodefault

%%

"+"		{ return T_PLUS; }
"-"		{ return T_MINUS; }
"*"		{ return T_MULT; }
"/"		{ return T_DIV; }
"program" 		{ return T_PROGRAM; }
"character"		{ return T_CHARACTER; }
"integer"		{ return T_INTEGER; }
"real"			{ return T_REAL; }
"String" 		{ return T_STRING; }
"boolean" 		{ return T_BOOLEAN; }
"begin"         { return BEG; }
"end"          { return END; }
"if"			{ return IF; }
"then"			{ return THEN; }
"true" 			{ return T_TRUE; }
"false" 		{ return T_FALSE; }
"exp"	{return T_EXP;}
":="	{ return T_EQUAL; }
"="		{return T_COMP_EQUAL; }
"<>"	{return T_COMP_DIFF; }
","		{ return T_SEP; }
"."		{ return T_DOT; }
":"		{ return T_DP; }
";"		{ return T_SC; }
"("		{ return T_LPAR; }
")"		{ return T_RPAR; }
"["		{ return T_LCOL; }
"]"		{ return T_RCOL; }
"{"		{ return T_LKEY; }
"}"		{ return T_RKEY; }
\'		{ return T_QUOTE_SIMPLE; }
\"		{ return T_QUOTE_DOUBLE; }

[a-zA-Z_][a-zA-Z0-9_]*	{ yylval.identifier = strdup(yytext); return T_IDENTIFIER; }

[0-9]+		{ yylval.int_value = atoi(yytext); return T_LITERAL_INTEGER; }

[0-9]+[\.][0-9]+	{ yylval.double_value = atof(yytext); return T_LITERAL_REAL; }

[\n\r\t ]+	{}

.		{ exit(1); }
%%
