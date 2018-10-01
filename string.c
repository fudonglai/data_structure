//
// Created by admin on 2018/10/1.
//
#include <stdio.h>

#define MAXSTRLEN 255
#define OK 0
#define ERROR 1
#define OVERFLOW 2
#define TRUE 1
#define FALSE 0

typedef int Status;
typedef unsigned char SString[MAXSTRLEN + 1];

Status Concat(SString T, SString S1, SString S2){
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