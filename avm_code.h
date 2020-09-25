#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "t_code.h"



struct avm_table;
struct avm_table_bucket;
struct avm_memcell;

typedef enum avm_memcell_t{
	number_m,
	string_m,
	bool_m,
	table_m,
	userfunc_m,
	libfunc_m,
	nil_m,
	undef_m
} avm_memcell_t;

#define AVM_TABLE_HASHSIZE 211

typedef struct avm_table
{
	unsigned refCounter;
	struct avm_table_bucket *strIndexed[AVM_TABLE_HASHSIZE];
	struct avm_table_bucket *numIndexed[AVM_TABLE_HASHSIZE];
	unsigned total_num;
	unsigned total_str;
} avm_table;

typedef struct avm_memcell{
	avm_memcell_t type;
	union	{
			double numVal;
			char*  strVal;
			unsigned char boolVal;
			avm_table*  tableVal;
			unsigned  funcVal; //address of function
			char*  libfuncVal;
			}data;	
}avm_memcell;

typedef struct avm_table_bucket
{
	avm_memcell key;
	avm_memcell value;
	struct avm_table_bucket *next;
} avm_table_bucket;



typedef unsigned char (*tobool_func_t)(avm_memcell*);

avm_memcell *avm_translate_operand(vmarg * arg , avm_memcell * reg);
void execute_cycle(void);

void execute_arithmetic(instruction* instr);
void execute_relop(instruction* instr);
void execute_jeq(instruction *instr);
void execute_newtable(instruction *instr);
void execute_jump(instruction* instr);
void execute_call(instruction* instr);
void execute_tablesetelem(instruction *instr);
void execute_tablegetelem(instruction *instr); // void avm_error(char * error_str);
	unsigned avm_get_envvalue(unsigned i);
void avm_push_envvalue(unsigned val);
void avm_callsaveenvironment();

double consts_getnumber(unsigned idx);
char *consts_getstring(unsigned idx);
char *libfuncs_getused(unsigned idx);
userfunc *avm_getfuncinfo(unsigned address);

	// avm_memcell*  avm_tablegetelem(avm_table* table,avm_memcell* index);
	// void avm_tablesetelem(avm_table* table ,avm_memcell* index,avm_memcell* content);
	double add_impl(double x, double y);
double sub_impl(double x , double y);
double mul_impl(double x , double y);
double div_impl(double x , double y);
double mod_impl(double x , double y);
int jle_impl(double, double);
int jge_impl(double, double);
int jlt_impl(double, double);
int jgt_impl(double, double);
void execute_assign(instruction* i);
void execute_call(instruction *instr);
void execute_funcenter(instruction *instr);
void execute_funcexit(instruction *instr);
void execute_pusharg(instruction *instr);

	unsigned char number_tobool(avm_memcell *m);
unsigned char string_tobool(avm_memcell *m);
unsigned char bool_tobool(avm_memcell *m);
unsigned char table_tobool(avm_memcell *m);
unsigned char userfunc_tobool(avm_memcell *m);
unsigned char libfunc_tobool(avm_memcell *m);
unsigned char nil_tobool(avm_memcell *m);
unsigned char undef_tobool(avm_memcell *m);
unsigned char avm_tobool(avm_memcell *m);
void avm_memcellclear(avm_memcell *m);

void memclear_string(avm_memcell *m);
void memclear_table(avm_memcell *m);
void avm_assign(avm_memcell *lv, avm_memcell *rv);
unsigned avm_totalactuals();
avm_memcell* avm_getactual(unsigned i);
void libfunc_print();
void libfunc_typeof(void);
void libfunc_argument();
void libfunc_totalArguments();
void libfunc_sqrt();
void libfunc_cos();
void libfunc_sin();


void avm_calllibfunc(char* id);
char *avm_tostring(avm_memcell *arg);

void avm_tableincrefcounter(avm_table *t);
void avm_tabledecrefcounter(avm_table *t);
void avm_tablebucketsinit(avm_table_bucket **p);
avm_table *avm_tablenew(void);
avm_table* avm_tablenew(void);
void avm_tablebucketsdestroy(avm_table_bucket * *p);
void avm_tabledestroy(avm_table * t);

void avm_tablesetelem(avm_table *table, avm_memcell *index, avm_memcell *content);
avm_memcell *avm_tablegetelem(avm_table *table, avm_memcell *index);
int hashChar(char *name);
int hashInt(int idx);