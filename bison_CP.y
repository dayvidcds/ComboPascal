/*

	~ Analizador sintático do ComboPascal ~

	Link para auxiliar na escolha dos tokens que serão utilizados: 

	http://www.frameworkpascal.com/helphtml/lang_struct.htm

	Exemplos de código em Pascal:

	http://ultrainvasao.blogspot.com.br/2011/09/exemplos-de-codigo-pascal.html

*/

%{
	#include "class_CP.hpp"
	#include <iostream>
	#include <map>
	#include <stdio.h>

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
	class Programa *prog;
	class ListaExp *Lexp;
	class Command *cmd;
	class Exp *xp;
	class Factor *fac;
	class ExpUn *expun;
	class ExpBinPLUS *BinPlus;
	class ExpBinMINUS *BinMinus;
	class FactorMul *MulFac;
	class FactorDiv *DivFac;
	class ExpUnPLUS *UnPlus;
	class ExpUnMINUS *UnMinus;
	class Value *value;
	class Parenteses *parenteses;
	class Atribuicao *atrib;
};
 
%type <prog> programa;
%type <Lexp> ListaExp;
%type <cmd> Command;
%type <xp> Exp;
%type <fac> Factor;
%type <expun> ExpUn;
%type <BinPlus> ExpBinPLUS;
%type <BinMinus> ExpBinMINUS;
%type <MulFac>FactorMul;
%type <DivFac>FactorDiv;
%type <UnPlus>PLUSValor;
%type <UnMinus>MINUSValor;
%type <value>Valor;
%type <parenteses> Parenteses;
%type <atrib> ATRIB;
%type <int_val> LITERAL_INT;
%type <double_val> LITERAL_REAL;
%type <str_val> IDENTIFIER;
%%

programa : ListaExp{
	$$ = $1;
	Context::getContext().setProgram($$);
}
;

ListaExp : Command{$$ = $1;}
;

Command : Exp{$$ = $1;}
		| ATRIB{$$ = $1;}
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
	  |Parenteses{$$ = $1;}
;

Valor : LITERAL_INT{
		$$ = new IntValue($1);
	}	
      | LITERAL_REAL{
		$$ = new RealValue($1);
	}
      | IDENTIFIER{
		$$ = new Identifier($1);
}
;
		
ExpBinPLUS : Exp PLUS Factor{
	$$ = new ExpBinPLUS($1,$3);
}
; 	  

ExpBinMINUS : Exp MINUS Factor{
	$$ = new ExpBinMINUS($1,$3);
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
	$$ = new ExpUnPLUS($2);
}
;

MINUSValor : MINUS Valor{
	$$ = new ExpUnMINUS($2);
}
;

Parenteses : LPAR Exp RPAR{
	$$ = new Parenteses($2);
}
;

ATRIB : IDENTIFIER EQ Exp SC{
	Identifier *id = new Identifier($1);
	$$ = new Atribuicao(id,$3);
}
;
		
%%
	
