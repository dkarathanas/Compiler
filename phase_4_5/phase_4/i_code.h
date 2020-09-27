#include <assert.h>
#include "symbol_table.h"
#include <stdio.h>


/*
------------------------------------
STRUCTS
------------------------------------
*/

typedef enum iopcode{
    assign, add, sub,
    mul, diva, mod, 
    or, jump, and,
    not, ifeq, if_noteq,
    if_lesseq, if_greatereq, if_less,
    if_greater, call, param, 
    getretval, funcstart, 
    funcend, tablecreate,
    tablegetelem, tablesetelem, ret, uminus     
} iopcode;

typedef enum expr_t {
    var_e,
    tableitem_e,
    
    programfunc_e,
    libfunc_e,

    arithexpr_e,
    boolexpr_e,
    assignexpr_e,
    newtable_e,

    constnum_e,
    constbool_e,
    conststring_e,

    nil_e,
}expr_t;

typedef struct forprefix{
    int test;
    int enter;
} forprefix;

typedef struct list{
    int label; //label tou quad pou antistoixei se unfinished jump
    struct list* next;
} list;

typedef struct e_stack{
    list* breaklist;
    list* contlist;
}e_stack;

typedef struct bc_stack{
    e_stack* bc_list;
    struct bc_stack* next;
}bc_stack;

typedef struct loop_stack{
    int counter;
    struct loop_stack* next;
}loop_stack;


// typedef struct symbol
// {
//     symbol_t type;
//     char *name;
//     scopespace_t space;
//     unsigned offset;
//     unsigned scope;
//     unsigned line;
// } symbol;

typedef struct expr {
    expr_t type;
    struct SymbolTableEntry* sym;
    struct expr* index;
    double numConst;
    char*  strConst;
    unsigned char boolConst;
    unsigned int const_init; //0->name, 1->num, 2->str, 3->bool
    unsigned method;
    struct expr* next;  //for elists etc
    struct e_stack* stack;

} expr;

typedef struct quad{
    iopcode op;
    expr* result;
    expr* arg1;
    expr* arg2;
    unsigned label;
    unsigned line;
    unsigned taddress;
} quad;

typedef struct function_stack{
    struct function_stack* next;
    int offset;
} func_stack;


#define EXPAND_SIZE 1024
#define CURR_SIZE (total*sizeof(quad))
#define NEW_SIZE  (EXPAND_SIZE*sizeof(quad)+CURR_SIZE)

/*
------------------------------------
FUNCTIONS
------------------------------------
*/


//dynamically expand total quad size
void expand();
//pass arguments to quads
void emit(iopcode op, expr* arg1, expr* arg2, expr* result, unsigned label, unsigned line);
//check scope space and return type
scopespace_t currscopespace(void);
//check type and return offset type
unsigned currscopeoffset(void);
//increase current scope offset
void inccurrentscopeoffset(void);
//enter scope space
void enterscopespace(void);
//exit scope space
void exitscopespace();
void resetformalargsoffet(void);
void resetfunclocaloffset(void);

void restorecurrscopeoffset(unsigned n);

unsigned nextquadlabel(void);

void patchlabel(unsigned quadNo, unsigned label);

//make a l-value expr out a symbol
expr* lvalue_expr(struct SymbolTableEntry* sym);
//create new expr
expr* newexpr(expr_t);
expr* newexpr_conststring(char*);
expr* newexpr_constnum(double);
expr *newexpr_constbool(char);
expr* member_item(expr* lvalue, char* name, unsigned label, unsigned line, unsigned int scope);

expr *make_call(expr *lvalue, expr *elist, unsigned label, unsigned int line, unsigned int scope);
expr *emit_iftableitem(expr * e, unsigned label, unsigned line, unsigned int scope);

expr *insert_list_front(expr *head, expr *new);
list *merge_list(list *head1, list *head2); 
int checkuminus(expr *e);

unsigned int istempname(char *s);
unsigned int istempexpr(expr * e);
st_entry *newtemp(int scope, int line);
void resettemp();

void print_op(FILE*, iopcode);
expr *merge(expr *head1, expr *head2);

void push_loop_stack(loop_stack **head, int c);
int pop_loop(loop_stack* head);

bc_stack* push_bc_stack(bc_stack **head, e_stack *c);
e_stack *pop_bc(bc_stack *head);

void push_func(func_stack **head, int offset);
int pop_func(func_stack  *head);
void print_quads();
void generate_instructions();
void append_list(return_list **list, int label);
void patch_instruction(unsigned instNo, unsigned label);
void backpatch_instruction(return_list *list, int label);