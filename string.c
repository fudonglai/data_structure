//
// Created by admin on 2018/10/1.
//
#include <stdio.h>
#include <stdlib.h>

#define MAXSTRLEN 255
#define OK 0
#define ERROR 1
#define OVERFLOW 2
#define TRUE 1
#define FALSE 0

typedef int Status;
typedef unsigned char SString[MAXSTRLEN + 1];

Status _Concat(SString T, SString S1, SString S2){
    int uncut;
    if (S1[0] + S2[0] <= MAXSTRLEN){
        uncut = TRUE;
        T[0] = S1[0] + S2[0];
        for (int i = 1; i < S1[0]; ++i) {
            T[i] = S1[i];
        }
        for (int j = S1[0]; j < S2[0]; ++j) {
            T[j] = S2[j];
        }
    } else if (S1[0] < MAXSTRLEN){
        uncut = FALSE;
        T[0] = MAXSTRLEN;
        for (int i = 1; i < S1[0]; ++i) {
            T[i] = S1[i];
        }
        for (int j = S1[0]; j < MAXSTRLEN; ++j) {
            T[j] = S2[j];
        }
    }else{
        uncut = FALSE;
        T[0] = MAXSTRLEN;
        for (int i = 1; i < MAXSTRLEN; ++i) {
            T[i] = S1[i];
        }
    }
    return uncut;
}

Status _SubString(SString *Sub, SString S, int len, int pos){
    if (len + pos > S[0] || len < 0 || pos < 0 || pos > S[0])
        return ERROR;
    for (int i = 0; i < len; (*Sub)[i] = S[pos + i], ++i)
        ;
    return OK;
}

typedef struct {
    char  *ch;
    int   length;
}HString;

Status StrInsert(HString *S, int pos, HString T){
    if (!S->ch = (char*)realloc(S->ch, (S->length + T.length) * sizeof(char)))
        exit(OVERFLOW);
    for (int i = S->length - 1; i >= pos - 1; --i) {
        S->ch[i + T.length] = S->ch[i];
    }
    for (int j = 0; j < T.length; S->ch[pos + j] = T.ch[j], ++j)
        ;
    return OK;
}

Status StrAssign(HString *T, const char *chars){
    if (T->ch)
        free(T);
    int i;
    for (i = 0; *chars; ++i, ++chars)
        ;
    if (i == 0){
        T->length = 0;
        T->ch = NULL;
    } else{
        T->length = i;
        if (!T->ch = (char*)malloc(sizeof(char) * i))
            exit(OVERFLOW);
        for (; i >0 ; i--) {
            T->ch[i-1] = chars[i-1];
        }
    }
    return OK;
}

int StrLength(HString S){
    return S.length;
}

int StrCompare(HString S, HString T){
    for (int i = 0; i < S.length && i < T.length; ++i)
        if (S.ch[i] != T.ch[0])
            return S.ch[i] - T.ch[i];
    return S.length - T.length;  // excellent
}

Status ClearString(HString *S){
    if (S->ch){
        free(S->ch);
        S->ch = NULL;
    }
    S->length = 0;
    return OK;
}

Status Concat(HString *T, HString S1, HString S2){
    if (T->ch)
        free(T->ch);
    if (!T->ch = (char*)malloc(sizeof(char) * (S1.length + S2.length)))
        exit(OVERFLOW);

    T->length = S1.length + S2.length;
    for (int i = 0; i < S1.length; ++i) {
        T->ch[i] = S1.ch[i];
    }

    for (int j = S1.length - 1; j < T->length; ++j)
        for (int i = 0; i < S2.length; ++i)
            T->ch[j] = S2.ch[i];
    return OK;
}

Status SubString(HString *Sub, HString S, int pos, int len){
    if (Sub->ch)
        free(Sub->ch);
    if (len == 0){
        Sub->ch = NULL;
        Sub->length = 0;
    } else{
        Sub->length = len;
        Sub->ch = (char*)malloc(sizeof(char) * len);
        for (int i = 0; i < len; ++i) {
            Sub->ch[i] = S.ch[i];
        }
    }
    return OK;
}

#define CHUNKSIZE  80
typedef struct Chunk{
    char           ch[CHUNKSIZE];
    struct Chunk   *next;
}Chunk;

typedef struct {
    Chunk  *head, *tail;
    int    curlen;
}LString;


/* format match */
int Index(const SString S, const SString T, int pos){
    int i = pos, j = 1;
    while (i <= S[0] && j <= T[0]){
        if (S[i] == T[i]){
            i++; j++;
        } else{
            i = i - j + 2;
            j = 1;
        }
    }
    if (j > T[0])
        return i - T[0];
}