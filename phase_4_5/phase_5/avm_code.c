#include "avm_code.h"
#include <math.h>

#define PI 3.14159265

#define KNRM "\x1B[0m"
#define KYEL "\x1B[33m"
#define KRED "\x1B[31m"
#define KMAG "\x1B[35m"
#define KGRN "\x1B[32m"
#define KBLU "\x1B[34m"
#define KCYN "\x1B[36m"
#define KWHT "\x1B[37m"

//arithmetic operations
#define execute_add execute_arithmetic
#define execute_sub execute_arithmetic
#define execute_mul execute_arithmetic
#define execute_div execute_arithmetic
#define execute_mod execute_arithmetic

//relational operations
#define execute_jge execute_relop
#define execute_jgt execute_relop
#define execute_jle execute_relop
#define execute_jlt execute_relop
#define execute_and execute_relop
#define execute_or execute_relop

#define AVM_STACKSIZE 4096
#define AVM_WIPEOUT(m) memset((&m), 0, sizeof(m))
#define AVM_STACKENV_SIZE 4
#define AVM_MAX_INSTRUCTIONS 300

#define AVM_NUMACTUALS_OFFSET +4
#define AVM_SAVEDPC_OFFSET +3
#define AVM_SAVEDTOP_OFFSET +2
#define AVM_SAVEDTOPSP_OFFSET +1

#define AVM_ENDING_PC currInst


avm_memcell stack[AVM_STACKSIZE];
avm_memcell ax, bx, cx, retval; //voh8itikoi kataxwrhtes
unsigned top, topsp;

double consts_getnumber(unsigned idx);
char *consts_getstring(unsigned idx);
char *libfuncs_getused(unsigned idx);


unsigned totalActuals = 0;

unsigned char executionFinished = 0;
unsigned pc = 0;
unsigned currLine = 0;
// unsigned		currInst = 0;
extern unsigned int currInst;
extern instruction *instructions;
extern unsigned globals;

extern double *numConsts;
extern char **stringConsts;
extern char **namedLibfuncs;
extern userfunc **userFuncs;


double consts_getnumber(unsigned idx)
{
	return numConsts[idx];
}

char *consts_getstring(unsigned idx)
{
	return stringConsts[idx];
}

char *libfuncs_getused(unsigned idx)
{
	return namedLibfuncs[idx];
}

userfunc *avm_getfuncinfo(unsigned address)
{
	int tmp = 0;
	if(userFuncs[tmp == address]){
		return userFuncs[tmp];
	}
	while (userFuncs[tmp]->address != address)
	{
		// printf("lala\n");
		printf("addr = %d\n", userFuncs[tmp]->address);
		if (userFuncs[tmp]->address == address)
		{
			// printf("idx = %d\n", tmp);
			return userFuncs[tmp];
		}
		if (userFuncs[tmp] == NULL)
		{
			printf("ERROR: out of bounds\n");
			executionFinished = 1;
			return NULL;
		}
		tmp++;
	}
}

typedef void (*execute_func_t)(instruction *);

execute_func_t executeFuncs[] = {
	execute_add,
	execute_sub,
	execute_mul,
	execute_div,
	execute_mod,
	execute_and,
	execute_or,
	0, //execute_not
	execute_jeq,
	0, //execute_jne,
	execute_jle,
	execute_jge,
	execute_jlt,
	execute_jgt,
	execute_call,
	execute_newtable,
	execute_tablegetelem,
	execute_tablesetelem,
	0, // execute_nop
	execute_jump,
	execute_pusharg,
	execute_assign,
	execute_funcenter,
	execute_funcexit
	};
//some shit for da functions that i dont understand

typedef double (*arithmetic_func_t)(double x, double y);

arithmetic_func_t arithmeticFuncs[] = {
	add_impl,
	sub_impl,
	mul_impl,
	div_impl,
	mod_impl};

typedef int (*relop_func_t)(double x, double y);

relop_func_t relopFuncs[] = {
	jle_impl,
	jge_impl,
	jlt_impl,
	jgt_impl

};

tobool_func_t toboolFuncs[] = {
	number_tobool,
	string_tobool,
	bool_tobool,
	table_tobool,
	userfunc_tobool,
	libfunc_tobool,
	nil_tobool,
	undef_tobool};

char *typeStrings[] = {
	"number",
	"string",
	"bool",
	"table",
	"userfunc",
	"libfunc",
	"nil",
	"undef"};

typedef void (*memclear_func_t)(avm_memcell *);

memclear_func_t memclearFuncs[] = {
	0, //number
	memclear_string,
	0, //bool
	memclear_table,
	0,
	0,
	0,
	0};

unsigned avm_get_envvalue(unsigned i)
{
	// printf("AVM_GET_ENVVALUE: stack[%d]->type = %d\n", i , stack[i].type);
	assert(stack[i].type == number_m);
	unsigned val = (unsigned)stack[i].data.numVal;
	assert(stack[i].data.numVal);
	return val;
}

void avm_dec_top()
{
	if (!top)
	{
		printf("ERROR: stack overflow!\n");
		executionFinished = 1;
	}
	else
	{
		--top;
	}
}

void avm_push_envvalue(unsigned val)
{
	stack[top].type = number_m;
	stack[top].data.numVal = val;
	avm_dec_top();
}

void avm_callsaveenvironment(void)
{
	avm_push_envvalue(totalActuals);
	avm_push_envvalue(pc + 1);
	avm_push_envvalue(top + totalActuals + 2);
	avm_push_envvalue(topsp);
}

typedef void (*library_func_t)(void);
library_func_t avm_getlibraryfunc(char *id);

library_func_t libFuncs[] = {
	libfunc_print,
	libfunc_totalArguments,
	libfunc_argument,
	libfunc_typeof,
	libfunc_sqrt,
	libfunc_cos,
	libfunc_sin
	};

library_func_t avm_getlibraryfunc(char *id)
{
	if (!strcmp(id, "print"))
	{
		return libFuncs[0];
	}
	if (!strcmp(id, "totalArguments"))
	{
		return libFuncs[1];
	}
	if (!strcmp(id, "argument"))
	{
		return libFuncs[2];
	}
	if (!strcmp(id, "typeof"))
	{
		return libFuncs[3];
	}
	if (!strcmp(id, "sqrt"))
	{
		return libFuncs[4];
	}
	if (!strcmp(id, "cos"))
	{
		return libFuncs[5];
	}
	if (!strcmp(id, "sin"))
	{
		return libFuncs[6];
	}
}

unsigned avm_totalactuals()
{
	return avm_get_envvalue(topsp + AVM_NUMACTUALS_OFFSET);
	// AVM_NUMACTUALS_OFFSET einai to plh8os twn arguments
}

avm_memcell *avm_getactual(unsigned i)
{
	assert(i < avm_totalactuals());
	return &stack[topsp + AVM_STACKENV_SIZE + 1 + i];
}

void libfunc_print()
{
	unsigned n = avm_totalactuals();
	unsigned i;
	for (i = 0; i < n; i++)
	{
		avm_memcell* tmp = avm_getactual(i);
		// printf("tmp->type=%d\n", tmp->type);
		char *s = avm_tostring(avm_getactual(i));
		// printf(KBLU "--PRINT--\n" KNRM);
		printf(KBLU"%s\n"KNRM,s);
		free(s);
	}
}

void libfunc_typeof(void){

	unsigned n = avm_totalactuals();

	if(n!=1){
		printf("one argument expected in 'typeof'\n");
		executionFinished = 1;

	}else{

		avm_memcellclear(&retval);
		retval.type = string_m;
		retval.data.strVal = strdup(typeStrings[(int)avm_getactual(0)->type]);
		printf("typeof = %s",strdup(typeStrings[(int)avm_getactual(0)->type]));
	}
}

void libfunc_argument(){

    unsigned p_topsp = (avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET));
    avm_memcellclear(&retval);

    if (!p_topsp){
        printf("'argument' called outside of function");
        retval.type = nil_m;
		executionFinished = 1;
    }
    else {
        unsigned i = 0;
        avm_memcell * temp = avm_getactual(0);
        i = temp->data.numVal;
        avm_assign(&retval, &stack[p_topsp + AVM_STACKENV_SIZE + i + 1]);
    }
}

void libfunc_totalArguments()
{
	unsigned p_topsp = avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET);
	avm_memcellclear(&retval);

	if(!p_topsp){
		printf(KRED"total arguments called outside a function"KNRM);
		retval.type = nil_m;
		executionFinished = 1;
	}
	else{
		retval.type = number_m;
		retval.data.numVal = avm_get_envvalue(p_topsp + AVM_NUMACTUALS_OFFSET);
	}
}

void libfunc_sqrt()
{
	unsigned n = avm_totalactuals(0);

	if(n!=1){
		printf("one arguument expected in sqrt!");
		executionFinished = 1;
	}
	else {
		avm_memcell* temp = avm_getactual(0);
		if(temp->type != number_m) {
			printf("not number given in sqrt");
			executionFinished = 1;
		}else{
			avm_memcellclear(&retval);
			retval.type = number_m;
			retval.data.numVal = sqrt(temp->data.numVal);
		}
	}
}

void libfunc_cos()
{
	unsigned n = avm_totalactuals(0);

	if(n!=1){
		printf("one arguument expected in cos!\n");
		executionFinished = 1;
	}
	else {
		avm_memcell* temp = avm_getactual(0);
		if(temp->type != number_m) {
			printf("not number given in cos");
			executionFinished = 1;
		}else{
			avm_memcellclear(&retval);
			retval.type = number_m;
			retval.data.numVal = cos(temp->data.numVal * PI / 180);
		}
	}
}

void libfunc_sin()
{
	unsigned n = avm_totalactuals(0);

	if(n!=1){
		printf("one arguument expected in sin!\n");
		executionFinished = 1;
	}
	else {
		avm_memcell* temp = avm_getactual(0);
		if(temp->type != number_m) {
			printf("not number given in sin");
			executionFinished = 1;
		}else{
			avm_memcellclear(&retval);
			retval.type = number_m;
			retval.data.numVal = sin(temp->data.numVal * PI / 180);
		}
	}
}
void avm_calllibfunc(char *id)
{
	library_func_t f = avm_getlibraryfunc(id);
	if (!f)
	{
		printf("ERROR: Unsupported lifunc %s BIATCH\n", id);
		executionFinished = 1;
	}
	else
	{
		topsp = top;
		totalActuals = 0;
		(*f)();
		if (!executionFinished)
		{
			execute_funcexit((instruction *)0);
		}
	}
}

char *avm_tostring(avm_memcell *arg)
{
	// printf("arg->type = %d\n", arg->type);
	char *s;
	switch (arg->type)
	{
	case number_m:
		s = (char *)malloc(sizeof(double));
		sprintf(s, "%f", arg->data.numVal);
		break;
	case string_m:
		s = strdup(arg->data.strVal);
		break;
	case bool_m:
		s = strdup((&arg->data.boolVal));
		break;
	case table_m:
		s = strdup("table");
		// avm_memcell tmp = *ax;
		printf("tmp->type = %d\n", cx.type);
		avm_memcell tmp_key;
		if(cx.type == string_m){
			s = (char *)malloc(sizeof(double));
			tmp_key.data.numVal = hashChar(cx.data.strVal);
			sprintf(s, "%f", arg->data.tableVal->strIndexed[(int)tmp_key.data.numVal]->value.data.numVal);
		}
		break;
	case userfunc_m:
		printf("AVM_TOSTRING: thats a function you want to print...\n");
		s = (char *)malloc(sizeof(double));

		sprintf(s, "%d", arg->data.funcVal);
		break;
	case libfunc_m:
		s = strdup(arg->data.libfuncVal);
		break;
	case nil_m:
		s = strdup("NULL");
		break;
	case undef_m:
		printf("WARNING: undef type\n");
		s = strdup("<undefined>");
		break;
	default:
		printf("invalid type\n");
		executionFinished = 1;
		return NULL;
	}
	return s;
}

void memclear_string(avm_memcell *m)
{
	assert(m->data.strVal);
	free(m->data.strVal);
}

void memclear_table(avm_memcell *m)
{
	assert(m->data.tableVal);
	avm_tabledecrefcounter(m->data.tableVal);
	printf("paei edw?\n");
}

void avm_memcellclear(avm_memcell *m)
{
	if (m->type != undef_m)
	{
		memclear_func_t f = memclearFuncs[m->type];
		if (f)
		{
			(*f)(m);
		}
		m->type = undef_m;
	}
}

static void avm_initstack()
{
	unsigned i;
	for (i = 0; i < AVM_STACKSIZE; i++)
	{
		AVM_WIPEOUT(stack[i]);
		stack[i].type = undef_m;
	}
}

double add_impl(double x, double y)
{
	return x + y;
}

double sub_impl(double x, double y)
{
	return x - y;
}

double mul_impl(double x, double y)
{
	return x * y;
}

double div_impl(double x, double y)
{
	return x / y;
}

double mod_impl(double x, double y)
{
	return ((unsigned)x) % ((unsigned)y);
}

unsigned char number_tobool(avm_memcell *m)
{
	return m->data.numVal != 0;
}

unsigned char string_tobool(avm_memcell *m)
{
	return m->data.strVal[0] != 0;
}

unsigned char bool_tobool(avm_memcell *m)
{
	return m->data.boolVal;
}

unsigned char table_tobool(avm_memcell *m)
{
	return 1;
}

unsigned char userfunc_tobool(avm_memcell *m)
{
	return 1;
}

unsigned char libfunc_tobool(avm_memcell *m)
{
	return 1;
}

unsigned char nil_tobool(avm_memcell *m)
{
	return 0;
}

unsigned char undef_tobool(avm_memcell *m)
{
	assert(0);
	return 0;
}

unsigned char avm_tobool(avm_memcell *m)
{
	assert(m->type >= 0 && m->type < undef_m);
	printf("m->type = %d\n", m->type);
	return (*toboolFuncs[m->type])(m);
}

int jle_impl(double x, double y)
{
	if (x <= y)
		return 1;
	return 0;
}

int jge_impl(double x, double y)
{
	if (x >= y)
		return 1;
	return 0;
}

int jlt_impl(double x, double y)
{
	if (x < y)
		return 1;
	return 0;
}

int jgt_impl(double x, double y)
{
	if (x > y)
		return 1;
	return 0;
}

void avm_assign(avm_memcell *lv, avm_memcell *rv)
{
	// printf("poutsa\n");
	if (lv == rv)
	{
		return;
	}
	if(lv->type == table_m && rv->type == table_m && lv->data.tableVal == rv->data.tableVal){
		return;
	}
	// printf("gamiesai lala\n");

	if (rv->type == undef_m)
	{
		printf("AVM_WARNING: Assigning from undefined content\n");
	}
	printf("rv->type = %d\n", rv->type);
	avm_memcellclear(lv);

	memcpy(lv, rv, sizeof(avm_memcell));
	printf(KGRN "AVM_ASSIGN: lv->type = %d\n", lv->type);
	switch (lv->type)
	{
	case number_m:
		printf("lv->data = %f\n", lv->data.numVal);
		break;
	case bool_m:
		printf("lv->data = %c\n", (char)lv->data.boolVal);
		break;
	}

	if (lv->type == string_m)
	{
		lv->data.strVal = strdup(rv->data.strVal); //TO NOU
	}
	else
	{
		if (lv->type == table_m)
		{
			avm_tableincrefcounter(lv->data.tableVal);
		}
	}
}

void execute_assign(instruction *i)
{
	// printf("lala\n");
	avm_memcell *lv = avm_translate_operand(i->result, (avm_memcell *)0);
	avm_memcell *rv = avm_translate_operand(i->arg1, &ax);
	assert(lv);
	assert(&stack[AVM_STACKSIZE - 1] >= lv);
	assert(lv > &stack[top] || lv == &retval);
	assert(rv); // to do similar tests
	avm_assign(lv, rv);
}

void execute_cycle(void)
{
	if (executionFinished)
	{
		printf("Execution finished\n");
		return;
	}
	else if (pc == AVM_ENDING_PC)
	{
		executionFinished = 1;
		return;
	}
	else
	{
		assert(pc < AVM_ENDING_PC);
		instruction *instr = instructions + pc;
		assert(instr->opcode >= 0 && instr->opcode <= AVM_MAX_INSTRUCTIONS);
		if (instr->srcLine)
			currLine = instr->srcLine;
		unsigned oldPC = pc;
		printf(KYEL "PC: %d\n" KNRM, pc);
		printf("EXECUTE_CYCLE: opcode = %d\n" KNRM, instr->opcode);
		(*executeFuncs[instr->opcode])(instr);
		if (pc == oldPC)
			++pc;
	}
}

avm_memcell *avm_translate_operand(vmarg *arg, avm_memcell *reg)
{

	switch (arg->type)
	{
	//Variables
	case global_a:
		return &stack[AVM_STACKSIZE - 1 - arg->val];
	case local_a:
		return &stack[topsp - arg->val];
	case formal_a:
		return &stack[topsp + AVM_STACKENV_SIZE + 1 + arg->val];
	case retval_a:
		return &retval;
	//Constants
	case number_a:
	{
		reg->type = number_m;
		reg->data.numVal = consts_getnumber(arg->val);
		return reg;
	}

	case string_a:
	{
		reg->type = string_m;
		reg->data.strVal = strdup(consts_getstring(arg->val));
		return reg;
	}

	case bool_a:
	{
		reg->type = bool_m;
		reg->data.boolVal = arg->val;
		return reg;
	}

	case nil_a:
	{
		reg->type = nil_m;
		return reg;
	}

	//Functions
	case userfunc_a:
	{
		printf("LAALLA\n");
		reg->type = userfunc_m;
		reg->data.funcVal = arg->val;
		//address apo tous pinakes
		return reg;
	}

	case libfunc_a:
	{
		reg->type = libfunc_m;
		reg->data.libfuncVal = strdup(libfuncs_getused(arg->val));
		return reg;
	}
	}
}

void execute_arithmetic(instruction *instr)
{
	avm_memcell *lv = avm_translate_operand(instr->result, (avm_memcell *)0);
	avm_memcell *rv1 = avm_translate_operand(instr->arg1, &ax);
	avm_memcell *rv2 = avm_translate_operand(instr->arg2, &bx);

	assert(lv && (&stack[AVM_STACKSIZE - 1] >= lv && &stack[top] < lv || lv == &retval));
	assert(rv1 && rv2);
	printf("poutses\n");
	if (rv1->type != number_m || rv2->type != number_m)
	{
		if (rv1->type != number_m)
		{
			printf("ERROR: not a number in rv1, rv1->type = %d ! \n", rv1->type);
		}
		if (rv2->type != number_m)
		{
			printf("ERROR: not a number in rv2, rv2->type = %d ! \n", rv2->type);
		}

		executionFinished = 1;
	}
	else
	{
		arithmetic_func_t op = arithmeticFuncs[instr->opcode - add_v];
		avm_memcellclear(lv);
		lv->type = number_m;
		lv->data.numVal = (*op)(rv1->data.numVal, rv2->data.numVal);
		printf("%f (op) %f\n", rv1->data.numVal, rv2->data.numVal);
		printf(KGRN "EXECUTE_ARITHMETIC: lv->type = %d, lv->data = %f\n" KNRM, lv->type, lv->data.numVal);
	}
}
//same for relation op's

void execute_relop(instruction *instr)
{
	assert(instr->result->type == label_a);
	printf("EXECUTE_RELOP\n");
	int result;
	avm_memcell *rv1 = avm_translate_operand(instr->arg1, &ax);
	avm_memcell *rv2 = avm_translate_operand(instr->arg2, &bx);

	if (rv1->type != number_m || rv2->type != number_m)
	{
		printf("EXECUTE_RELOP: equality check only between numbers!! \n ");
		executionFinished = 1;
		return;
	}

	relop_func_t relop = relopFuncs[instr->opcode - jle_v];
	result = (*relop)(rv1->data.numVal, rv2->data.numVal);
	printf("result = %d\n", result);
	if (result == 1 && !executionFinished)
	{
		pc = instr->result->val;
	}
}

void execute_jump(instruction *instr)
{
	assert(instr->result->type == label_a);
	if (!executionFinished)
	{
		pc = instr->result->val;
	}
}

void execute_jeq(instruction *instr)
{

	assert(instr->result->type == label_a);

	avm_memcell *rv1 = avm_translate_operand(instr->arg1, &ax);
	avm_memcell *rv2 = avm_translate_operand(instr->arg2, &bx);

	unsigned char result = 0;

	if (rv1->type == undef_m || rv2->type == undef_m)
		printf(" undef involved in equality check ! \n ");
	else if (rv1->type == nil_m || rv2->type == nil_m)
		result = rv1->type == nil_m && rv2->type == nil_m;
	else if (rv1->type == bool_m || rv2->type == bool_m)
		result = (avm_tobool(rv1) == avm_tobool(rv2));
	else if (rv1->type != rv2->type)
		printf(" %s == %s is illegal ! \n", typeStrings[rv1->type], typeStrings[rv2->type]);
	else
	{
		/*Equality check with dispatching*/

		// unsigned char arg1 = (tobool_func_t)(rv1);
		if (rv1->type == number_m && rv2->type == number_m)
		{
			result = (rv1->data.numVal == rv2->data.numVal);
		}
	}
	if (!executionFinished && result)
		pc = instr->result->val;
}

void execute_call(instruction *instr)
{
	avm_memcell *func = avm_translate_operand(instr->arg1, &ax);

	assert(func);
	avm_callsaveenvironment();
	unsigned oldpc = pc;
	printf("func->type = %d\n", func->type);
	switch (func->type)
	{
	case userfunc_m:
	{

		pc = userFuncs[func->data.funcVal]->address;
		printf("funcval = %d\n", userFuncs[func->data.funcVal]->address );
		assert(pc < AVM_ENDING_PC);
		// assert(instructions[pc] == funcenter_v);
		break;
	}
	case string_m:
		avm_calllibfunc(func->data.strVal);
		break;
	case libfunc_m:
		avm_calllibfunc(func->data.libfuncVal);
		break;

	default:
	{
		char *s = avm_tostring(func);
		printf("CALL: cannot bind %s to function!\n", s);
		executionFinished = 1;
		free(s);
	}
	}
}

void execute_funcenter(instruction *instr)
{
	avm_memcell *func = avm_translate_operand(instr->result, &ax);
	assert(func);
	printf("FUNCSTART: address = %d\n", userFuncs[func->data.funcVal]->address );
	assert(pc == userFuncs[func->data.funcVal]->address ); // func address should match pc
	//callee actions here
	totalActuals = 0;
	userfunc *funcfinfo = avm_getfuncinfo(pc);
	topsp = top;
	printf("lala\n");
	top = top - funcfinfo->localSize;
	printf("funcenter Top = %d\n", top);
}

void execute_funcexit(instruction *instr)
{
	unsigned oldTop = top;
		printf("funcexit TOp = %d\n", top);
	top = avm_get_envvalue(topsp + AVM_SAVEDTOP_OFFSET);
		printf("TOp = %d\n", top);

	pc = avm_get_envvalue(topsp + AVM_SAVEDPC_OFFSET);
	topsp = avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET);
	while (++oldTop <= top)
	{
		avm_memcellclear(&stack[oldTop]);
	}
}

void execute_pusharg(instruction *instr)
{
	avm_memcell *arg = avm_translate_operand(instr->arg1, &ax);
	assert(arg);
	avm_assign(&stack[top], arg);
	++totalActuals;
	avm_dec_top();
}

void execute_newtable(instruction *instr)
{
	avm_memcell *lv = avm_translate_operand(instr->result, (avm_memcell *)0);
	assert(lv && (&stack[AVM_STACKSIZE - 1] >= lv && lv > &stack[top] || lv == &retval));
	// printf("ftanei?\n");
	if(!lv->type==table_m)
	avm_memcellclear(lv);
	lv->type = table_m;
	lv->data.tableVal = avm_tablenew();
	avm_tableincrefcounter(lv->data.tableVal);
}

avm_memcell *avm_tablegetelem(avm_table *table, avm_memcell *index)
{
	if (index->type == number_m)
	{
		int key = hashInt(index->data.numVal);
		printf("TABLEGETELEM: key = %d\n" , key);
		//check content type
		if (table->numIndexed[key]->value.type == number_m)
		{
			printf("value = %f\n", table->numIndexed[key]->value.data.numVal);
		}
		else if (table->numIndexed[key]->value.type == string_m)
		{
			printf("value = %s\n", table->numIndexed[key]->value.data.strVal);
		}
		return &table->numIndexed[key]->value;
	}
	else if (index->type == string_m)
	{
		int key = hashChar(index->data.strVal);
		printf("TABLEGETELEM: key = %d\n", key);

		if (table->strIndexed[key]->value.type == number_m)
		{
			printf("value = %f\n", table->strIndexed[key]->value.data.numVal);
		}
		else if (table->strIndexed[key]->value.type == string_m)
		{
			printf("value = %s\n", table->strIndexed[key]->value.data.strVal);
		}

		return &table->strIndexed[key]->value;
	}
	else
	{
		printf("AVM_TABLEGETELEM: fix the rest of types\n");
	}
}

void avm_tablesetelem(avm_table *table, avm_memcell *index, avm_memcell *content)
{
	if (content->type == number_m)
	{
		if (index->type == number_m)
		{
			//index is number and content is number
			avm_memcell key;
			key.data.numVal = hashInt((int)index->data.numVal);
			key.type = number_m;
			table->numIndexed[(int)key.data.numVal]->key = key;
			printf("key = %d\n", (int)table->numIndexed[(int)key.data.numVal]->key.data.numVal);
			table->numIndexed[(int)key.data.numVal]->value.data.numVal = content->data.numVal;
			table->numIndexed[(int)key.data.numVal]->value.type = number_m;
			printf("value = %f\n", table->numIndexed[(int)key.data.numVal]->value.data.numVal);
		}
		else if (index->type == string_m)
		{
			//index is string and content is number
			printf("string index\n");
			avm_memcell key;
			//find position by hashing the index
			key.data.numVal = hashChar(index->data.strVal);
			key.type = number_m;
			table->strIndexed[(int)key.data.numVal]->key = key;
			printf("key = %d\n", (int)table->strIndexed[(int)key.data.numVal]->key.data.numVal);
			// printf("lala\n");
			table->strIndexed[(int)key.data.numVal]->value.data.numVal = content->data.numVal;
			table->strIndexed[(int)key.data.numVal]->value.type = number_m;
			printf("value = %f\n", table->strIndexed[(int)key.data.numVal]->value.data.numVal);
		}
	}
	else if (content->type == string_m)
	{
		if (index->type == number_m)
		{
			//index is number and content is string
			avm_memcell key;
			key.data.numVal = hashInt((int)index->data.numVal);
			key.type = number_m;
			table->numIndexed[(int)key.data.numVal]->key = key;
			printf("key = %d\n", (int)table->numIndexed[(int)key.data.numVal]->key.data.numVal);
			table->numIndexed[(int)key.data.numVal]->value.data.strVal = strdup(content->data.strVal);
			table->numIndexed[(int)key.data.numVal]->value.type = string_m;
			printf("value = %s\n", table->numIndexed[(int)key.data.numVal]->value.data.strVal);
		}
		else if (index->type == string_m)
		{
			//index is string and content is number
			printf("string index\n");
			avm_memcell key;
			//find position by hashing the index
			key.data.numVal = hashChar(index->data.strVal);
			key.type = number_m;
			table->strIndexed[(int)key.data.numVal]->key = key;
			printf("key = %d\n", (int)table->strIndexed[(int)key.data.numVal]->key.data.numVal);
			// printf("lala\n");
			table->strIndexed[(int)key.data.numVal]->value.data.strVal = strdup(content->data.strVal);
			table->strIndexed[(int)key.data.numVal]->value.type = string_m;
			printf("value = %s\n", table->strIndexed[(int)key.data.numVal]->value.data.strVal);
		}
	}
	else if (content->type == table_m){
		content->data.tableVal->refCounter++;
			printf("to content einai table\n");
		if (index->type == number_m)
		{
			//index is number and content is string
			avm_memcell key;
			key.data.numVal = hashInt((int)index->data.numVal);
			key.type = number_m;
			table->numIndexed[(int)key.data.numVal]->key = key;
			printf("key = %d\n", (int)table->numIndexed[(int)key.data.numVal]->key.data.numVal);
			table->numIndexed[(int)key.data.numVal]->value.data.tableVal = content->data.tableVal;
			table->numIndexed[(int)key.data.numVal]->value.type = table_m;
			printf("value = %d\n", table->numIndexed[(int)key.data.numVal]->value.data.tableVal->refCounter);
		}
		else if (index->type == string_m)
		{
			//index is number and content is string
			avm_memcell key;
			key.data.numVal = hashChar(index->data.strVal);
			key.type = number_m;
			table->strIndexed[(int)key.data.numVal]->key = key;
			printf("key = %d\n", (int)table->strIndexed[(int)key.data.numVal]->key.data.numVal);
			table->strIndexed[(int)key.data.numVal]->value.data.tableVal = content->data.tableVal;
			table->strIndexed[(int)key.data.numVal]->value.type = table_m;
			printf("value = %d\n", table->strIndexed[(int)key.data.numVal]->value.data.tableVal->refCounter);
		}
	}
}

void execute_tablegetelem(instruction *instr)
{

	avm_memcell *lv = avm_translate_operand(instr->result, (avm_memcell *)0);
	avm_memcell *t = avm_translate_operand(instr->arg1, (avm_memcell *)0);
	avm_memcell *i = avm_translate_operand(instr->arg2, &ax);
	cx = *i;



	assert(lv && (&stack[AVM_STACKSIZE - 1] >= lv && &stack[top] < lv || lv == &retval));
	assert(t && &stack[AVM_STACKSIZE - 1] >= t && &stack[top] < t);
	assert(i);
	
	avm_memcellclear(lv);
	lv->type = nil_m;

	if (t->type != table_m)
	{
		printf("Illegal use of type %s as table ! \n", typeStrings[t->type]);
	}
	else
	{
		avm_memcell *content = avm_tablegetelem(t->data.tableVal, i);
		printf("content->type = %d\n", content->type);
		if (content)
			avm_assign(lv, content);
		else
		{
			char *ts = avm_tostring(t);
			char *is = avm_tostring(i);

			printf("%s[%s] not found ! \n", ts, is);
			free(ts);
			free(is);
		}
	}
}

void execute_tablesetelem(instruction *instr)
{
	avm_memcell *t = avm_translate_operand(instr->arg1, (avm_memcell *)0);
	avm_memcell *i = avm_translate_operand(instr->arg2, &ax);
	avm_memcell *c = avm_translate_operand(instr->result, &bx);

	assert(t && &stack[AVM_STACKSIZE - 1] >= t && &stack[top] < t);
	assert(i && c);

	if (t->type != table_m)
		printf("illegal use of type %s as table ! \n", typeStrings[t->type]);
	else
		avm_tablesetelem(t->data.tableVal, i, c);
}

void avm_tableincrefcounter(avm_table *t)
{
	++t->refCounter;
}

void avm_tabledecrefcounter(avm_table *t)
{
	printf("refcounter = %d\n", t->refCounter); 
	assert(t->refCounter > 0);
	if (!--t->refCounter)
	{
		avm_tabledestroy(t);
	}
}

void avm_tablebucketsinit(avm_table_bucket **p)
{
	unsigned i;
	for (i = 0; i < AVM_TABLE_HASHSIZE; ++i)
	{
		p[i] = (avm_table_bucket *)malloc(sizeof(avm_table_bucket));
	}
}

avm_table *avm_tablenew(void)
{
	avm_table *t = (avm_table *)malloc(sizeof(avm_table));
	AVM_WIPEOUT(*t);

	t->refCounter = 0;
	t->total_num = 0;
	t->total_str = 0;

	avm_tablebucketsinit(t->numIndexed);
	avm_tablebucketsinit(t->strIndexed);

	return t;
}

void avm_tablebucketsdestroy(avm_table_bucket **p)
{
	unsigned i;

	for (i = 0; i < AVM_TABLE_HASHSIZE; ++i, ++p)
	{
		avm_table_bucket* b;
		for (b = *p; b;)
		{

			avm_table_bucket *del = b;
			b = b->next;
			avm_memcellclear(&del->key);
			avm_memcellclear(&del->value);
			free(del);
		}
		p[i] = (avm_table_bucket *)0;
	}
}

void avm_tabledestroy(avm_table *t)
{
	avm_tablebucketsdestroy(t->strIndexed);
	avm_tablebucketsdestroy(t->numIndexed);
	free(t);
}

int hashChar(char *name)
{
	char c;
	int result = 0;
	while (c = *name++)
	{
		result += (int)c;
	}
	return result % AVM_TABLE_HASHSIZE;
}

int hashInt(int idx)
{
	return idx % AVM_TABLE_HASHSIZE;
}

// void insert_to_bucket(avm_table_bucket** head, avm_memcell key, avm_memcell content){
// 	avm_table_bucket *tmp = *head[key];

// }

int main()
{
	binary();
	avm_initstack();
	top = AVM_STACKSIZE - 1 - globals;
	topsp = top;
	while (executionFinished == 0)
		execute_cycle();
}


//TODO: at table insert: if cell->type == nil_m insert at cell else go to next, repeat until nil cell is found