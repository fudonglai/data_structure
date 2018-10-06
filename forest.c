//
// Created by admin on 2018/10/3.
//
#include <stdio.h>
#include <stdlib.h>
#include <intrin.h>
#include "condition.h"

#define MAX_TREE_SIZE  100
typedef int TElemType;

/* parent representation */
typedef struct PTNode{
    TElemType data;
    int       parent;
}PTNode;
typedef struct{
    PTNode  nodes[MAX_TREE_SIZE];
    int     r, n;  //index of root, total of nodes. (positions of the first and last)
}PTree;

/* child representation */
typedef struct CTNode{  //Child Node
    int            child;
    struct CTNode  *next;
}*ChildPrt;

typedef struct {
    TElemType data;
    ChildPrt  first_child;
}CTBox;

typedef struct {
    CTBox nodes[MAX_TREE_SIZE];
    int   n, r;
}CTree;

/* Binary-Link Child-Sibling Tree representation */
typedef struct CSNode{
    TElemType data;
    struct CSNode *child;
    struct CSNode *sibling;
}CSNode, *CSTree;

typedef PTree MFSet;

int find_mfset(MFSet S, int i){
    int j;
    if (i<1 || i > S.n)
        return -1;
    for (j = i; S.nodes[j].parent > 0; j = S.nodes[j].parent)
        ;
    return j;
}//find

Status merge_mfset(MFSet *S, int i, int j){
    if (i < 1 || i > S->n || j < 1 || j > S->n)
        exit(ERROR);
    S->nodes[i].parent = j;
    return OK;
}//merge

Status mix_mfset(MFSet *S, int i, int j){  //修改存储结构，root 的 parent 内存储子集中成员个数的相反数
    if (i < 1 || i > S->n || j < 1 || j > S->n)
        return ERROR;
    if (S->nodes[i].parent > S->nodes[j].parent){
        S->nodes[j].parent += S->nodes[i].parent;
        S->nodes[i].parent = j;
    } else{
        S->nodes[i].parent += S->nodes[j].parent;
        S->nodes[j].parent = i;
    }
}

/* HuffmanTree */
typedef struct {
    unsigned int weight;
    unsigned int parent, l_child, r_child;
}HTNode, *HuffmanTree;
typedef char** HuffmanCode;

void HuffmanCoding(HuffmanTree HT, HuffmanCode HC, unsigned int *w, int n) {
    if (n <= 1) return;
    void Select(HuffmanTree, int, int*, int*);
    int *s1 = NULL, *s2 = NULL;
    int m = 2 * n + 1;
    HuffmanTree p = HT;
    HT = (HuffmanTree) malloc(sizeof(HTNode) * (m + 1)); //ignore the 0 index
            
    for (int i = 1; i <= n; ++i, ++p, ++w)
        *p = {*w, 0, 0, 0};
    for (int j = n; j < m; ++j)
        *p = {0, 0, 0, 0};
    for (int k = n + 1; k < m; ++k) {  //Build the tree
        Select(HT, k-1, s1, s2);
        HT[*s1].parent = HT[*s2].parent = (unsigned int)k;
        HT[k].l_child = (unsigned int)*s1;
        HT[k].r_child = (unsigned int)*s2;
        HT[k].weight = HT[*s1].weight = HT[*s2].weight;
    }

    HC = (HuffmanCode)malloc(sizeof(char*) * (n + 1));
    char *cd = (char*)malloc(sizeof(char) * n);
    cd[n - 1] = '\0';
    unsigned int c, f;
    for (int i = 0; i <= n ; ++i) {
        int start = n - 1;
        for ( c = (unsigned int)i, f = HT[i].parent; f != 0; c = f, f = HT[f].parent) {
            if (HT[f].l_child == c)
                cd[--start] = '1';
            else
                cd[--start] = '0';
        }
            HC[i] =  (char*)malloc((n - start) * sizeof(char));
            strcpy(HC[i], &cd[start]);
    }
    free(cd);
}