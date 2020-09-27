#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "symbol_table.h"

#define KNRM "\x1B[0m"
#define KYEL "\x1B[33m"
#define KRED "\x1B[31m"
#define KMAG "\x1B[35m"
#define KGRN "\x1B[32m"
#define KBLU "\x1B[34m"
#define KCYN "\x1B[36m"
#define KWHT "\x1B[37m"

st_entry *bucket[BUCKET_SIZE];
st_entry *scope_list[20];
st_entry* dummy;
int scope_counter;

// int main()
// {
//     scope_list = malloc(sizeof(st_entry*));

//     var *s1 = create_symbol_var("putsa", 0, 2);
//     func *f1 = create_symbol_func("lala", NULL, 0, 1);
//     var *s2 = create_symbol_var("putsa", 1, 4);

//     init_bucket();
//     init_libfuncs();
//     st_entry *e1 = create_entry(s1, GLOBAL);
//     st_entry *e2 = create_entry(f1, USERFUNC);
//     st_entry *e3 = create_entry(s2, LOCAL);
//     lookup(0, "putsa");
//     // print_list(scope_list[0], 1);
//     print_st();
//     char* name = "print";
//     collisions(name);
// }

int hash(char *name)
{
    char c;
    int result = 0;
    while (c = *name++)
    {
        result += (int)c;
    }
    return result % BUCKET_SIZE;
}

//creates a new symbol table entry and adds it to bucket and scope list
st_entry *create_entry(void *value, st_type type)
{
    st_entry *new = (st_entry *)malloc(sizeof(st_entry));

    new->isActive = 1;
    new->type = type;

    switch (type)
    {
        case GLOBAL:
        new->value.varVal = (var *)value;
        new->name = strdup(new->value.varVal->name);
        new->s_type = var_s;
        printf(KGRN "Symbol Table Global variable \'%s\' created at scope %d\n" KNRM, new->value.varVal->name, new->value.varVal->scope);
        break;
        case LOCAL:
        new->value.varVal = (var *)value;
        new->name = strdup(new->value.varVal->name);
        new->s_type = var_s;
        printf(KGRN "Symbol Table Local variable \'%s\' created at scope %d\n" KNRM, new->value.varVal->name, new->value.varVal->scope);
        break;
        case FORMAL:
        {
            new->value.varVal = (var *)value;
            new->name = strdup(new->value.varVal->name);
            new->s_type = var_s;
            printf(KGRN "Symbol Table Formal Argument \'%s\' created at scope %d\n" KNRM, new->value.varVal->name, new->value.varVal->scope);
            break;
        }
        case USERFUNC:
        new->value.funcVal = (func *)value;
        new->name = strdup(new->value.funcVal->name);
        new->s_type = programfunc_s;
        printf(KGRN "Symbol Table User Function \'%s\' created at scope %d\n" KNRM, new->value.funcVal->name, new->value.funcVal->scope);

        break;
        case LIBFUNC:
        {
            new->value.funcVal = (func *)value;
            new->name = strdup(new->value.funcVal->name);
            new->s_type = libfunc_s;
            printf(KGRN"Symbol Table Library Function \'%s\' created at scope %d\n"KNRM, new->value.funcVal->name, new->value.funcVal->scope);

            break;
        }
    }

    //add new entry to bucket and scope list
    if (!insert_entry(new))
    {
        printf("Error inserting entry\n");
    }
    new->bucket_next = NULL;
    new->scope_next = NULL;
    // printf("Symbol Table Entry \'%s\' at scope %d created\n", new->value.varVal->name,  new->value.varVal->scope);
    return new;
}

//create a variable symbol
var *create_symbol_var(const char *name, unsigned int scope, unsigned int line)
{
    var *new = (var *)malloc(sizeof(new));
    new->name = strdup(name);
    new->scope = scope;
    new->line = line;

    // printf("new var: name = %s\t scope = %d\t line=%d\n", new->name, new->scope, new->line);
    return new;
}

//create a function symbol
func *create_symbol_func(const char *name, arguments *args, unsigned int scope, unsigned int line)
{
    func *new = (func *)malloc(sizeof(new));
    new->name = strdup(name);
    new->scope = scope;
    new->line = line;
    // new->totallocals = 0;
    if (args)
    {
        new->args = args;
    }

    // printf("new var: name = %s\t scope = %d\t line=%d\n", new->name, new->scope, new->line);

    return new;
}


//initialize bucket 
int init_bucket()
{
    int i = 0;
    for (i = 0; i < BUCKET_SIZE; i++)
    {
        bucket[i] = NULL;
    }
    return 1;
}

//function to add new entry to bucket and scope list
int insert_entry(st_entry *new_entry)
{
    char *name;
    int idx;
    int result = 0;
    switch(new_entry->type)
    {
        case GLOBAL:
        case LOCAL:
        case FORMAL:
        {
            name = strdup(new_entry->value.varVal->name);
            idx = hash(name);

            //insert to bucket list
            if (!insert_bucket_list(idx, new_entry))
            {
                printf("error inserting to bucket list\n");
                return 0;
            }

            //insert to scope list
            if(!insert_scope_list(new_entry->value.varVal->scope, new_entry)){
                printf("Error inserting to scope list\n");
                return 0;
            }

            result = 1;
            break;

        }
        case USERFUNC:
        case LIBFUNC:
        {
            name = strdup(new_entry->value.funcVal->name);
            idx = hash(name);

            //insert to bucket list
            if (!insert_bucket_list(idx, new_entry))
            {
                printf("error inserting to bucket list\n");
                return 0;
            }

            //insert to scope list
            insert_scope_list(new_entry->value.funcVal->scope, new_entry);

            result = 1;
            break;
        }
    }
    return result;
}

//insert new entry to bucket list at bucket[idx]
int insert_bucket_list(int idx, st_entry *new)
{
    st_entry *tmp = bucket[idx];
    if (tmp == NULL)
    {
        // printf("bucket:added at the beggining\n");
        bucket[idx] = new;
        return 1;
    }
    while (tmp->bucket_next != NULL)
    {
        tmp = tmp->bucket_next;
    }
    tmp->bucket_next = new;
    // printf("bucket:added at the end\n");
    return 1;
}


//insert new entry to scope list at scope_table[scope]
int insert_scope_list(int scope, st_entry *new)
{

    if(!scope_list[scope]) scope_list[scope] = NULL;

    st_entry *tmp = scope_list[scope];
    // scope_list = (st_entry **)realloc(scope_list, (scope_counter + 1) * sizeof(st_entry **));

    scope_counter++;

    if (tmp == NULL)
    {
        scope_list[scope] = new;
        // printf("scope:added at the beggining\n");

        return 1;
    }
    while (tmp->scope_next != NULL)
    {
        tmp = tmp->scope_next;
    }
    tmp->scope_next = new;
    // printf("scope:added at the end\n");
    // if(scope_list[scope+1]){
    //     printf("init %d\n", scope+1);
    //     scope_list[scope+1] = NULL;
    // }
    // scope_list = (st_entry**)realloc(scope_list, (counter+1)*sizeof(st_entry**));
    // prev = counter;
    // if(scope > prev){
    //     printf("addind dummy from %d to %d\n", prev, scope);
    //     for(i=prev; i<scope; i++){
    //         scope_list[i] = dummy;
    //     }
    // }
    // counter++;
    return 1;
}


//print the lists, flag=0 for bucket, flag=1 for scope
void print_list(st_entry *head, int flag)
{
    st_entry *tmp = head;
    while (tmp != NULL)
    {
        printf("Symbol name: %s\t scope=%d\n", tmp->value.varVal->name, tmp->value.varVal->scope);
        if(flag == 0)
            tmp = tmp->bucket_next;
        else if(flag == 1)
            tmp = tmp->scope_next;
        else{
            printf("Wrong flag: 0 for bucket 1 for scope\n");
            return;
        }
    }
}

st_entry *lookup(int scope, char *name)
{
    st_entry *tmp = (st_entry*)scope_list[scope];
    while (tmp)
    {
        if(tmp->isActive==-20) continue;
        switch (tmp->type)
        {
            case GLOBAL:
            case LOCAL:
            case FORMAL:
            {
                if (!strcmp(tmp->value.varVal->name, name))
                {
                // printf(KCYN"LOOKUP: symbol \'%s\' found in scope %d\n"KNRM , tmp->value.varVal->name, tmp->value.varVal->scope);
                    return tmp;
                }
                break;
            }
            case USERFUNC:
            case LIBFUNC:
            {
                if (!strcmp(tmp->value.funcVal->name, name))
                {
                // printf(KCYN"LOOKUP: symbol \'%s\' found\n"KNRM, tmp->value.funcVal->name);
                    return tmp;
                }
            }
        }
        tmp = tmp->scope_next;
    }
    return NULL;
}

void print_st(){
    int i;
    st_entry* tmp;
    i=0;
    while(i<scope_counter){
        tmp = (st_entry*)scope_list[i];
        if(!tmp){
            i++;
            continue;
        }
        printf(KGRN"Scope %d: \n"KNRM, i);
        while(tmp){
            switch (tmp->type)
            {
                case GLOBAL:
                printf("\n\tName: %-12s\tLine: %-6d\tActive: %-12d\tType: GLOBAL", tmp->value.varVal->name, tmp->value.varVal->line, tmp->isActive);
                break;
                case LOCAL:
                printf("\n\tName: %-12s\tLine: %-6d\tActive: %-12d\tType: LOCAL", tmp->value.varVal->name, tmp->value.varVal->line, tmp->isActive);
                break;
                case FORMAL:
                printf("\n\tName: %-12s\tLine: %-6d\tActive: %-12d\tType: FORMAL", tmp->value.varVal->name, tmp->value.varVal->line, tmp->isActive);
                break;
                case USERFUNC:
                printf("\n\tName: %-12s\tLine: %-6d\tActive: %-12d\tType: USERFUNC", tmp->value.funcVal->name, tmp->value.funcVal->line, tmp->isActive);
                break;
                case LIBFUNC:
                printf("\n\tName: %-12s\tLine: %-6d\tActive: %-12d\tType: LIBFUNC", tmp->value.funcVal->name, tmp->value.funcVal->line, tmp->isActive);
                break;
                default:
                printf("invalid\n");
            }
            printf("\n");
            tmp=tmp->scope_next;
        }
        i++;
    }
}


int init_libfuncs(){
    func* lib_func;
    st_entry* tmp;
    lib_func = create_symbol_func("print", NULL, 0, 0);
    tmp = create_entry(lib_func, LIBFUNC);
    //input
    lib_func = create_symbol_func("input", NULL, 0, 0);
    tmp = create_entry(lib_func, LIBFUNC);

    lib_func = create_symbol_func("obj_mem_keys", NULL, 0, 0);
    tmp = create_entry(lib_func, LIBFUNC);

    lib_func = create_symbol_func("obj_cp", NULL, 0, 0);
    tmp = create_entry(lib_func, LIBFUNC);

    lib_func = create_symbol_func("total_args", NULL, 0, 0);
    tmp = create_entry(lib_func, LIBFUNC);

    lib_func = create_symbol_func("argument", NULL, 0, 0);
    tmp = create_entry(lib_func, LIBFUNC);

    lib_func = create_symbol_func("typeof", NULL, 0, 0);
    tmp = create_entry(lib_func, LIBFUNC);

    lib_func = create_symbol_func("strtonum", NULL, 0, 0);
    tmp = create_entry(lib_func, LIBFUNC);

    lib_func = create_symbol_func("sqrt", NULL, 0, 0);
    tmp = create_entry(lib_func, LIBFUNC);

    lib_func = create_symbol_func("cos", NULL, 0, 0);
    tmp = create_entry(lib_func, LIBFUNC);

    lib_func = create_symbol_func("sin", NULL, 0, 0);
    tmp = create_entry(lib_func, LIBFUNC);

    return 1;
}

int collisions(char* name){
    st_entry* tmp = scope_list[0];
    while(tmp){
        if(!strcmp(name, tmp->value.funcVal->name) && tmp->type == LIBFUNC){
            printf(KRED"Error: Collision found with libfunc %s\n"KNRM, tmp->value.funcVal->name);
            return 1;
        }
        tmp = tmp->scope_next;
    }
    return 0;
}

void hide(int scope){
    st_entry* tmp = scope_list[scope];
    while(tmp){
        tmp->isActive = 0;
        tmp=tmp->scope_next;
    }
}

void free_arg_list(arguments *head)
{
    arguments *tmp;

    while (head != NULL)
    {
        //printf("lala\n");
        tmp = head;
        head = head->next;
        tmp=NULL;
    }
    printf(KYEL"ARGUMENTS FREE\n"KNRM);
}



char * newUnnamedFunc(){

    static int i = 1;
    char * prefix = "_f";
    char * funcname;
    char temp[10];
    sprintf(temp, "%d", i);
    funcname = (char*)malloc(sizeof(prefix) + sizeof(temp));
    strcpy(funcname,prefix);
    funcname = strcat(funcname,temp);
    i++;
    return funcname;
}