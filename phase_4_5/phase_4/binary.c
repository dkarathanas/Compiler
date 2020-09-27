#include "t_code.h"
#include <string.h>

extern unsigned total_inst;
extern unsigned int currInst;
extern double *numConsts;
extern char **stringConsts;
extern char **namedLibfuncs;
extern userfunc **userFuncs;
extern instruction* instructions;
extern unsigned programVarOffset;

extern unsigned int num_idx;
extern unsigned int str_idx;
extern unsigned int lib_idx;
extern unsigned int func_idx;

void binary(){
    printf("creating .abc...\n");
    FILE* fp = fopen("binary.abc", "wb");
    printMagicNumber(fp);
    printArrays(fp);
    printCode(fp);
    fclose(fp);
}

void printMagicNumber(FILE* fp){
    unsigned int magicNumber = 707;
    fwrite(&magicNumber, sizeof(unsigned int), 1, fp);
    printf("Magicnumber: %d\n", magicNumber);
    printf("Total globals = %d\n", programVarOffset);
    return;
}

void printArrays(FILE* fp){
    unsigned int size, i, s_size;
    //number consts
    size = num_idx;
    //write number_consts size
    fwrite(&size, sizeof(size), 1, fp);
    printf("NumConsts size = %d\nNumCostsArray:\n", size);
    //print items
    for(i=0;i<size;i++){
        fwrite(&numConsts[i], sizeof(double), 1, fp);
        printf("[%d] = %f\n", i, numConsts[i]);
    }
    //string costs
    size = str_idx;
    fwrite(&size, sizeof(size), 1, fp);
    printf("StrConsts size = %d\nStrConstArray:\n", size);
    for(i=0;i<size;i++){
        s_size = strlen(stringConsts[i]);
        fwrite(&s_size, sizeof(s_size), 1, fp);
        fwrite(stringConsts[i], s_size+1, 1, fp);
        printf("[%d] = %s, size = %d\n", i, stringConsts[i], s_size);
    }
    //userfuncs
    size = func_idx;
    fwrite(&size, sizeof(size), 1, fp);
    printf("Userfunc size = %d\nUserFuncArray:\n", size);
    for(i=0;i<size;i++){
        //f->id
        if(!userFuncs[i]){
            s_size = 0;
        }
        else{
            s_size = strlen(userFuncs[i]->id);
        }
        fwrite(&s_size, sizeof(s_size), 1, fp);
        if(s_size == 0) break;
        fwrite(userFuncs[i]->id, s_size+1, 1, fp);
        //f->localsize
        fwrite(&userFuncs[i]->localSize, sizeof(unsigned), 1, fp);
        //f->address
        fwrite(&userFuncs[i]->address, sizeof(unsigned), 1, fp);
        printf("[%d] = %s  locals=%u  iaddress=%u, length: %d\n", i, userFuncs[i]->id, userFuncs[i]->localSize, userFuncs[i]->address, s_size);
    }
    //namedlibfuncs
    size = lib_idx;
    fwrite(&size, sizeof(size), 1, fp);
    printf("LibFuncs size = %d\nLibfuncsArray:\n", size);
    for (i = 0; i < size; i++)
    {
        s_size = strlen(namedLibfuncs[i]);
        fwrite(&s_size, sizeof(s_size), 1, fp);
        fwrite(namedLibfuncs[i], s_size, 1, fp);
        printf("[%d] = %s, size = %d\n", i, namedLibfuncs[i], s_size);
    }
}

void printCode(FILE* fp){
    int i;
    //total instructions
    fwrite(&currInst, sizeof(unsigned int), 1, fp);
    printf("total instructions: %d\n", currInst);
    for(i=0;i<currInst;i++){
        instruction tmp = instructions[i];
        fwrite(&tmp.opcode, sizeof(char), 1, fp);
        printf("opcode: %d", tmp.opcode);
        //type, value: arg1
        fwrite(&tmp.arg1->type, sizeof(vmarg_t), 1, fp);
        fwrite(&tmp.arg1->val, sizeof(unsigned), 1, fp);
        printf("\targ1->type: %d\tval: %d\n", tmp.arg1->type, tmp.arg1->val);

        //arg2
        fwrite(&tmp.arg2->type, sizeof(vmarg_t), 1, fp);
        fwrite(&tmp.arg2->val, sizeof(unsigned), 1, fp);
        //result
        fwrite(&tmp.result->type, sizeof(vmarg_t), 1, fp);
        fwrite(&tmp.result->val, sizeof(unsigned), 1, fp);
        //line
        fwrite(&tmp.srcLine, sizeof(unsigned), 1, fp);
    }
    fwrite(&programVarOffset, sizeof(unsigned), 1, fp);
}