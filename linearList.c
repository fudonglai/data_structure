#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE (-1)
#define OVERFLOW (-2)
#define LIST_INIT_SIZE 100  // initial distribution
#define LIST_INCREMENT 10   // increasing memory when overflow
#define MAXSIZE 1000        // Static Chain List Size

typedef int Status;
typedef int ElemType;
typedef ElemType* List;

/* Linear List */
Status InitList(List L);
Status DestroyList(List L);
Status ClearList(List L);
Status ListInsert(List L, int i, ElemType e); // insert e before i'th element
Status ListDelete(List L, int i, ElemType* e); // delete i'th element and assign it to e
int ListEmpty(List L); // return TRUE if List is empty else FALSE
int ListLength(List L);  // return the number of the elements in list
Status GetElem(List L, int i, ElemType* e); // e equals to the i'th element
int LocateElem(List L, ElemType e, int (*compare)(ElemType, ElemType)); //return the index of the first element fits the compare function or 0

void UnionList(List La, List Lb){
    int len_a = ListLength(La), len_b = ListLength(Lb);
    ElemType *e = NULL;
    int equal(ElemType, ElemType);
    for (int j = 1; j < len_b; ++j) {
        GetElem(Lb, j, e);
        if (!LocateElem(La, *e, equal))
            ListInsert(La, *e, j);
    }
}//UnionList

Status MergeList(List La, List Lb){
    List Lc = NULL;
    ElemType *p1 = La, *p2 = Lb;
    int Len_a = ListLength(La), Len_b = ListLength(Lb);
    int i = 1, j = 1, k = 0;
    InitList(Lc);
//    for (int i = 1; i < (Len_a >= Len_b ? Len_b: Len_a); i++, p2++, p1++)
    while (i <= Len_a && j <= Len_b){
        if (*p1 >= *p2){
            ListInsert(Lc, k++, *p2); j++;
        }
        else{
            ListInsert(Lc, k++, *p1); i++;
        }
    }
    while (i++ <= Len_a)
        ListInsert(Lc, k++, *(p1++));
    while (j++ <= Len_b)
        ListInsert(Lc, k++, *(p2++));
    return OK;
}// MergeList

/* Sequence List */
typedef struct {
    ElemType *elem;
    int      length;     //number of elements
    int      list_size;  //maximum num of elements
}SqList;

Status InitList_Sq(SqList L){
    L.elem = (ElemType * )malloc(LIST_INIT_SIZE * sizeof(ElemType));
    if (!L.elem)
        exit(OVERFLOW);
    L.length = 0;
    L.list_size = LIST_INIT_SIZE;
    return OK;
}

Status ListInsert_Sq(SqList L, int i, ElemType e){
    ElemType *q  = &(L.elem[i - 1]);
    ElemType *p = &(L.elem[L.length - 1]);
    for(; p >= q; p--)
        *(p + 1) = *p;
    *q = e;
    L.length += 1;
    return OK;
}

Status ListDelete_Sq(SqList L, int i, ElemType* e){
    ElemType *p = &(L.elem[i]);
    ElemType *q = L.elem + L.length - 1;
    *e = *p;
    while (p <= q)
        *p = *(p++);
    L.length--;
    return OK;
}

int LocateElem_Sq(SqList L, ElemType e, Status (*compare)(ElemType, ElemType)){
    int i = 1;
    while (!(*compare)(L.elem[i -1], e) && i++ <= L.length)
        return i-1;
    return -1;
}

void MergeList_Sq(SqList La, SqList Lb, SqList Lc){
    ElemType *pa = La.elem, *pb = Lb.elem;
    int i = 1, j = 1, k =0;
    while (i <= La.length && j <= Lb.length){
        if (*pa <= *pb){
            ListInsert_Sq(Lc, k++, *(pa++)); i++;
        }
        else{
            ListInsert_Sq(Lc, k++, *(pb++)); j++;
        }
    }
    while (i++ <= La.length)
        ListInsert_Sq(Lc, k++, *(pa++));
    while (j++ <= Lb.length)
        ListInsert_Sq(Lc, k++, *(pb++));
}

/* Linked List */
typedef struct LNode{
    ElemType       data;
    struct LNode*  next;
}LNode, *LinkList;


void GetElem_L(LinkList L, int i, ElemType* e){
    LNode *p = L;
    while (p && --i){
        p = p -> next;
    }
    *e = p -> data;
}

void ListInsert_L(LinkList L, int i, ElemType e){
    LNode* p = L;
    int j =1;
    while (p && j++ < i - 1){
        p = p -> next;
    }
    LNode* s = (LNode*) malloc(sizeof(LNode));
    s->next = p->next->next;
    s->data = e;
    p->next = s;
}

void ListDelete_L(LinkList L, int i, ElemType* e){
    LNode *p = L, *temp = NULL;
    while (p && (--i)-1){
        p = p->next;
    }
    temp = p->next;
    p->next = temp->next;
    *e = temp->data;
    temp->next = NULL;
    free(temp);
}

void CreateList_L(LinkList L, int n){
    L = (LinkList)malloc(sizeof(LNode));
    L->next = NULL;
    for (; n > 0; n--){
        LNode* p = (LNode*)malloc(sizeof(LNode));
        scanf((const char *) &(p->data));
        p->next = L->next;
        L->next = p;
    }
}

void MergeList_L(LinkList La, LinkList Lb, LinkList Lc){
    LNode *p1 = La->next, *p2 = Lb->next;
    Lc = La; Lb->next = NULL; free(Lb);
    LNode *p = Lc;
    while (p1 && p2){
        if (p1->data >= p2->data){
            p->next = p2; p = p2; p2 = p2->next;
        } else{
            p->next = p1; p = p1; p1 = p1->next;
        }
    }
    p->next = p1 ? p1: p2;
}


/* Static List */
typedef struct {
    ElemType  data;
    int       cur;
}Component, SLinkList[MAXSIZE];

int LocateElem_SL(SLinkList S, ElemType e, int (*compare)(ElemType, ElemType)){
    int i = S->cur;
    while (i && !(*compare)(S[i].data, e)){
        i = S[i].cur;
    }
    return i;
}

void InitSpace_SL(SLinkList space){
    for (int i = 0; i < MAXSIZE - 1; space[i++].cur = i)
        ;
    space[MAXSIZE - 1].cur = 0;
}

int Malloc_Sl(SLinkList space){
    int i = space->cur;
    space->cur = space[i].cur;
    return i;
}

void Free_SL(SLinkList space, int k){
    space[k].cur =  space->cur;
    space->cur = k;
}

void difference(SLinkList space, int S){  //(A - B)U(B - A)
    space = (Component*)malloc(sizeof(SLinkList));
    InitSpace_SL(space);
    S = Malloc_Sl(space);
    int p1 = S, p2 = space[S].cur;
    int m, n, i, b, k;
    scanf("%d%d", &m, &n); // the number of elements in A and B

    for (int j = 0; j < m; ++j) {
        i = Malloc_Sl(space);
        scanf((const char*)&space[i].data);
        space[p1].cur = i;
        p1 = i;  //p1 is the last index of the Static List
    }
    space[p1].cur = 0;
    
    for (int j = 0; j < n; ++j) {
        scanf((const char*)&b);
        while (p2 && b != space[p2].data){
            p2 = space[p2].cur;
        }
        if (p2 == 0){
            k = Malloc_Sl(space);
            space[k].data = b;
            space[k].cur = 0;
            space[p1].cur = k;
            p1 = k;

        } else{
            Free_SL(space, p2);
        }
    }
}

/* Dual Linked List */
typedef struct DulNode{
    ElemType          data;
    struct DulNode   *prior;
    struct DulNode   *next;
}DulNode, *DulLinkList;

Status ListInsert_DuL(DulLinkList L, int i, ElemType e){
    DulNode* p = L;
    DulNode* s = (DulNode*)malloc(sizeof(DulNode));
    while (p && --i - 1)
        p = p->next;  // p points to the previous node
    s->data = e; s->prior = p; s->next = p->next;
    p->next->prior = s; p->next = s;
    return OK;
}

Status ListDelete_DuL(DulLinkList L, int i, ElemType* e){
    DulNode* p = L;
    while (p && --i)
        p = p->next;  // p points to i'th node
    if (p == NULL)
        exit(ERROR);
    *e = p->data;
    p->prior->next = p->next;
    p->next->prior = p->prior;
    p->next = p->prior = NULL;
    free(p);
    return OK;
}

typedef struct Term{
    float         coef;
    int           expn;
    struct Term  *next;
} Term, *Polynomial;

int CompareExp(Term a, Term b){
    switch (a.expn % b.expn){
        case 1:
            return 0;
        case 0:
            return -1;
        default:
            return 1;
    }
}

void AddPolynomial(Polynomial Pa, Polynomial Pb){
    Term *ta = Pa->next, *tb = Pb->next;
    Term *p = NULL, *q = NULL;
    while (ta && tb){
        switch (CompareExp(*ta, *tb)){
            case 1:
                p = tb->next; tb->next = ta; tb = p; q = ta->next; ta->next = p; ta = q;
                break;// a greater than b
            case -1:
                p = ta->next; ta->next = tb; ta = p; q = tb->next; tb->next = p; tb = q;
                break;
            case 0:
                ta->coef += tb->coef; p = tb; tb = tb->next; ta = ta->next; free(p);
                break;
            default: break;
        }
    }
}

int main() {
    printf("Hello, World!\n");
    return 0;
}