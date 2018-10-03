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
Status PreOrderTraverse(BiTree T, Status(*Visit)(TElemType e));
Status InOrderTraverse(BiTree T, Status(*Visit)(TElemType e));
Status PostOrderTraverse(BiTree T, Status(*Visit)(TElemType e));
Status LevelOrderTraverse(BiTree T, Status(*Visit)(TElemType e));

Status PreOrderTraverse(BiTree T, Status(*Visit)(TElemType e)){
    if (T){
        if (Visit(T->data))
            if (PreOrderTraverse(T->LChild, Visit))
                if (PreOrderTraverse(T->RChild, Visit))
                    return OK;
        return ERROR;
    } else {
        return OK;
    }
}

Status InOrderTraverse(BiTree T, Status(*Visit)(TElemType e)){
    if (T){
        if (PreOrderTraverse(T->LChild, Visit))
            if (Visit(T->data))
                if (PreOrderTraverse(T->RChild, Visit))
                    return OK;
        return ERROR;
    } else {
        return OK;
    }
}

Status PostOrderTraverse(BiTree T, Status(*Visit)(TElemType e)){
    if (T){
        if (PreOrderTraverse(T->LChild, Visit))
            if (PreOrderTraverse(T->RChild, Visit))
                if (Visit(T->data))
                    return OK;
        return ERROR;
    } else {
        return OK;
    }
}

Status InOrderTraverse_nonRecur1(BiTree T, Status(*Visit)(TElemType e)){
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
            if (!Visit(p->data))
                return ERROR;
            Push(S, *(p->RChild));
        }
    }
}

Status InOrderTraverse_nonRecur2(BiTree T, Status(*Visit)(TElemType e)){
    SqStack S = NULL;
    BiTNode *p = T;
    InitSqStack(S);
    while (p || !StackEmpty(S)){
        if (p){
            Push(S, *p);
            p = p->LChild;
        } else {
            Pop(S, p);
            Visit(p->data);
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
typedef enum PointerTag {Link, Thread};  // Link == 0, Thread == 1
typedef struct BiThrNode{
    TElemType          data;
    struct BiThrNode   *LChild, *RChild;
    enum PointerTag    LTag, RTag;
}BiThrNode, *BiThrTree;

Status InOrderTraverse_Thr(BiThrTree T, Status(*Visit)(TElemType e)){
    BiThrNode *p = T->LChild;
    while (p != T){
        while (p->LTag == Link){
            p = p->LChild;
        }
        Visit(p->data);
        while (p->RTag == Thread && p->RChild != T){
            p = p->RChild;
            Visit(p->data);
        }
        p = p->RChild;
    }
}

Status InOrderThreading(BiThrTree ThrT, BiThrTree T){
    if (!(ThrT = (BiThrTree)malloc(sizeof(BiThrNode))))
        exit(OVERFLOW);
    ThrT->LTag = Link;
    ThrT->RTag = Thread;
    ThrT->RChild = ThrT;  // 右指针回指
    if (!T){
        ThrT->LChild = ThrT;
    } else{

    }
}

Status InThreading(BiThrTree p, BiThrTree pre){
    if (p){
        InThreading(p->LChild, pre);
        if (!p->LChild){
            p->LTag = Thread;
            p->LChild = pre;
            pre = p;
            if (!pre->RChild){
                pre->RTag = Thread;
                pre->RChild = p;
            }

        }
        // let me consider for some days
        InThreading(p->RChild, pre);
        if (!p->RChild){
            p->RTag = Thread;
        }

    }
}