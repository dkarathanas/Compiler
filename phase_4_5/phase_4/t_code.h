#include "i_code.h"

//Structs
typedef enum vmopcode
{
    add_v,
    sub_v,
    mul_v,
    div_v,
    mod_v,
    and_v,
    or_v,
    not_v,
    jeq_v,
    jne_v,
    jle_v,
    jge_v,
    jlt_v,
    jgt_v,
    call_v,
    newtable_v,
    tablegetelem_v,
    tablesetelem_v,
    nop_v,
    jump_v,
    pusharg_v,
    assign_v,
    funcenter_v,
    funcexit_v,
} vmopcode;

typedef enum vmarg_t{

    label_a,
    global_a,
    local_a,
    formal_a,

    bool_a,
    string_a,
    number_a,
    nil_a,

    userfunc_a,
    libfunc_a,
    retval_a
}vmarg_t;

typedef struct vmarg{
    vmarg_t type;
    unsigned val;
} vmarg;

typedef struct instruction{
    vmopcode opcode;
    vmarg* result;
    vmarg* arg1;
    vmarg* arg2;
    // unsigned label;
    unsigned srcLine;
} instruction;

typedef struct incomplete_jump{
    unsigned instrNo; //the jump instruction number
    unsigned iaddress; // the i-code jump-target address
    struct incomplete_jump* next; //linked list
} incomplete_jump;

typedef struct userfunc{
    unsigned address;
    unsigned localSize;
    char* id;
}userfunc;

typedef struct funcstack{
    st_entry* func;
    struct funcstack* next;
}funcstack;

#define I_EXPAND_SIZE 20
#define I_CURR_SIZE (total_inst*sizeof(instruction))
#define I_NEW_SIZE (I_EXPAND_SIZE*sizeof(instruction)+I_CURR_SIZE)

//Functions

unsigned consts_newstring(char*s);
unsigned consts_newnumber(double n);
unsigned libfuncs_newused(char* s);
unsigned userfuncs_newfunc(st_entry* sym);
void add_incomplete_jump(unsigned instrNo, unsigned iaddress);
void patch_incomplete_jumps();
void expand_inst();
void emit_instruction(instruction*);
unsigned nextinstructionlabel();
void generate(vmopcode, quad*);
void make_booloperand(vmarg*, char);
void make_numberoperand(vmarg*, double);
void make_retvaloperand(vmarg*);
void generate_add(quad*);
void generate_sub(quad*);
void generate_mul(quad*);
void generate_div(quad*);
void generate_mod(quad*);
void generate_newtable(quad*);
void generate_tablegetelem(quad*);
void generate_tablesetelem(quad*);
void generate_assign(quad*);
void generate_jump(quad*);
void generate_eq(quad*);
void generate_noteq(quad*);
void generate_greater(quad*);
void generate_greatereq(quad*);
void generate_less(quad*);
void generate_lesseq(quad*);
void generate_nop(quad*);
void generate_relational(vmopcode, quad*);
void generate_not(quad*);
void generate_or(quad*);
void generate_and(quad*);
void generate_call(quad*);
void generate_getretval(quad*);
void generate_param(quad*);
void generate_uminus(quad *q);
void binary();

void generate_instructions();

void print_instructions();
void print_opi(FILE*, vmopcode);
void push_funcstack(st_entry* f);

void printMagicNumber(FILE *fp);
void printArrays(FILE *fp);
void printCode(FILE *fp);

st_entry *pop_funcstack();
st_entry* top_funcstack();