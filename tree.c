//
// Created by admin on 2018/10/2.
//

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>   // va_start, va_arg, va_end
#include "stack.h"

#define TREE_C__ 0
#define OK 0
#define ERROR 1
#define OVERFLOW 2
#define UNDERFLOW (-2)
#define TRUE 1
#define FALSE 0
#define MAX_TREE_SIZE 100

typedef int TElemType;
typedef TElemType SqBiTree[MAX_TREE_SIZE];
SqBiTree bt;

typedef struct BiTNode {
    TElemType        data;
    struct BiTNode   *LChild, *RChild;
}BiTNode, *BiTree;

Status createBiTree(BiTree T);
Status PreOrderTraverse(BiTree T, Status(*visit)(TElemType e));
Status InOrderTraverse(BiTree T, Status(*visit)(TElemType e));
Status PostOrderTraverse(BiTree T, Status(*visit)(TElemType e));
Status LevelOrderTraverse(BiTree T, Status(*visit)(TElemType e));

Status PreOrderTraverse(BiTree T, Status(*visit)(TElemType e)){
    if (T){
        if (visit(T->data))
            if (PreOrderTraverse(T->LChild, visit))
                if (PreOrderTraverse(T->RChild, visit))
                    return OK;
        return ERROR;
    } else {
        return OK;
    }
}

Status InOrderTraverse(BiTree T, Status(*visit)(TElemType e)){
    if (T){
        if (PreOrderTraverse(T->LChild, visit))
            if (visit(T->data))
                if (PreOrderTraverse(T->RChild, visit))
                    return OK;
        return ERROR;
    } else {
        return OK;
    }
}

Status PostOrderTraverse(BiTree T, Status(*visit)(TElemType e)){
    if (T){
        if (PreOrderTraverse(T->LChild, visit))
            if (PreOrderTraverse(T->RChild, visit))
                if (visit(T->data))
                    return OK;
        return ERROR;
    } else {
        return OK;
    }
}

Status InOrderTraverse_nonRecur1(BiTree T, Status(*visit)(TElemType e)){
    SqStack S = NULL;
    BiTNode *p;
    InitSqStack(S);
    Pop(S, T);
    while (!StackEmpty(S)){
        while (GetTop(S, p) && p){
            Push(S, *(p->LChild));
        }
        Pop(S, p);  // NULL pointer pop out
        if (!StackEmpty(S)) {
            Pop(S, p);
            if (!visit(p->data))
                return ERROR;
            Push(S, *(p->RChild));
        }
    }
}

Status InOrderTraverse_nonRecur2(BiTree T, Status(*visit)(TElemType e)){
    SqStack S = NULL;
    BiTNode *p = T;
    InitSqStack(S);
    while (p || !StackEmpty(S)){
        if (p){
            Push(S, *p);
            p = p->LChild;
        } else {
            Pop(S, p);
            visit(p->data);
            p = p->RChild;
        }
    }
}

Status CreateBiTree(BiTree T){
    int ch = getchar();
    if (ch == ' ')
        T = NULL;
    else{
        if (!T = (BiTNode*)malloc(sizeof(BiTNode)))
            exit(OVERFLOW);
        T->data = ch;
        CreateBiTree(T->LChild);
        CreateBiTree(T->RChild);
    }
    return OK;
}

/* Threaded Binary Tree */
