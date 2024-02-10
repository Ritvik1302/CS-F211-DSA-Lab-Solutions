#include <stdio.h>
#include <stdlib.h>
#include "criminalMerge.h"

void merge(criminal A[], int s, int mid, int e)
{
    criminal *C = (criminal *)malloc(sizeof(criminal) * (e - s + 1));
    mergeAux(A, s, mid, A, mid + 1, e, C, 0, e - s);
    for (int i = 0; i < e - s + 1; i++)
    {
        A[s + i] = C[i];
    }
    free(C);
}
