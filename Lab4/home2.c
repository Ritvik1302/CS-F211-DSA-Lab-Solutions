#include "intMerge.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

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
    int n = 4;
    int arr[4] = {3,2,1,3};
    mergeSort(arr,0,n-1);
    for(int i=0;i<n;i++)printf("%d",arr[i]);
    for(int i=0;i<n;i++){
        if(arr[i]==n-i-1){
            printf("\n%d\n",arr[i]);
            return 0;
        }
    }
	printf("\nNo Such Integer Found\n");
}