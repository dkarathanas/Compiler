#include <stdbool.h>

/*--------------------------
DEFINITIONS

----------------------------*/

#define BUCKET_SIZE 1000

/*----------------------------
STRUCTS
----------------------------*/



typedef struct Variable{
    const char* name;
    unsigned int scope;
    unsigned int line;
} var;

typedef struct arguments{
    var* arg;
    struct arguments* next;
} arguments;

typedef struct return_list{
    int label;

    struct return_list* next;
}return_list;

typedef struct Function{
    const char* name;
    arguments* args; //list of arguments
    unsigned int scope;
    unsigned int line;
    int totallocals;
    unsigned int iaddress;
    return_list* r_list;
} func;


typedef enum SymbolTableType{
    GLOBAL,
    LOCAL,
    FORMAL,
    USERFUNC,
    LIBFUNC,
    DUMMY
}st_type;

typedef enum scopespace_t {
    programvar,
    funclocal,
    formalarg
} scopespace_t;

typedef enum symbol_t {
    var_s,
    programfunc_s,
    libfunc_s
} symbol_t;

typedef struct SymbolTableEntry{
    int isActive;
    union{
        var *varVal;
        func *funcVal;
    } value;
    enum SymbolTableType type;
    
    scopespace_t space;
    symbol_t s_type;
    unsigned offset;
    char* name;
    

    struct SymbolTableEntry *bucket_next;
    struct SymbolTableEntry *scope_next;
} st_entry;

/*
----------------------------
FUNCTION PROTOTYPES
----------------------------
*/

int hash(char*);

st_entry* create_entry(void*, st_type);
var *create_symbol_var(const char *, unsigned int, unsigned int);
func *create_symbol_func(const char *, arguments *, unsigned int, unsigned int);
int init_bucket();
int insert_entry(st_entry*);
int insert_bucket_list(int, st_entry*);
int insert_scope_list(int, st_entry*);
void print_list(st_entry *head, int flag);
st_entry *lookup(int scope, char *name);

int init_libfuncs();
void print_st();
int collisions(char*);
void hide(int);
void free_arg_list(arguments*);


char * newUnnamedFunc();