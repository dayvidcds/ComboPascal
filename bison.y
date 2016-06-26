/*

	~ Analizador sintático do ComboPascal ~

	Link para auxiliar na escolha dos tokens que serão utilizados: 

	http://www.frameworkpascal.com/helphtml/lang_struct.htm

	Exemplos de código em Pascal:

	http://ultrainvasao.blogspot.com.br/2011/09/exemplos-de-codigo-pascal.html

*/

%{

	#include "class.hpp"
	#include <map>
	#include <iostream>
	#include <string.h>
	#include <stdio.h>

	extern int yylex();

	void yyerror(const char *error) { 
		printf("%s\n", error);
	}

	using namespace std;
	
%}

%token T_CHARACTER;
%token T_INTEGER;
%token T_REAL;
%token T_STRING;
%token T_BOOLEAN;
%token T_TRUE;
%token T_FALSE;
%token T_EXP;
%token T_EQUAL;
%token T_PLUS;
%token T_MINUS;
%token T_MULT;
%token T_DIV;
%token T_SEP;
%token T_DOT;
%token T_DP;
%token T_SC;
%token T_LPAR;
%token T_RPAR;
%token T_LCOL;
%token T_RCOL;
%token T_LKEY;
%token T_RKEY;
%token T_QUOTE_SIMPLE;
%token T_QUOTE_DOUBLE;
%token T_RETURN;
%token T_IDENTIFIER;
%token T_LITERAL_INTEGER;
%token T_LITERAL_REAL;
%token T_DOC_PARAM;
%token BEG;
%token ENDDOT;
%token THEN;
%token END;
%token IF;
%token T_COMP_EQUAL;
%token T_COMP_DIFF;
%token T_PROGRAM;


%union {
	int int_value;
	double double_value;
	char char_value;
	char *identifier;
	class Program *program;
	class ExpList *explist;
	class Command *command;
	class Commands *commands;
	class Value *value;
	class Exp *exp;
	class ExpPlusMinusBin *bepm;
	class ExpUn *unexp;
	class Factor *factor;
	class ExpBinPlus *binexpplus;
	class ExpBinMinus *binexpminus;
	class FactorMul *factormul;
	class FactorDiv *factordiv;
	class ExpUnPlus *unexpplus;
	class ExpUnMinus *unexpminus;
	class Atribuicao *assignment;
	class ExpIgDif *EqExpDiff;
	class ExpDif *diffexp;
	class ExpIg *eqexp;
	class If *iff;
};

%type<program> Program;
%type<explist> ExpList;
%type<command> Command;
%type<commands> Commands;
%type<char_value> T_CHARACTER;
%type<int_value> T_LITERAL_INTEGER;
%type<double_value> T_LITERAL_REAL;
%type<identifier> T_IDENTIFIER;
%type<value> Value;
%type<exp> Exp;
%type<bepm> ExpPlusMinusBin;
%type<factor> Factor;
%type<unexp> ExpUn;
%type<binexpplus> ExpBinPlus;
%type<binexpminus> ExpBinMinus;
%type<factormul> FactorMul;
%type<factordiv> FactorDiv;
%type<unexpplus> ExpUnPlus;
%type<unexpminus> ExpUnMinus;
%type<assignment> Atrib;
%type<EqExpDiff> ExpIgDif;
%type<diffexp> ExpDif;
%type<eqexp> ExpIg;
%type<iff> If;


%%

Program : T_PROGRAM T_IDENTIFIER T_SC ExpList T_DOT{
		$$ = $4;
		Context::getContext().setProgram($$);
	}
;

ExpList : BEG Commands END{ $$ = $2; }
;

Commands : Commands Command T_SC{ $$ = new CommandsCommand($1,$2); }
		 | Command T_SC { $$ = $1; }
;

Command : Atrib {$$ = $1;}
		|Exp {$$ = $1; }
		|If {$$ = $1; }
;

Exp : ExpPlusMinusBin { $$ = $1; }
	|ExpIgDif {$$ = $1;}
	|Factor {$$ = $1;}
;

ExpIgDif : ExpIg { $$ = $1; }
		 |ExpDif { $$ = $1; }
;

ExpPlusMinusBin : ExpBinPlus {$$ = $1;}
				|ExpBinMinus {$$ = $1;}
;

ExpBinPlus : Exp T_PLUS Factor{
		$$ = new ExpBinPlus($1,$3);
	}
;  

ExpBinMinus : Exp T_MINUS Factor{
		$$ = new ExpBinMinus($1, $3);
	}
;

Factor : FactorMul { $$ = $1; }
		|FactorDiv { $$ = $1; }
		|ExpUn { $$ = $1; }
;

FactorMul : Factor T_MULT ExpUn{
		$$ = new FactorMul($1, $3);
	}
;		

FactorDiv : Factor T_DIV ExpUn {
		$$ = new FactorDiv($1, $3);
	}
;

ExpUn : ExpUnPlus { $$ = $1; }
        |ExpUnMinus { $$ = $1; }
		|Value { $$ = $1; }
;

ExpUnPlus : T_PLUS Value {
		$$ = new ExpUnPlus($2);	
	}
;

ExpUnMinus : T_MINUS Value {
		$$ = new ExpUnMinus($2);
	}
;

ExpIg : Exp T_COMP_EQUAL Factor {
		$$ = new ExpIg($1, $3);
	}
;

ExpDif : Exp T_COMP_DIFF Factor {
		$$ = new ExpDif($1, $3);
	}
;

If : IF Exp THEN BEG Commands END{
		$$ = new If($2,$5);
    }
;

Value : T_LITERAL_INTEGER {		
		$$ = new IntValue($1);
	}
		|T_LITERAL_REAL{
		$$ = new RealValue($1);
	}
		|T_IDENTIFIER { $$ = new Identifier($1); }
;	


Atrib : T_IDENTIFIER T_EQUAL Exp {
		Identifier *ident = new Identifier($1);
		$$ = new Atribuicao(ident, $3);
	}
;
