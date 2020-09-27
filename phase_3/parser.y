%{
	#include <stdio.h>
	#include <unistd.h>
	#include <stdlib.h>

#include "i_code.h"

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
%}

%union{
	char* stringVal;
	int intVal;
	double realVal;
	struct SymbolTableEntry *exprNode;
	struct expr* exp;
	struct forprefix *forprfx;
	struct list* l;
}

%start program



%token <stringVal> IDENTIFIER STRING
%token <intVal> INTEGER
%token <realVal> FLOAT
%token <l> BREAK CONTINUE 

%type <exprNode>   funcprefix funcdef
%type <exp> const expr term primary lvalue assignexpr member methodcall normcall callsuffix call whilestmt
%type <exp> elist objectdef indexed indexedelem stmt stmts block break continue loopstmt
%type <stringVal> funcname
%type <intVal> funcbody ifprefix elseprefix whilestart whilecond M N
%type <forprfx> forprefix

%token IF ELSE WHILE FOR FUNCTION RETURN LOCL TRUE FALSE NIL
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

program: stmts 
			{
			// $$ = $1;
			}
			|

			;

stmts : stmt
			{
				$$ = $1;

					} 
		|stmts	stmt{
						// printf("stmts->stmt stmts\n");
						// $2 = $1;
						// if($$->stack){
							// $$->stack->breaklist = merge_list(curr_stack->breaklist, $1->stack->breaklist);
							// $$->stack->contlist = merge_list($1->stack->contlist, curr_stack->contlist);
							$$ = (expr *)malloc(sizeof(expr));
							$$->stack = (e_stack *)malloc(sizeof(e_stack));
							//link with break-continue stack next element
							if (curr_stack->breaklist)
								$$->stack->breaklist = merge_list($$->stack->breaklist, curr_stack->breaklist);
							 if(curr_stack->contlist)
								$$->stack->contlist = merge_list($$->stack->contlist, curr_stack->contlist);
						// }
						}
		;		

stmt:		expr SEMICOLON	{}
		|	ifstmt			{}
		|	whilestmt		{}

		|	forstmt			{}

		|	returnstmt		{
							if(!is_func){
								printf(KRED"Error at line %d: return used outside of function\n"KNRM, yylineno);
							}}
		|	break{

							//printf("is_loop = %d\tis_loop_in_func = %d\n", is_loop, is_loop_in_func);
							//if not in loop -> error
							if (loopcounter==0)
							{
								printf(KRED "Error at line %d: break used outside of loop\n" KNRM, yylineno);
							}
							$$ = $1;
							// printf("LABEL stmt: %d\n", $$->stack->breaklist->label);

								// $$->stack->breaklist = $1;
							}
		|	continue	{
							if (loopcounter==0)
								//if not in loop -> error

								{
									printf(KRED "Error at line %d: continue used outside of loop\n" KNRM, yylineno);
								}
								$$ = $1;
								}
		|	block				{$$ = $1;}
		|	funcdef				{}
		|	SEMICOLON			{}
		;

break:	BREAK SEMICOLON	{
							emit(jump, NULL, NULL, NULL, -1, yylineno);
							$$ = (expr*)malloc(sizeof(expr));	
							$$->stack = (e_stack*)malloc(sizeof(e_stack));
							$$->stack->breaklist = (list*)malloc(sizeof(list));
							$$->stack->breaklist->label = nextquadlabel();
							curr_stack->breaklist = $$->stack->breaklist;
							printf("LABEL: %d\n", $$->stack->breaklist->label);

						}
	;

continue: CONTINUE SEMICOLON 	{	
							emit(jump, NULL, NULL, NULL, -1, yylineno);
							$$ = (expr*)malloc(sizeof(expr));	
							$$->stack = (e_stack*)malloc(sizeof(e_stack));
							$$->stack->contlist = (list*)malloc(sizeof(list));
							$$->stack->contlist->label = nextquadlabel();
							curr_stack->contlist = $$->stack->contlist;

							printf("LABEL: %d\n", $$->stack->contlist->label);
								}

assignexpr:	lvalue ASSIGN expr {
								if($1!=NULL){
									if($1->type == tableitem_e){
										emit(tablesetelem, $1, $1->index, $3, nextquadlabel(), yylineno);
										$$ = emit_iftableitem($1, nextquadlabel(), yylineno, scope);
										$$->type = assignexpr_e;
									}
									else{
										//lvalue = expr
										emit(assign, $3, NULL, $1, nextquadlabel(), yylineno);
										$$ = newexpr(assignexpr_e);
										$$->sym = newtemp(scope, yylineno);
										emit(assign, $1, NULL, $$, nextquadlabel(), yylineno);
									}
								}

								if($1->type == USERFUNC || $1->type == LIBFUNC){
									printf(KRED "Error: Invalid action on function in line %d: %s \'=\' expr\n" KNRM, yylineno, $1->sym->value.funcVal->name);
								}
								}
			;
expr:		expr PLUS expr			{
									 $$ = newexpr(arithexpr_e);
									 $$->sym = newtemp(scope, yylineno);
									 emit(add, $1, $3, $$, nextquadlabel(), yylineno);}

		|	expr MINUS expr			{
									$$ = newexpr(arithexpr_e);
									 $$->sym = newtemp(scope, yylineno);
									 emit(sub, $1, $3, $$, nextquadlabel(), yylineno);}

		|	expr MULTIPLY expr		{
									$$ = newexpr(arithexpr_e);
									$$->sym = newtemp(scope, yylineno);
									emit(mul, $1, $3, $$, nextquadlabel(), yylineno);}

		|	expr DIVIDE expr		{
									$$ = newexpr(arithexpr_e);
									$$->sym = newtemp(scope, yylineno);
									emit(diva, $1, $3, $$, nextquadlabel(), yylineno);}

		|	expr MODULO expr		{
									$$ = newexpr(arithexpr_e);
									$$->sym = newtemp(scope, yylineno);
									emit(mod, $1, $3, $$, nextquadlabel(), yylineno);}

		|	expr EQUAL expr			{
									$$ = newexpr(boolexpr_e);
									$$->sym = newtemp(scope, yylineno);
									emit(ifeq, $1, $3, NULL, nextquadlabel()+3, yylineno);
									emit(assign, NULL, newexpr_constbool('F'), $$, nextquadlabel(), yylineno);
									emit(jump, NULL, NULL, NULL, nextquadlabel()+2, yylineno);
									emit(assign, NULL, newexpr_constbool('T'), $$, nextquadlabel(), yylineno);
									}

		| 	expr DIFFERENT expr		{
									$$ = newexpr(boolexpr_e);
									$$->sym = newtemp(scope, yylineno);
									emit(if_noteq, $1, $3, NULL, nextquadlabel()+3, yylineno);
									emit(assign, NULL, newexpr_constbool('F'), $$, nextquadlabel(), yylineno);
									emit(jump, NULL, NULL, NULL, nextquadlabel()+2, yylineno);
									emit(assign, NULL, newexpr_constbool('T'), $$, nextquadlabel(), yylineno);
		}
		| 	expr BIGGER expr		{
									$$ = newexpr(boolexpr_e);
									$$->sym = newtemp(scope, yylineno);
									emit(if_greater, $1, $3, NULL, nextquadlabel()+3, yylineno);
									emit(assign, NULL, newexpr_constbool('F'), $$, nextquadlabel(), yylineno);
									emit(jump, NULL, NULL, NULL, nextquadlabel()+2, yylineno);
									emit(assign, NULL, newexpr_constbool('T'), $$, nextquadlabel(), yylineno);
		}
		| 	expr BIGGER_EQUAL expr	{
									$$ = newexpr(boolexpr_e);
									$$->sym = newtemp(scope, yylineno);
									emit(if_greatereq, $1, $3, NULL, nextquadlabel()+3, yylineno);
									emit(assign, NULL, newexpr_constbool('F'), $$, nextquadlabel(), yylineno);
									emit(jump, NULL, NULL, NULL, nextquadlabel()+2, yylineno);
									emit(assign, NULL, newexpr_constbool('T'), $$, nextquadlabel(), yylineno);
		}
		|	expr SMALLER expr		{
									$$ = newexpr(boolexpr_e);
									$$->sym = newtemp(scope, yylineno);
									emit(if_less, $1, $3, NULL, nextquadlabel()+3, yylineno);
									emit(assign, NULL, newexpr_constbool('F'), $$, nextquadlabel(), yylineno);
									emit(jump, NULL, NULL, NULL, nextquadlabel()+2, yylineno);
									emit(assign, NULL, newexpr_constbool('T'), $$, nextquadlabel(), yylineno);}
		|	expr SMALLER_EQUAL expr	{
									$$ = newexpr(boolexpr_e);
									$$->sym = newtemp(scope, yylineno);
									emit(if_lesseq, $1, $3, NULL, nextquadlabel()+3, yylineno);
									emit(assign, NULL, newexpr_constbool('F'), $$, nextquadlabel(), yylineno);
									emit(jump, NULL, NULL, NULL, nextquadlabel()+2, yylineno);
									emit(assign, NULL, newexpr_constbool('T'), $$, nextquadlabel(), yylineno);
		}
		|	expr AND expr			{
									$$ = newexpr(boolexpr_e);
									$$->sym = newtemp(scope, yylineno);
									emit(and, $1, $3, $$, nextquadlabel(), yylineno);
		}
		|	expr OR expr			{
									$$ = newexpr(boolexpr_e);
									$$->sym = newtemp(scope, yylineno);
									emit(or, $1, $3, $$, nextquadlabel(), yylineno);
		}
		| 	assignexpr 				{$$ = $1;}
		|	term 					{$$ = $1;}
									
		;

term : LPARENTHESIS expr RPARENTHESIS { $$ = $2; }
		| MINUS expr %prec UMINUS
		{
			if (checkuminus($2) == 0)
			{
				//printf("UMINUS SUCCESS\n");
				$$ = newexpr(arithexpr_e);
				$$->sym = newtemp(scope, yylineno);
				emit(uminus, $2, NULL, $$, nextquadlabel(), yylineno);
			}
			else
			{
				printf(KRED "Error: Invalid action on expression in line %d: \n" KNRM, yylineno);
			}
		}
		| NOT expr
		{
			$$ = newexpr(boolexpr_e);
			$$->sym = newtemp(scope, yylineno);
			emit(not, $2, NULL, $$, nextquadlabel(), yylineno);
		}
		| DPLUS lvalue
		{
			if ($2->type == tableitem_e)
			{ 
				$<exp>$ = emit_iftableitem($2, nextquadlabel(), yylineno, scope);
				emit(add, $<exp>$, newexpr_constnum(1), $<exp>$, nextquadlabel(), yylineno);
				emit(tablesetelem, $2, $2->index, $<exp>$, nextquadlabel(), yylineno);
			}
			else
			{
				emit(add, $2, newexpr_constnum(1), $2, nextquadlabel(), yylineno);
				$<exp>$ = newexpr(arithexpr_e);
				$<exp>$->sym = newtemp(scope, yylineno);
				emit(assign, $2, NULL, $<exp>$, nextquadlabel(), yylineno);
			}
		{
			if ($2->type == USERFUNC || $2->type == LIBFUNC)
			{
				printf(KRED "Error: Invalid action on function in line %d: ++%s\n" KNRM, yylineno, $2->sym->value.funcVal->name);
			}
		}
		}
		| lvalue DPLUS
		{
			$$ = newexpr(var_e);
			$$->sym = newtemp(scope, yylineno);
			if ($1->type == tableitem_e)
			{
				value = emit_iftableitem($1, nextquadlabel(), yylineno, scope);
				emit(assign, value, NULL, $$, nextquadlabel(), yylineno);
				emit(add, value, newexpr_constnum(1), value, nextquadlabel(), yylineno);
				emit(tablesetelem, $1, $1->index, value, nextquadlabel(), yylineno);
			}
			else
			{
				emit(assign, $1, NULL, $$, nextquadlabel(), yylineno);
				emit(add, $1, newexpr_constnum(1), $1, nextquadlabel(), yylineno);
			}
			if ($1->type == USERFUNC || $1->type == LIBFUNC)
			{
				printf(KRED "Error: Invalid action on function in line %d: %s++\n" KNRM, yylineno, $1->sym->value.funcVal->name);
			}
		}
		| DMINUS lvalue
		{
			if ($2->type == tableitem_e)
			{
				$<exp>$ = emit_iftableitem($2, nextquadlabel(), yylineno, scope);
				emit(sub, $<exp>$, newexpr_constnum(1), $<exp>$, nextquadlabel(), yylineno);
				emit(tablesetelem, $2, $2->index, $<exp>$, nextquadlabel(), yylineno);
			}
			else
			{
				emit(sub, $2, newexpr_constnum(1), $2, nextquadlabel(), yylineno);
				$<exp>$ = newexpr(arithexpr_e);
				$<exp>$->sym = newtemp(scope, yylineno);
				emit(assign, $2, NULL, $<exp>$, nextquadlabel(), yylineno);
			}
			if ($2->type == USERFUNC || $2->type == LIBFUNC)
			{
				printf(KRED "Error: Invalid action on function in line %d: --%s\n" KNRM, yylineno, $2->sym->value.funcVal->name);
			}
		}
		| lvalue DMINUS
		{
			$$ = newexpr(var_e);
			$$->sym = newtemp(scope, yylineno);
			if ($1->type == tableitem_e)
			{
				value = emit_iftableitem($1, nextquadlabel(), yylineno, scope);
				emit(assign, value, NULL, $$, nextquadlabel(), yylineno);
				emit(sub, value, newexpr_constnum(1), value, nextquadlabel(), yylineno);
				emit(tablesetelem, $1, $1->index, value, nextquadlabel(), yylineno);
			}
			else
			{
				emit(assign, $1, NULL, $$, nextquadlabel(), yylineno);
				emit(sub, $1, newexpr_constnum(1), $1, nextquadlabel(), yylineno);
			}
			if ($1->type == USERFUNC || $1->type == LIBFUNC)
			{
				printf(KRED "Error: Invalid action on function in line %d: %s--\n" KNRM, yylineno, $1->sym->value.funcVal->name);
			}
		}
		| primary { $$ = $1; };

primary : lvalue { $$ = emit_iftableitem($1, nextquadlabel(), yylineno, scope); }
		|	call				{$$ = $1;}
		|	objectdef			{$$ = $1;}
		|	LPARENTHESIS funcdef RPARENTHESIS	{
								$$ = newexpr(programfunc_e);
								$$->sym = $2;
		}
		|	const				{$$ = $1;}
		;

lvalue:		IDENTIFIER			{
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

								if(entry==NULL){
								//if no entry found
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
									entry->space = currscopespace();
									entry->offset = currscopeoffset();
									inccurrentscopeoffset();
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
								
								$$ = lvalue_expr(entry);

								

								}
								
		|	LOCL IDENTIFIER		{
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
									entry->space = currscopespace();
									entry->offset = currscopeoffset();
									inccurrentscopeoffset();
								}
								else{
									printf(KCYN "LOOKUP: local symbol \'%s\', at line %d found in scope %d\n" KNRM, $2, yylineno, scope);
								}

								//lvalue = entry
								$$ = lvalue_expr(entry);
							}
		|	DCOLON IDENTIFIER		{
								//lookup only
								entry = lookup(GLOBAl_SCOPE, $2);
								if(entry){
									$$ = lvalue_expr(entry);
									printf(KCYN "LOOKUP: Global symbol \'%s\', at line %d found in global scope\n" KNRM, $2, yylineno);
								}

								else{
									$$->sym = (st_entry*)$2;
									//TODO: check lvalue ($$ = lvalue_expr(..))
								printf(KRED "LOOKUP ERROR: Global symbol \'%s\', at line %d not found in global scope\n" KNRM, $2, yylineno);
								}

								//lvalue = entry
								
								
								}
		|	member			
								{
									//lvalue = member
									$$ = $1;
								}
		;

member : lvalue DOT IDENTIFIER {
									entry = lookup(scope, $3);
									$$ = member_item($1, (char*)$3, nextquadlabel(), yylineno, scope);
										}
		|	lvalue LSBRACKET expr RSBRACKET {
									$1 = emit_iftableitem($1, nextquadlabel(), yylineno, scope);
									$$ = newexpr(tableitem_e);
									$$->sym = $1->sym;
									$$->index = $3; //the index is the expression
											}
		|	call DOT IDENTIFIER			{

										$$ = $1;
										}
		|	call LSBRACKET expr RSBRACKET	{
												$$ = $3;}
		;

call:		call LPARENTHESIS elist RPARENTHESIS {

										$$ = make_call($1, $3, nextquadlabel(), yylineno, scope);

}
		|	lvalue callsuffix				
											{
												if($2->method == 1){
													expr* self = $1;
													$1 = emit_iftableitem(member_item(self, $2->strConst, nextquadlabel(), yylineno, scope), nextquadlabel(), yylineno, scope);
													$2 = merge($2, self);
													
											}
												// printf("lala0\n");
												$$ = make_call($1, $2->next, nextquadlabel(), yylineno, scope);
											}
		|	LPARENTHESIS funcdef RPARENTHESIS LPARENTHESIS elist RPARENTHESIS
											{
												expr* func = newexpr(programfunc_e);
												func->sym = $2;
												$$ = make_call(func, $5, nextquadlabel(), yylineno, scope);
											}
		;

callsuffix:	normcall  {
						$$ = $1;
						}
		|	methodcall{
						$$ = $1;
						}
		;

normcall:	LPARENTHESIS elist RPARENTHESIS		{

											printf("elist type: %d\n", $2->type);
											$$ = newexpr(nil_e);

											// $$->next = (expr*)malloc(sizeof(expr));
											$$->next = $2;
											$$->method = 0;
										}
		;

methodcall : DDOT IDENTIFIER LPARENTHESIS elist RPARENTHESIS
				{
					$$->next = $4;
					$$->method = 1;
					$$->strConst = strdup($2);
				};

elist : elist COMMA expr
			{$$ = insert_list_front($1, $3);} 
		
		| expr
				{
					$$ = $1;  }
		|	{
				printf("lala\n");
				$$ = newexpr(nil_e);
			}

	;

objectdef:	LSBRACKET  elist RSBRACKET	
										{
											expr* t = newexpr(newtable_e);
											t->sym = newtemp(scope, yylineno);
											emit(tablecreate, NULL, NULL, t, nextquadlabel(), yylineno);
											expr* list = $2;
											int i = 0;
											while(list){
												emit(tablesetelem, t, newexpr_constnum(i++), newexpr_constnum(list->numConst), nextquadlabel(), yylineno);
												if(!list->next) break;
												list = list->next;
											}
											$$ = t;
										}
		|	LSBRACKET indexed RSBRACKET	
										{
											expr* t = newexpr(newtable_e);
											t->sym = newtemp(scope, yylineno);
											emit(tablecreate, NULL, NULL, t, nextquadlabel(), yylineno);
											expr* key = $2;
											expr* val = key->index;
											while(key){
												emit(tablesetelem, t, key, val, nextquadlabel(), yylineno);
												if(!key->next) break;
												key = key->next;
												val = key->index;
											}
											$$ = t;
										}
		// |	LSBRACKET RSBRACKET						{printf("objectdef-> []\t line: %d\n", yylineno);}
		;

indexed:	indexed COMMA indexedelem			{$$ = insert_list_front($1, $3);}
		|	indexedelem							{$$ = $1;}
		;

indexedelem:LBRACKET expr COLON expr RBRACKET	{$$ = $2; $$->index =$4;}
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
		 stmt program RBRACKET	{$$ = $<exp>2;
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
		 RBRACKET		{
		 							if(scope>0)
									scope--; //recheck
									}
		;

funcblockstart: {
					push_loop_stack(&loop_head, loopcounter);
					loopcounter=0;
				}

funcblockend: 	{
					loopcounter = pop_loop(loop_head);
				}

funcname:	IDENTIFIER
								{
								$$ = strdup($1);
								}
		|						{
								$$ = newUnnamedFunc();
			 					}
		;

funcprefix: FUNCTION funcname	{
									// printf("funcprefix\n");
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
										entry->space = currscopespace();
										entry->offset = currscopeoffset();
										inccurrentscopeoffset();
									}
									else{
										printf(KRED"Error at line %d: %s already defined\n"KNRM,yylineno, $2);
									}
									$$ = entry;
									$$->value.funcVal->iaddress = nextquadlabel();
									emit(funcstart, NULL, NULL, lvalue_expr($$), nextquadlabel(), yylineno);
									push_func(&func_head, functionLocalOffset);
									enterscopespace();	//entering function args scope space
									resetformalargsoffet(); //start formals from zero 
								}
								;
funcargs: LPARENTHESIS{
						// printf("funcargs\n");

						scope++; is_func++; is_loop_in_func = 0;
						} idlist {
						if (args == NULL)
				 			free_arg_list(args);
							} 
								RPARENTHESIS {
											enterscopespace();	//entering function local offset
											resetfunclocaloffset();	//need to start locals from zero
											}
											;

funcbody: block {
				// printf("funcbody\n");
				is_func--;
				exitscopespace();
				}
		;


funcdef: funcprefix funcargs funcblockstart funcbody funcblockend
								{
									// printf("funcdef\n");
									exitscopespace(); //exiting function definition space
									$1->value.funcVal->totallocals = functionLocalOffset;
									functionLocalOffset = pop_func(func_head);
									// functionLocalOffset = func_head->offset;

									emit(funcend, NULL, NULL, lvalue_expr($1), nextquadlabel(), yylineno);
								}
		;	
		

// funcdef:	FUNCTION IDENTIFIER {
// 								tmp_scope = scope;
// 								while(tmp_scope>=GLOBAl_SCOPE){
// 									entry=lookup(scope, (char*)$2);
// 									tmp_scope--;
// 								}
// 								if(entry==NULL){
// 									printf(KCYN "LOOKUP: function symbol \'%s\', at line %d not found in symbol table\n" KNRM, $2, yylineno);
// 									func_scope = scope+1;
// 									func_symbol = create_symbol_func($2, args, scope, yylineno);
// 									entry = create_entry(func_symbol, USERFUNC);
// 								}
// 								else{
// 									printf(KRED"Error at line %d: %s already defined\n"KNRM,yylineno, $2);
// 								}

// 								}
// 			 LPARENTHESIS {scope++; is_func++; is_loop_in_func = 0;}
// 			 idlist { 
// 			 	if(args==NULL)
// 			 		free_arg_list(args); }
// 			 RPARENTHESIS block
// 			 {
// 				 is_func--;
// 			 }
// 			 | FUNCTION {
// 			 	char * funcname = newUnnamedFunc();
// 			 	func_scope = scope+1;
// 			 	func_symbol = create_symbol_func(funcname, args, scope, yylineno);
// 			 	entry = create_entry(func_symbol, USERFUNC);

// 			 				}LPARENTHESIS{scope++; is_func++; is_loop_in_func = 0;}
// 			 				 idlist { free_arg_list(args); }

// 			 RPARENTHESIS block
// 			 {
// 				 is_func--;
// 				 };

const : INTEGER { 
					$$ = newexpr(constnum_e);
					$$->numConst = $1;
					// printf("integer: %f\n", $$->numConst);
					}

				 | STRING {
				 	$$ = newexpr(conststring_e);
					$$->strConst = strdup($1);
					// printf("String: %s\n", $$->strConst); 
					 }
				 | FLOAT {
					 $$ = newexpr(constnum_e);
					 $$->numConst = $1;
					//  printf("float: %f\n", $$->numConst);
				 }
				 
				 | NIL {
					 	$$ = newexpr(nil_e);
						 printf("NIL\n"); }
				 | TRUE { 
				 		$$ = newexpr(boolexpr_e);
						$$->boolConst = 'T';
						// printf("%c\n", $$->boolConst);
				 }
				 | FALSE
				 {
					 $$ = newexpr(boolexpr_e);
					 $$->boolConst = 'F';
					//  printf("%c\n", $$->boolConst);
				 };

idlist :

					 IDENTIFIER COMMA idlist
				 {
					 //link the rest of the arguments to argument list
					 
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
					 else if (collision_flag)
					 {
					 }

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


ifprefix: IF LPARENTHESIS expr RPARENTHESIS
									{
										emit(ifeq, NULL, $3, newexpr_constbool('T'), nextquadlabel()+2, yylineno);
										$$ = nextquadlabel();
										emit(jump, NULL, NULL, NULL, -1, yylineno);
									}
		;


elseprefix: ELSE 
				{
					$$ = nextquadlabel();
					emit(jump, NULL, NULL, NULL, -1, yylineno);
				}
			;

ifstmt:		ifprefix stmt
									{
										printf("lala\n");
										patchlabel($1, nextquadlabel()); //patch to $1 sto nextquadlabel???
									}
			|	ifprefix stmt elseprefix stmt
									{
										patchlabel($1, $3+1);
										patchlabel($3, nextquadlabel());
									}
			;



// whilestmt:
// 				 WHILE
// 				 {	
// 					 if (is_func)
// 						 is_loop_in_func++;
// 					is_loop++;}
// 				 LPARENTHESIS expr RPARENTHESIS stmt
// 			{

// 					if (is_func)
// 						is_loop_in_func=0;
// 					else
// 						is_loop --;
// 				}
// 			;


loopstart: {

			bc_head = push_bc_stack(&bc_head, curr_stack);
			++loopcounter;
			// curr_stack->breaklist = NULL;
			// curr_stack->contlist = NULL;
			}

loopend: 	{

			--loopcounter;

			}

loopstmt: loopstart stmt loopend {$$ = $2;}

whilestart: WHILE {$$ = nextquadlabel();}

whilecond: LPARENTHESIS expr RPARENTHESIS	{
												emit(ifeq, NULL, $2, newexpr_constbool('T'), nextquadlabel()+2, yylineno);
												$$ = nextquadlabel();
												emit(jump, NULL, NULL, NULL, -1, yylineno);
											}

whilestmt: whilestart whilecond loopstmt		{
												
												emit(jump, NULL, NULL, NULL, $1, yylineno);
												patchlabel($2, nextquadlabel());
												

													
												if(curr_stack->breaklist!=NULL){
													printf("breaklist->label = %d\n", curr_stack->breaklist->label);
														patchlabel(curr_stack->breaklist->label-1, nextquadlabel());
												}
												if(curr_stack->contlist!=NULL){
													patchlabel(curr_stack->contlist->label-1, $1);
												}
												curr_stack = pop_bc(bc_head);
											}

N: {$$ = nextquadlabel();
	emit(jump, NULL, NULL, NULL, -1, yylineno);}

M: {$$= nextquadlabel();}

forprefix: FOR	LPARENTHESIS elist SEMICOLON M expr SEMICOLON
	{

						$$ = (forprefix*)malloc(sizeof(forprefix));
						$$->test = $5;
						$$->enter = nextquadlabel();
						emit(ifeq, NULL, $6, newexpr_constbool('T'), -1, yylineno);

						
						
}

forstmt:	forprefix N elist RPARENTHESIS N loopstmt N
					{
						patchlabel($1->enter, $5+1); //true jump
						patchlabel($2, nextquadlabel()); //false jump
						patchlabel($5, $1->test); //loop jump
						patchlabel($7, $2+1); //closure jump

						if(curr_stack->breaklist!=NULL){
							patchlabel(curr_stack->breaklist->label-1, nextquadlabel());
						}
						if(curr_stack->contlist!=NULL){
							patchlabel(curr_stack->contlist->label-1, $2+1);
						}
						curr_stack = pop_bc(bc_head);
					}

returnstmt:	RETURN expr SEMICOLON {
									printf("return expr;\n");
									emit(ret, NULL, NULL, $2, nextquadlabel(), yylineno);
									}
		| 	RETURN SEMICOLON	{
									printf("return;\n");
									emit(ret, NULL, NULL, NULL, nextquadlabel(), yylineno);
									}
		;

%%

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
	clock_t end = clock();
	double time_spent = ((double)(end - begin) / CLOCKS_PER_SEC) * 1000;

	printf("\n");
 	printf("-------------------------- SYNTAX ANALYZER -------------------------- \n");
 	printf(KGRN"Syntax Analysis Completed in %.3fms !!!\n"KNRM, time_spent);
	return 0;
}



