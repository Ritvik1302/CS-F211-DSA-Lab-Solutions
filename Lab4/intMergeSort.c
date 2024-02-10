#include "intMerge.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
struct timeval t1, t2;
double time_taken;
void mergeSort(int A[], int st, int en)
{
    if (en - st < 1)
        return;
    int mid = (st + en) / 2;   // mid is the floor of (st+en)/2
    mergeSort(A, st, mid);     // sort the first half
    mergeSort(A, mid + 1, en); // sort the second half
    merge(A, st, mid, en);     // merge the two halves
}

int main(int argc, char* argv[])
{
    FILE *fp;
    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("Error opening file");
        exit(1);
    }
    char *line = malloc(10);
    int num;
    long int lines = 0;
    while (fscanf(fp, "%d\n", &num) == 1) {
        lines++;
    }
    printf("%d",lines);
    fclose(fp);
    int arr[lines];
    fp = fopen(argv[1], "r");
    int i=0;
    while (fscanf(fp, "%d\n", &num) == 1) {
        arr[i]-num;
        i++;
    }
    gettimeofday(&t1,NULL);
    mergeSort(arr,0,lines-1);
    gettimeofday(&t2,NULL);

    time_taken = (t2.tv_sec - t1.tv_sec) * 1e6;
	time_taken = (time_taken + (t2.tv_usec - t1.tv_usec)) * 1e-6;

	printf("\nTime to Sort %f seconds to execute\n", time_taken);
}