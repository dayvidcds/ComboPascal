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
		//printf("\nlex error!!\n");
	}
%}

%token PROGRAM
%token PLUS					//+
%token MINUS				//-
%token MULT					//*
%token DIVINT				//Integer Division
%token DIVREAL				//Real Division
%token IDENTIFIER			//identifier
%token LPAR 				//(
%token RPAR					//)
%token LCOL					//[
%token RCOL					//]
%token LKEY					//{
%token RKEY					//}
%token EXP 					//expression
%token QUOTDOUBLE					//Quotation Mark(")
%token QUOTSIMPLE			//(')
%token EXPUN				//unary expression
%token INTEGER 					//integer
%token REAL					//float
%token STRING				//string("asdsf")
%token CHAR					//caracter('a')
%token LITERAL_INT			//0-9
%token LITERAL_REAL		    //0.000...
%token BOOLEAN              //0-1
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
%token BEG 					//begin
%token ENDFIM 				//end.
%token FOR 					//for
%token NIL 					//null
%token SEP					//,
%token DOT					//ponto(.)
%token SC 					//semi colon(;)
%token EQ					//=
%token NL 					//new line(\n)
%token LOG2 				//Function Logaritm
%token DP 					//:
%token PGR
%token Escopo
%token DIV
%token INT_VALUE
%token DOUBLE_VALUE
%token EQATRIB
%token WRITE

%union{
	int int_val;
	double double_val;
	char *str_val;
	class PGR *pgr;
	class Atrib *atrib;
	class Value *Valor;
};
 
%type <str_val> IDENTIFIER;
%type <int_val> INT_VALUE;
%type <double_val> DOUBLE_VALUE;
%type <pgr> PROGRAM;

%%

programa : PROGRAMA CODIGO
;

CODIGO : VAR DEC CODIGO
	   | BEG ListaExp CODIGO
	   | ENDFIM
;

DEC : DECLR DEC
    | ATRIB DEC	   
	| CODIGO
;

ListaExp : Exp
		 | ATRIB ListaExp
		 | SUPPORT ListaExp
;	
		
Exp : ExpBinPLUS
	| ExpBinMINUS
	| Factor
;
	  
Factor : FactorMul
	   | FactorDiv
	   | ExpUn
;
		 
ExpUn : PLUSValor
	  | MINUSValor 
	  | Valor
;

Valor : LITERAL_INT{}	
      | LITERAL_REAL{}
      | IDENTIFIER{}
	  | Parenteses{}
;

TIPO : INTEGER SC{}
	 | REAL SC{}
;

DECLR : IDENTIFIER DP TIPO{}
	  | IDENTIFIER SEP DECLR{}
;

SUPPORT : W
;
//IDENTIFIER
W : WRITE LPAR QUOTDOUBLE IDENTIFIER QUOTDOUBLE RPAR SC{}
  | WRITE LPAR QUOTDOUBLE QUOTDOUBLE RPAR SC{}
;

PROGRAMA : PROGRAM IDENTIFIER SC{}
;
		
ATRIB : Atribuicao{}
;		
		
ExpBinPLUS : Exp PLUS Factor{}
; 	  

ExpBinMINUS : Exp MINUS Factor{}
;

FactorMul : Factor MULT ExpUn{}
;

FactorDiv : Factor DIVINT ExpUn{}
;	
		
PLUSValor : PLUS Valor{}
;

MINUSValor : MINUS Valor{}
;
		
Atribuicao : IDENTIFIER EQATRIB ListaExp SC{}
;

Parenteses : LPAR ListaExp RPAR{}
;

%%
