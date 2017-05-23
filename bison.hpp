/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_BISON_HPP_INCLUDED
# define YY_YY_BISON_HPP_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     T_CHARACTER = 258,
     T_INTEGER = 259,
     T_REAL = 260,
     T_STRING = 261,
     T_BOOLEAN = 262,
     T_TRUE = 263,
     T_FALSE = 264,
     T_EXP = 265,
     T_EQUAL = 266,
     T_PLUS = 267,
     T_MINUS = 268,
     T_MULT = 269,
     T_DIV = 270,
     T_SEP = 271,
     T_DOT = 272,
     T_DP = 273,
     T_SC = 274,
     T_LPAR = 275,
     T_RPAR = 276,
     T_LCOL = 277,
     T_RCOL = 278,
     T_LKEY = 279,
     T_RKEY = 280,
     T_QUOTE_SIMPLE = 281,
     T_QUOTE_DOUBLE = 282,
     T_RETURN = 283,
     T_IDENTIFIER = 284,
     T_LITERAL_INTEGER = 285,
     T_LITERAL_REAL = 286,
     T_DOC_PARAM = 287,
     T_BEG = 288,
     T_ENDDOT = 289,
     T_THEN = 290,
     T_END = 291,
     T_PROGRAM = 292,
     T_COMP_EQUAL = 293,
     T_COMP_DIFF = 294,
     T_COMP_LESS = 295,
     T_COMP_LESS_EQ = 296,
     T_COMP_GREATER = 297,
     T_COMP_GREATER_EQ = 298,
     T_IF = 299,
     T_ELSE = 300,
     T_FOR = 301,
     T_WHILE = 302
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 2058 of yacc.c  */
#line 80 "bison.y"

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


/* Line 2058 of yacc.c  */
#line 143 "bison.hpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_YY_BISON_HPP_INCLUDED  */
