#include "avm_code.h"

//arithmetic operations
#define execute_add execute_arithmetic
#define execute_sub execute_arithmetic
#define execute_mul execute_arithmetic
#define execute_div execute_arithmetic
#define execute_mod execute_arithmetic

typedef double (*arithmetic_func_t)(double x, double y);

arithmetic_func_t arithmeticFuncs[] = { 
add_impl,
sub_impl,
mul_impl,
div_impl,
mod_impl
};

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

void avm_assign(avm_memcell *lv, avm_memcell *rv)
{
    if (lv == rv)
    {
        // printf("lv->data = %d\n", lv->data.numVal);
        return;
    }
    // if(lv->type == table_m && rv->type == table_m && lv->data.tableVal == rv->data.tableVal)
    // return;

    if (rv->type == undef_m)
    {
        printf("AVM_WARNING: Assigning from undefined content\n");
    }
    avm_memcellclear(lv);
    memcpy(lv, rv, sizeof(avm_memcell));
    printf(KGRN "AVM_ASSIGN: lv->type = %d\n", lv->type);
    switch (lv->type)
    {
    case number_m:
        printf("lv->type = %f\n", lv->data.numVal);
        break;
    case bool_m:
        printf("lv->type = %c\n", (char)lv->data.boolVal);
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
            //avm_tableincrefcounter(lv->data.tableVal);
            printf("FIX ME\n");
        }
    }
}

void execute_assign(instruction *i)
{
    // printf("lala\n");
    avm_memcell *lv = avm_translate_operand(i->result, (avm_memcell *)0);
    avm_memcell *rv = avm_translate_operand(i->arg1, &ax);
    assert(lv && &stack[AVM_STACKSIZE - 1] >= lv && lv > &stack[top] || lv == &retval);
    assert(rv); // to do similar tests
    avm_assign(lv, rv);
}
