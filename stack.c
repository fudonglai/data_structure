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


/* MazePath */

typedef int Dir;
typedef int* Pos;
typedef int Maze[10][10];
typedef struct {
    int    ord;
    Dir    dir;
    Pos    pos;
}MElemType;

typedef struct {
    MElemType *base;
    MElemType *top;
    int        stack_size;
}*MSqStack;

Status MPush(SqStack S, MElemType e);
Status MPop(SqStack S, MElemType *e);

void FootPrint(Pos pos);
int Pass(Pos pos, Dir d);
Status NextStep(MSqStack S, MElemType* e){
    MElemType top = *(S->top - 1);
    switch (top.dir){
        case 1:
            if (Pass(top.pos, ++top.dir)){
                top.pos[0]++;
                top.ord++;
                FootPrint(top.pos);
                break;
            }
        case 2:
            if (Pass(top.pos, ++top.dir)) {
                top.pos[1]++;
                top.ord++;
                FootPrint(top.pos);
                break;
            }
        case 3:
            if (Pass(top.pos, ++top.dir)) {
                top.pos[0]--;
                top.ord++;
                FootPrint(top.pos);
                break;
            }
        case 4:
            if (Pass(top.pos, ++top.dir)) {
                top.pos[1]--;
                top.ord++;
                FootPrint(top.pos);
                break;
            }
        default:
            return 0;
    }
} // if fail then return 0

Status MazePath(Maze maze, Pos start, Pos end){
    SqStack S = NULL;
    Pos curPos = start;
    int curStep = 1;
    MElemType e = {curStep, 1, curPos};
    InitSqStack(S);
    MPush(S, e);

    do{
        if (NextStep(S, &e))
            MPush(S, e);
        else
            MPop(S, &e);

        if (S->top != S->base + 1)
            exit(ERROR);
    }while (curPos != end);
    return OK;
}


/* Hanoi */
typedef char From, To, By;
typedef int No;
void move(From , No , To);
void hanoi(int, From, By, To);

void hanoi(int n, From x, By y, To z){
    if (n == 1)
        move(x, 1, z);
    else{  // 精彩异常。自顶向下传递，自下向上回归。
        hanoi(n - 1, x, z, y);
        move(x, n, z);
        hanoi(n - 1, y, x, z);
    }
}
