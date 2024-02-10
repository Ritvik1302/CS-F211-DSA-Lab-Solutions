#include <stdio.h>
#include <stdlib.h>
#include "personMerge.h"

void merge(person A[], int s, int mid, int e)
{
    person *C = (person *)malloc(sizeof(person) * (e - s + 1));
    mergeAux(A, s, mid, A, mid + 1, e, C, 0, e - s);
    for (int i = 0; i < e - s + 1; i++)
    {
        A[s + i] = C[i];
    }
    free(C);
}
