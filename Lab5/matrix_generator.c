#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
void matGen(int ** M1, int N)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            M1[i][j] = rand() % 100;
        }
    }
}