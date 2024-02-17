#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stringMerge.h"

void merge(char* A[], int s, int mid, int e)
{
    char** C = (char**)malloc(sizeof(char*) * (e - s + 1));
    for(int i=0; i < e-s+1; i++){
        C[i] = (char*)malloc(6*sizeof(char));
    }
    mergeAux(A, s, mid, A, mid + 1, e, C, 0, e - s);
    for (int i = 0; i < e - s + 1; i++)
    {
        strcpy(A[s + i],C[i]);
    }
    free(C);
}

void mergeStatic(char A[][6], int s, int mid, int e)
{
    char C[e-s+1][6];

    mergeAuxStatic(A, s, mid, A, mid + 1, e, C, 0, e - s);

    for (int i = 0; i < e - s + 1; i++)
    {
        strcpy(A[s + i],C[i]);
    }
    free(C);
}

