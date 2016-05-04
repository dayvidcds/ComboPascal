/*
	~ Analizador sintático do ComboPascal ~

	Link para auxiliar na escolha dos tokens que serão utilizados: 

	https://www.google.com.br/url?sa=t&rct=j&q=&esrc=s&source=web&cd=2&ved=0ahUKEwjnt_TxucHMAhUIGJAKHb80BXYQFggjMAE&url=http%3A%2F%2Fwww.marlosmarques.com%2Fmain%2Farq%2Fcompiladores_fase01_scanner.pdf&usg=AFQjCNGcql6sNL22Y9vTzZ1ZgwqzReoA_A&sig2=1XAGXTGxDySqE3LIsi1bzQ&cad=rja
*/

%{
	void yyerror(const char *ERROR){
		printf("%s\n", ERROR);
	}
%}

%token PLUS
%token MINUS
%token MULT
%token DIV
%token EXP
%token IDENTIFIER
%token LPAR 
%token RPAR
%token EXPUN
%token LOG2
%token LF
%token INT
%token REAL
%token BOOLEAN
%token IF
%token ELSE
%token AND
%token OR

%%