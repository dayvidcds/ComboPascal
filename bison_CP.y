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
	class Programa *pgr;
	class Command *command;
	class List *list;
	class Codigo *code;
	class Dec *dec;
	class ListaExp *lexp;
	class Exp *exp;
	class Factor *fac;
	class ExpUn *expUn;
	class Atrib *atrib1;
	class Value *Valor;
	class ExpBinPlus *expBinPlus;
	class ExpBinMinus *expBinMinus;
	class FactorMul *facmul;
	class FactorDiv *facdiv;
	class ExpUnPlus *expUnPlus;
	class ExpUnMinus *expUnMinus;
	class Atribuicao *atrib;
	class Pgr *PROG;
	class Var *var1;
	class Beg *beg1;
	class Endfim *end1;
	class Decler *decler;
	class Tipo *tipo1;
	class Integer *int1;
	class Real *real1;
	
};
 
%type <str_val> IDENTIFIER;
%type <int_val> LITERAL_INT;
%type <double_val> LITERAL_REAL;
%type <pgr> programa;
%type <command> Command;
%type <lexp> ListaExp
%type <exp> Exp
%type <fac> Factor
%type <expUn> ExpUn
%type <atrib1> ATRIB
%type <Valor> Valor
%type <expBinPlus>ExpBinPLUS
%type <expBinMinus>ExpBinMINUS
%type <facmul>FactorMul
%type <facdiv>FactorDiv
%type <expUnPlus>PLUSValor
%type <expUnMinus>MINUSValor
%type <atrib>Atribuicao
%type <var1> VAR
%type <beg1> BEG
%type <end1> ENDFIM
%type <int1> INTEGER
%type <real1> REAL

%%

programa : Command{
	$$ = $1;
	Context :: getContext().setProgram($$);
}
;

Command : ListaExp{$$ = $1;}
;

/*Lista : PROGRAM Lista{$$ = $1;} 
		|CODIGO Lista{$$ = $1;}
;

CODIGO : VAR ListaExp BEG ListaExp ENDFIM{$$ = $2;}
;
*/

ListaExp : Exp{ $$ = $1; }
		 | ATRIB ListaExp{ $$ = $1; }
;	
		
Exp : ExpBinPLUS{$$ = $1;}
	| ExpBinMINUS{$$ = $1;}
	| Factor{$$ = $1;}
;
	  
Factor : FactorMul{$$ = $1;}
	   | FactorDiv{$$ = $1;}
	   | ExpUn{$$ = $1;}
;
		 
ExpUn : PLUSValor{$$ = $1;}
	  | MINUSValor{$$ = $1;} 
	  | Valor{$$ = $1;}
;

Valor : LITERAL_INT{
		$$ = new IntValue($1);
		}	
      | LITERAL_REAL{
		$$ = new RealValue($1);
		}
      | IDENTIFIER{
		$$ = new Identifier($1);}
;

/*
PROGRAMA : PROGRAM IDENTIFIER SC{}
;
*/
		
ATRIB : Atribuicao{$$ = $1;}
;		
		
ExpBinPLUS : Exp PLUS Factor{
	$$ = new  ExpBinPlus($1,$3);

	}
; 	  

ExpBinMINUS : Exp MINUS Factor{
	$$ = new ExpBinMinus($1,$3);

	}
;

FactorMul : Factor MULT ExpUn{
	$$ = new FactorMul($1,$3);
	}
;

FactorDiv : Factor DIVINT ExpUn{
	$$ = new FactorDiv($1,$3);
	}
;	
		
PLUSValor : PLUS Valor{
	$$ = new ExpUnPlus($2);
	}
;

MINUSValor : MINUS Valor{
	$$ = new ExpUnMinus($2);
	}
;
		
Atribuicao : IDENTIFIER EQATRIB Exp SC{
	Identifier *id = new Identifier($1);
	$$ = new Atribuicao(id,$3);
	}
;


%%
