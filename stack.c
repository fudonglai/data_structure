//
// Created by admin on 2018/9/26.
//
#include <stdio.h>
#include <stdlib.h>

#define OK 0
#define ERROR 1
#define OVERFLOW 2
#define STACK_INIT_SIZE 100
#define STACK_INCREMENT 10

typedef int Status;
typedef int SElemType;
typedef struct {
    SElemType *base;
    SElemType *top;
    int        stack_size;
}*SqStack;

Status InitSqStack(SqStack S);
Status Push(SqStack S, SElemType e);
Status Pop(SqStack S, SElemType *e);
Status GetTop(SqStack S, SElemType *e);

void DestroyStack(SqStack S){ free(S);}
void ClearStack(SqStack S){ S->top = S->base;}
int StackEmpty(SqStack S){ return S->top == S->base;}

Status InitSqStack(SqStack S){
    S->base = S->top = (SElemType*)malloc(STACK_INIT_SIZE * sizeof(SElemType));
    S->stack_size = STACK_INIT_SIZE;
    return OK;
}

Status GetTop(SqStack S, SElemType *e){
    if (S->top == S->base)
        exit(ERROR);
    else
        *e = *(S->top - 1);
    return OK;
}

Status Push(SqStack S, SElemType e){
    if (S->top - S->base >= S->stack_size){
        S->base = (SElemType*)realloc(S->base, (S->stack_size + STACK_INCREMENT) * sizeof(SElemType));
        S->top = S->base + S->stack_size;
        S->stack_size += STACK_INCREMENT;
    }else{
        *S->top++ = e;
    }
    return OK;
}

Status Pop(SqStack S, SElemType *e){
    if (S->top == S->base)
        exit(ERROR);
    *e = *(--S->top);
    return OK;
}


void conversion(){
    int N;
    SElemType *e = NULL;
    SqStack S = NULL;
    InitSqStack(S);
    scanf("%d", &N);
        while (N){
        Push(S, N % 8);
        N /= 8;
    }
    while (!StackEmpty(S)){
            Pop(S, e);
            printf("%d", *e);
        }
}

void LineEdit(){
    SqStack S = NULL;
    InitSqStack(S);
    int ch = getchar();
    while (ch != EOF){
        while (ch != '\n' && ch != EOF){
            switch (ch){
                case '#': Pop(S, &ch);   break;
                case '@': ClearStack(S); break;
                default : Push(S, ch);   break;
            }
            ch = getchar();
        }
        // do something with the data in stack
        ClearStack(S);
        if (ch != EOF)
            ch = getchar();
    }
    DestroyStack(S);
}