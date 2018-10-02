//
// Created by admin on 2018/10/2.
//

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>   // va_start, va_arg, va_end

#define OK 0
#define ERROR 1
#define OVERFLOW 2
#define UNDERFLOW (-2)
#define TRUE 1
#define FALSE 0
#define MAX_ARRAY_DIM   8

typedef int Status;
typedef int ElemType;
typedef struct {
    ElemType  *base;
    int        dim;
    int       *bounds;
    int       *constants;
}Array;

Status InitArray(Array *A, int dim, ...){
    if (dim < 1 || dim > MAX_ARRAY_DIM)
        return ERROR;
    A->dim = dim;
    if (!A->bounds = (int*)malloc(sizeof(int) * dim))
        exit(OVERFLOW);

    int elem_total = 1;
    va_list ap;
    va_start(ap, dim);
    for (int i = 0; i < dim; ++i) {
        A->bounds[i] = va_arg(ap, int);
        if (A->bounds[i] < 0)
            return UNDERFLOW;
        elem_total *= A->bounds[i];
    }
    va_end(ap);

    if (!A->base = (ElemType*)malloc(sizeof(ElemType) * elem_total))
        exit(OVERFLOW);
    if (!A->constants = (int*)malloc(sizeof(int) * dim))
        exit(OVERFLOW);
    A->constants[dim -1] = 1;  // identity pointer
    for (int j = dim - 2; j >= 0; --j) {
        A->constants[j] = A->constants[j + 1] * A->bounds[j + 1];
    }
    return OK;
}

Status DestroyArray(Array *A){
    if (!A->bounds)
        return ERROR;
    free(A->bounds); A->bounds = NULL;

    if (!A->constants)
        return ERROR;
    free(A->constants); A->constants = NULL;

    if (!A->base)
        return ERROR;
    free(A->base); A->base = NULL;

    return OK;
}

Status Locate(Array A, va_list ap, int *off){
    int ind;
    *off = 0; // records the relative address
    for (int i = 0; i < A.dim; ++i) {
        ind = va_arg(ap, int);
        if (ind < 0 || ind >= A.bounds[i])
            return ERROR;
        *off += ind * A.constants[i];
    }
    return OK;
}

Status Value(Array A, ElemType *e, ...){
    va_list ap;
    int off = 0;
    Status res;
    va_start(ap, A.dim);
    if ((res = Locate(A, ap, &off)) != OK)
        return res;
    va_end(ap);
    *e = *(A.base + off);
    return OK;
}

Status Assign(Array *A, ElemType e, ...){
    int off = 0;
    va_list ap;
    Status res;
    va_start(ap, A->dim);
    if ((res = Locate(*A, ap, &off)) != OK)
        return res;
    va_end(ap);
    *(A->base + off) = e;
    return OK;
}