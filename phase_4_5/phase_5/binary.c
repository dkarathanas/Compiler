#include "binary.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

unsigned total_inst;
unsigned int currInst;
double *numConsts;
char **stringConsts;
char **namedLibfuncs;
userfunc **userFuncs;
instruction *instructions;
unsigned globals;

void binary(){
    printf("reading binary..\n");
    FILE* fp = fopen("../phase_4/binary.abc", "rb");
    readMagicNumber(fp);
    readArrays(fp);
    readCode(fp);
    fclose(fp);
}

void readMagicNumber(FILE* fp){
    unsigned int magicNumber;
    fread(&magicNumber, sizeof(unsigned int), 1, fp);
    printf("Magicnumber: %d\n", magicNumber);
    return;
}

void readArrays(FILE* fp){
    unsigned int size, i , s_size;
    char* tmp_string;
    //numConsts
    fread(&size, sizeof(size), 1, fp);
    printf("NumConsts size = %d\nNumCostsArray:\n", size);
    numConsts = (double*)malloc(size*(sizeof(double)));
    for(i=0;i<size;i++){
        fread(&numConsts[i], sizeof(double), 1, fp);
        printf("[%d] = %f\n", i, numConsts[i]);
    }

    //strConsts
    fread(&size, sizeof(size), 1, fp);
    stringConsts = (char**)malloc(size*(sizeof(char*)));
    printf("StrConsts size = %d\nStrConstArray:\n", size);
    for(i=0;i<size;i++){
        fread(&s_size, sizeof(s_size), 1, fp);
        printf("s_size = %d\n", s_size);
        stringConsts[i] = (char*)malloc((s_size+1)*sizeof(char));
        fread(stringConsts[i], s_size+1, 1, fp);
        printf("[%d] = %s, size = %d\n", i, stringConsts[i], s_size);
    }

    //userFuncs
    fread(&size, sizeof(size), 1, fp);
    printf("Userfunc size = %d\nUserFuncArray:\n", size);
    userFuncs = (userfunc**)malloc(sizeof(userfunc*)*(size/2+1));
    for(i=0;i<size;i++){
        //f->id
        userFuncs[i] = (userfunc*)malloc(sizeof(userfunc));
        fread(&s_size, sizeof(s_size), 1, fp);
        if(s_size == 0) break;
        userFuncs[i]->id = (char*)malloc(sizeof(char)*(s_size+1));
        fread(userFuncs[i]->id, s_size+1, 1 , fp);
        fread(&userFuncs[i]->localSize, sizeof(unsigned), 1 , fp);
        fread(&userFuncs[i]->address, sizeof(unsigned), 1, fp);
        printf("[%d] = %s  locals=%u  iaddress=%u, length: %d\n", i, userFuncs[i]->id, userFuncs[i]->localSize, userFuncs[i]->address, s_size);
    }

    //libFuncs
    fread(&size, sizeof(size), 1, fp);
    printf("LibFuncs size = %d\nLibfuncsArray:\n", size);
    namedLibfuncs = (char**)malloc(sizeof(char*)*size);
    for (i = 0; i < size; i++)
    {
        fread(&s_size, sizeof(s_size), 1, fp);
        printf("s_size = %d\n", s_size);
        namedLibfuncs[i] = (char*)malloc(sizeof(char*)*(s_size+1));
        fread(namedLibfuncs[i], s_size, 1, fp);
        printf("[%d] = %s, size = %d\n", i, namedLibfuncs[i], s_size);
    }
}

void readCode(FILE* fp){
    int i;
    fread(&currInst, sizeof(unsigned int), 1, fp);
    instructions = (instruction*)malloc(sizeof(instruction)*currInst);
    printf("total instructions: %d\n", currInst);
    for (i = 0; i < currInst; i++)
    {
        instruction *tmp = (instruction*)malloc(sizeof(instruction));
        
        tmp->arg1 = (vmarg*)malloc(sizeof(vmarg));
        tmp->arg2 = (vmarg *)malloc(sizeof(vmarg));
        tmp->result = (vmarg *)malloc(sizeof(vmarg));
        fread(&tmp->opcode, sizeof(char), 1, fp);
        printf("opcode: %d", tmp->opcode);
        //type, value: arg1
        fread(&tmp->arg1->type, sizeof(vmarg_t), 1, fp);
        fread(&tmp->arg1->val, sizeof(unsigned), 1, fp);
        printf("\targ1->type: %d\tval: %d", tmp->arg1->type, tmp->arg1->val);

        //arg2
        fread(&tmp->arg2->type, sizeof(vmarg_t), 1, fp);
        fread(&tmp->arg2->val, sizeof(unsigned), 1, fp);
        printf("\targ2->type: %d\tval: %d", tmp->arg2->type, tmp->arg2->val);

        //result
        fread(&tmp->result->type, sizeof(vmarg_t), 1, fp);
        fread(&tmp->result->val, sizeof(unsigned), 1, fp);
        printf("\tresult->type: %d\tval: %d\n", tmp->result->type, tmp->result->val);

        //line
        fread(&tmp->srcLine, sizeof(unsigned), 1, fp);
        instructions[i] = *tmp;
    }
    fread(&globals, sizeof(unsigned), 1, fp);
    printf("Total globals = %d\n", globals);
}

