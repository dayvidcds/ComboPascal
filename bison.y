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
%token T_BEG;
%token T_ENDDOT;
%token T_THEN;
%token T_END;
%token T_PROGRAM;
%token T_COMP_EQUAL;
%token T_COMP_DIFF;
%token T_COMP_LESS;
%token T_COMP_LESS_EQ;
%token T_COMP_GREATER;
%token T_COMP_GREATER_EQ;

%token T_IF;
%token T_ELSE;//ADDICIONADO
%token T_FOR;//ADDICIONADO
%token T_WHILE;//ADDICIONADO

%union {
	int int_value;
	double real_value;
	char char_value;
	char *identifier_value;
	int var_type;//ADDICIONADO
	
	class Program *program;
	
	class ExpList *explist;
	class Commands *commands;
	
	class Command *command;
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
	class ExpLessGreater *elg;
	class LessThen *lt;
	class LessEqualThen *let;
	class GreaterThen *gt;
	class GreaterEqualThen *get;
	class SymbolTable *symbols;
};

%type<program> Program;
%type<explist> ExpList;
%type<command> Command;
%type<commands> Commands;
%type<char_value> T_CHARACTER;
%type<int_value> T_LITERAL_INTEGER;
%type<real_value> T_LITERAL_REAL;
%type<identifier_value> T_IDENTIFIER;
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
%type<elg> ExpLessGreater;
%type<lt> LessThen;
%type<let> LessEqualThen;
%type<gt> GreaterThen;
%type<get> GreaterEqualThen;


%%

Program : T_PROGRAM T_IDENTIFIER T_SC ExpList T_DOT{
		$$ = $4;
		Context::getContext().setProgram($$);
	}
;

ExpList : T_BEG Commands T_END {
		// Tentei fazer pro $2 ser passado no construtor...
		// não funcionou, nao sei o motivo...
		// então coloquei um método setCommands
		
		ExpList *expList = new ExpList();
		expList->setCommands($2);
		
		$$ = expList;
	}
;

Commands : Commands Command T_SC{ $$ = new CommandsCommand($1,$2); }
		 | Command T_SC { $$ = $1; }
;

Command : Atrib {$$ = $1;}
		|Exp {$$ = $1; }
		|If {$$ = $1; }
;

If : T_IF Exp T_THEN ExpList {
		$$ = new If($2,$4);
    }
;

Exp : ExpPlusMinusBin { $$ = $1; }
	|ExpIgDif {$$ = $1;}
	|Factor {$$ = $1;}
	|ExpLessGreater {$$ = $1;}
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


ExpLessGreater : LessThen {$$ = $1;}
			   | LessEqualThen {$$ = $1;}
			   | GreaterThen {$$ = $1;}
			   | GreaterEqualThen {$$ = $1;}
;

ExpBinMinus : Exp T_MINUS Factor{
		$$ = new ExpBinMinus($1, $3);
};

LessThen : Exp T_COMP_LESS Factor{
		$$ =  new LessThen($1,$3);
}
;

LessEqualThen : Exp T_COMP_LESS_EQ Factor{
		$$ = new LessEqualThen($1,$3);
}
;

GreaterThen : Exp T_COMP_GREATER Factor{
		$$ = new GreaterThen($1,$3);
}
;

GreaterEqualThen : Exp T_COMP_GREATER_EQ Factor{
		$$ = new GreaterEqualThen($1,$3);
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
