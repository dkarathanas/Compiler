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

#include "t_code.h"

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
	extern st_entry *scope_list[20];
	extern st_entry *dummy;
	extern int scope_counter;

	extern unsigned programVarOffset;
	extern unsigned functionLocalOffset;
	extern unsigned formalArgOffset;
	extern unsigned scopeSpaceCounter;

	extern int tempcounter;


	st_entry *entry;
	var* var_symbol;
	func* func_symbol;
	arguments* args;
	arguments* tmp_arg;
	e_stack* curr_stack;

	expr* value;

	loop_stack* loop_head = NULL;
	func_stack* func_head = NULL;
	bc_stack*	bc_head = NULL;

	unsigned int scope = 0;		//this is the scope
	unsigned int curr_scope = 0;
	int tmp_scope = 0;			//tmp scope to traverse scopes
	unsigned int func_scope;	//scope the function was declared
	unsigned int is_func = 0;	//flag to check is we are inside a function body
	unsigned int is_loop = 0;	//loop counter (while, for...)
	unsigned int is_loop_in_func = 0;	//scope flag to handle block inside a loop inside a function :)
	int collision_flag = 0;				//this is a flag to check collisions with library functions
	int loopcounter = 0;

#line 134 "parser.c" /* yacc.c:339  */

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
    BREAK = 262,
    CONTINUE = 263,
    IF = 264,
    ELSE = 265,
    WHILE = 266,
    FOR = 267,
    FUNCTION = 268,
    RETURN = 269,
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
#define BREAK 262
#define CONTINUE 263
#define IF 264
#define ELSE 265
#define WHILE 266
#define FOR 267
#define FUNCTION 268
#define RETURN 269
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
#line 69 "parser.y" /* yacc.c:355  */

	char* stringVal;
	int intVal;
	double realVal;
	struct SymbolTableEntry *exprNode;
	struct expr* exp;
	struct forprefix *forprfx;
	struct list* l;

#line 280 "parser.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 297 "parser.c" /* yacc.c:358  */

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
#define YYFINAL  74
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   518

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  49
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  48
/* YYNRULES -- Number of rules.  */
#define YYNRULES  108
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  191

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
       0,   116,   116,   120,   124,   129,   146,   147,   148,   150,
     152,   156,   169,   178,   179,   180,   183,   195,   206,   229,
     235,   241,   247,   254,   261,   271,   280,   289,   298,   307,
     316,   322,   328,   329,   333,   334,   350,   357,   381,   403,
     424,   447,   449,   450,   451,   452,   456,   459,   532,   560,
     578,   585,   589,   595,   599,   603,   608,   619,   627,   630,
     635,   646,   653,   656,   659,   666,   685,   705,   706,   709,
     713,   713,   728,   728,   743,   748,   752,   756,   761,   797,
     801,   797,   811,   819,   871,   877,   882,   888,   892,   897,
     906,   946,   970,   974,   983,   990,   995,  1021,  1029,  1035,
    1037,  1039,  1045,  1062,  1065,  1067,  1079,  1095,  1099
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IDENTIFIER", "STRING", "INTEGER",
  "FLOAT", "BREAK", "CONTINUE", "IF", "ELSE", "WHILE", "FOR", "FUNCTION",
  "RETURN", "LOCL", "TRUE", "FALSE", "NIL", "AND", "OR", "NOT", "ASSIGN",
  "PLUS", "MINUS", "MULTIPLY", "DIVIDE", "MODULO", "DPLUS", "DMINUS",
  "EQUAL", "DIFFERENT", "BIGGER", "SMALLER", "BIGGER_EQUAL",
  "SMALLER_EQUAL", "LBRACKET", "RBRACKET", "LSBRACKET", "RSBRACKET",
  "LPARENTHESIS", "RPARENTHESIS", "SEMICOLON", "COMMA", "COLON", "DCOLON",
  "DOT", "DDOT", "UMINUS", "$accept", "program", "stmts", "stmt", "break",
  "continue", "assignexpr", "expr", "term", "primary", "lvalue", "member",
  "call", "callsuffix", "normcall", "methodcall", "elist", "objectdef",
  "indexed", "indexedelem", "block", "@1", "$@2", "funcblockstart",
  "funcblockend", "funcname", "funcprefix", "funcargs", "$@3", "$@4",
  "funcbody", "funcdef", "const", "idlist", "ifprefix", "elseprefix",
  "ifstmt", "loopstart", "loopend", "loopstmt", "whilestart", "whilecond",
  "whilestmt", "N", "M", "forprefix", "forstmt", "returnstmt", YY_NULLPTR
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

#define YYPACT_NINF -169

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-169)))

#define YYTABLE_NINF -73

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-73)))

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     124,  -169,  -169,  -169,  -169,   -26,   -14,   -32,  -169,     3,
      47,   167,    54,  -169,  -169,  -169,   229,   229,    16,    16,
      43,     9,   198,  -169,    78,    87,   124,  -169,  -169,  -169,
    -169,   274,  -169,  -169,    56,  -169,   -17,  -169,  -169,    52,
    -169,  -169,   124,  -169,    58,  -169,  -169,  -169,  -169,  -169,
    -169,   229,   229,  -169,  -169,  -169,   294,  -169,  -169,  -169,
      88,    53,   -17,    53,   124,    67,   229,   444,   -21,    -7,
    -169,   334,    68,  -169,  -169,  -169,   229,   229,   229,   229,
     229,   229,   229,   229,   229,   229,   229,   229,   229,  -169,
     229,  -169,  -169,   229,   229,   110,   111,  -169,  -169,  -169,
     229,   229,   112,  -169,  -169,   106,   229,  -169,   229,   353,
      -8,  -169,    76,   124,  -169,   252,  -169,   229,  -169,    82,
    -169,    79,   457,   457,    37,    37,  -169,  -169,  -169,   470,
     470,   483,   483,   483,   483,   444,   391,   -34,  -169,    80,
     408,     5,  -169,   119,    89,  -169,   124,   372,   124,  -169,
      45,  -169,  -169,    79,    97,   229,   444,  -169,   229,  -169,
    -169,   229,  -169,  -169,    81,  -169,  -169,  -169,  -169,  -169,
    -169,  -169,   229,  -169,   425,    64,    69,   119,    85,  -169,
    -169,  -169,   314,  -169,  -169,  -169,  -169,  -169,  -169,  -169,
    -169
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,    47,    85,    84,    86,     0,     0,     0,   100,     0,
      77,     0,     0,    88,    89,    87,     0,     0,     0,     0,
      70,    64,     0,    15,     0,     0,     2,     4,    11,    12,
      32,     0,    33,    41,    42,    50,    43,    44,    13,     0,
      14,    46,     0,     7,     0,     8,   103,     9,    10,    16,
      17,     0,    64,    76,    78,   108,     0,    48,    36,    35,
       0,    37,     0,    39,     0,     0,     0,    63,     0,     0,
      68,     0,     0,    49,     1,     5,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     6,
       0,    38,    40,     0,    64,     0,     0,    56,    58,    59,
       0,    64,     0,    79,    74,    95,     0,    97,    64,     0,
       0,   107,     0,     3,    73,     0,    65,     0,    66,     0,
      34,    45,    30,    31,    19,    20,    21,    22,    23,    24,
      25,    26,    28,    27,    29,    18,     0,     0,    51,     0,
       0,     0,    53,    92,     0,    94,     0,     0,     0,   102,
       0,    93,   104,     0,     0,     0,    62,    67,    64,    52,
      60,    64,    54,    55,    91,    80,    82,    75,    96,   101,
      98,   103,     0,    71,     0,     0,     0,    92,     0,    83,
      99,    97,     0,    69,    57,    61,    90,    81,   103,   105,
     106
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -169,    30,  -169,   -25,  -169,  -169,  -169,   -11,  -169,  -169,
      34,  -169,    41,  -169,  -169,  -169,   -50,  -169,  -169,    27,
       7,  -169,  -169,  -169,  -169,  -169,  -169,  -169,  -169,  -169,
    -169,   -18,  -169,   -28,  -169,  -169,  -169,  -169,  -169,   -27,
    -169,  -169,  -169,  -168,  -169,  -169,  -169,  -169
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    97,    98,    99,    68,    37,    69,    70,
      38,    64,    65,   144,   179,    54,    39,   104,   143,   178,
     167,    40,    41,   165,    42,   146,    43,   148,   180,   149,
      44,   107,    45,   108,   172,    46,    47,    48
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      56,    75,   110,   181,    72,    58,    59,   160,    51,   117,
      67,    71,     1,     2,     3,     4,    49,   105,   116,     1,
     190,   100,   117,   101,    12,    13,    14,    15,    50,   102,
      16,    12,   118,    17,   152,   117,   119,    18,    19,   113,
     109,    67,   112,    52,   137,    66,   163,    21,   117,    22,
      53,   141,    61,    63,    24,   115,    60,    57,   150,    62,
      62,    24,    80,    81,    82,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   133,   134,    90,   135,
     -72,    73,   136,    67,    91,    92,   171,    74,   117,   140,
      67,    93,   103,    94,    93,   147,    94,    67,   106,    95,
      96,    10,    95,    96,   114,   184,   156,   117,   175,   121,
     185,   176,   117,   138,   139,   142,   145,   153,    66,   158,
     161,   168,   164,   170,   177,    20,   187,     1,     2,     3,
       4,     5,     6,     7,   173,     8,     9,    10,    11,    12,
      13,    14,    15,   154,   174,    16,   157,    67,    17,   186,
      67,   166,    18,    19,   188,     0,     0,     0,     0,     0,
      20,   182,    21,     0,    22,     0,    23,     0,     0,    24,
       1,     2,     3,     4,     0,     0,     0,     0,     0,     0,
       0,     0,    12,    13,    14,    15,     0,     0,    16,     0,
       0,    17,     0,     0,     0,    18,    19,     0,     0,     0,
       0,     1,     2,     3,     4,    21,     0,    22,     0,    55,
       0,    10,    24,    12,    13,    14,    15,     0,     0,    16,
       0,     0,    17,     0,     0,     0,    18,    19,     0,     0,
       0,     0,     1,     2,     3,     4,    21,     0,    22,     0,
       0,     0,     0,    24,    12,    13,    14,    15,     0,     0,
      16,     0,     0,    17,     0,     0,     0,    18,    19,     0,
       0,     0,     0,     0,     0,     0,     0,    21,     0,    22,
       0,    76,    77,     0,    24,    78,    79,    80,    81,    82,
       0,     0,    83,    84,    85,    86,    87,    88,     0,     0,
       0,     0,     0,    76,    77,     0,   155,    78,    79,    80,
      81,    82,     0,     0,    83,    84,    85,    86,    87,    88,
       0,     0,     0,    76,    77,     0,    89,    78,    79,    80,
      81,    82,     0,     0,    83,    84,    85,    86,    87,    88,
       0,     0,     0,    76,    77,     0,   111,    78,    79,    80,
      81,    82,     0,     0,    83,    84,    85,    86,    87,    88,
       0,     0,     0,    76,    77,     0,   189,    78,    79,    80,
      81,    82,     0,     0,    83,    84,    85,    86,    87,    88,
       0,     0,    76,    77,     0,   120,    78,    79,    80,    81,
      82,     0,     0,    83,    84,    85,    86,    87,    88,     0,
       0,    76,    77,     0,   151,    78,    79,    80,    81,    82,
       0,     0,    83,    84,    85,    86,    87,    88,     0,     0,
      76,    77,     0,   169,    78,    79,    80,    81,    82,     0,
       0,    83,    84,    85,    86,    87,    88,    76,    77,     0,
     159,    78,    79,    80,    81,    82,     0,     0,    83,    84,
      85,    86,    87,    88,    76,    77,     0,   162,    78,    79,
      80,    81,    82,     0,     0,    83,    84,    85,    86,    87,
      88,     0,   183,    76,    77,     0,     0,    78,    79,    80,
      81,    82,     0,     0,    83,    84,    85,    86,    87,    88,
      78,    79,    80,    81,    82,     0,     0,    83,    84,    85,
      86,    87,    88,    78,    79,    80,    81,    82,     0,     0,
     -73,   -73,    85,    86,    87,    88,    78,    79,    80,    81,
      82,     0,     0,     0,     0,   -73,   -73,   -73,   -73
};

static const yytype_int16 yycheck[] =
{
      11,    26,    52,   171,    22,    16,    17,    41,    40,    43,
      21,    22,     3,     4,     5,     6,    42,    42,    39,     3,
     188,    38,    43,    40,    15,    16,    17,    18,    42,    46,
      21,    15,    39,    24,    42,    43,    43,    28,    29,    64,
      51,    52,    60,    40,    94,    36,    41,    38,    43,    40,
       3,   101,    18,    19,    45,    66,    40,     3,   108,    18,
      19,    45,    25,    26,    27,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    22,    90,
      37,     3,    93,    94,    28,    29,    41,     0,    43,   100,
     101,    38,    40,    40,    38,   106,    40,   108,    40,    46,
      47,    13,    46,    47,    37,    41,   117,    43,   158,    41,
      41,   161,    43,     3,     3,     3,    10,    41,    36,    40,
      40,   146,     3,   148,    43,    36,    41,     3,     4,     5,
       6,     7,     8,     9,    37,    11,    12,    13,    14,    15,
      16,    17,    18,   113,   155,    21,   119,   158,    24,   177,
     161,   144,    28,    29,   181,    -1,    -1,    -1,    -1,    -1,
      36,   172,    38,    -1,    40,    -1,    42,    -1,    -1,    45,
       3,     4,     5,     6,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    15,    16,    17,    18,    -1,    -1,    21,    -1,
      -1,    24,    -1,    -1,    -1,    28,    29,    -1,    -1,    -1,
      -1,     3,     4,     5,     6,    38,    -1,    40,    -1,    42,
      -1,    13,    45,    15,    16,    17,    18,    -1,    -1,    21,
      -1,    -1,    24,    -1,    -1,    -1,    28,    29,    -1,    -1,
      -1,    -1,     3,     4,     5,     6,    38,    -1,    40,    -1,
      -1,    -1,    -1,    45,    15,    16,    17,    18,    -1,    -1,
      21,    -1,    -1,    24,    -1,    -1,    -1,    28,    29,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,    -1,    40,
      -1,    19,    20,    -1,    45,    23,    24,    25,    26,    27,
      -1,    -1,    30,    31,    32,    33,    34,    35,    -1,    -1,
      -1,    -1,    -1,    19,    20,    -1,    44,    23,    24,    25,
      26,    27,    -1,    -1,    30,    31,    32,    33,    34,    35,
      -1,    -1,    -1,    19,    20,    -1,    42,    23,    24,    25,
      26,    27,    -1,    -1,    30,    31,    32,    33,    34,    35,
      -1,    -1,    -1,    19,    20,    -1,    42,    23,    24,    25,
      26,    27,    -1,    -1,    30,    31,    32,    33,    34,    35,
      -1,    -1,    -1,    19,    20,    -1,    42,    23,    24,    25,
      26,    27,    -1,    -1,    30,    31,    32,    33,    34,    35,
      -1,    -1,    19,    20,    -1,    41,    23,    24,    25,    26,
      27,    -1,    -1,    30,    31,    32,    33,    34,    35,    -1,
      -1,    19,    20,    -1,    41,    23,    24,    25,    26,    27,
      -1,    -1,    30,    31,    32,    33,    34,    35,    -1,    -1,
      19,    20,    -1,    41,    23,    24,    25,    26,    27,    -1,
      -1,    30,    31,    32,    33,    34,    35,    19,    20,    -1,
      39,    23,    24,    25,    26,    27,    -1,    -1,    30,    31,
      32,    33,    34,    35,    19,    20,    -1,    39,    23,    24,
      25,    26,    27,    -1,    -1,    30,    31,    32,    33,    34,
      35,    -1,    37,    19,    20,    -1,    -1,    23,    24,    25,
      26,    27,    -1,    -1,    30,    31,    32,    33,    34,    35,
      23,    24,    25,    26,    27,    -1,    -1,    30,    31,    32,
      33,    34,    35,    23,    24,    25,    26,    27,    -1,    -1,
      30,    31,    32,    33,    34,    35,    23,    24,    25,    26,
      27,    -1,    -1,    -1,    -1,    32,    33,    34,    35
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,    11,    12,
      13,    14,    15,    16,    17,    18,    21,    24,    28,    29,
      36,    38,    40,    42,    45,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    66,    69,    75,
      80,    81,    83,    85,    89,    91,    94,    95,    96,    42,
      42,    40,    40,     3,    74,    42,    56,     3,    56,    56,
      40,    59,    61,    59,    70,    71,    36,    56,    65,    67,
      68,    56,    80,     3,     0,    52,    19,    20,    23,    24,
      25,    26,    27,    30,    31,    32,    33,    34,    35,    42,
      22,    28,    29,    38,    40,    46,    47,    62,    63,    64,
      38,    40,    46,    40,    76,    52,    40,    90,    92,    56,
      65,    42,    80,    52,    37,    56,    39,    43,    39,    43,
      41,    41,    56,    56,    56,    56,    56,    56,    56,    56,
      56,    56,    56,    56,    56,    56,    56,    65,     3,     3,
      56,    65,     3,    77,    72,    10,    84,    56,    86,    88,
      65,    41,    42,    41,    50,    44,    56,    68,    40,    39,
      41,    40,    39,    41,     3,    82,    69,    79,    52,    41,
      52,    41,    93,    37,    56,    65,    65,    43,    78,    73,
      87,    92,    56,    37,    41,    41,    82,    41,    88,    42,
      92
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    49,    50,    50,    51,    51,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    53,    54,    55,    56,
      56,    56,    56,    56,    56,    56,    56,    56,    56,    56,
      56,    56,    56,    56,    57,    57,    57,    57,    57,    57,
      57,    57,    58,    58,    58,    58,    58,    59,    59,    59,
      59,    60,    60,    60,    60,    61,    61,    61,    62,    62,
      63,    64,    65,    65,    65,    66,    66,    67,    67,    68,
      70,    69,    71,    69,    72,    73,    74,    74,    75,    77,
      78,    76,    79,    80,    81,    81,    81,    81,    81,    81,
      82,    82,    82,    83,    84,    85,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    96
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     1,     2,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     2,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     1,     1,     3,     2,     2,     2,     2,     2,
       2,     1,     1,     1,     1,     3,     1,     1,     2,     2,
       1,     3,     4,     3,     4,     4,     2,     6,     1,     1,
       3,     5,     3,     1,     0,     3,     3,     3,     1,     5,
       0,     5,     0,     3,     0,     0,     1,     0,     2,     0,
       0,     5,     1,     5,     1,     1,     1,     1,     1,     1,
       3,     1,     0,     4,     1,     2,     4,     0,     0,     3,
       1,     3,     3,     0,     0,     7,     7,     3,     2
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
        case 2:
#line 117 "parser.y" /* yacc.c:1646  */
    {
			// $$ = $1;
			}
#line 1583 "parser.c" /* yacc.c:1646  */
    break;

  case 4:
#line 125 "parser.y" /* yacc.c:1646  */
    {
				(yyval.exp) = (yyvsp[0].exp);

					}
#line 1592 "parser.c" /* yacc.c:1646  */
    break;

  case 5:
#line 129 "parser.y" /* yacc.c:1646  */
    {
						// printf("stmts->stmt stmts\n");
						// $2 = $1;
						// if($$->stack){
							// $$->stack->breaklist = merge_list(curr_stack->breaklist, $1->stack->breaklist);
							// $$->stack->contlist = merge_list($1->stack->contlist, curr_stack->contlist);
							(yyval.exp) = (expr *)malloc(sizeof(expr));
							(yyval.exp)->stack = (e_stack *)malloc(sizeof(e_stack));
							//link with break-continue stack next element
							if (curr_stack->breaklist)
								(yyval.exp)->stack->breaklist = merge_list((yyval.exp)->stack->breaklist, curr_stack->breaklist);
							 if(curr_stack->contlist)
								(yyval.exp)->stack->contlist = merge_list(curr_stack->contlist, bc_head->bc_list->contlist);
						// }
						}
#line 1612 "parser.c" /* yacc.c:1646  */
    break;

  case 6:
#line 146 "parser.y" /* yacc.c:1646  */
    {}
#line 1618 "parser.c" /* yacc.c:1646  */
    break;

  case 7:
#line 147 "parser.y" /* yacc.c:1646  */
    {}
#line 1624 "parser.c" /* yacc.c:1646  */
    break;

  case 8:
#line 148 "parser.y" /* yacc.c:1646  */
    {}
#line 1630 "parser.c" /* yacc.c:1646  */
    break;

  case 9:
#line 150 "parser.y" /* yacc.c:1646  */
    {}
#line 1636 "parser.c" /* yacc.c:1646  */
    break;

  case 10:
#line 152 "parser.y" /* yacc.c:1646  */
    {
							if(!is_func){
								printf(KRED"Error at line %d: return used outside of function\n"KNRM, yylineno);
							}}
#line 1645 "parser.c" /* yacc.c:1646  */
    break;

  case 11:
#line 156 "parser.y" /* yacc.c:1646  */
    {

							//printf("is_loop = %d\tis_loop_in_func = %d\n", is_loop, is_loop_in_func);
							//if not in loop -> error
							if (loopcounter==0)
							{
								printf(KRED "Error at line %d: break used outside of loop\n" KNRM, yylineno);
							}
							(yyval.exp) = (yyvsp[0].exp);
							// printf("LABEL stmt: %d\n", $$->stack->breaklist->label);

								// $$->stack->breaklist = $1;
							}
#line 1663 "parser.c" /* yacc.c:1646  */
    break;

  case 12:
#line 169 "parser.y" /* yacc.c:1646  */
    {
							if (loopcounter==0)
								//if not in loop -> error

								{
									printf(KRED "Error at line %d: continue used outside of loop\n" KNRM, yylineno);
								}
								(yyval.exp) = (yyvsp[0].exp);
								}
#line 1677 "parser.c" /* yacc.c:1646  */
    break;

  case 13:
#line 178 "parser.y" /* yacc.c:1646  */
    {(yyval.exp) = (yyvsp[0].exp);}
#line 1683 "parser.c" /* yacc.c:1646  */
    break;

  case 14:
#line 179 "parser.y" /* yacc.c:1646  */
    {}
#line 1689 "parser.c" /* yacc.c:1646  */
    break;

  case 15:
#line 180 "parser.y" /* yacc.c:1646  */
    {}
#line 1695 "parser.c" /* yacc.c:1646  */
    break;

  case 16:
#line 183 "parser.y" /* yacc.c:1646  */
    {
							emit(jump, NULL, NULL, NULL, -1, yylineno);
							(yyval.exp) = (expr*)malloc(sizeof(expr));	
							(yyval.exp)->stack = (e_stack*)malloc(sizeof(e_stack));
							(yyval.exp)->stack->breaklist = (list*)malloc(sizeof(list));
							(yyval.exp)->stack->breaklist->label = nextquadlabel();
							curr_stack->breaklist = (yyval.exp)->stack->breaklist;
							printf("LABEL: %d\n", (yyval.exp)->stack->breaklist->label);

						}
#line 1710 "parser.c" /* yacc.c:1646  */
    break;

  case 17:
#line 195 "parser.y" /* yacc.c:1646  */
    {	
							emit(jump, NULL, NULL, NULL, -1, yylineno);
							(yyval.exp) = (expr*)malloc(sizeof(expr));	
							(yyval.exp)->stack = (e_stack*)malloc(sizeof(e_stack));
							(yyval.exp)->stack->contlist = (list*)malloc(sizeof(list));
							(yyval.exp)->stack->contlist->label = nextquadlabel();
							curr_stack->contlist = (yyval.exp)->stack->contlist;

							printf("LABEL: %d\n", (yyval.exp)->stack->contlist->label);
								}
#line 1725 "parser.c" /* yacc.c:1646  */
    break;

  case 18:
#line 206 "parser.y" /* yacc.c:1646  */
    {
								if((yyvsp[-2].exp)!=NULL){
									if((yyvsp[-2].exp)->type == tableitem_e){
										emit(tablesetelem, (yyvsp[-2].exp), (yyvsp[-2].exp)->index, (yyvsp[0].exp), nextquadlabel(), yylineno);
										(yyval.exp) = emit_iftableitem((yyvsp[-2].exp), nextquadlabel(), yylineno, scope);
										(yyval.exp)->type = assignexpr_e;
									}
									else{
										//lvalue = expr
										emit(assign, (yyvsp[0].exp), NULL, (yyvsp[-2].exp), nextquadlabel(), yylineno);
										(yyval.exp) = newexpr(assignexpr_e);
										(yyval.exp)->sym = newtemp(scope, yylineno);
										emit(assign, (yyvsp[-2].exp), NULL, (yyval.exp), nextquadlabel(), yylineno);
										resettemp();
									}

								}

								if((yyvsp[-2].exp)->type == USERFUNC || (yyvsp[-2].exp)->type == LIBFUNC){
									printf(KRED "Error: Invalid action on function in line %d: %s \'=\' expr\n" KNRM, yylineno, (yyvsp[-2].exp)->sym->value.funcVal->name);
								}
								}
#line 1752 "parser.c" /* yacc.c:1646  */
    break;

  case 19:
#line 229 "parser.y" /* yacc.c:1646  */
    {
									 (yyval.exp) = newexpr(arithexpr_e);
									 (yyval.exp)->sym = newtemp(scope, yylineno);
									 emit(add, (yyvsp[-2].exp), (yyvsp[0].exp), (yyval.exp), nextquadlabel(), yylineno);
									 resettemp();
									 }
#line 1763 "parser.c" /* yacc.c:1646  */
    break;

  case 20:
#line 235 "parser.y" /* yacc.c:1646  */
    {
									(yyval.exp) = newexpr(arithexpr_e);
									 (yyval.exp)->sym = newtemp(scope, yylineno);
									 emit(sub, (yyvsp[-2].exp), (yyvsp[0].exp), (yyval.exp), nextquadlabel(), yylineno);
									// resettemp();
									 }
#line 1774 "parser.c" /* yacc.c:1646  */
    break;

  case 21:
#line 241 "parser.y" /* yacc.c:1646  */
    {
									(yyval.exp) = newexpr(arithexpr_e);
									(yyval.exp)->sym = newtemp(scope, yylineno);
									emit(mul, (yyvsp[-2].exp), (yyvsp[0].exp), (yyval.exp), nextquadlabel(), yylineno);
									resettemp();
									}
#line 1785 "parser.c" /* yacc.c:1646  */
    break;

  case 22:
#line 247 "parser.y" /* yacc.c:1646  */
    {
									(yyval.exp) = newexpr(arithexpr_e);
									(yyval.exp)->sym = newtemp(scope, yylineno);
									emit(diva, (yyvsp[-2].exp), (yyvsp[0].exp), (yyval.exp), nextquadlabel(), yylineno);
									resettemp();
									}
#line 1796 "parser.c" /* yacc.c:1646  */
    break;

  case 23:
#line 254 "parser.y" /* yacc.c:1646  */
    {
									(yyval.exp) = newexpr(arithexpr_e);
									(yyval.exp)->sym = newtemp(scope, yylineno);
									emit(mod, (yyvsp[-2].exp), (yyvsp[0].exp), (yyval.exp), nextquadlabel(), yylineno);
									resettemp();
									}
#line 1807 "parser.c" /* yacc.c:1646  */
    break;

  case 24:
#line 261 "parser.y" /* yacc.c:1646  */
    {
									(yyval.exp) = newexpr(boolexpr_e);
									(yyval.exp)->sym = newtemp(scope, yylineno);
									emit(ifeq, (yyvsp[-2].exp), (yyvsp[0].exp), NULL, nextquadlabel()+3, yylineno);
									emit(assign, newexpr_constbool('F'),NULL, (yyval.exp), nextquadlabel(), yylineno);
									emit(jump, NULL, NULL, NULL, nextquadlabel()+2, yylineno);
									emit(assign, newexpr_constbool('T'), NULL, (yyval.exp), nextquadlabel(), yylineno);
									resettemp();
									}
#line 1821 "parser.c" /* yacc.c:1646  */
    break;

  case 25:
#line 271 "parser.y" /* yacc.c:1646  */
    {
									(yyval.exp) = newexpr(boolexpr_e);
									(yyval.exp)->sym = newtemp(scope, yylineno);
									emit(if_noteq, (yyvsp[-2].exp), (yyvsp[0].exp), NULL, nextquadlabel()+3, yylineno);
									emit(assign, newexpr_constbool('F'),NULL, (yyval.exp), nextquadlabel(), yylineno);
									emit(jump, NULL, NULL, NULL, nextquadlabel()+2, yylineno);
									emit(assign, newexpr_constbool('T'), NULL, (yyval.exp), nextquadlabel(), yylineno);
									resettemp();
		}
#line 1835 "parser.c" /* yacc.c:1646  */
    break;

  case 26:
#line 280 "parser.y" /* yacc.c:1646  */
    {
									(yyval.exp) = newexpr(boolexpr_e);
									(yyval.exp)->sym = newtemp(scope, yylineno);
									emit(if_greater, (yyvsp[-2].exp), (yyvsp[0].exp), NULL, nextquadlabel()+3, yylineno);
									emit(assign, newexpr_constbool('F'),NULL, (yyval.exp), nextquadlabel(), yylineno);
									emit(jump, NULL, NULL, NULL, nextquadlabel()+2, yylineno);
									emit(assign, newexpr_constbool('T'), NULL, (yyval.exp), nextquadlabel(), yylineno);
									resettemp();
		}
#line 1849 "parser.c" /* yacc.c:1646  */
    break;

  case 27:
#line 289 "parser.y" /* yacc.c:1646  */
    {
									(yyval.exp) = newexpr(boolexpr_e);
									(yyval.exp)->sym = newtemp(scope, yylineno);
									emit(if_greatereq, (yyvsp[-2].exp), (yyvsp[0].exp), NULL, nextquadlabel()+3, yylineno);
									emit(assign, newexpr_constbool('F'),NULL, (yyval.exp), nextquadlabel(), yylineno);
									emit(jump, NULL, NULL, NULL, nextquadlabel()+2, yylineno);
									emit(assign, newexpr_constbool('T'), NULL, (yyval.exp), nextquadlabel(), yylineno);
									resettemp();
		}
#line 1863 "parser.c" /* yacc.c:1646  */
    break;

  case 28:
#line 298 "parser.y" /* yacc.c:1646  */
    {
									(yyval.exp) = newexpr(boolexpr_e);
									(yyval.exp)->sym = newtemp(scope, yylineno);
									emit(if_less, (yyvsp[-2].exp), (yyvsp[0].exp), NULL, nextquadlabel()+3, yylineno);
									emit(assign, newexpr_constbool('F'),NULL, (yyval.exp), nextquadlabel(), yylineno);
									emit(jump, NULL, NULL, NULL, nextquadlabel()+2, yylineno);
									emit(assign, newexpr_constbool('T'), NULL, (yyval.exp), nextquadlabel(), yylineno);
									resettemp();
									}
#line 1877 "parser.c" /* yacc.c:1646  */
    break;

  case 29:
#line 307 "parser.y" /* yacc.c:1646  */
    {
									(yyval.exp) = newexpr(boolexpr_e);
									(yyval.exp)->sym = newtemp(scope, yylineno);
									emit(if_lesseq, (yyvsp[-2].exp), (yyvsp[0].exp), NULL, nextquadlabel()+3, yylineno);
									emit(assign, newexpr_constbool('F'),NULL, (yyval.exp), nextquadlabel(), yylineno);
									emit(jump, NULL, NULL, NULL, nextquadlabel()+2, yylineno);
									emit(assign, NULL, newexpr_constbool('T'), (yyval.exp), nextquadlabel(), yylineno);
									resettemp();
		}
#line 1891 "parser.c" /* yacc.c:1646  */
    break;

  case 30:
#line 316 "parser.y" /* yacc.c:1646  */
    {
									(yyval.exp) = newexpr(boolexpr_e);
									(yyval.exp)->sym = newtemp(scope, yylineno);
									emit(and, (yyvsp[-2].exp), (yyvsp[0].exp), (yyval.exp), nextquadlabel(), yylineno);
									resettemp();
		}
#line 1902 "parser.c" /* yacc.c:1646  */
    break;

  case 31:
#line 322 "parser.y" /* yacc.c:1646  */
    {
									(yyval.exp) = newexpr(boolexpr_e);
									(yyval.exp)->sym = newtemp(scope, yylineno);
									emit(or, (yyvsp[-2].exp), (yyvsp[0].exp), (yyval.exp), nextquadlabel(), yylineno);
									resettemp();
		}
#line 1913 "parser.c" /* yacc.c:1646  */
    break;

  case 32:
#line 328 "parser.y" /* yacc.c:1646  */
    {(yyval.exp) = (yyvsp[0].exp);}
#line 1919 "parser.c" /* yacc.c:1646  */
    break;

  case 33:
#line 329 "parser.y" /* yacc.c:1646  */
    {(yyval.exp) = (yyvsp[0].exp);}
#line 1925 "parser.c" /* yacc.c:1646  */
    break;

  case 34:
#line 333 "parser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[-1].exp); }
#line 1931 "parser.c" /* yacc.c:1646  */
    break;

  case 35:
#line 335 "parser.y" /* yacc.c:1646  */
    {
			if (checkuminus((yyvsp[0].exp)) == 0)
			{
				//printf("UMINUS SUCCESS\n");
				(yyval.exp) = newexpr(arithexpr_e);
				(yyval.exp)->sym = newtemp(scope, yylineno);
				// emit(uminus, $2, NULL, $$, nextquadlabel(), yylineno);
				emit(mul, (yyvsp[0].exp), newexpr_constnum(-1), (yyval.exp), nextquadlabel(), yylineno);
				resettemp();
			}
			else
			{
				printf(KRED "Error: Invalid action on expression in line %d: \n" KNRM, yylineno);
			}
		}
#line 1951 "parser.c" /* yacc.c:1646  */
    break;

  case 36:
#line 351 "parser.y" /* yacc.c:1646  */
    {
			(yyval.exp) = newexpr(boolexpr_e);
			(yyval.exp)->sym = newtemp(scope, yylineno);
			emit(not, (yyvsp[0].exp), NULL, (yyval.exp), nextquadlabel(), yylineno);
			resettemp();
		}
#line 1962 "parser.c" /* yacc.c:1646  */
    break;

  case 37:
#line 358 "parser.y" /* yacc.c:1646  */
    {
			if ((yyvsp[0].exp)->type == tableitem_e)
			{ 
				(yyval.exp) = emit_iftableitem((yyvsp[0].exp), nextquadlabel(), yylineno, scope);
				emit(add, (yyval.exp), newexpr_constnum(1), (yyval.exp), nextquadlabel(), yylineno);
				emit(tablesetelem, (yyvsp[0].exp), (yyvsp[0].exp)->index, (yyval.exp), nextquadlabel(), yylineno);
			}
			else
			{
				emit(add, (yyvsp[0].exp), newexpr_constnum(1), (yyvsp[0].exp), nextquadlabel(), yylineno);
				(yyval.exp) = newexpr(arithexpr_e);
				(yyval.exp)->sym = newtemp(scope, yylineno);
				emit(assign, (yyvsp[0].exp), NULL, (yyval.exp), nextquadlabel(), yylineno);
				resettemp();

			}
		{
			if ((yyvsp[0].exp)->type == USERFUNC || (yyvsp[0].exp)->type == LIBFUNC)
			{
				printf(KRED "Error: Invalid action on function in line %d: ++%s\n" KNRM, yylineno, (yyvsp[0].exp)->sym->value.funcVal->name);
			}
		}
		}
#line 1990 "parser.c" /* yacc.c:1646  */
    break;

  case 38:
#line 382 "parser.y" /* yacc.c:1646  */
    {
			(yyval.exp) = newexpr(var_e);
			(yyval.exp)->sym = newtemp(scope, yylineno);
			if ((yyvsp[-1].exp)->type == tableitem_e)
			{
				value = emit_iftableitem((yyvsp[-1].exp), nextquadlabel(), yylineno, scope);
				emit(assign, value, NULL, (yyval.exp), nextquadlabel(), yylineno);
				emit(add, value, newexpr_constnum(1), value, nextquadlabel(), yylineno);
				emit(tablesetelem, (yyvsp[-1].exp), (yyvsp[-1].exp)->index, value, nextquadlabel(), yylineno);
			}
			else
			{
				emit(assign, (yyvsp[-1].exp), NULL, (yyval.exp), nextquadlabel(), yylineno);
				emit(add, (yyvsp[-1].exp), newexpr_constnum(1), (yyvsp[-1].exp), nextquadlabel(), yylineno);
			}
			if ((yyvsp[-1].exp)->type == USERFUNC || (yyvsp[-1].exp)->type == LIBFUNC)
			{
				printf(KRED "Error: Invalid action on function in line %d: %s++\n" KNRM, yylineno, (yyvsp[-1].exp)->sym->value.funcVal->name);
			}
			resettemp();
		}
#line 2016 "parser.c" /* yacc.c:1646  */
    break;

  case 39:
#line 404 "parser.y" /* yacc.c:1646  */
    {
			if ((yyvsp[0].exp)->type == tableitem_e)
			{
				(yyval.exp) = emit_iftableitem((yyvsp[0].exp), nextquadlabel(), yylineno, scope);
				emit(sub, (yyval.exp), newexpr_constnum(1), (yyval.exp), nextquadlabel(), yylineno);
				emit(tablesetelem, (yyvsp[0].exp), (yyvsp[0].exp)->index, (yyval.exp), nextquadlabel(), yylineno);
			}
			else
			{
				emit(sub, (yyvsp[0].exp), newexpr_constnum(1), (yyvsp[0].exp), nextquadlabel(), yylineno);
				(yyval.exp) = newexpr(arithexpr_e);
				(yyval.exp)->sym = newtemp(scope, yylineno);
				emit(assign, (yyvsp[0].exp), NULL, (yyval.exp), nextquadlabel(), yylineno);
				resettemp();
			}
			if ((yyvsp[0].exp)->type == USERFUNC || (yyvsp[0].exp)->type == LIBFUNC)
			{
				printf(KRED "Error: Invalid action on function in line %d: --%s\n" KNRM, yylineno, (yyvsp[0].exp)->sym->value.funcVal->name);
			}
		}
#line 2041 "parser.c" /* yacc.c:1646  */
    break;

  case 40:
#line 425 "parser.y" /* yacc.c:1646  */
    {
			(yyval.exp) = newexpr(var_e);
			(yyval.exp)->sym = newtemp(scope, yylineno);
			if ((yyvsp[-1].exp)->type == tableitem_e)
			{
				value = emit_iftableitem((yyvsp[-1].exp), nextquadlabel(), yylineno, scope);
				emit(assign, value, NULL, (yyval.exp), nextquadlabel(), yylineno);
				emit(sub, value, newexpr_constnum(1), value, nextquadlabel(), yylineno);
				emit(tablesetelem, (yyvsp[-1].exp), (yyvsp[-1].exp)->index, value, nextquadlabel(), yylineno);
				
			}
			else
			{
				emit(assign, (yyvsp[-1].exp), NULL, (yyval.exp), nextquadlabel(), yylineno);
				emit(sub, (yyvsp[-1].exp), newexpr_constnum(1), (yyvsp[-1].exp), nextquadlabel(), yylineno);
			}
			if ((yyvsp[-1].exp)->type == USERFUNC || (yyvsp[-1].exp)->type == LIBFUNC)
			{
				printf(KRED "Error: Invalid action on function in line %d: %s--\n" KNRM, yylineno, (yyvsp[-1].exp)->sym->value.funcVal->name);
			}
			resettemp();
		}
#line 2068 "parser.c" /* yacc.c:1646  */
    break;

  case 41:
#line 447 "parser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2074 "parser.c" /* yacc.c:1646  */
    break;

  case 42:
#line 449 "parser.y" /* yacc.c:1646  */
    { (yyval.exp) = emit_iftableitem((yyvsp[0].exp), nextquadlabel(), yylineno, scope); }
#line 2080 "parser.c" /* yacc.c:1646  */
    break;

  case 43:
#line 450 "parser.y" /* yacc.c:1646  */
    {(yyval.exp) = (yyvsp[0].exp);}
#line 2086 "parser.c" /* yacc.c:1646  */
    break;

  case 44:
#line 451 "parser.y" /* yacc.c:1646  */
    {(yyval.exp) = (yyvsp[0].exp);}
#line 2092 "parser.c" /* yacc.c:1646  */
    break;

  case 45:
#line 452 "parser.y" /* yacc.c:1646  */
    {
								(yyval.exp) = newexpr(programfunc_e);
								(yyval.exp)->sym = (yyvsp[-1].exprNode);
		}
#line 2101 "parser.c" /* yacc.c:1646  */
    break;

  case 46:
#line 456 "parser.y" /* yacc.c:1646  */
    {(yyval.exp) = (yyvsp[0].exp);}
#line 2107 "parser.c" /* yacc.c:1646  */
    break;

  case 47:
#line 459 "parser.y" /* yacc.c:1646  */
    {
								tmp_scope = scope;
								//lookup id from current scope to global
								while(tmp_scope>=GLOBAl_SCOPE){
									entry=lookup(tmp_scope, (char*)(yyvsp[0].stringVal));
									if(entry!=NULL && entry->isActive){
										printf(KCYN "LOOKUP: symbol \'%s\', at line %d found in scope %d\n" KNRM, (yyvsp[0].stringVal), yylineno, tmp_scope);
										break;
									}
									tmp_scope--;
								}
								tmp_scope++;

								if(entry==NULL){
								//if no entry found
									printf(KCYN "LOOKUP: symbol \'%s\', at line %d not found in symbol table\n" KNRM, (yyvsp[0].stringVal), yylineno);

									
									if(is_func){	//if we are inside a function
										// printf(KRED"TERASTIO PEOS\n"KNRM);
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
									entry->space = currscopespace();
									entry->offset = currscopeoffset();
									inccurrentscopeoffset();
								}
								else{
									// printf(KCYN "LOOKUP: symbol \'%s\', at line %d found in scope %d\n" KNRM, $1, yylineno, tmp_scope-1);
									// printf("tempscore = %d\n", tmp_scope-1);
									// printf("function scope = %d\n", func_scope);
									// printf(KRED "TERASTIO PEOS\n" KNRM);

									//if entry found out of current function scope and not in global->error
									if (is_func && (tmp_scope-1 < func_scope) && (tmp_scope-1) != GLOBAl_SCOPE)
									{
										{
											printf(KRED "Error: Cannot access %s in scope %d\n" KNRM, (yyvsp[0].stringVal), tmp_scope-1);
										}
									}
								}
								//lvalue = symbol_entry;
								
								(yyval.exp) = lvalue_expr(entry);

								

								}
#line 2184 "parser.c" /* yacc.c:1646  */
    break;

  case 48:
#line 532 "parser.y" /* yacc.c:1646  */
    {
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
									entry->space = currscopespace();
									entry->offset = currscopeoffset();
									inccurrentscopeoffset();
								}
								else{
									printf(KCYN "LOOKUP: local symbol \'%s\', at line %d found in scope %d\n" KNRM, (yyvsp[0].stringVal), yylineno, scope);
								}

								//lvalue = entry
								(yyval.exp) = lvalue_expr(entry);
							}
#line 2217 "parser.c" /* yacc.c:1646  */
    break;

  case 49:
#line 560 "parser.y" /* yacc.c:1646  */
    {
								//lookup only
								entry = lookup(GLOBAl_SCOPE, (yyvsp[0].stringVal));
								if(entry){
									(yyval.exp) = lvalue_expr(entry);
									printf(KCYN "LOOKUP: Global symbol \'%s\', at line %d found in global scope\n" KNRM, (yyvsp[0].stringVal), yylineno);
								}

								else{
									(yyval.exp)->sym = (st_entry*)(yyvsp[0].stringVal);
									//TODO: check lvalue ($$ = lvalue_expr(..))
								printf(KRED "LOOKUP ERROR: Global symbol \'%s\', at line %d not found in global scope\n" KNRM, (yyvsp[0].stringVal), yylineno);
								}

								//lvalue = entry
								
								
								}
#line 2240 "parser.c" /* yacc.c:1646  */
    break;

  case 50:
#line 579 "parser.y" /* yacc.c:1646  */
    {
									//lvalue = member
									(yyval.exp) = (yyvsp[0].exp);
								}
#line 2249 "parser.c" /* yacc.c:1646  */
    break;

  case 51:
#line 585 "parser.y" /* yacc.c:1646  */
    {
									entry = lookup(scope, (yyvsp[0].stringVal));
									(yyval.exp) = member_item((yyvsp[-2].exp), (char*)(yyvsp[0].stringVal), nextquadlabel(), yylineno, scope);
										}
#line 2258 "parser.c" /* yacc.c:1646  */
    break;

  case 52:
#line 589 "parser.y" /* yacc.c:1646  */
    {
									(yyvsp[-3].exp) = emit_iftableitem((yyvsp[-3].exp), nextquadlabel(), yylineno, scope);
									(yyval.exp) = newexpr(tableitem_e);
									(yyval.exp)->sym = (yyvsp[-3].exp)->sym;
									(yyval.exp)->index = (yyvsp[-1].exp); //the index is the expression
											}
#line 2269 "parser.c" /* yacc.c:1646  */
    break;

  case 53:
#line 595 "parser.y" /* yacc.c:1646  */
    {

										(yyval.exp) = (yyvsp[-2].exp);
										}
#line 2278 "parser.c" /* yacc.c:1646  */
    break;

  case 54:
#line 599 "parser.y" /* yacc.c:1646  */
    {
												(yyval.exp) = (yyvsp[-1].exp);}
#line 2285 "parser.c" /* yacc.c:1646  */
    break;

  case 55:
#line 603 "parser.y" /* yacc.c:1646  */
    {

										(yyval.exp) = make_call((yyvsp[-3].exp), (yyvsp[-1].exp), nextquadlabel(), yylineno, scope);

}
#line 2295 "parser.c" /* yacc.c:1646  */
    break;

  case 56:
#line 609 "parser.y" /* yacc.c:1646  */
    {
												if((yyvsp[0].exp)->method == 1){
													expr* self = (yyvsp[-1].exp);
													(yyvsp[-1].exp) = emit_iftableitem(member_item(self, (yyvsp[0].exp)->strConst, nextquadlabel(), yylineno, scope), nextquadlabel(), yylineno, scope);
													(yyvsp[0].exp) = merge((yyvsp[0].exp), self);
													
											}
												printf("lala0\n");
												(yyval.exp) = make_call((yyvsp[-1].exp), (yyvsp[0].exp)->next, nextquadlabel(), yylineno, scope);
											}
#line 2310 "parser.c" /* yacc.c:1646  */
    break;

  case 57:
#line 620 "parser.y" /* yacc.c:1646  */
    {
												expr* func = newexpr(programfunc_e);
												func->sym = (yyvsp[-4].exprNode);
												(yyval.exp) = make_call(func, (yyvsp[-1].exp), nextquadlabel(), yylineno, scope);
											}
#line 2320 "parser.c" /* yacc.c:1646  */
    break;

  case 58:
#line 627 "parser.y" /* yacc.c:1646  */
    {
						(yyval.exp) = (yyvsp[0].exp);
						}
#line 2328 "parser.c" /* yacc.c:1646  */
    break;

  case 59:
#line 630 "parser.y" /* yacc.c:1646  */
    {
						(yyval.exp) = (yyvsp[0].exp);
						}
#line 2336 "parser.c" /* yacc.c:1646  */
    break;

  case 60:
#line 635 "parser.y" /* yacc.c:1646  */
    {

											printf("elist type: %d\n", (yyvsp[-1].exp)->type);
											(yyval.exp) = newexpr(programfunc_e);

											// $$->next = (expr*)malloc(sizeof(expr));
											(yyval.exp)->next = (yyvsp[-1].exp);
											(yyval.exp)->method = 0;
										}
#line 2350 "parser.c" /* yacc.c:1646  */
    break;

  case 61:
#line 647 "parser.y" /* yacc.c:1646  */
    {
					(yyval.exp)->next = (yyvsp[-1].exp);
					(yyval.exp)->method = 1;
					(yyval.exp)->strConst = strdup((yyvsp[-3].stringVal));
				}
#line 2360 "parser.c" /* yacc.c:1646  */
    break;

  case 62:
#line 654 "parser.y" /* yacc.c:1646  */
    {(yyval.exp) = insert_list_front((yyvsp[-2].exp), (yyvsp[0].exp));}
#line 2366 "parser.c" /* yacc.c:1646  */
    break;

  case 63:
#line 657 "parser.y" /* yacc.c:1646  */
    {
					(yyval.exp) = (yyvsp[0].exp);  }
#line 2373 "parser.c" /* yacc.c:1646  */
    break;

  case 64:
#line 659 "parser.y" /* yacc.c:1646  */
    {
				printf("lala\n");
				(yyval.exp) = newexpr(nil_e);
			}
#line 2382 "parser.c" /* yacc.c:1646  */
    break;

  case 65:
#line 667 "parser.y" /* yacc.c:1646  */
    {
											tempcounter++;
											expr* t = newexpr(newtable_e);
											t->sym = newtemp(scope, yylineno);
											emit(tablecreate, NULL, NULL, t, nextquadlabel(), yylineno);
											expr* list = (yyvsp[-1].exp);
											int i = 0;
											while(list){
												if(list->type!=nil_e){

												emit(tablesetelem, t, newexpr_constnum(i++), newexpr_constnum(list->numConst), nextquadlabel(), yylineno);
												if(!list->next) break;
												}
												list = list->next;
											}
											(yyval.exp) = t;
											resettemp();
										}
#line 2405 "parser.c" /* yacc.c:1646  */
    break;

  case 66:
#line 686 "parser.y" /* yacc.c:1646  */
    {
											tempcounter++;
											expr* t = newexpr(newtable_e);
											t->sym = newtemp(scope, yylineno);
											emit(tablecreate, NULL, NULL, t, nextquadlabel(), yylineno);
											expr* key = (yyvsp[-1].exp);
											expr* val = key->index;
											while(key){
												emit(tablesetelem, t, key, val, nextquadlabel(), yylineno);
												if(!key->next) break;
												key = key->next;
												val = key->index;
											}
											(yyval.exp) = t;
											resettemp();
										}
#line 2426 "parser.c" /* yacc.c:1646  */
    break;

  case 67:
#line 705 "parser.y" /* yacc.c:1646  */
    {(yyval.exp) = insert_list_front((yyvsp[-2].exp), (yyvsp[0].exp));}
#line 2432 "parser.c" /* yacc.c:1646  */
    break;

  case 68:
#line 706 "parser.y" /* yacc.c:1646  */
    {(yyval.exp) = (yyvsp[0].exp);}
#line 2438 "parser.c" /* yacc.c:1646  */
    break;

  case 69:
#line 709 "parser.y" /* yacc.c:1646  */
    {(yyval.exp) = (yyvsp[-3].exp); (yyval.exp)->index =(yyvsp[-1].exp);}
#line 2444 "parser.c" /* yacc.c:1646  */
    break;

  case 70:
#line 713 "parser.y" /* yacc.c:1646  */
    {if((!is_func)){
								//if we are inside a function scope is already incr
								// by funcdef rule so we dont increase twice
								scope++;
								}
								if((is_func)&&is_loop_in_func){
									scope++;
								}
							}
#line 2458 "parser.c" /* yacc.c:1646  */
    break;

  case 71:
#line 722 "parser.y" /* yacc.c:1646  */
    {(yyval.exp) = (yyvsp[-3].exp);
		 						hide(scope);
		 						if(func_scope){func_scope--;}
		 						if(scope>0)
		 						scope--;
											}
#line 2469 "parser.c" /* yacc.c:1646  */
    break;

  case 72:
#line 728 "parser.y" /* yacc.c:1646  */
    {if((!is_func)){
								//if we are inside a function scope is already incr
								// by funcdef rule so we dont increase twice
								scope++;
								}
								if((is_func)&&is_loop_in_func){
									scope++;
								}
							}
#line 2483 "parser.c" /* yacc.c:1646  */
    break;

  case 73:
#line 737 "parser.y" /* yacc.c:1646  */
    {
		 							if(scope>0)
									scope--; //recheck
									}
#line 2492 "parser.c" /* yacc.c:1646  */
    break;

  case 74:
#line 743 "parser.y" /* yacc.c:1646  */
    {
					push_loop_stack(&loop_head, loopcounter);
					loopcounter=0;
				}
#line 2501 "parser.c" /* yacc.c:1646  */
    break;

  case 75:
#line 748 "parser.y" /* yacc.c:1646  */
    {
					loopcounter = pop_loop(loop_head);
				}
#line 2509 "parser.c" /* yacc.c:1646  */
    break;

  case 76:
#line 753 "parser.y" /* yacc.c:1646  */
    {
								(yyval.stringVal) = strdup((yyvsp[0].stringVal));
								}
#line 2517 "parser.c" /* yacc.c:1646  */
    break;

  case 77:
#line 756 "parser.y" /* yacc.c:1646  */
    {
								(yyval.stringVal) = newUnnamedFunc();
			 					}
#line 2525 "parser.c" /* yacc.c:1646  */
    break;

  case 78:
#line 761 "parser.y" /* yacc.c:1646  */
    {
									// printf("funcprefix\n");
									tmp_scope = scope;
									while(tmp_scope>=GLOBAl_SCOPE){
										entry=lookup(scope, (char*)(yyvsp[0].stringVal));
										printf("FUNCTION FOUND\n");
										tmp_scope--;
									}
									if(entry==NULL){
										printf(KCYN "LOOKUP: function symbol \'%s\', at line %d not found in symbol table\n" KNRM, (yyvsp[0].stringVal), yylineno);
										func_scope = scope+1;
										func_symbol = create_symbol_func((yyvsp[0].stringVal), args, scope, yylineno);
										entry = create_entry(func_symbol, USERFUNC);
										entry->space = currscopespace();
										entry->offset = currscopeoffset();
										inccurrentscopeoffset();
									}
									else{
										// if(entry->s_type == libfunc_s){
											printf(KRED"Error at line %d: %s already defined\n"KNRM,yylineno, (yyvsp[0].stringVal));
										// }
										// else{
										// 	if(entry->s_type == var_s){
										// 		entry->s_type = programfunc_s;
										// 	}
										// }
									}
									(yyval.exprNode) = entry;
									//$$->value.funcVal->name = strdup($2);
									(yyval.exprNode)->value.funcVal->iaddress = nextquadlabel();
									emit(funcstart, NULL, NULL, lvalue_expr((yyval.exprNode)), nextquadlabel(), yylineno);
									push_func(&func_head, functionLocalOffset);
									enterscopespace();	//entering function args scope space
									resetformalargsoffet(); //start formals from zero 
								}
#line 2565 "parser.c" /* yacc.c:1646  */
    break;

  case 79:
#line 797 "parser.y" /* yacc.c:1646  */
    {
						// printf("funcargs\n");

						scope++; is_func++; is_loop_in_func = 0;
						}
#line 2575 "parser.c" /* yacc.c:1646  */
    break;

  case 80:
#line 801 "parser.y" /* yacc.c:1646  */
    {
						if (args == NULL)
				 			free_arg_list(args);
							}
#line 2584 "parser.c" /* yacc.c:1646  */
    break;

  case 81:
#line 805 "parser.y" /* yacc.c:1646  */
    {
											enterscopespace();	//entering function local offset
											resetfunclocaloffset();	//need to start locals from zero
											}
#line 2593 "parser.c" /* yacc.c:1646  */
    break;

  case 82:
#line 811 "parser.y" /* yacc.c:1646  */
    {
				// printf("funcbody\n");
				is_func--;
				exitscopespace();
				}
#line 2603 "parser.c" /* yacc.c:1646  */
    break;

  case 83:
#line 820 "parser.y" /* yacc.c:1646  */
    {
									// printf("funcdef\n");
									exitscopespace(); //exiting function definition space
									(yyvsp[-4].exprNode)->value.funcVal->totallocals = functionLocalOffset;
									functionLocalOffset = pop_func(func_head);
									// functionLocalOffset = func_head->offset;

									emit(funcend, NULL, NULL, lvalue_expr((yyvsp[-4].exprNode)), nextquadlabel(), yylineno);
								}
#line 2617 "parser.c" /* yacc.c:1646  */
    break;

  case 84:
#line 871 "parser.y" /* yacc.c:1646  */
    { 
					(yyval.exp) = newexpr(constnum_e);
					(yyval.exp)->numConst = (yyvsp[0].intVal);
					// printf("integer: %f\n", $$->numConst);
					}
#line 2627 "parser.c" /* yacc.c:1646  */
    break;

  case 85:
#line 877 "parser.y" /* yacc.c:1646  */
    {
				 	(yyval.exp) = newexpr(conststring_e);
					(yyval.exp)->strConst = strdup((yyvsp[0].stringVal));
					// printf("String: %s\n", $$->strConst); 
					 }
#line 2637 "parser.c" /* yacc.c:1646  */
    break;

  case 86:
#line 882 "parser.y" /* yacc.c:1646  */
    {
					 (yyval.exp) = newexpr(constnum_e);
					 (yyval.exp)->numConst = (yyvsp[0].realVal);
					//  printf("float: %f\n", $$->numConst);
				 }
#line 2647 "parser.c" /* yacc.c:1646  */
    break;

  case 87:
#line 888 "parser.y" /* yacc.c:1646  */
    {
					 	(yyval.exp) = newexpr(nil_e);

						 printf("NIL\n"); }
#line 2656 "parser.c" /* yacc.c:1646  */
    break;

  case 88:
#line 892 "parser.y" /* yacc.c:1646  */
    { 
				 		(yyval.exp) = newexpr(constbool_e);
						(yyval.exp)->boolConst = 'T';
						// printf("%c\n", $$->boolConst);
				 }
#line 2666 "parser.c" /* yacc.c:1646  */
    break;

  case 89:
#line 898 "parser.y" /* yacc.c:1646  */
    {
					 (yyval.exp) = newexpr(constbool_e);
					 (yyval.exp)->boolConst = 'F';
					//  printf("%c\n", $$->boolConst);
				 }
#line 2676 "parser.c" /* yacc.c:1646  */
    break;

  case 90:
#line 907 "parser.y" /* yacc.c:1646  */
    {
					 //link the rest of the arguments to argument list
					 
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
						 entry->space = currscopespace();
						 entry->offset = currscopeoffset();
						 inccurrentscopeoffset();
					 }
					 else if (collision_flag)
					 {
					 }

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
#line 2720 "parser.c" /* yacc.c:1646  */
    break;

  case 91:
#line 947 "parser.y" /* yacc.c:1646  */
    {
					 
					 
					 
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
						 entry->space = currscopespace();
						 entry->offset = currscopeoffset();
						 inccurrentscopeoffset();
					 }
					 else
					 {
						 //printf(KRED "Error: formal redeclaration\n" KNRM);
					 }
				 }
#line 2748 "parser.c" /* yacc.c:1646  */
    break;

  case 93:
#line 975 "parser.y" /* yacc.c:1646  */
    {
										emit(ifeq, NULL, (yyvsp[-1].exp), newexpr_constbool('T'), nextquadlabel()+2, yylineno);
										(yyval.intVal) = nextquadlabel();
										emit(jump, NULL, NULL, NULL, -1, yylineno);
									}
#line 2758 "parser.c" /* yacc.c:1646  */
    break;

  case 94:
#line 984 "parser.y" /* yacc.c:1646  */
    {
					(yyval.intVal) = nextquadlabel();
					emit(jump, NULL, NULL, NULL, -1, yylineno);
				}
#line 2767 "parser.c" /* yacc.c:1646  */
    break;

  case 95:
#line 991 "parser.y" /* yacc.c:1646  */
    {
										printf("lala\n");
										patchlabel((yyvsp[-1].intVal), nextquadlabel()); //patch to $1 sto nextquadlabel???
									}
#line 2776 "parser.c" /* yacc.c:1646  */
    break;

  case 96:
#line 996 "parser.y" /* yacc.c:1646  */
    {
										patchlabel((yyvsp[-3].intVal), (yyvsp[-1].intVal)+1);
										patchlabel((yyvsp[-1].intVal), nextquadlabel());
									}
#line 2785 "parser.c" /* yacc.c:1646  */
    break;

  case 97:
#line 1021 "parser.y" /* yacc.c:1646  */
    {

			bc_head = push_bc_stack(&bc_head, curr_stack);
			++loopcounter;
			// curr_stack->breaklist = NULL;
			// curr_stack->contlist = NULL;
			}
#line 2797 "parser.c" /* yacc.c:1646  */
    break;

  case 98:
#line 1029 "parser.y" /* yacc.c:1646  */
    {

			--loopcounter;

			}
#line 2807 "parser.c" /* yacc.c:1646  */
    break;

  case 99:
#line 1035 "parser.y" /* yacc.c:1646  */
    {(yyval.exp) = (yyvsp[-1].exp);}
#line 2813 "parser.c" /* yacc.c:1646  */
    break;

  case 100:
#line 1037 "parser.y" /* yacc.c:1646  */
    {(yyval.intVal) = nextquadlabel();}
#line 2819 "parser.c" /* yacc.c:1646  */
    break;

  case 101:
#line 1039 "parser.y" /* yacc.c:1646  */
    {
												emit(ifeq, NULL, (yyvsp[-1].exp), newexpr_constbool('T'), nextquadlabel()+2, yylineno);
												(yyval.intVal) = nextquadlabel();
												emit(jump, NULL, NULL, NULL, -1, yylineno);
											}
#line 2829 "parser.c" /* yacc.c:1646  */
    break;

  case 102:
#line 1045 "parser.y" /* yacc.c:1646  */
    {
												
												emit(jump, NULL, NULL, NULL, (yyvsp[-2].intVal), yylineno);
												patchlabel((yyvsp[-1].intVal), nextquadlabel());
												

													
												if(curr_stack->breaklist!=NULL){
													printf("breaklist->label = %d\n", curr_stack->breaklist->label);
														patchlabel(curr_stack->breaklist->label-1, nextquadlabel());
												}
												if(curr_stack->contlist!=NULL){
													patchlabel(curr_stack->contlist->label-1, (yyvsp[-2].intVal));
												}
												curr_stack = pop_bc(bc_head);
											}
#line 2850 "parser.c" /* yacc.c:1646  */
    break;

  case 103:
#line 1062 "parser.y" /* yacc.c:1646  */
    {(yyval.intVal) = nextquadlabel();
	emit(jump, NULL, NULL, NULL, -1, yylineno);}
#line 2857 "parser.c" /* yacc.c:1646  */
    break;

  case 104:
#line 1065 "parser.y" /* yacc.c:1646  */
    {(yyval.intVal)= nextquadlabel();}
#line 2863 "parser.c" /* yacc.c:1646  */
    break;

  case 105:
#line 1068 "parser.y" /* yacc.c:1646  */
    {

						(yyval.forprfx) = (forprefix*)malloc(sizeof(forprefix));
						(yyval.forprfx)->test = (yyvsp[-2].intVal);
						(yyval.forprfx)->enter = nextquadlabel();
						emit(ifeq, NULL, (yyvsp[-1].exp), newexpr_constbool('T'), -1, yylineno);

						
						
}
#line 2878 "parser.c" /* yacc.c:1646  */
    break;

  case 106:
#line 1080 "parser.y" /* yacc.c:1646  */
    {
						patchlabel((yyvsp[-6].forprfx)->enter, (yyvsp[-2].intVal)+1); //true jump
						patchlabel((yyvsp[-5].intVal), nextquadlabel()); //false jump
						patchlabel((yyvsp[-2].intVal), (yyvsp[-6].forprfx)->test); //loop jump
						patchlabel((yyvsp[0].intVal), (yyvsp[-5].intVal)+1); //closure jump

						if(curr_stack->breaklist!=NULL){
							patchlabel(curr_stack->breaklist->label-1, nextquadlabel());
						}
						if(curr_stack->contlist!=NULL){
							patchlabel(curr_stack->contlist->label-1, (yyvsp[-5].intVal)+1);
						}
						curr_stack = pop_bc(bc_head);
					}
#line 2897 "parser.c" /* yacc.c:1646  */
    break;

  case 107:
#line 1095 "parser.y" /* yacc.c:1646  */
    {
									printf("return expr;\n");
									emit(ret, NULL, NULL, (yyvsp[-1].exp), nextquadlabel(), yylineno);
									}
#line 2906 "parser.c" /* yacc.c:1646  */
    break;

  case 108:
#line 1099 "parser.y" /* yacc.c:1646  */
    {
									printf("return;\n");
									emit(ret, NULL, NULL, NULL, nextquadlabel(), yylineno);
									}
#line 2915 "parser.c" /* yacc.c:1646  */
    break;


#line 2919 "parser.c" /* yacc.c:1646  */
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
#line 1105 "parser.y" /* yacc.c:1906  */


int main(int argc, char* argv[])
{
	printf("-------------------------- SYNTAX ANALYZER --------------------------  \n\n");
	clock_t begin = clock();

	// scope_list = (st_entry**)malloc(sizeof(st_entry *));
	scope_counter = 1;
	args = malloc(sizeof(arguments));

	// func_head = (func_stack*)malloc(sizeof(func_stack));

	// symbol = (st_entry*)malloc(sizeof(st_entry));
	curr_stack = (e_stack*)malloc(sizeof(e_stack));
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
	// print_st();
	print_quads();
	generate_instructions();
	patch_incomplete_jumps();
	print_instructions();
	binary();
	clock_t end = clock();
	double time_spent = ((double)(end - begin) / CLOCKS_PER_SEC) * 1000;

	printf("\n");
 	printf("-------------------------- SYNTAX ANALYZER -------------------------- \n");
 	printf(KGRN"Syntax Analysis Completed in %.3fms !!!\n"KNRM, time_spent);
	return 0;
}



