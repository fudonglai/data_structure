//
// Created by admin on 2018/10/8.
//
#include "condition.h"
#include <stdlib.h>
#include <stdio.h>

typedef enum {ATOM, LIST}ElemTag; // ATOM == 0, LIST == 1, atom, lists
typedef int AtomType;

typedef struct _GLNode{
    ElemTag  tag;
    union {
        AtomType  atom;
        struct {
            struct _GLNode *hp, *tp;
        }ptr;
    };
}*_GList;

typedef struct GLNode{
    ElemTag             tag;
    union {
        AtomType        atom;
        struct GLNode   *hp;
    };
    struct GLNode       *tg;
}*GList;


typedef struct MPNode {
    ElemTag     tag;
    int         exp;
    union {
        float   coef;
        struct MPNode *hp;
    };
    struct MPNode *tp;
}*MPList;
