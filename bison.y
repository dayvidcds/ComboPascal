%{
	#include <stdio.h>
	#include <math.h>
	#include "class.h"
	extern int yylex();
	void yyerror(const char *isso) {printf("%s\n", isso);}
%}

%token PLUS
%token MINUS
%token MULT
%token DIVINT
%token EXP
%token IDENTIFIER
%token LITERAL_DOUBLE
%token LPAR 
%token RPAR
%token LOG2
%token LF
%token LITERAL_INT
%token AO


%union {
	int int_val;
	double double_val;
	char * str_val;
	class Valor * valor;
};

%type <valor> Valor
%type <valor> ExpUn
%type <valor> Factor
%type <valor> Exp
%type <valor> ExpBinPLUS
%type <valor> ExpBinMINUS
%type <valor> FactorMul
%type <valor> FactorDiv
%type <double_val> LITERAL_DOUBLE
%type <int_val> LITERAL_INT
%type <str_val> IDENTIFIER


%%

programa : ListaExp{};

ListaExp : comando{}
		 |ListaExp LF comando{};
		 
comando : Exp{}
		|Atrib{};
		
Atrib : Atribuicao{};		
		
Exp : ExpBinPLUS{}
	  |ExpBinMINUS{}
	  |Factor{};
	  
Factor : FactorMul{}
	     |FactorDiv{}
		 |ExpUn{};
		 
ExpUn : PLUSValor{}
	    |MINUSValor{} 
	    |Log2{}
	    |EXPO{}
	    |Valor{};

Valor : LITERAL_INT{} 
	    |IDENTIFIER{}	
		|LITERAL_DOUBLE{}
	    |Parenteses{};

ExpBinPLUS : Exp PLUS Factor{}; 	  

ExpBinMINUS : Exp MINUS Factor{};
		 
FactorMul : Factor MULT ExpUn{};

FactorDiv : Factor DIVINT ExpUn{};
		
Log2 : LOG2 LPAR Exp RPAR{};		
		
EXPO : EXP LPAR Exp RPAR{};		
		
PLUSValor : PLUS Valor{};

MINUSValor : MINUS Valor{};
		
Atribuicao : IDENTIFIER AO Exp{};

Parenteses : LPAR Exp RPAR{};




















