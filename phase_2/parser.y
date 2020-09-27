%{
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
%}

%union{
	char* stringVal;
	int intVal;
	double realVal;
	struct SymbolTableEntry *exprNode;
}

%start program



%token <stringVal> IDENTIFIER STRING
%token <intVal> INTEGER
%token <realVal> FLOAT

%type <exprNode> expr lvalue member

%token IF ELSE WHILE FOR FUNCTION RETURN BREAK CONTINUE LOCL TRUE FALSE NIL
%token AND OR NOT
%token ASSIGN PLUS MINUS MULTIPLY DIVIDE MODULO DPLUS DMINUS
%token EQUAL DIFFERENT BIGGER SMALLER BIGGER_EQUAL SMALLER_EQUAL
%token LBRACKET RBRACKET LSBRACKET RSBRACKET LPARENTHESIS RPARENTHESIS SEMICOLON COMMA COLON DCOLON DOT DDOT

%right ASSIGN
%left OR AND
%nonassoc EQUAL DIFFERENT
%nonassoc BIGGER BIGGER_EQUAL SMALLER SMALLER_EQUAL
%left PLUS MINUS
%left MULTIPLY DIVIDE MODULO 
%right NOT DPLUS DMINUS UMINUS
%left DOT DDOT
%left LPARENTHESIS RPARENTHESIS LSBRACKET RSBRACKET




%%

program:	stmts
		;

stmts:	 	stmt stmts	{printf("stmts->stmt stmts\n");}
		|	{printf("stmts-> *empty*\n");}
		;		

stmt:		expr SEMICOLON	{printf("stmt->expr;\n");}
		|	ifstmt			{printf("stmt->ifstmt\n");}
		|	whilestmt		{printf("stmt->whilestmt\n");}

		|	forstmt			{printf("stmt->forstmt\n");}

		|	returnstmt		{printf("stmt->returnstmt\n");
							if(!is_func){
								printf(KRED"Error at line %d: return used outside of function\n"KNRM, yylineno);
							}}
		|	BREAK SEMICOLON	{printf("stmt->break\n");

							//printf("is_loop = %d\tis_loop_in_func = %d\n", is_loop, is_loop_in_func);
							//if not in loop -> error
							if (!is_loop && !is_loop_in_func)
							{
								printf(KRED "Error at line %d: break used outside of loop\n" KNRM, yylineno);
							}
							}
		|	CONTINUE SEMICOLON	{printf("stmt->continue\n");
								if (!is_loop && !is_loop_in_func)
								//if not in loop -> error

								{
									printf(KRED "Error at line %d: continue used outside of loop\n" KNRM, yylineno);
								}
								}
		|	block				{printf("stmt->block\n");}
		|	funcdef				{printf("stmt->funcdef\n");}
		|	SEMICOLON			{printf("stmt->semicolon\n");}
		;

assignexpr:	lvalue ASSIGN expr {printf("Assinexpr-> lvalue = expr\n");
								if($1!=NULL){
								printf("lalala\n");}

								if($1->type == USERFUNC || $1->type == LIBFUNC){
									printf(KRED "Error: Invalid action on function in line %d: %s \'=\' expr\n" KNRM, yylineno, $1->value.funcVal->name);
								}
								}
			;

expr:		expr PLUS expr			{printf("expr + expr\n");}
		|	expr MINUS expr			{printf("expr - expr\n");}
		|	expr MULTIPLY expr		{printf("expr * expr\n");}
		|	expr DIVIDE expr		{printf("expr / expr\n");}
		|	expr MODULO expr		{printf("expr mod expr\n");}
		|	expr EQUAL expr			{printf("expr == expr\n");}
		| 	expr DIFFERENT expr		{printf("expr != expr\n");}
		| 	expr BIGGER expr		{printf("expr > expr\n");}
		| 	expr BIGGER_EQUAL expr	{printf("expr->expr >= expr\n");}
		|	expr SMALLER expr		{printf("expr->expr < expr\n");}
		|	expr SMALLER_EQUAL expr	{printf("expr->expr <= expr\n");}
		|	expr AND expr			{printf("expr->expr AND expr\n");}
		|	expr OR expr			{printf("expr->expr OR expr\n");}
		| 	assignexpr 				{printf("expr->assignexpr\n"); }
		|	term 					{printf("expr-> term\n");}
		;



term:		LPARENTHESIS expr RPARENTHESIS  {printf("term->(expr)\n");}
		|	MINUS expr	%prec UMINUS		{printf("term->-expr\n");}
		|	NOT expr						{printf("term->!expr");}
		|	DPLUS lvalue					{printf("term->++lvalue\n");}
											{
											if($2->type == USERFUNC || $2->type == LIBFUNC){
												printf(KRED"Error: Invalid action on function in line %d: ++%s\n"KNRM, yylineno, $2->value.funcVal->name);
											}
											}
		|	lvalue DPLUS					{
											if($1->type == USERFUNC || $1->type == LIBFUNC){
												printf(KRED"Error: Invalid action on function in line %d: %s++\n"KNRM, yylineno, $1->value.funcVal->name);
											}
											}
		|	DMINUS lvalue																{
											if($2->type == USERFUNC || $2->type == LIBFUNC){
												printf(KRED"Error: Invalid action on function in line %d: --%s\n"KNRM, yylineno, $2->value.funcVal->name);
											}
											}
		| 	lvalue DMINUS																{
											if($1->type == USERFUNC || $1->type == LIBFUNC){
												printf(KRED"Error: Invalid action on function in line %d: %s--\n"KNRM, yylineno, $1->value.funcVal->name);
											}
											}
		| 	primary							{printf("term->primary\n");}
		;

primary: 	lvalue				{printf("primary->lvalue\n");}
		|	call				{printf("primary->call\n");}
		|	objectdef			{printf("primary->objectdef\n");}
		|	LPARENTHESIS funcdef RPARENTHESIS	{printf("primary->(funcdef)\n");}
		|	const				{printf("primary->const\n");}
		;

lvalue:		IDENTIFIER			{printf("lvalue->IDENTIFIER: %s\n", $1);
								tmp_scope = scope;
								//lookup id from current scope to global
								while(tmp_scope>=GLOBAl_SCOPE){
									entry=lookup(tmp_scope, (char*)$1);
									if(entry!=NULL){
										break;
									}
									tmp_scope--;
								}
								tmp_scope++;

								//if no entry found
								if(entry==NULL){
									printf(KCYN "LOOKUP: symbol \'%s\', at line %d not found in symbol table\n" KNRM, $1, yylineno);

									
									if(is_func){	//if we are inside a function
										if(tmp_scope-1 >= func_scope){
											//if we are inside inside a function body
											var_symbol = create_symbol_var((char *)$1, scope, yylineno);
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
										var_symbol = create_symbol_var((char*)$1, scope, yylineno);
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
									printf(KCYN "LOOKUP: symbol \'%s\', at line %d found in scope %d\n" KNRM, $1, yylineno, tmp_scope-1);
									// printf("tempscore = %d\n", tmp_scope-1);
									// printf("function scope = %d\n", func_scope);

									//if entry found out of current function scope and not in global->error
									if (is_func && (tmp_scope-1 < func_scope) && (tmp_scope-1) != GLOBAl_SCOPE)
									{
										{
											printf(KRED "Error: Cannot access %s in scope %d\n" KNRM, $1, tmp_scope-1);
										}
									}
								}
								//lvalue = symbol_entry;
								$$ = entry;

								

								}
								
		|	LOCL IDENTIFIER		{printf("lvalue->LOCAL ID\n");
								//lookup in current scope

								entry = lookup(scope, (char*)$2);
								collision_flag = collisions($2);

								if(entry==NULL && !collision_flag){
									printf(KCYN "LOOKUP: local symbol \'%s\', at line %d not found in scope %d\n" KNRM, $2, yylineno, scope);

									//if symbol not found, insert entry locally
									var_symbol = create_symbol_var((char*)$2, scope, yylineno);
									if(scope==0){
										entry = create_entry(var_symbol, GLOBAL);
									}
									else{
										entry = create_entry(var_symbol, LOCAL);
									}
								}
								else{
									printf(KCYN "LOOKUP: local symbol \'%s\', at line %d found in scope %d\n" KNRM, $2, yylineno, scope);
								}

								//lvalue = entry
								$$ = entry;
							}
		|	DCOLON IDENTIFIER		{printf("lvalue->::ID\n");
								//lookup only
								entry = lookup(GLOBAl_SCOPE, $2);
								if(entry){
									$$ = entry;
									printf(KCYN "LOOKUP: Global symbol \'%s\', at line %d found in global scope\n" KNRM, $2, yylineno);
								}

								else{
									$$ = (st_entry*)$2;
								printf(KRED "LOOKUP ERROR: Global symbol \'%s\', at line %d not found in global scope\n" KNRM, $2, yylineno);
								}

								//lvalue = entry
								
								
								}
		|	member				{printf("lvalue->member\n");}
								{
									//lvalue = member
									$$ = $1;
								}
		;

member : lvalue DOT IDENTIFIER { printf("member->lvalue.ID: lvalue.ID\n"); 
									entry = lookup(scope, $3);
									$1 = entry;
									$$ = (st_entry*)$3;
										}
		|	lvalue LSBRACKET expr RSBRACKET {printf("member->lvalue[expr]\n");}
		|	call DOT IDENTIFIER			{printf("member->call.ID\n");

										$$ = (st_entry*)$3;
										}
		|	call LSBRACKET expr RSBRACKET	{printf("member->call[expr]\n");
												$$ = $3;}
		;

call:		call LPARENTHESIS elist RPARENTHESIS {printf("call->call(elist)\n");}
		|	lvalue callsuffix				{printf("call->lvalue callsufix\n");}
		|	LPARENTHESIS funcdef RPARENTHESIS LPARENTHESIS elist RPARENTHESIS
			{printf("call->(funcdef) (elist)\n");}
		;

callsuffix:	normcall  {printf("callsuffix->normcall\n");}
		|	methodcall{printf("callsuffix->methodcall\n");}
		;

normcall:	LPARENTHESIS elist RPARENTHESIS		{printf("normcall-> (elist)\n");}
		;

methodcall : DDOT IDENTIFIER LPARENTHESIS elist RPARENTHESIS
				 {printf("methodcal-> ..%s\n", $2);}
			;

elist:	 elist COMMA expr { printf("elist-> expr, elist\n"); }
		|expr { printf("elist-> expr \n"); }
		|	{printf("elist -> *empty*\n");}

	;

objectdef:	LSBRACKET  elist RSBRACKET	{printf("objectdef-> [expr, elist]\t line: %d\n", yylineno);}
		|	LSBRACKET indexed RSBRACKET	{printf("objectdef-> [indexelem, indexed]\t line: %d\n", yylineno);}
		// |	LSBRACKET RSBRACKET						{printf("objectdef-> []\t line: %d\n", yylineno);}
		;

indexed:	indexed COMMA indexedelem			{printf("indexed-> indexedelem, indexed\t line: %d\n", yylineno);}
		|	indexedelem							{printf("indexed-> indexedelem\t line: %d\n", yylineno);}
		;

indexedelem:LBRACKET expr COLON expr RBRACKET	{printf("indexedelem-> {expr:expr}\t line: %d\n", yylineno);}
		;


block: 		LBRACKET		{if((!is_func)){
								//if we are inside a function scope is already incr
								// by funcdef rule so we dont increase twice
								scope++;
								}
								if((is_func)&&is_loop_in_func){
									scope++;
								}
							}
		 stmt program RBRACKET	{printf("block-> { stmt }\n");
		 						hide(scope);
		 						if(func_scope){func_scope--;}
		 						if(scope>0)
		 						scope--;
											}
		|	LBRACKET 	{if((!is_func)){
								//if we are inside a function scope is already incr
								// by funcdef rule so we dont increase twice
								scope++;
								}
								if((is_func)&&is_loop_in_func){
									scope++;
								}
							}
		 RBRACKET		{printf("block-> {}\n");
		 							if(scope>0)
									scope--; //recheck
									}
		;

funcdef:	FUNCTION IDENTIFIER {printf("funcdef-> function ID (idlist) block\n");
								tmp_scope = scope;
								while(tmp_scope>=GLOBAl_SCOPE){
									entry=lookup(scope, (char*)$2);
									tmp_scope--;
								}
								if(entry==NULL){
									printf(KCYN "LOOKUP: function symbol \'%s\', at line %d not found in symbol table\n" KNRM, $2, yylineno);
									func_scope = scope+1;
									func_symbol = create_symbol_func($2, args, scope, yylineno);
									entry = create_entry(func_symbol, USERFUNC);
								}
								else{
									printf(KRED"Error at line %d: %s already defined\n"KNRM,yylineno, $2);
								}

								}
			 LPARENTHESIS {scope++; is_func++; is_loop_in_func = 0;}
			 idlist { 
			 	if(args==NULL)
			 		free_arg_list(args); }
			 RPARENTHESIS block
			 {
				 is_func--;
			 }
			 | FUNCTION {printf("funcdef-> function (idlist) block\n");
			 	char * funcname = newUnnamedFunc();
			 	func_scope = scope+1;
			 	func_symbol = create_symbol_func(funcname, args, scope, yylineno);
			 	entry = create_entry(func_symbol, USERFUNC);

			 				}LPARENTHESIS{scope++; is_func++; is_loop_in_func = 0;}
			 				 idlist { free_arg_list(args); }

			 RPARENTHESIS block
			 {
				 is_func--;
				 };

				 const : INTEGER { printf("integer: %d\n", $1); }
				 | STRING { printf("String: %s\n", $1); }
				 | FLOAT { printf("Float %f\n", $1); }
				 | NIL { printf("NIL\n"); }
				 | TRUE { printf("TRUE\n"); }
				 | FALSE { printf("FALSE\n"); };

 idlist:

			 IDENTIFIER COMMA idlist
			 {
				 //link the rest of the arguments to argument list
				 printf("idlist-> Argument, Arguments\n");
				 tmp_arg = args;
				 while (tmp_arg->next)
				 {
					 tmp_arg = tmp_arg->next;
				 }
				 entry = lookup(scope, $1);
				 collision_flag = collisions($1);
				 if (entry == NULL && !collision_flag)
				 {
					 var_symbol = create_symbol_var($1, scope, yylineno);
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
						 if(!strcmp(tmp_arg->arg->name, $1)){
					 		printf(KRED "Error: Formal redeclaration \'%s\' at line %d\n" KNRM, $1, yylineno);
							 break;
						 }
						 // printf("name: %s\n", tmp_arg->arg->name);
						 tmp_arg = tmp_arg->next;
					 }
				 }
				 }
				 | IDENTIFIER
				 {
					 
					 
					 printf("idlist-> Argument = %s\n", $1);
					 //initialize and insert first argument to argument list
					 entry = lookup(scope, $1);
					 collision_flag = collisions($1);
					 if (!collision_flag)
					 {
						 printf(KCYN "LOOKUP: Formal Argument \'%s\', at line %d not found in function arguments\n" KNRM, $1, yylineno);
						 var_symbol = create_symbol_var($1, scope, yylineno);
						 entry = create_entry(var_symbol, FORMAL);
						 args->arg = var_symbol;
						 args->next = NULL;
					 }
					 else
					 {
						 //printf(KRED "Error: formal redeclaration\n" KNRM);
					 }
				 }
				 | //clear args list
					 ;

ifstmt:
				 IF LPARENTHESIS expr RPARENTHESIS stmt { printf("ifstmt-> if (expr) stmt\n"); }
				 | IF LPARENTHESIS expr RPARENTHESIS stmt ELSE stmt { printf("ifstmt->if (expr) stmt else (stmt)\n"); };

whilestmt:
				 WHILE
				 {	printf("whilestmt-> wile (expr) stmt\n");
					 if (is_func)
						 is_loop_in_func++;
					is_loop++;}
				 LPARENTHESIS expr RPARENTHESIS stmt
			{printf("while (expr){stmt}\n");

					if (is_func)
						is_loop_in_func=0;
					else
						is_loop --;
				}
			;

forstmt:	FOR
			{	printf("forstmt-> for(elist; expr; elist;) stmt\n");
				if (is_func)
					is_loop_in_func++;
				
					is_loop ++;
			}
			LPARENTHESIS elist SEMICOLON expr SEMICOLON elist RPARENTHESIS stmt
			{printf("for (elist); (expr); (elist))\n");
					if (is_func)
						is_loop_in_func=0;
					else
					is_loop--;
				};

returnstmt:	RETURN expr SEMICOLON {printf("return expr;\n");}
		| 	RETURN SEMICOLON	{printf("return;\n");}
		;

%%

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



