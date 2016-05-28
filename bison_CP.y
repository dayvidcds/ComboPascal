/*

	~ Analizador sintático do ComboPascal ~

	Link para auxiliar na escolha dos tokens que serão utilizados: 

	http://www.frameworkpascal.com/helphtml/lang_struct.htm

	Exemplos de código em Pascal:

	http://ultrainvasao.blogspot.com.br/2011/09/exemplos-de-codigo-pascal.html

*/

%{
	#include <stdio.h>
	#include <math.h>
	#include "class_CP.hpp"

	extern int yylex();

	void yyerror(const char *ERROR){
		printf("%s\n", ERROR);
	}
%}

%token PROGRAM
%token PLUS					//+
%token MINUS				//-
%token MULT					//*
%token DIVINT				//Integer Division
%token DIVREAL				//Real Division
%token IDENTIFIER			//identifier
%token ATRIB 				//assignment values
%token LPAR 				//(
%token RPAR					//)
%token LCOL					//[
%token RCOL					//]
%token LKEY					//{
%token RKEY					//}
%token EXP 					//expression
%token QUOT					//Quotation Mark(")
%token QUOTSIMPLE			//(')
%token EXPUN				//unary expression
%token INT 					//integer
%token REAL				//float
%token BOOLEAN				//boolean
%token STRING				//string("asdsf")
%token CHAR					//caracter('a')
%token LITERAL_INT			//0-9
%token LITERAL_DOUBLE		//0.000...
%token CONST 				//const
%token TRUEE				//condition(1)
%token FALSEE				//condition(0)
%token REPEAT				//repeat
%token IF 					//condition
%token ELSE 				//otherwise
%token THEN					//then
%token AND 					//logical and
%token OR 					//logical or
%token LTOP					//Less Than Operator(<)
%token GTOP					//Greater Than Operator(>)
%token LTOEO 				//Less than or equal operator(<=)
%token GTOEO 				//Greater than or equal operator(>=)
%token NEO 					//Not equal operator(<> : !=)
%token OF 					//of
%token DO 					//do
%token TO 					//to
%token VAR 					//var
%token BEG 				//begin
%token END 					//end
%token FOR 					//for
%token NIL 					//null
%token SEP					//,
%token FSO					//field selection operator(.)
%token SC 					//semi colon(;)
%token AO					//=
%token NL 					//new line(\n)
%token LOG2 				//Function Logaritm
%token DP 					//:
%token PGR
%token Escopo

%union {
	class Int_Value *int_val;
	class Double_Value *double_val;
	class Identifier *id;
	class PGR *pgr;
};
 
%type <pgr> INI
%type <id> IDENTIFIER

%%
		 
programa : ListaExp{};

ListaExp : Comandos{};

Comandos : INI Escopo{};

INI : PROGRAM IDENTIFIER SC{};
