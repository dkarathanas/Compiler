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

typedef struct Function{
    const char* name;
    arguments* args; //list of arguments
    unsigned int scope;
    unsigned int line;
} func;


typedef enum SymbolTableType{
    GLOBAL,
    LOCAL,
    FORMAL,
    USERFUNC,
    LIBFUNC,
    DUMMY
}st_type;

typedef struct SymbolTableEntry{
    int isActive;
    union{
        var *varVal;
        func *funcVal;
    } value;
    enum SymbolTableType type;

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