#include "t_code.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


instruction* instructions = (instruction*)0;
unsigned total_inst = 0;
unsigned int currInst = 0;

double* numConsts;
char** stringConsts;
char** namedLibfuncs;
userfunc** userFuncs;

extern quad *quads;
extern unsigned total;
extern unsigned int currQuad;
extern unsigned int currprocquad;
extern unsigned programVarOffset;
incomplete_jump **ij_head = (incomplete_jump **)0;
unsigned ij_total = 0;
funcstack** funcstack_head = (funcstack**)0;

unsigned int num_idx = 0;
unsigned int str_idx = 0;
unsigned int lib_idx = 0;
unsigned int func_idx = 0;

unsigned consts_newnumber(double val){
    
    if(num_idx == 0){
        numConsts = (double*)malloc(sizeof(double));
        numConsts[num_idx++] = val;
        printf("lala\n");
        return num_idx-1;
    }
    else{
        unsigned int tmp = 0;
        while (tmp < num_idx)
        {
            if (val == numConsts[tmp] && tmp>0)
            {
                printf("tmp = %d\nval = %f, table= %f\n", tmp, val, numConsts[tmp]);
                return tmp;
            }
            tmp++;
        }
        numConsts = (double*)realloc(numConsts, (num_idx+1)*sizeof(double));
    }
    // printf("")
    numConsts[num_idx++] = val;
    return num_idx-1;
}

unsigned consts_newstring(char *s){
    
    if(str_idx == 0){
        stringConsts = (char**)malloc(sizeof(char*));
    }
    else{
        if (s == NULL)
        {
            return str_idx;
        }
        unsigned int tmp = 0;
        while (tmp < str_idx)
        {
            if (!strcmp(s, stringConsts[tmp]))
            {
                return tmp;
            }
            tmp++;
        }
        stringConsts = (char**)realloc(stringConsts, (str_idx+1)*sizeof(char*));
    }
    stringConsts[str_idx++] = strdup(s);
    return str_idx-1;
}

unsigned libfuncs_newused(char *s)
{
    if (lib_idx == 0)
    {
        namedLibfuncs = (char **)malloc(sizeof(char *));
    }
    else
    {
        if (s == NULL)
        {
            return lib_idx;
        }
        unsigned int tmp = 0;
        while (tmp < lib_idx)
        {
            if (!strcmp(s, namedLibfuncs[tmp]))
            {
                return tmp;
            }
            tmp++;
        }
        namedLibfuncs = (char **)realloc(namedLibfuncs, (lib_idx + 1) * sizeof(char *));
    }
    namedLibfuncs[lib_idx++] = strdup(s);
    return lib_idx - 1;
}

unsigned userfuncs_newfunc(st_entry* f){
    static int temp = 0;
    
    if(func_idx == 0){
        userFuncs = (userfunc**)malloc(sizeof(userfunc*));
    }
    else{
        if(f==NULL){
            return func_idx;
        }
        unsigned int tmp = 0;
        while(tmp<func_idx){
            if((f->value.funcVal->iaddress ==  userFuncs[tmp]->address)){
                return tmp;
            }
            tmp++;
        }
    }
    if(f==NULL){
        return func_idx;
    }
    // else if (func_idx>=1){
    //     if(f->value.funcVal->iaddress == userFuncs[func_idx-1]->address){
    //         return func_idx;
    //     }
    // }
    if(temp%2==0){
        userFuncs = (userfunc**)realloc(userFuncs, (func_idx+1)*sizeof(userfunc*));
        userFuncs[func_idx] = (userfunc*)malloc(sizeof(userfunc));
        userFuncs[func_idx]->address = f->value.funcVal->iaddress;
        userFuncs[func_idx]->localSize = f->value.funcVal->totallocals;
        userFuncs[func_idx]->id = strdup(f->name);
        printf("%d %d %s\n",userFuncs[func_idx]->address, userFuncs[func_idx]->localSize, userFuncs[func_idx]->id );

        temp++;
        printf("idx = %d\n", func_idx);

        return func_idx;
        
        }
    else{

    func_idx++;
    // userFuncs[func_idx-1] = (userfunc*)malloc(sizeof(userfunc));
    printf("idx = %d\n", temp-func_idx);
    userFuncs[temp-func_idx] = (userfunc*)malloc(sizeof(userfunc));
    userFuncs[temp - func_idx]->address = f->value.funcVal->iaddress;
    userFuncs[temp - func_idx]->localSize = f->value.funcVal->totallocals;
    userFuncs[temp - func_idx]->id = strdup(f->name);
    printf("%d %d %s\n",userFuncs[temp - func_idx]->address, userFuncs[temp - func_idx]->localSize, userFuncs[temp - func_idx]->id );
    temp++;
    return temp-func_idx-1;
    }
}

void
make_operand(expr * e, vmarg *arg)
{   
    if(e!=NULL){

    printf("e->type = %d\n", e->type);
    switch(e->type){
		case var_e:
		case tableitem_e:
        case arithexpr_e:
        case boolexpr_e:
        case newtable_e:
        case assignexpr_e:
        {
            assert(e->sym);
            arg->val = e->sym->offset;

            switch(e->sym->space){
                case programvar: arg->type = global_a; break;
                case funclocal:  arg->type = local_a;  break;
                case formalarg:  arg->type = formal_a; break;
                default: assert(0);
            }
            break;
        }
    //Constants
        case constbool_e:{
            arg->val = e->boolConst;
            arg->type = bool_a;
            break;
        }
        case conststring_e:{
            arg->val = consts_newstring(e->strConst);
            arg->type = string_a;
            break;
        }
        case constnum_e:{
            arg->val = consts_newnumber(e->numConst);
            arg->type = number_a;
            break;
        }
        case nil_e:{
            arg->type = nil_a;
            break;
        }

        //Functions
        case programfunc_e:{
            arg->type = userfunc_a;
            // arg->val = e->sym->value.funcVal->iaddress;
            //or
                arg->val = userfuncs_newfunc(e->sym);
                printf("userfunc Arg->val = %d\n", arg->val);
            
            break;
        }
        case libfunc_e:{
            arg->type = libfunc_a;
            arg->val = libfuncs_newused(e->sym->name);
            break;
        }
        default: assert(0);
	}
    }
}

void patch_incomplete_jumps(){
    incomplete_jump *tmp;
    if(ij_head!=NULL){
        tmp = *ij_head;
    }
    else return;
    while(tmp){
        if(instructions[tmp->instrNo+1].result->type == userfunc_a) {
            tmp = tmp->next;
            continue;
        }
        if(tmp->iaddress == currprocquad){
            instructions[tmp->instrNo].result->val = tmp->iaddress;
        }
        else{
            instructions[tmp->instrNo].result->val = quads[tmp->iaddress].taddress;
        }
        if(tmp->next==NULL){
            break;
        }
        tmp = tmp->next;
    }
}


void expand_inst(){
    assert(total_inst == currInst);
    instruction* i = (instruction*)malloc(I_NEW_SIZE);
    if(instructions){
        memcpy(i, instructions, I_CURR_SIZE);
        free(instructions);
    }
    instructions = i;
    total_inst+=I_EXPAND_SIZE;
}

void emit_instruction(instruction* t){
    if(currInst == total_inst)
    {
        expand_inst();
    }
    instruction* i = instructions+currInst++;
    memcpy(i, t, sizeof(instruction));
}

unsigned nextinstructionlabel(){
    return currInst;
}

void generate(vmopcode op, quad* q){
    instruction* t = (instruction*)malloc(sizeof(instruction));
    t->opcode = op;
    t->arg1 = (vmarg*)malloc(sizeof(vmarg));
    t->arg2 = (vmarg *)malloc(sizeof(vmarg));
    t->result = (vmarg *)malloc(sizeof(vmarg));
    t->srcLine = q->line;

    make_operand(q->arg1, t->arg1);
    make_operand(q->arg2, t->arg2);
    make_operand(q->result, t->result);
    q->taddress = nextinstructionlabel();
    emit_instruction(t);
    
}

void make_booloperand(vmarg *arg, char c)
{

    arg->type = bool_a;
    arg->val = c;
}

void make_numberoperand(vmarg* arg, double val){
    arg->type = number_a;
    arg->val = consts_newnumber(val);
}

void make_retvaloperand(vmarg* arg){
    arg->type = retval_a;
}

void generate_add(quad* q){
    generate(add_v, q);
}

void generate_sub(quad *q)
{
    generate(sub_v, q);
}

void generate_mul(quad *q)
{
    generate(mul_v, q);
}

void generate_div(quad *q)
{
    generate(div_v, q);
}

void generate_mod(quad *q)
{
    generate(mod_v, q);
}

void generate_newtable(quad *q)
{
    generate(newtable_v, q);
}

void generate_tablegetelem(quad *q)
{
    generate(tablegetelem_v, q);
}

void generate_tablesetelem(quad *q)
{
    generate(tablesetelem_v, q);
}

void generate_assign(quad *q)
{
    generate(assign_v, q);
}

// void generate_uminus(quad *q){

// }

void generate_jump(quad* q){
    generate_relational(jump_v, q);
}

void generate_eq(quad* q){
    generate_relational(jeq_v, q);
}

void generate_noteq(quad *q){
    generate_relational(jne_v, q);
}

void generate_greater(quad *q)
{

    generate_relational(jgt_v, q);
}

void generate_greatereq(quad *q)
{

    generate_relational(jge_v, q);
}

void generate_less(quad *q)
{

    generate_relational(jlt_v, q);
}

void generate_lesseq(quad *q)
{

    generate_relational(jle_v, q);
}

void generate_nop(quad *q)
{
    instruction* t = (instruction*)malloc(sizeof(instruction));
    t->opcode = nop_v;
    t->srcLine = q->line;

    emit_instruction(t);
}

void generate_relational(vmopcode op, quad* q){
    instruction* t  = (instruction*)malloc(sizeof(instruction));
    t->arg1 = (vmarg*)malloc(sizeof(vmarg));
    t->arg2 = (vmarg*)malloc(sizeof(vmarg));
    t->result = (vmarg*)malloc(sizeof(vmarg));
    t->opcode = op;
    t->srcLine = q->line;

    make_operand(q->result, t->arg1);
    make_operand(q->arg2, t->arg2);
    make_operand(q->arg1, t->arg1);

    t->result->type = label_a;
    if(q->label < currprocquad){
        t->result->val = quads[q->label].taddress;
    }
    else{
        add_incomplete_jump(nextinstructionlabel(), q->label);
    }
    q->taddress = nextinstructionlabel();
    emit_instruction(t);
}


void generate_not(quad* q){
    q->taddress = nextinstructionlabel();
    instruction* t1 = (instruction*)malloc(sizeof(instruction));
    t1->opcode = jeq_v;
    t1->arg1 = (vmarg *)malloc(sizeof(vmarg));
    t1->arg2 = (vmarg *)malloc(sizeof(vmarg));
    t1->result = (vmarg *)malloc(sizeof(vmarg));
    make_operand(q->arg1, t1->arg1);
    make_booloperand(t1->arg2, 'F');
    t1->result->type = label_a;
    t1->result->val = nextinstructionlabel()+3;
    t1->srcLine = q->line;

    emit_instruction(t1);

    instruction* t2 = (instruction*)malloc(sizeof(instruction));
    t2->arg1 = (vmarg *)malloc(sizeof(vmarg));
    t2->arg2 = (vmarg *)malloc(sizeof(vmarg));
    t2->result = (vmarg *)malloc(sizeof(vmarg));
    t2->result->type = label_a;
    t2->result->val = nextinstructionlabel()+2;
    t2->srcLine = q->line;

    emit_instruction(t2);

    instruction* t3 = (instruction*)malloc(sizeof(instruction));
    t3->arg1 = (vmarg *)malloc(sizeof(vmarg));
    t3->arg2 = (vmarg *)malloc(sizeof(vmarg));
    t3->result = (vmarg *)malloc(sizeof(vmarg));
    t3->srcLine = q->line;

    make_booloperand(t3->arg1, 'T');
    make_operand(q->result, t1->result);
    emit_instruction(t3);
    
}

void generate_or(quad* q){
    q->taddress = nextinstructionlabel();

    instruction* t1 = (instruction*)malloc(sizeof(instruction));
    t1->arg1 = (vmarg*)malloc(sizeof(vmarg));
    t1->arg2 = (vmarg*)malloc(sizeof(vmarg));
    t1->result = (vmarg*)malloc(sizeof(vmarg));
    t1->opcode = jeq_v;
    make_operand(q->arg1, t1->arg1);
    make_booloperand(t1->arg2, 'T');
    t1->result->type = label_a;
    t1->result->val = nextinstructionlabel()+4;
    t1->srcLine = q->line;

    emit_instruction(t1);

    instruction* t2 = (instruction*)malloc(sizeof(instruction));
    t2->arg1 = (vmarg *)malloc(sizeof(vmarg));
    t2->arg2 = (vmarg *)malloc(sizeof(vmarg));
    t2->result = (vmarg *)malloc(sizeof(vmarg));
    make_operand(q->arg2, t2->arg1);
    make_booloperand(t2->arg2, 'T');
    t2->opcode = jeq_v;
    t2->result->type = label_a;
    t2->result->val = nextinstructionlabel()+3;
    t2->srcLine = q->line;

    emit_instruction(t2);

    instruction *t3 = (instruction *)malloc(sizeof(instruction));
    t3->arg1 = (vmarg *)malloc(sizeof(vmarg));
    t3->arg2 = (vmarg *)malloc(sizeof(vmarg));
    t3->result = (vmarg *)malloc(sizeof(vmarg));
    t3->opcode = assign_v;
    make_booloperand(t3->arg1, 'F');
    make_operand(q->result, t3->result);
    t3->srcLine = q->line;

    emit_instruction(t3);

    instruction *t4 = (instruction *)malloc(sizeof(instruction));
    t4->arg1 = (vmarg *)malloc(sizeof(vmarg));
    t4->arg2 = (vmarg *)malloc(sizeof(vmarg));
    t4->result = (vmarg *)malloc(sizeof(vmarg));

    t4->opcode = jump_v;
    t4->result->type = label_a;
    t4->result->val = nextinstructionlabel()+2;
    t4->srcLine = q->line;

    emit_instruction(t4);

    instruction *t5 = (instruction *)malloc(sizeof(instruction));
    t5->arg1 = (vmarg *)malloc(sizeof(vmarg));
    t5->arg2 = (vmarg *)malloc(sizeof(vmarg));
    t5->result = (vmarg *)malloc(sizeof(vmarg));
    t5->opcode = assign_v;
    make_booloperand(t5->arg1, 'T');
    make_operand(q->result, t5->result);
    t5->srcLine = q->line;

    emit_instruction(t5);
}

//TODO: generate_and Paromoia me thn or
void generate_and(quad* q){
    q->taddress = nextinstructionlabel();

    instruction *t1 = (instruction *)malloc(sizeof(instruction));
    t1->arg1 = (vmarg *)malloc(sizeof(vmarg));
    t1->arg2 = (vmarg *)malloc(sizeof(vmarg));
    t1->result = (vmarg *)malloc(sizeof(vmarg));
    t1->opcode = jeq_v;
    make_operand(q->arg1, t1->arg1);
    make_booloperand(t1->arg2, 'F');
    t1->result->type = label_a;
    t1->result->val = nextinstructionlabel() + 4;
    t1->srcLine = q->line;

    emit_instruction(t1);

    instruction *t2 = (instruction *)malloc(sizeof(instruction));
    t2->arg1 = (vmarg *)malloc(sizeof(vmarg));
    t2->arg2 = (vmarg *)malloc(sizeof(vmarg));
    t2->result = (vmarg *)malloc(sizeof(vmarg));
    make_operand(q->arg2, t2->arg1);
    make_booloperand(t2->arg2, 'F');
    t2->opcode = jeq_v;
    t2->result->type = label_a;
    t2->result->val = nextinstructionlabel() + 3;
    t2->srcLine = q->line;

    emit_instruction(t2);

    instruction *t3 = (instruction *)malloc(sizeof(instruction));
    t3->arg1 = (vmarg *)malloc(sizeof(vmarg));
    t3->arg2 = (vmarg *)malloc(sizeof(vmarg));
    t3->result = (vmarg *)malloc(sizeof(vmarg));
    t3->opcode = assign_v;
    make_booloperand(t3->arg1, 'T');
    make_operand(q->result, t3->result);
    t3->srcLine = q->line;

    emit_instruction(t3);

    instruction *t4 = (instruction *)malloc(sizeof(instruction));
    t4->arg1 = (vmarg *)malloc(sizeof(vmarg));
    t4->arg2 = (vmarg *)malloc(sizeof(vmarg));
    t4->result = (vmarg *)malloc(sizeof(vmarg));

    t4->opcode = jump_v;
    t4->result->type = label_a;
    t4->result->val = nextinstructionlabel() + 2;
    t4->srcLine = q->line;

    emit_instruction(t4);

    instruction *t5 = (instruction *)malloc(sizeof(instruction));
    t5->arg1 = (vmarg *)malloc(sizeof(vmarg));
    t5->arg2 = (vmarg *)malloc(sizeof(vmarg));
    t5->result = (vmarg *)malloc(sizeof(vmarg));
    t5->opcode = assign_v;
    make_booloperand(t5->arg1, 'F');
    make_operand(q->result, t5->result);
    t5->srcLine = q->line;

    emit_instruction(t5);
}

void generate_param(quad* q){
    q->taddress=nextinstructionlabel();
    instruction *t = (instruction *)malloc(sizeof(instruction));
    t->arg1 = (vmarg*)malloc(sizeof(vmarg));
    t->arg2 = (vmarg*)malloc(sizeof(vmarg));
    t->result = (vmarg*)malloc(sizeof(vmarg));
    t->opcode = pusharg_v;
    t->srcLine = q->line;

    make_operand(q->result, t->arg1);
    emit_instruction(t);
}

void generate_call(quad* q){
    unsigned tmp = 0;
    q->taddress = nextinstructionlabel();


    instruction* t = (instruction*)malloc(sizeof(instruction));
    t->arg1 = (vmarg *)malloc(sizeof(vmarg));
    t->arg2 = (vmarg *)malloc(sizeof(vmarg));
    t->result = (vmarg *)malloc(sizeof(vmarg));
    t->opcode = call_v;
    t->srcLine = q->line;

    make_operand(q->result, t->arg1);
    printf("result->val = %d\n", t->arg1->val);
    emit_instruction(t);
}

void generate_getretval(quad* q){
    q->taddress = nextinstructionlabel();
    instruction* t = (instruction*)malloc(sizeof(instruction));
    t->arg1 = (vmarg *)malloc(sizeof(vmarg));
    t->arg2 = (vmarg *)malloc(sizeof(vmarg));
    t->result = (vmarg *)malloc(sizeof(vmarg));
    t->opcode = assign_v;
    t->srcLine = q->line;

    make_operand(q->result, t->result);
    make_retvaloperand(t->arg1);
    emit_instruction(t);
}

void generate_funcstart(quad* q){

    generate_jump(q);

    st_entry* f = q->result->sym;
    f->value.funcVal->r_list = NULL;

    f->value.funcVal->iaddress = nextinstructionlabel();
    // userFuncs[func_idx]->address = f->value.funcVal->iaddress-1;
    q->taddress = nextinstructionlabel();
    instruction* t = (instruction*)malloc(sizeof(instruction));
    t->arg1 = (vmarg *)malloc(sizeof(vmarg));
    t->arg2 = (vmarg *)malloc(sizeof(vmarg));
    t->result = (vmarg *)malloc(sizeof(vmarg));
    t->opcode = funcenter_v;
    t->srcLine = q->line;

    push_funcstack(f);

    make_operand(q->result, t->result);
    emit_instruction(t);
}

void generate_funcend(quad* q){

    st_entry* f = pop_funcstack();
    backpatch_instruction(f->value.funcVal->r_list, nextinstructionlabel());
    patch_instruction(f->value.funcVal->iaddress-1 , nextinstructionlabel()+1);
    // f->value.funcVal->tiaddress = nextinstructionlabel();
    // printf("taddress = %d\n", f->value.funcVal->tiaddress);
    q->taddress = nextinstructionlabel();
    instruction *t = (instruction *)malloc(sizeof(instruction));
    t->arg1 = (vmarg *)malloc(sizeof(vmarg));
    t->arg2 = (vmarg *)malloc(sizeof(vmarg));
    t->result = (vmarg *)malloc(sizeof(vmarg));
    t->opcode = funcexit_v;
    t->srcLine = q->line;
    printf("funcend address: %d\n", f->value.funcVal->iaddress);
    make_operand(q->result, t->result);
    emit_instruction(t);
    printf("lala\n");
    // generate_jump(q);
}


void generate_return(quad* q){
    q->taddress = nextinstructionlabel();

    instruction* t1 = (instruction*)malloc(sizeof(instruction));
    t1->arg1 = (vmarg *)malloc(sizeof(vmarg));
    t1->arg2 = (vmarg *)malloc(sizeof(vmarg));
    t1->result = (vmarg *)malloc(sizeof(vmarg));
    t1->opcode = assign_v;
    t1->srcLine = q->line;

    make_retvaloperand(t1->result);
    make_operand(q->result, t1->arg1);
    emit_instruction(t1);

    st_entry* f = top_funcstack();
    append_list(&f->value.funcVal->r_list, nextinstructionlabel());
    instruction *t2 = (instruction *)malloc(sizeof(instruction));
    t2->arg1 = (vmarg *)malloc(sizeof(vmarg));
    t2->arg2 = (vmarg *)malloc(sizeof(vmarg));
    t2->result = (vmarg *)malloc(sizeof(vmarg));
    t2->opcode = jump_v;
    make_retvaloperand(t2->result);
    t2->result->type = label_a;
    t2->srcLine = q->line;

    emit_instruction(t2);
}

void add_incomplete_jump(unsigned instrNo, unsigned iaddrr)
{
    if ((ij_head) == NULL)
    {
        ij_head = (incomplete_jump **)malloc(sizeof(incomplete_jump *));
        (*ij_head) = (incomplete_jump *)malloc(sizeof(incomplete_jump));
        (*ij_head)->instrNo = instrNo;
        (*ij_head)->iaddress = iaddrr;
        (*ij_head)->next = NULL;
        return;
    }
    incomplete_jump *new = (incomplete_jump *)malloc(sizeof(incomplete_jump));
    new->instrNo = instrNo;
    new->iaddress = iaddrr;
    new->next = (*ij_head);
    (*ij_head) = new;
}

void push_funcstack(st_entry *f)
{
    if (funcstack_head == NULL)
    {
        funcstack_head = (funcstack **)malloc(sizeof(funcstack *));
        (*funcstack_head) = (funcstack *)malloc(sizeof(funcstack));
        (*funcstack_head)->func = f;
        (*funcstack_head)->next = NULL;
        return;
    }
    funcstack *new = (funcstack *)malloc(sizeof(funcstack));
    new->func = f;
    new->next = (*funcstack_head);
    (*funcstack_head) = new;
}

st_entry *top_funcstack()
{
    return (*funcstack_head)->func;
}
st_entry *pop_funcstack()
{
    if ((*funcstack_head) == NULL)
    {
        printf("Empty funcstack list\n");
        return NULL;
    }
    funcstack *tmp = (*funcstack_head);
    st_entry *result = tmp->func;
    (*funcstack_head) = tmp->next;

    return result;
}
 
void append_list(return_list** list, int label){
    return_list* tmp = *list;
    if((*list)==NULL){
        tmp = (return_list*)malloc(sizeof(return_list));
        tmp->label = label;
        tmp->next = NULL;
        (*list) = tmp;
        printf("first elemnt: %d\n", tmp->label);
        return;
    }
    while(tmp->next!=NULL){
        tmp = tmp->next;
    }
    return_list* new = (return_list*)malloc(sizeof(return_list));
    new->label = label;
    new->next = NULL;
    tmp->next = new;
    printf("append element: %d\n", tmp->next->label);
}

void patch_instruction(unsigned instNo, unsigned label)
{
    assert(instNo < currInst);
    printf("PATCH LABEL: instNo: %d, LABEL: %d\n", instNo, label);
    // printf("ju")
    instructions[instNo].result->val = label;
}

void backpatch_instruction(return_list *list, int label){
    return_list* tmp = list;
    while(tmp!=NULL){
        patch_instruction(tmp->label, label);
        tmp = tmp->next;
    }
}

void print_opi(FILE *fp, vmopcode op)
{
    char *s;
    switch (op)
    {
    case assign_v:
        s = strdup("assign");
        printf("%-15s", s);
        fprintf(fp, "%-15s", s);
        break;
    case add_v:
        s = strdup("add");
        printf("%-15s", s);
        fprintf(fp, "%-15s", s);
        break;
    case sub_v:
        s = strdup("sub");
        printf("%-15s", s);
        fprintf(fp, "%-15s", s);
        break;
    case mul_v:
        s = strdup("mul");
        printf("%-15s", s);
        fprintf(fp, "%-15s", s);
        break;
    case div_v:
        s = strdup("div");
        printf("%-15s", s);
        fprintf(fp, "%-15s", s);
        break;
    case mod_v:
        s = strdup("mod");
        printf("%-15s", s);
        fprintf(fp, "%-15s", s);
        break;
    case or_v:
        s = strdup("or");
        printf("%-15s", s);
        fprintf(fp, "%-15s", s);
        break;
    case and_v:
        s = strdup("and");
        printf("%-15s", s);
        fprintf(fp, "%-15s", s);
        break;
    case jump_v:
        s = strdup("jump");
        printf("%-15s", s);
        fprintf(fp, "%-15s", s);
        break;
    case not_v:
        s = strdup("not");
        printf("%-15s", s);
        fprintf(fp, "%-15s", s);
        break;
    case jeq_v:
        s = strdup("ifeq");
        printf("%-15s", s);
        fprintf(fp, "%-15s", s);
        break;
    case jne_v:
        s = strdup("ifnoteq");
        printf("%-15s", s);
        fprintf(fp, "%-15s", s);
        break;
    case jle_v:
        s = strdup("if_lesseq");
        printf("%-15s", s);
        fprintf(fp, "%-15s", s);
        break;
    case jge_v:
        s = strdup("if_grtereq");
        printf("%-15s", s);
        fprintf(fp, "%-15s", s);
        break;
    case jlt_v:
        s = strdup("if_less");
        printf("%-15s", s);
        fprintf(fp, "%-15s", s);
        break;
    case jgt_v:
        s = strdup("if_greater");
        printf("%-15s", s);
        fprintf(fp, "%-15s", s);
        break;
    case call_v:
        s = strdup("call");
        printf("%-15s", s);
        fprintf(fp, "%-15s", s);
        break;
    case pusharg_v:
        s = strdup("param");
        printf("%-15s", s);
        fprintf(fp, "%-15s", s);
        break;
    case nop_v:
        s = strdup("nop");
        printf("%-15s", s);
        fprintf(fp, "%-15s", s);
        break;
    case funcenter_v:
        s = strdup("funcstart");
        printf("%-15s", s);
        fprintf(fp, "%-15s", s);
        break;
    case funcexit_v:
        s = strdup("funcend");
        printf("%-15s", s);
        fprintf(fp, "%-15s", s);
        break;
    case newtable_v:
        s = strdup("tblcrt");
        printf("%-15s", s);
        fprintf(fp, "%-15s", s);
        break;
    case tablegetelem_v:
        s = strdup("tblgetelem");
        printf("%-15s", s);
        fprintf(fp, "%-15s", s);
        break;
    case tablesetelem_v:
        s = strdup("tblsetelem");
        printf("%-15s", s);
        fprintf(fp, "%-15s", s);
        break;
    default:
        printf("wtf");
        fprintf(fp, "wtf");
        break;
    }
    return;
}

void print_instructions()
{
    FILE *ip = fopen("instructions.txt", "w");
    int i;
    for (i = 0; i < currInst; i++)
    {
        instruction *p = &instructions[i];
        printf("[%d]%-3s\t", i,"");
    	// printf("koble\n");
        fprintf(ip, "[%d]\t", i);
        print_opi(ip, p->opcode);
        
        if (p->arg1 != NULL)
        {
            switch (p->arg1->type)
            {
            case number_a:
                fprintf(ip, "%-14f", numConsts[p->arg1->val]);
                printf("%-14f", numConsts[p->arg1->val]);
                break;
            case bool_a:
                printf("%-14c", p->arg1->val);
                fprintf(ip, "%-14c", p->arg1->val);
                break;

            case string_a:
                printf("%-14s", stringConsts[p->arg1->val]);
                fprintf(ip, "%-14s", stringConsts[p->arg1->val]);
                break;
            case nil_a:
                printf("%-14s", "nil");
                fprintf(ip, "\'%-14s\'", "nil");
                break;
            case global_a:{
                printf("Global: %-14d", p->arg1->val);
                fprintf(ip, "Global: %-14d", p->arg1->val);
                break;
            }
            case local_a:{
                printf("Local: %-14d", p->arg1->val);
                fprintf(ip, "Local: %-14d", p->arg1->val);
                break;
            }
            case formal_a:{
                printf("Formal: %-14d", p->arg1->val);
                fprintf(ip, "Formal: %-14d", p->arg1->val);
                break;
            }
            case label_a:{
                printf("goto: %-14d",p->arg1->val);
                fprintf(ip, "goto: %-14d", p->arg1->val);
                break;
            }
            case userfunc_a:{
                fprintf(ip, "%-14s", userFuncs[p->arg1->val]->id);
                printf("%-14s", userFuncs[p->arg1->val]->id);
                break;
            }
            case libfunc_a:{
                printf("%-14s", namedLibfuncs[p->arg1->val]);
                fprintf(ip, "%-14s", namedLibfuncs[p->arg1->val]);
            }
            case retval_a:{
                fprintf(ip, "%-14s", "retval");
                printf("%-14s", "retval");
                break;
            }
            default:
                printf("%-14s", "NULL");
                fprintf(ip, "%-14s", "NULL");
                }
        }
        else{
            printf("%-14s", "NULL");
            fprintf(ip, "%-14s", "NULL");
        }
        if (p->arg2 != NULL)
        {
            switch (p->arg2->type)
            {
            case number_a:
                fprintf(ip, "%-14f", numConsts[p->arg2->val]);
                printf("%-14f", numConsts[p->arg2->val]);
                break;
            case bool_a:
                printf("%-14c", p->arg2->val);
                fprintf(ip, "%-14c", (char)p->arg2->val);
                break;

            case string_a:
                printf("%-14s", stringConsts[p->arg2->val]);
                fprintf(ip, "%-14s", stringConsts[p->arg2->val]);
                break;
            case nil_a:
                printf("%-14s", "nil");
                fprintf(ip, "\'%-14s\'", "nil");
                break;
            case global_a:
            {
                printf("Global: %-14d", p->arg2->val);
                fprintf(ip, "Global: %-14d", p->arg2->val);

                break;
            }
            case local_a:
            {
                printf("Local: %-14d", p->arg2->val);
                fprintf(ip, "Local: %-14d", p->arg2->val);

                break;
            }
            case formal_a:
            {
                printf("Formal: %-14d", p->arg2->val);
                fprintf(ip, "Formal: %-14d", p->arg2->val);
                break;
            }
            case label_a:
            {
                printf("goto: %-14d", p->arg2->val);
                fprintf(ip, "goto: %-14d", p->arg2->val);
                break;
            }
            case userfunc_a:
            {
                fprintf(ip, "%-14s", userFuncs[p->arg2->val]->id);
                printf("%-14s", userFuncs[p->arg2->val]->id);
                break;
            }
            case libfunc_a:
            {
                printf("%-14s", namedLibfuncs[p->arg2->val]);
                fprintf(ip, "%-14s", namedLibfuncs[p->arg2->val]);
            }
            case retval_a:
            {
                fprintf(ip, "%-14s", "retval");
                printf("%-14s", "retval");
                break;
            }
            default:
                printf("%-14s","NULL");
                fprintf(ip, "%-14s","NULL");

            }
        }
        else{
            printf("%-14s", "NULL");
            fprintf(ip, "%-14s", "NULL");
        }
        if (p->result != NULL)
        {
            switch (p->result->type)
            {
            case number_a:
                fprintf(ip, "%-14f", numConsts[p->result->val]);
                printf("%-14f", numConsts[p->result->val]);
                break;
            case bool_a:
                printf("%-14c", p->result->val);
                fprintf(ip, "%-14c", (char)p->result->val);
                break;

            case string_a:
                printf("%-14s", stringConsts[p->result->val]);
                fprintf(ip, "%-14s", stringConsts[p->result->val]);
                break;
            case nil_a:
                printf("%-14s", "nil");
                fprintf(ip, "\'%-14s\'", "nil");
                break;
            case global_a:
            {
                printf("Global: %-14d", p->result->val);
                fprintf(ip,"Global: %-14d", p->result->val);

                break;
            }
            case local_a:
            {
                printf("Local: %-14d", p->result->val);
                fprintf(ip,"Local: %-14d", p->result->val);

                break;
            }
            case formal_a:
            {
                printf("Formal: %-14d", p->result->val);
                fprintf(ip,"Formal: %-14d", p->result->val);

                break;
            }
            case label_a:
            {
                printf("\tgoto: %-14d", p->result->val);
                fprintf(ip, "\tgoto: %-14d", p->result->val);
                break;
            }
            case userfunc_a:
            {
                fprintf(ip, "%-14s", userFuncs[p->result->val]->id);
                printf("%-14s", userFuncs[p->result->val]->id);
                break;
            }
            case libfunc_a:
            {
                printf("%-14s", namedLibfuncs[p->result->val]);
                fprintf(ip, "%-14s", namedLibfuncs[p->result->val]);
            }
            case retval_a:
            {
                fprintf(ip, "%-14s", "retval");
                printf("%-14s", "retval");
                break;
            }
            default:
                printf("%-14s", "NULL");
                fprintf(ip, "%-14s", "NULL");

                // fprintf(ip, "%-14s", p->arg1->sym->value.varVal->name);
            }
        }
        else{
            printf("%-14s", "NULL");
            fprintf(ip, "%-14s", "NULL");
        }
        printf("Line:%-14d", p->srcLine);
        fprintf(ip, "Line:%-8d", p->srcLine);
        fprintf(ip, "\n");
        printf("\n");
    }
    fclose(ip);
}

