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
    int n = 6;
    int arr[6] = {-1,0,1,2,-1,-4};
    mergeSort(arr,0,n-1);
    int i = 0, l=0, r=n-1;
    for(i=0;i<n;i++){
        l=i+1;
        r=n-1;
        while(l<r){
            if(arr[l]+arr[i]+arr[r]==0&&i!=l&&l!=r&&i!=r){
                printf("\n%d %d %d\n",arr[l],arr[i],arr[r]);
                break;
            }
            if(arr[l]+arr[i]+arr[r]<=0)l++;
            else r--;
        }
    }
}