#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "stringMerge.h"

void mergeSort(char* A[], int st, int en)
{
    if (en - st < 1)
        return;
    int mid = (st + en) / 2;   // mid is the floor of (st+en)/2
    mergeSort(A, st, mid);     // sort the first half
    mergeSort(A, mid + 1, en); // sort the second half
    merge(A, st, mid, en);     // merge the two halves
}
void mergeSortStatic(char A[][6], int st, int en)
{
    if (en - st < 1)
        return;
    int mid = (st + en) / 2;   // mid is the floor of (st+en)/2
    mergeSortStatic(A, st, mid);     // sort the first half
    mergeSortStatic(A, mid + 1, en); // sort the second half
    mergeStatic(A, st, mid, en);     // merge the two halves
}

int main(){

    int n;
    printf("Enter Size: ");
    scanf("%d",&n);

    char **A = (char**)malloc(n*sizeof(char *));
    char B[n][6];
    for(int i=0;i<n;i++){
        A[i] = (char*)malloc(6*sizeof(char));
        strcpy(A[i] , "hello");
        strcpy(B[i] , "hello");
    }

	struct timeval t1, t2;
	double time_taken;

	gettimeofday(&t1, NULL);
    mergeSort(A,0,n-1);
	gettimeofday(&t2, NULL);
	
	time_taken = (t2.tv_sec - t1.tv_sec) * 1e6;
	time_taken = (time_taken + (t2.tv_usec - t1.tv_usec)) * 1e-6;
	printf("Pointer Array took %f seconds to Sort\n", time_taken);

	gettimeofday(&t1, NULL);
    mergeSortStatic(B,0,n-1);
	gettimeofday(&t2, NULL);
	
	time_taken = (t2.tv_sec - t1.tv_sec) * 1e6;
	time_taken = (time_taken + (t2.tv_usec - t1.tv_usec)) * 1e-6;
	printf("Static Array took %f seconds to Sort\n", time_taken);

	return 0;
}