/*

	~ Analizador sintático do ComboPascal ~

	Link para auxiliar na escolha dos tokens que serão utilizados: 

	http://www.frameworkpascal.com/helphtml/lang_struct.htm

	Exemplos de código em Pascal:

	http://ultrainvasao.blogspot.com.br/2011/09/exemplos-de-codigo-pascal.html

*/

%{
	void yyerror(const char *ERROR){
		printf("%s\n", ERROR);
	}
%}

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
%token DOUBLE				//float
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
%token BEGIN 				//begin
%token END 					//end
%token FOR 					//for
%token NIL 					//null
%token SEP					//,
%token FSO					//field selection operator(.)
%token SC 					//semi colon(;)
%token AO					//=
%token NL 					//new line(\n)
%token LOG2 				//Function Logaritm
%token LF

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