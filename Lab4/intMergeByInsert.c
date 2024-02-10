#include <stdio.h>
#include <stdlib.h>
#include "intMerge.h"

void insertInOrder(int v, int A[], int last)
{
	int j = last - 1;
	while (j >= 0 && v< A[j])
	{
		A[j + 1] = A[j];
		j--;
	}
	A[j + 1] = v;
}

void insertionSort(int A[], int n)
{
	for (int j = 1; j < n; j++)
	{
		insertInOrder(A[j], A, j);
	}
}

void merge(int A[], int s, int mid, int e)
{
    insertionSort(A,e-s+1);
}
