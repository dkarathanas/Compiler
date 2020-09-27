/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "parser.y" /* yacc.c:339  */

	#include <stdio.h>
	#include <unistd.h>
	#include <stdlib.h>
	#include "symbol_table.h"
	#include <time.h>
	#include <string.h>

	#define KNRM "\x1B[0m"
	#define KYEL "\x1B[33m"
	#define KRED "\x1B[31m"
	#define KMAG "\x1B[35m"
	#define KGRN "\x1B[32m"
	#define KBLU "\x1B[34m"
	#define KCYN "\x1B[36m"
	#define KWHT "\x1B[37m"

#define GLOBAl_SCOPE 0

	int yylex(void);
	int yyerror(char* xaxa){
		printf("YYPARSE ERROR\n");
	}

	extern FILE* yyin;
	extern FILE* yyout;
	extern int yylineno;
	extern char* yytext;

	extern st_entry *bucket[BUCKET_SIZE];
	extern st_entry **scope_list;
	extern st_entry *dummy;
	extern int scope_counter;


	st_entry *entry;
	var* var_symbol;
	func* func_symbol;
	arguments* args;
	arguments* tmp_arg;
	unsigned int scope = 0;		//this is the scope
	unsigned int curr_scope = 0;
	int tmp_scope = 0;			//tmp scope to traverse scopes
	unsigned int func_scope;	//scope the function was declared
	unsigned int is_func = 0;	//flag to check is we are inside a function body
	unsigned int is_loop = 0;	//loop counter (while, for...)
	unsigned int is_loop_in_func = 0;	//scope flag to handle block inside a loop inside a function :)
	int collision_flag = 0;				//this is a flag to check collisions with library functions

#line 116 "parser.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.h".  */
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
#line 51 "parser.y" /* yacc.c:355  */

	char* stringVal;
	int intVal;
	double realVal;
	struct SymbolTableEntry *exprNode;

#line 259 "parser.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 276 "parser.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  69
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   520

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  49
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  38
/* YYNRULES -- Number of rules.  */
#define YYNRULES  97
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  183

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   303

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    89,    89,    92,    93,    96,    97,    98,   100,   102,
     106,   115,   123,   124,   125,   128,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   157,   158,   159,   160,   160,   166,   171,   176,   181,
     184,   185,   186,   187,   188,   191,   256,   281,   298,   298,
     305,   310,   311,   315,   319,   320,   321,   325,   326,   329,
     332,   336,   337,   338,   342,   343,   347,   348,   351,   355,
     355,   370,   370,   385,   402,   403,   385,   410,   416,   417,
     410,   424,   425,   426,   427,   428,   429,   433,   468,   489,
     493,   494,   498,   497,   513,   512,   527,   528
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IDENTIFIER", "STRING", "INTEGER",
  "FLOAT", "IF", "ELSE", "WHILE", "FOR", "FUNCTION", "RETURN", "BREAK",
  "CONTINUE", "LOCL", "TRUE", "FALSE", "NIL", "AND", "OR", "NOT", "ASSIGN",
  "PLUS", "MINUS", "MULTIPLY", "DIVIDE", "MODULO", "DPLUS", "DMINUS",
  "EQUAL", "DIFFERENT", "BIGGER", "SMALLER", "BIGGER_EQUAL",
  "SMALLER_EQUAL", "LBRACKET", "RBRACKET", "LSBRACKET", "RSBRACKET",
  "LPARENTHESIS", "RPARENTHESIS", "SEMICOLON", "COMMA", "COLON", "DCOLON",
  "DOT", "DDOT", "UMINUS", "$accept", "program", "stmts", "stmt",
  "assignexpr", "expr", "term", "$@1", "primary", "lvalue", "$@2",
  "member", "call", "callsuffix", "normcall", "methodcall", "elist",
  "objectdef", "indexed", "indexedelem", "block", "$@3", "$@4", "funcdef",
  "$@5", "$@6", "$@7", "$@8", "$@9", "$@10", "const", "idlist", "ifstmt",
  "whilestmt", "$@11", "forstmt", "$@12", "returnstmt", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303
};
# endif

#define YYPACT_NINF -146

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-146)))

#define YYTABLE_NINF -72

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-72)))

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     116,  -146,  -146,  -146,  -146,   -31,  -146,  -146,    20,    15,
       8,    16,    48,  -146,  -146,  -146,   231,   231,     1,     1,
      40,   162,   200,  -146,    82,    86,  -146,   116,  -146,   276,
    -146,  -146,    68,  -146,    65,  -146,  -146,  -146,  -146,  -146,
    -146,  -146,  -146,   231,    49,    54,  -146,    59,  -146,   296,
    -146,  -146,  -146,  -146,  -146,    89,     2,    65,     2,   116,
      67,   231,   446,   -38,   -33,  -146,   336,    72,  -146,  -146,
    -146,   231,   231,   231,   231,   231,   231,   231,   231,   231,
     231,   231,   231,   231,  -146,   231,  -146,  -146,   231,   231,
     106,   113,  -146,  -146,  -146,  -146,   231,   231,   114,   355,
     231,   231,    78,  -146,  -146,    95,  -146,   116,  -146,   254,
    -146,   231,  -146,   103,  -146,   102,   459,   459,    57,    57,
    -146,  -146,  -146,   472,   472,   485,   485,   485,   485,   446,
     393,   -17,  -146,   107,   410,     4,  -146,   116,   374,   -28,
    -146,   140,   102,   111,   231,   446,  -146,   231,  -146,  -146,
     231,  -146,  -146,   141,   116,   231,   140,   108,  -146,  -146,
     427,    13,    18,   116,  -146,   316,  -146,   140,   109,  -146,
    -146,  -146,  -146,   231,   112,  -146,   119,    52,   119,  -146,
     116,  -146,  -146
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,    45,    82,    81,    83,     0,    92,    94,    77,     0,
       0,     0,     0,    85,    86,    84,     0,     0,     0,     0,
      69,    63,     0,    14,     0,     0,     2,     4,    29,     0,
      30,    39,    40,    48,    41,    42,    12,    13,    44,     6,
       7,     8,     9,     0,     0,     0,    73,     0,    97,     0,
      10,    11,    46,    33,    32,     0,    34,     0,    37,     0,
       0,     0,    62,     0,     0,    67,     0,     0,    47,     1,
       3,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     5,     0,    36,    38,     0,    63,
       0,     0,    55,    57,    58,    49,     0,    63,     0,     0,
       0,    63,     0,    78,    96,     0,    35,     4,    72,     0,
      64,     0,    65,     0,    31,    43,    27,    28,    16,    17,
      18,    19,    20,    21,    22,    23,    25,    24,    26,    15,
       0,     0,    50,     0,     0,     0,    52,     0,     0,     0,
      74,    89,     0,     0,     0,    61,    66,    63,    51,    59,
      63,    53,    54,    90,     0,     0,    89,    88,    79,    70,
       0,     0,     0,     0,    93,     0,    75,    89,     0,    68,
      56,    60,    91,    63,     0,    87,     0,     0,     0,    80,
       0,    76,    95
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -146,    50,   132,   -56,  -146,    -9,  -146,  -146,  -146,     9,
    -146,  -146,    19,  -146,  -146,  -146,   -72,  -146,  -146,    47,
     -66,  -146,  -146,   -20,  -146,  -146,  -146,  -146,  -146,  -146,
    -146,  -145,  -146,  -146,  -146,  -146,  -146,  -146
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    25,    26,    27,    28,    29,    30,   106,    31,    32,
      95,    33,    34,    92,    93,    94,    63,    35,    64,    65,
      36,    59,    60,    37,   102,   156,   174,    47,   141,   168,
      38,   158,    39,    40,    44,    41,    45,    42
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      49,   110,    67,   107,     1,   111,   112,    53,    54,    43,
     113,   166,    62,    66,   155,   111,    12,   131,     1,     2,
       3,     4,   175,    46,   149,   135,   111,    56,    58,   139,
      12,    13,    14,    15,    99,   105,    16,    57,    57,    17,
      88,    55,    89,    18,    19,   152,    24,   111,    90,    91,
      50,    52,   109,    21,   170,    22,   111,    48,    51,   171,
      24,   111,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   161,   129,   -71,   162,   130,
      62,   153,    75,    76,    77,    68,    69,   134,    62,   100,
      85,   138,    62,   180,   101,   111,    86,    87,   164,   103,
       8,   177,   145,    96,   108,    97,    88,   172,    89,   132,
     179,    98,   181,   115,    90,    91,   133,   136,   140,     1,
       2,     3,     4,     5,   182,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,   160,   142,    16,    62,    61,
      17,    62,   147,   157,    18,    19,   165,   150,   159,   163,
     176,   167,    20,   178,    21,    20,    22,   143,    23,    70,
     146,    24,     0,     0,    62,     1,     2,     3,     4,     0,
       0,     0,     0,     0,     0,     0,     0,    12,    13,    14,
      15,     0,     0,    16,     0,     0,    17,     0,     0,     0,
      18,    19,     0,     0,     0,     0,     0,     0,    61,     0,
      21,     0,    22,     1,     2,     3,     4,    24,     0,     0,
       0,     8,     0,     0,     0,    12,    13,    14,    15,     0,
       0,    16,     0,     0,    17,     0,     0,     0,    18,    19,
       0,     0,     0,     0,     1,     2,     3,     4,    21,     0,
      22,     0,     0,     0,     0,    24,    12,    13,    14,    15,
       0,     0,    16,     0,     0,    17,     0,     0,     0,    18,
      19,     0,     0,     0,     0,     0,     0,     0,     0,    21,
       0,    22,     0,    71,    72,     0,    24,    73,    74,    75,
      76,    77,     0,     0,    78,    79,    80,    81,    82,    83,
       0,     0,     0,     0,     0,    71,    72,     0,   144,    73,
      74,    75,    76,    77,     0,     0,    78,    79,    80,    81,
      82,    83,     0,     0,     0,    71,    72,     0,    84,    73,
      74,    75,    76,    77,     0,     0,    78,    79,    80,    81,
      82,    83,     0,     0,     0,    71,    72,     0,   104,    73,
      74,    75,    76,    77,     0,     0,    78,    79,    80,    81,
      82,    83,     0,     0,     0,    71,    72,     0,   173,    73,
      74,    75,    76,    77,     0,     0,    78,    79,    80,    81,
      82,    83,     0,     0,    71,    72,     0,   114,    73,    74,
      75,    76,    77,     0,     0,    78,    79,    80,    81,    82,
      83,     0,     0,    71,    72,     0,   137,    73,    74,    75,
      76,    77,     0,     0,    78,    79,    80,    81,    82,    83,
       0,     0,    71,    72,     0,   154,    73,    74,    75,    76,
      77,     0,     0,    78,    79,    80,    81,    82,    83,    71,
      72,     0,   148,    73,    74,    75,    76,    77,     0,     0,
      78,    79,    80,    81,    82,    83,    71,    72,     0,   151,
      73,    74,    75,    76,    77,     0,     0,    78,    79,    80,
      81,    82,    83,     0,   169,    71,    72,     0,     0,    73,
      74,    75,    76,    77,     0,     0,    78,    79,    80,    81,
      82,    83,    73,    74,    75,    76,    77,     0,     0,    78,
      79,    80,    81,    82,    83,    73,    74,    75,    76,    77,
       0,     0,   -72,   -72,    80,    81,    82,    83,    73,    74,
      75,    76,    77,     0,     0,     0,     0,   -72,   -72,   -72,
     -72
};

static const yytype_int16 yycheck[] =
{
       9,    39,    22,    59,     3,    43,    39,    16,    17,    40,
      43,   156,    21,    22,    42,    43,    15,    89,     3,     4,
       5,     6,   167,     3,    41,    97,    43,    18,    19,   101,
      15,    16,    17,    18,    43,    55,    21,    18,    19,    24,
      38,    40,    40,    28,    29,    41,    45,    43,    46,    47,
      42,     3,    61,    38,    41,    40,    43,    42,    42,    41,
      45,    43,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,   147,    85,    37,   150,    88,
      89,   137,    25,    26,    27,     3,     0,    96,    97,    40,
      22,   100,   101,    41,    40,    43,    28,    29,   154,    40,
      11,   173,   111,    38,    37,    40,    38,   163,    40,     3,
     176,    46,   178,    41,    46,    47,     3,     3,    40,     3,
       4,     5,     6,     7,   180,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,   144,    41,    21,   147,    36,
      24,   150,    40,     3,    28,    29,   155,    40,    37,     8,
      41,    43,    36,    41,    38,    36,    40,   107,    42,    27,
     113,    45,    -1,    -1,   173,     3,     4,     5,     6,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    15,    16,    17,
      18,    -1,    -1,    21,    -1,    -1,    24,    -1,    -1,    -1,
      28,    29,    -1,    -1,    -1,    -1,    -1,    -1,    36,    -1,
      38,    -1,    40,     3,     4,     5,     6,    45,    -1,    -1,
      -1,    11,    -1,    -1,    -1,    15,    16,    17,    18,    -1,
      -1,    21,    -1,    -1,    24,    -1,    -1,    -1,    28,    29,
      -1,    -1,    -1,    -1,     3,     4,     5,     6,    38,    -1,
      40,    -1,    -1,    -1,    -1,    45,    15,    16,    17,    18,
      -1,    -1,    21,    -1,    -1,    24,    -1,    -1,    -1,    28,
      29,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,
      -1,    40,    -1,    19,    20,    -1,    45,    23,    24,    25,
      26,    27,    -1,    -1,    30,    31,    32,    33,    34,    35,
      -1,    -1,    -1,    -1,    -1,    19,    20,    -1,    44,    23,
      24,    25,    26,    27,    -1,    -1,    30,    31,    32,    33,
      34,    35,    -1,    -1,    -1,    19,    20,    -1,    42,    23,
      24,    25,    26,    27,    -1,    -1,    30,    31,    32,    33,
      34,    35,    -1,    -1,    -1,    19,    20,    -1,    42,    23,
      24,    25,    26,    27,    -1,    -1,    30,    31,    32,    33,
      34,    35,    -1,    -1,    -1,    19,    20,    -1,    42,    23,
      24,    25,    26,    27,    -1,    -1,    30,    31,    32,    33,
      34,    35,    -1,    -1,    19,    20,    -1,    41,    23,    24,
      25,    26,    27,    -1,    -1,    30,    31,    32,    33,    34,
      35,    -1,    -1,    19,    20,    -1,    41,    23,    24,    25,
      26,    27,    -1,    -1,    30,    31,    32,    33,    34,    35,
      -1,    -1,    19,    20,    -1,    41,    23,    24,    25,    26,
      27,    -1,    -1,    30,    31,    32,    33,    34,    35,    19,
      20,    -1,    39,    23,    24,    25,    26,    27,    -1,    -1,
      30,    31,    32,    33,    34,    35,    19,    20,    -1,    39,
      23,    24,    25,    26,    27,    -1,    -1,    30,    31,    32,
      33,    34,    35,    -1,    37,    19,    20,    -1,    -1,    23,
      24,    25,    26,    27,    -1,    -1,    30,    31,    32,    33,
      34,    35,    23,    24,    25,    26,    27,    -1,    -1,    30,
      31,    32,    33,    34,    35,    23,    24,    25,    26,    27,
      -1,    -1,    30,    31,    32,    33,    34,    35,    23,    24,
      25,    26,    27,    -1,    -1,    -1,    -1,    32,    33,    34,
      35
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    21,    24,    28,    29,
      36,    38,    40,    42,    45,    50,    51,    52,    53,    54,
      55,    57,    58,    60,    61,    66,    69,    72,    79,    81,
      82,    84,    86,    40,    83,    85,     3,    76,    42,    54,
      42,    42,     3,    54,    54,    40,    58,    61,    58,    70,
      71,    36,    54,    65,    67,    68,    54,    72,     3,     0,
      51,    19,    20,    23,    24,    25,    26,    27,    30,    31,
      32,    33,    34,    35,    42,    22,    28,    29,    38,    40,
      46,    47,    62,    63,    64,    59,    38,    40,    46,    54,
      40,    40,    73,    40,    42,    72,    56,    52,    37,    54,
      39,    43,    39,    43,    41,    41,    54,    54,    54,    54,
      54,    54,    54,    54,    54,    54,    54,    54,    54,    54,
      54,    65,     3,     3,    54,    65,     3,    41,    54,    65,
      40,    77,    41,    50,    44,    54,    68,    40,    39,    41,
      40,    39,    41,    52,    41,    42,    74,     3,    80,    37,
      54,    65,    65,     8,    52,    54,    80,    43,    78,    37,
      41,    41,    52,    42,    75,    80,    41,    65,    41,    69,
      41,    69,    52
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    49,    50,    51,    51,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    53,    54,    54,    54,    54,
      54,    54,    54,    54,    54,    54,    54,    54,    54,    54,
      54,    55,    55,    55,    56,    55,    55,    55,    55,    55,
      57,    57,    57,    57,    57,    58,    58,    58,    59,    58,
      60,    60,    60,    60,    61,    61,    61,    62,    62,    63,
      64,    65,    65,    65,    66,    66,    67,    67,    68,    70,
      69,    71,    69,    73,    74,    75,    72,    76,    77,    78,
      72,    79,    79,    79,    79,    79,    79,    80,    80,    80,
      81,    81,    83,    82,    85,    84,    86,    86
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     0,     2,     1,     1,     1,     1,
       2,     2,     1,     1,     1,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     1,
       1,     3,     2,     2,     0,     3,     2,     2,     2,     1,
       1,     1,     1,     3,     1,     1,     2,     2,     0,     2,
       3,     4,     3,     4,     4,     2,     6,     1,     1,     3,
       5,     3,     1,     0,     3,     3,     3,     1,     5,     0,
       5,     0,     3,     0,     0,     0,     9,     0,     0,     0,
       8,     1,     1,     1,     1,     1,     1,     3,     1,     0,
       5,     7,     0,     6,     0,    10,     3,     2
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 3:
#line 92 "parser.y" /* yacc.c:1646  */
    {printf("stmts->stmt stmts\n");}
#line 1552 "parser.c" /* yacc.c:1646  */
    break;

  case 4:
#line 93 "parser.y" /* yacc.c:1646  */
    {printf("stmts-> *empty*\n");}
#line 1558 "parser.c" /* yacc.c:1646  */
    break;

  case 5:
#line 96 "parser.y" /* yacc.c:1646  */
    {printf("stmt->expr;\n");}
#line 1564 "parser.c" /* yacc.c:1646  */
    break;

  case 6:
#line 97 "parser.y" /* yacc.c:1646  */
    {printf("stmt->ifstmt\n");}
#line 1570 "parser.c" /* yacc.c:1646  */
    break;

  case 7:
#line 98 "parser.y" /* yacc.c:1646  */
    {printf("stmt->whilestmt\n");}
#line 1576 "parser.c" /* yacc.c:1646  */
    break;

  case 8:
#line 100 "parser.y" /* yacc.c:1646  */
    {printf("stmt->forstmt\n");}
#line 1582 "parser.c" /* yacc.c:1646  */
    break;

  case 9:
#line 102 "parser.y" /* yacc.c:1646  */
    {printf("stmt->returnstmt\n");
							if(!is_func){
								printf(KRED"Error at line %d: return used outside of function\n"KNRM, yylineno);
							}}
#line 1591 "parser.c" /* yacc.c:1646  */
    break;

  case 10:
#line 106 "parser.y" /* yacc.c:1646  */
    {printf("stmt->break\n");

							//printf("is_loop = %d\tis_loop_in_func = %d\n", is_loop, is_loop_in_func);
							//if not in loop -> error
							if (!is_loop && !is_loop_in_func)
							{
								printf(KRED "Error at line %d: break used outside of loop\n" KNRM, yylineno);
							}
							}
#line 1605 "parser.c" /* yacc.c:1646  */
    break;

  case 11:
#line 115 "parser.y" /* yacc.c:1646  */
    {printf("stmt->continue\n");
								if (!is_loop && !is_loop_in_func)
								//if not in loop -> error

								{
									printf(KRED "Error at line %d: continue used outside of loop\n" KNRM, yylineno);
								}
								}
#line 1618 "parser.c" /* yacc.c:1646  */
    break;

  case 12:
#line 123 "parser.y" /* yacc.c:1646  */
    {printf("stmt->block\n");}
#line 1624 "parser.c" /* yacc.c:1646  */
    break;

  case 13:
#line 124 "parser.y" /* yacc.c:1646  */
    {printf("stmt->funcdef\n");}
#line 1630 "parser.c" /* yacc.c:1646  */
    break;

  case 14:
#line 125 "parser.y" /* yacc.c:1646  */
    {printf("stmt->semicolon\n");}
#line 1636 "parser.c" /* yacc.c:1646  */
    break;

  case 15:
#line 128 "parser.y" /* yacc.c:1646  */
    {printf("Assinexpr-> lvalue = expr\n");
								if((yyvsp[-2].exprNode)!=NULL){
								printf("lalala\n");}

								if((yyvsp[-2].exprNode)->type == USERFUNC || (yyvsp[-2].exprNode)->type == LIBFUNC){
									printf(KRED "Error: Invalid action on function in line %d: %s \'=\' expr\n" KNRM, yylineno, (yyvsp[-2].exprNode)->value.funcVal->name);
								}
								}
#line 1649 "parser.c" /* yacc.c:1646  */
    break;

  case 16:
#line 138 "parser.y" /* yacc.c:1646  */
    {printf("expr + expr\n");}
#line 1655 "parser.c" /* yacc.c:1646  */
    break;

  case 17:
#line 139 "parser.y" /* yacc.c:1646  */
    {printf("expr - expr\n");}
#line 1661 "parser.c" /* yacc.c:1646  */
    break;

  case 18:
#line 140 "parser.y" /* yacc.c:1646  */
    {printf("expr * expr\n");}
#line 1667 "parser.c" /* yacc.c:1646  */
    break;

  case 19:
#line 141 "parser.y" /* yacc.c:1646  */
    {printf("expr / expr\n");}
#line 1673 "parser.c" /* yacc.c:1646  */
    break;

  case 20:
#line 142 "parser.y" /* yacc.c:1646  */
    {printf("expr mod expr\n");}
#line 1679 "parser.c" /* yacc.c:1646  */
    break;

  case 21:
#line 143 "parser.y" /* yacc.c:1646  */
    {printf("expr == expr\n");}
#line 1685 "parser.c" /* yacc.c:1646  */
    break;

  case 22:
#line 144 "parser.y" /* yacc.c:1646  */
    {printf("expr != expr\n");}
#line 1691 "parser.c" /* yacc.c:1646  */
    break;

  case 23:
#line 145 "parser.y" /* yacc.c:1646  */
    {printf("expr > expr\n");}
#line 1697 "parser.c" /* yacc.c:1646  */
    break;

  case 24:
#line 146 "parser.y" /* yacc.c:1646  */
    {printf("expr->expr >= expr\n");}
#line 1703 "parser.c" /* yacc.c:1646  */
    break;

  case 25:
#line 147 "parser.y" /* yacc.c:1646  */
    {printf("expr->expr < expr\n");}
#line 1709 "parser.c" /* yacc.c:1646  */
    break;

  case 26:
#line 148 "parser.y" /* yacc.c:1646  */
    {printf("expr->expr <= expr\n");}
#line 1715 "parser.c" /* yacc.c:1646  */
    break;

  case 27:
#line 149 "parser.y" /* yacc.c:1646  */
    {printf("expr->expr AND expr\n");}
#line 1721 "parser.c" /* yacc.c:1646  */
    break;

  case 28:
#line 150 "parser.y" /* yacc.c:1646  */
    {printf("expr->expr OR expr\n");}
#line 1727 "parser.c" /* yacc.c:1646  */
    break;

  case 29:
#line 151 "parser.y" /* yacc.c:1646  */
    {printf("expr->assignexpr\n"); }
#line 1733 "parser.c" /* yacc.c:1646  */
    break;

  case 30:
#line 152 "parser.y" /* yacc.c:1646  */
    {printf("expr-> term\n");}
#line 1739 "parser.c" /* yacc.c:1646  */
    break;

  case 31:
#line 157 "parser.y" /* yacc.c:1646  */
    {printf("term->(expr)\n");}
#line 1745 "parser.c" /* yacc.c:1646  */
    break;

  case 32:
#line 158 "parser.y" /* yacc.c:1646  */
    {printf("term->-expr\n");}
#line 1751 "parser.c" /* yacc.c:1646  */
    break;

  case 33:
#line 159 "parser.y" /* yacc.c:1646  */
    {printf("term->!expr");}
#line 1757 "parser.c" /* yacc.c:1646  */
    break;

  case 34:
#line 160 "parser.y" /* yacc.c:1646  */
    {printf("term->++lvalue\n");}
#line 1763 "parser.c" /* yacc.c:1646  */
    break;

  case 35:
#line 161 "parser.y" /* yacc.c:1646  */
    {
											if((yyvsp[-1].exprNode)->type == USERFUNC || (yyvsp[-1].exprNode)->type == LIBFUNC){
												printf(KRED"Error: Invalid action on function in line %d: ++%s\n"KNRM, yylineno, (yyvsp[-1].exprNode)->value.funcVal->name);
											}
											}
#line 1773 "parser.c" /* yacc.c:1646  */
    break;

  case 36:
#line 166 "parser.y" /* yacc.c:1646  */
    {
											if((yyvsp[-1].exprNode)->type == USERFUNC || (yyvsp[-1].exprNode)->type == LIBFUNC){
												printf(KRED"Error: Invalid action on function in line %d: %s++\n"KNRM, yylineno, (yyvsp[-1].exprNode)->value.funcVal->name);
											}
											}
#line 1783 "parser.c" /* yacc.c:1646  */
    break;

  case 37:
#line 171 "parser.y" /* yacc.c:1646  */
    {
											if((yyvsp[0].exprNode)->type == USERFUNC || (yyvsp[0].exprNode)->type == LIBFUNC){
												printf(KRED"Error: Invalid action on function in line %d: --%s\n"KNRM, yylineno, (yyvsp[0].exprNode)->value.funcVal->name);
											}
											}
#line 1793 "parser.c" /* yacc.c:1646  */
    break;

  case 38:
#line 176 "parser.y" /* yacc.c:1646  */
    {
											if((yyvsp[-1].exprNode)->type == USERFUNC || (yyvsp[-1].exprNode)->type == LIBFUNC){
												printf(KRED"Error: Invalid action on function in line %d: %s--\n"KNRM, yylineno, (yyvsp[-1].exprNode)->value.funcVal->name);
											}
											}
#line 1803 "parser.c" /* yacc.c:1646  */
    break;

  case 39:
#line 181 "parser.y" /* yacc.c:1646  */
    {printf("term->primary\n");}
#line 1809 "parser.c" /* yacc.c:1646  */
    break;

  case 40:
#line 184 "parser.y" /* yacc.c:1646  */
    {printf("primary->lvalue\n");}
#line 1815 "parser.c" /* yacc.c:1646  */
    break;

  case 41:
#line 185 "parser.y" /* yacc.c:1646  */
    {printf("primary->call\n");}
#line 1821 "parser.c" /* yacc.c:1646  */
    break;

  case 42:
#line 186 "parser.y" /* yacc.c:1646  */
    {printf("primary->objectdef\n");}
#line 1827 "parser.c" /* yacc.c:1646  */
    break;

  case 43:
#line 187 "parser.y" /* yacc.c:1646  */
    {printf("primary->(funcdef)\n");}
#line 1833 "parser.c" /* yacc.c:1646  */
    break;

  case 44:
#line 188 "parser.y" /* yacc.c:1646  */
    {printf("primary->const\n");}
#line 1839 "parser.c" /* yacc.c:1646  */
    break;

  case 45:
#line 191 "parser.y" /* yacc.c:1646  */
    {printf("lvalue->IDENTIFIER: %s\n", (yyvsp[0].stringVal));
								tmp_scope = scope;
								//lookup id from current scope to global
								while(tmp_scope>=GLOBAl_SCOPE){
									entry=lookup(tmp_scope, (char*)(yyvsp[0].stringVal));
									if(entry!=NULL){
										break;
									}
									tmp_scope--;
								}
								tmp_scope++;

								//if no entry found
								if(entry==NULL){
									printf(KCYN "LOOKUP: symbol \'%s\', at line %d not found in symbol table\n" KNRM, (yyvsp[0].stringVal), yylineno);

									
									if(is_func){	//if we are inside a function
										if(tmp_scope-1 >= func_scope){
											//if we are inside inside a function body
											var_symbol = create_symbol_var((char *)(yyvsp[0].stringVal), scope, yylineno);
											//insert entry
											if (scope == 0)
											{
												entry = create_entry(var_symbol, GLOBAL);
											}
											else
											{
												entry = create_entry(var_symbol, LOCAL);
											}
										}
									}
									else{
										//if we are not inside insert entry at current scope
										var_symbol = create_symbol_var((char*)(yyvsp[0].stringVal), scope, yylineno);
										if (scope == 0)
										{
											entry = create_entry(var_symbol, GLOBAL);
										}
										else
										{
											entry = create_entry(var_symbol, LOCAL);
										}
									}
								}
								else{
									printf(KCYN "LOOKUP: symbol \'%s\', at line %d found in scope %d\n" KNRM, (yyvsp[0].stringVal), yylineno, tmp_scope-1);
									// printf("tempscore = %d\n", tmp_scope-1);
									// printf("function scope = %d\n", func_scope);

									//if entry found out of current function scope and not in global->error
									if (is_func && (tmp_scope-1 < func_scope) && (tmp_scope-1) != GLOBAl_SCOPE)
									{
										{
											printf(KRED "Error: Cannot access %s in scope %d\n" KNRM, (yyvsp[0].stringVal), tmp_scope-1);
										}
									}
								}
								//lvalue = symbol_entry;
								(yyval.exprNode) = entry;

								

								}
#line 1908 "parser.c" /* yacc.c:1646  */
    break;

  case 46:
#line 256 "parser.y" /* yacc.c:1646  */
    {printf("lvalue->LOCAL ID\n");
								//lookup in current scope

								entry = lookup(scope, (char*)(yyvsp[0].stringVal));
								collision_flag = collisions((yyvsp[0].stringVal));

								if(entry==NULL && !collision_flag){
									printf(KCYN "LOOKUP: local symbol \'%s\', at line %d not found in scope %d\n" KNRM, (yyvsp[0].stringVal), yylineno, scope);

									//if symbol not found, insert entry locally
									var_symbol = create_symbol_var((char*)(yyvsp[0].stringVal), scope, yylineno);
									if(scope==0){
										entry = create_entry(var_symbol, GLOBAL);
									}
									else{
										entry = create_entry(var_symbol, LOCAL);
									}
								}
								else{
									printf(KCYN "LOOKUP: local symbol \'%s\', at line %d found in scope %d\n" KNRM, (yyvsp[0].stringVal), yylineno, scope);
								}

								//lvalue = entry
								(yyval.exprNode) = entry;
							}
#line 1938 "parser.c" /* yacc.c:1646  */
    break;

  case 47:
#line 281 "parser.y" /* yacc.c:1646  */
    {printf("lvalue->::ID\n");
								//lookup only
								entry = lookup(GLOBAl_SCOPE, (yyvsp[0].stringVal));
								if(entry){
									(yyval.exprNode) = entry;
									printf(KCYN "LOOKUP: Global symbol \'%s\', at line %d found in global scope\n" KNRM, (yyvsp[0].stringVal), yylineno);
								}

								else{
									(yyval.exprNode) = (st_entry*)(yyvsp[0].stringVal);
								printf(KRED "LOOKUP ERROR: Global symbol \'%s\', at line %d not found in global scope\n" KNRM, (yyvsp[0].stringVal), yylineno);
								}

								//lvalue = entry
								
								
								}
#line 1960 "parser.c" /* yacc.c:1646  */
    break;

  case 48:
#line 298 "parser.y" /* yacc.c:1646  */
    {printf("lvalue->member\n");}
#line 1966 "parser.c" /* yacc.c:1646  */
    break;

  case 49:
#line 299 "parser.y" /* yacc.c:1646  */
    {
									//lvalue = member
									(yyval.exprNode) = (yyvsp[-1].exprNode);
								}
#line 1975 "parser.c" /* yacc.c:1646  */
    break;

  case 50:
#line 305 "parser.y" /* yacc.c:1646  */
    { printf("member->lvalue.ID: lvalue.ID\n"); 
									entry = lookup(scope, (yyvsp[0].stringVal));
									(yyvsp[-2].exprNode) = entry;
									(yyval.exprNode) = (st_entry*)(yyvsp[0].stringVal);
										}
#line 1985 "parser.c" /* yacc.c:1646  */
    break;

  case 51:
#line 310 "parser.y" /* yacc.c:1646  */
    {printf("member->lvalue[expr]\n");}
#line 1991 "parser.c" /* yacc.c:1646  */
    break;

  case 52:
#line 311 "parser.y" /* yacc.c:1646  */
    {printf("member->call.ID\n");

										(yyval.exprNode) = (st_entry*)(yyvsp[0].stringVal);
										}
#line 2000 "parser.c" /* yacc.c:1646  */
    break;

  case 53:
#line 315 "parser.y" /* yacc.c:1646  */
    {printf("member->call[expr]\n");
												(yyval.exprNode) = (yyvsp[-1].exprNode);}
#line 2007 "parser.c" /* yacc.c:1646  */
    break;

  case 54:
#line 319 "parser.y" /* yacc.c:1646  */
    {printf("call->call(elist)\n");}
#line 2013 "parser.c" /* yacc.c:1646  */
    break;

  case 55:
#line 320 "parser.y" /* yacc.c:1646  */
    {printf("call->lvalue callsufix\n");}
#line 2019 "parser.c" /* yacc.c:1646  */
    break;

  case 56:
#line 322 "parser.y" /* yacc.c:1646  */
    {printf("call->(funcdef) (elist)\n");}
#line 2025 "parser.c" /* yacc.c:1646  */
    break;

  case 57:
#line 325 "parser.y" /* yacc.c:1646  */
    {printf("callsuffix->normcall\n");}
#line 2031 "parser.c" /* yacc.c:1646  */
    break;

  case 58:
#line 326 "parser.y" /* yacc.c:1646  */
    {printf("callsuffix->methodcall\n");}
#line 2037 "parser.c" /* yacc.c:1646  */
    break;

  case 59:
#line 329 "parser.y" /* yacc.c:1646  */
    {printf("normcall-> (elist)\n");}
#line 2043 "parser.c" /* yacc.c:1646  */
    break;

  case 60:
#line 333 "parser.y" /* yacc.c:1646  */
    {printf("methodcal-> ..%s\n", (yyvsp[-3].stringVal));}
#line 2049 "parser.c" /* yacc.c:1646  */
    break;

  case 61:
#line 336 "parser.y" /* yacc.c:1646  */
    { printf("elist-> expr, elist\n"); }
#line 2055 "parser.c" /* yacc.c:1646  */
    break;

  case 62:
#line 337 "parser.y" /* yacc.c:1646  */
    { printf("elist-> expr \n"); }
#line 2061 "parser.c" /* yacc.c:1646  */
    break;

  case 63:
#line 338 "parser.y" /* yacc.c:1646  */
    {printf("elist -> *empty*\n");}
#line 2067 "parser.c" /* yacc.c:1646  */
    break;

  case 64:
#line 342 "parser.y" /* yacc.c:1646  */
    {printf("objectdef-> [expr, elist]\t line: %d\n", yylineno);}
#line 2073 "parser.c" /* yacc.c:1646  */
    break;

  case 65:
#line 343 "parser.y" /* yacc.c:1646  */
    {printf("objectdef-> [indexelem, indexed]\t line: %d\n", yylineno);}
#line 2079 "parser.c" /* yacc.c:1646  */
    break;

  case 66:
#line 347 "parser.y" /* yacc.c:1646  */
    {printf("indexed-> indexedelem, indexed\t line: %d\n", yylineno);}
#line 2085 "parser.c" /* yacc.c:1646  */
    break;

  case 67:
#line 348 "parser.y" /* yacc.c:1646  */
    {printf("indexed-> indexedelem\t line: %d\n", yylineno);}
#line 2091 "parser.c" /* yacc.c:1646  */
    break;

  case 68:
#line 351 "parser.y" /* yacc.c:1646  */
    {printf("indexedelem-> {expr:expr}\t line: %d\n", yylineno);}
#line 2097 "parser.c" /* yacc.c:1646  */
    break;

  case 69:
#line 355 "parser.y" /* yacc.c:1646  */
    {if((!is_func)){
								//if we are inside a function scope is already incr
								// by funcdef rule so we dont increase twice
								scope++;
								}
								if((is_func)&&is_loop_in_func){
									scope++;
								}
							}
#line 2111 "parser.c" /* yacc.c:1646  */
    break;

  case 70:
#line 364 "parser.y" /* yacc.c:1646  */
    {printf("block-> { stmt }\n");
		 						hide(scope);
		 						if(func_scope){func_scope--;}
		 						if(scope>0)
		 						scope--;
											}
#line 2122 "parser.c" /* yacc.c:1646  */
    break;

  case 71:
#line 370 "parser.y" /* yacc.c:1646  */
    {if((!is_func)){
								//if we are inside a function scope is already incr
								// by funcdef rule so we dont increase twice
								scope++;
								}
								if((is_func)&&is_loop_in_func){
									scope++;
								}
							}
#line 2136 "parser.c" /* yacc.c:1646  */
    break;

  case 72:
#line 379 "parser.y" /* yacc.c:1646  */
    {printf("block-> {}\n");
		 							if(scope>0)
									scope--; //recheck
									}
#line 2145 "parser.c" /* yacc.c:1646  */
    break;

  case 73:
#line 385 "parser.y" /* yacc.c:1646  */
    {printf("funcdef-> function ID (idlist) block\n");
								tmp_scope = scope;
								while(tmp_scope>=GLOBAl_SCOPE){
									entry=lookup(scope, (char*)(yyvsp[0].stringVal));
									tmp_scope--;
								}
								if(entry==NULL){
									printf(KCYN "LOOKUP: function symbol \'%s\', at line %d not found in symbol table\n" KNRM, (yyvsp[0].stringVal), yylineno);
									func_scope = scope+1;
									func_symbol = create_symbol_func((yyvsp[0].stringVal), args, scope, yylineno);
									entry = create_entry(func_symbol, USERFUNC);
								}
								else{
									printf(KRED"Error at line %d: %s already defined\n"KNRM,yylineno, (yyvsp[0].stringVal));
								}

								}
#line 2167 "parser.c" /* yacc.c:1646  */
    break;

  case 74:
#line 402 "parser.y" /* yacc.c:1646  */
    {scope++; is_func++; is_loop_in_func = 0;}
#line 2173 "parser.c" /* yacc.c:1646  */
    break;

  case 75:
#line 403 "parser.y" /* yacc.c:1646  */
    { 
			 	if(args==NULL)
			 		free_arg_list(args); }
#line 2181 "parser.c" /* yacc.c:1646  */
    break;

  case 76:
#line 407 "parser.y" /* yacc.c:1646  */
    {
				 is_func--;
			 }
#line 2189 "parser.c" /* yacc.c:1646  */
    break;

  case 77:
#line 410 "parser.y" /* yacc.c:1646  */
    {printf("funcdef-> function (idlist) block\n");
			 	char * funcname = newUnnamedFunc();
			 	func_scope = scope+1;
			 	func_symbol = create_symbol_func(funcname, args, scope, yylineno);
			 	entry = create_entry(func_symbol, USERFUNC);

			 				}
#line 2201 "parser.c" /* yacc.c:1646  */
    break;

  case 78:
#line 416 "parser.y" /* yacc.c:1646  */
    {scope++; is_func++; is_loop_in_func = 0;}
#line 2207 "parser.c" /* yacc.c:1646  */
    break;

  case 79:
#line 417 "parser.y" /* yacc.c:1646  */
    { free_arg_list(args); }
#line 2213 "parser.c" /* yacc.c:1646  */
    break;

  case 80:
#line 420 "parser.y" /* yacc.c:1646  */
    {
				 is_func--;
				 }
#line 2221 "parser.c" /* yacc.c:1646  */
    break;

  case 81:
#line 424 "parser.y" /* yacc.c:1646  */
    { printf("integer: %d\n", (yyvsp[0].intVal)); }
#line 2227 "parser.c" /* yacc.c:1646  */
    break;

  case 82:
#line 425 "parser.y" /* yacc.c:1646  */
    { printf("String: %s\n", (yyvsp[0].stringVal)); }
#line 2233 "parser.c" /* yacc.c:1646  */
    break;

  case 83:
#line 426 "parser.y" /* yacc.c:1646  */
    { printf("Float %f\n", (yyvsp[0].realVal)); }
#line 2239 "parser.c" /* yacc.c:1646  */
    break;

  case 84:
#line 427 "parser.y" /* yacc.c:1646  */
    { printf("NIL\n"); }
#line 2245 "parser.c" /* yacc.c:1646  */
    break;

  case 85:
#line 428 "parser.y" /* yacc.c:1646  */
    { printf("TRUE\n"); }
#line 2251 "parser.c" /* yacc.c:1646  */
    break;

  case 86:
#line 429 "parser.y" /* yacc.c:1646  */
    { printf("FALSE\n"); }
#line 2257 "parser.c" /* yacc.c:1646  */
    break;

  case 87:
#line 434 "parser.y" /* yacc.c:1646  */
    {
				 //link the rest of the arguments to argument list
				 printf("idlist-> Argument, Arguments\n");
				 tmp_arg = args;
				 while (tmp_arg->next)
				 {
					 tmp_arg = tmp_arg->next;
				 }
				 entry = lookup(scope, (yyvsp[-2].stringVal));
				 collision_flag = collisions((yyvsp[-2].stringVal));
				 if (entry == NULL && !collision_flag)
				 {
					 var_symbol = create_symbol_var((yyvsp[-2].stringVal), scope, yylineno);
					 entry = create_entry(var_symbol, FORMAL);
					// tmp_arg->next = args;
					  args = tmp_arg;
					 tmp_arg->arg = var_symbol;
					 tmp_arg->next = args;
					 args->next = NULL;
				 }
				 else if(collision_flag){}
				 
				 else{
					 tmp_arg = args;
					 while(tmp_arg){
						 if(!strcmp(tmp_arg->arg->name, (yyvsp[-2].stringVal))){
					 		printf(KRED "Error: Formal redeclaration \'%s\' at line %d\n" KNRM, (yyvsp[-2].stringVal), yylineno);
							 break;
						 }
						 // printf("name: %s\n", tmp_arg->arg->name);
						 tmp_arg = tmp_arg->next;
					 }
				 }
				 }
#line 2296 "parser.c" /* yacc.c:1646  */
    break;

  case 88:
#line 469 "parser.y" /* yacc.c:1646  */
    {
					 
					 
					 printf("idlist-> Argument = %s\n", (yyvsp[0].stringVal));
					 //initialize and insert first argument to argument list
					 entry = lookup(scope, (yyvsp[0].stringVal));
					 collision_flag = collisions((yyvsp[0].stringVal));
					 if (!collision_flag)
					 {
						 printf(KCYN "LOOKUP: Formal Argument \'%s\', at line %d not found in function arguments\n" KNRM, (yyvsp[0].stringVal), yylineno);
						 var_symbol = create_symbol_var((yyvsp[0].stringVal), scope, yylineno);
						 entry = create_entry(var_symbol, FORMAL);
						 args->arg = var_symbol;
						 args->next = NULL;
					 }
					 else
					 {
						 //printf(KRED "Error: formal redeclaration\n" KNRM);
					 }
				 }
#line 2321 "parser.c" /* yacc.c:1646  */
    break;

  case 90:
#line 493 "parser.y" /* yacc.c:1646  */
    { printf("ifstmt-> if (expr) stmt\n"); }
#line 2327 "parser.c" /* yacc.c:1646  */
    break;

  case 91:
#line 494 "parser.y" /* yacc.c:1646  */
    { printf("ifstmt->if (expr) stmt else (stmt)\n"); }
#line 2333 "parser.c" /* yacc.c:1646  */
    break;

  case 92:
#line 498 "parser.y" /* yacc.c:1646  */
    {	printf("whilestmt-> wile (expr) stmt\n");
					 if (is_func)
						 is_loop_in_func++;
					is_loop++;}
#line 2342 "parser.c" /* yacc.c:1646  */
    break;

  case 93:
#line 503 "parser.y" /* yacc.c:1646  */
    {printf("while (expr){stmt}\n");

					if (is_func)
						is_loop_in_func=0;
					else
						is_loop --;
				}
#line 2354 "parser.c" /* yacc.c:1646  */
    break;

  case 94:
#line 513 "parser.y" /* yacc.c:1646  */
    {	printf("forstmt-> for(elist; expr; elist;) stmt\n");
				if (is_func)
					is_loop_in_func++;
				
					is_loop ++;
			}
#line 2365 "parser.c" /* yacc.c:1646  */
    break;

  case 95:
#line 520 "parser.y" /* yacc.c:1646  */
    {printf("for (elist); (expr); (elist))\n");
					if (is_func)
						is_loop_in_func=0;
					else
					is_loop--;
				}
#line 2376 "parser.c" /* yacc.c:1646  */
    break;

  case 96:
#line 527 "parser.y" /* yacc.c:1646  */
    {printf("return expr;\n");}
#line 2382 "parser.c" /* yacc.c:1646  */
    break;

  case 97:
#line 528 "parser.y" /* yacc.c:1646  */
    {printf("return;\n");}
#line 2388 "parser.c" /* yacc.c:1646  */
    break;


#line 2392 "parser.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 531 "parser.y" /* yacc.c:1906  */


int main(int argc, char* argv[])
{
	printf("-------------------------- SYNTAX ANALYZER --------------------------  \n\n");
	clock_t begin = clock();

	scope_list = (st_entry**)malloc(sizeof(st_entry *));
	scope_counter = 1;
	args = malloc(sizeof(arguments));

	// symbol = (st_entry*)malloc(sizeof(st_entry));
	init_bucket();
	printf("--LIBFUNCS--\n");
	init_libfuncs();
	printf("--LIBFUNCS--\n\n");
	printf(KYEL"----------Parsing Started----------\n\n"KNRM);
	if(argc > 1) {
		if(!(yyin = fopen(argv[1],"r"))) {
			fprintf(stderr, "Cannot read file: %s\n", argv[1]);
			return 1;
		}
	}
	else{
	yyin = stdin;
	}
	if(argc>2){					//read output
		if(!(yyout = fopen(argv[2], "w"))){
			fprintf(stderr, "Cannot write to file: %s\n", argv[2]);
			return -1;
		}
	}
	yyparse();
	print_st();
	clock_t end = clock();
	double time_spent = ((double)(end - begin) / CLOCKS_PER_SEC) * 1000;

	printf("\n");
 	printf("-------------------------- SYNTAX ANALYZER -------------------------- \n");
 	printf(KGRN"Syntax Analysis Completed in %.3fms !!!\n"KNRM, time_spent);
	return 0;
}



