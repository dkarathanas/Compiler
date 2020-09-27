/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    IDENTIFIER = 258,
    STRING = 259,
    INTEGER = 260,
    FLOAT = 261,
    IF = 262,
    ELSE = 263,
    WHILE = 264,
    FOR = 265,
    FUNCTION = 266,
    RETURN = 267,
    BREAK = 268,
    CONTINUE = 269,
    LOCL = 270,
    TRUE = 271,
    FALSE = 272,
    NIL = 273,
    AND = 274,
    OR = 275,
    NOT = 276,
    ASSIGN = 277,
    PLUS = 278,
    MINUS = 279,
    MULTIPLY = 280,
    DIVIDE = 281,
    MODULO = 282,
    DPLUS = 283,
    DMINUS = 284,
    EQUAL = 285,
    DIFFERENT = 286,
    BIGGER = 287,
    SMALLER = 288,
    BIGGER_EQUAL = 289,
    SMALLER_EQUAL = 290,
    LBRACKET = 291,
    RBRACKET = 292,
    LSBRACKET = 293,
    RSBRACKET = 294,
    LPARENTHESIS = 295,
    RPARENTHESIS = 296,
    SEMICOLON = 297,
    COMMA = 298,
    COLON = 299,
    DCOLON = 300,
    DOT = 301,
    DDOT = 302,
    UMINUS = 303
  };
#endif
/* Tokens.  */
#define IDENTIFIER 258
#define STRING 259
#define INTEGER 260
#define FLOAT 261
#define IF 262
#define ELSE 263
#define WHILE 264
#define FOR 265
#define FUNCTION 266
#define RETURN 267
#define BREAK 268
#define CONTINUE 269
#define LOCL 270
#define TRUE 271
#define FALSE 272
#define NIL 273
#define AND 274
#define OR 275
#define NOT 276
#define ASSIGN 277
#define PLUS 278
#define MINUS 279
#define MULTIPLY 280
#define DIVIDE 281
#define MODULO 282
#define DPLUS 283
#define DMINUS 284
#define EQUAL 285
#define DIFFERENT 286
#define BIGGER 287
#define SMALLER 288
#define BIGGER_EQUAL 289
#define SMALLER_EQUAL 290
#define LBRACKET 291
#define RBRACKET 292
#define LSBRACKET 293
#define RSBRACKET 294
#define LPARENTHESIS 295
#define RPARENTHESIS 296
#define SEMICOLON 297
#define COMMA 298
#define COLON 299
#define DCOLON 300
#define DOT 301
#define DDOT 302
#define UMINUS 303

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 51 "parser.y" /* yacc.c:1909  */

	char* stringVal;
	int intVal;
	double realVal;
	struct SymbolTableEntry *exprNode;

#line 157 "parser.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
