#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
struct timeval t1, t2;
double time_taken;

void mergeAuxRec(int L1[], int s1, int e1, int L2[], int s2, int e2, int L3[], int s3, int e3)
{
    if(L1[s1] > L2[s2])
    {
        L3[s3] = L2[s2];
        mergeAuxRec(L1, s1, e1, L2, s2 + 1, e2, L3, s3 + 1, e3);
    }
    else
    {
        L3[s3] = L1[s1];
        mergeAuxRec(L1, s1 + 1, e1, L2, s2, e2, L3, s3 + 1, e3);
    }
}

void mergeAuxIter(int L1[], int s1, int e1, int L2[], int s2, int e2, int L3[], int s3, int e3)
{
    int i, j, k;
    // Traverse both arrays
    i = s1;
    j = s2;
    k = s3;
    while (i <= e1 && j <= e2)
    {
        // Check if current element of first array is smaller
        // than current element of second array
        // If yes, store first array element and increment first
        // array index. Otherwise do same with second array
        if (L1[i] < L2[j])
            L3[k++] = L1[i++];
        else
            L3[k++] = L2[j++];
    }
    // Store remaining elements of first array
    while (i <= e1)
        L3[k++] = L1[i++];
    // Store remaining elements of second array
    while (j <= e2)
        L3[k++] = L2[j++];
}

void mergeRec(int A[], int s, int mid, int e)
{
    int *C = (int *)malloc(sizeof(int) * (e - s + 1));
    mergeAuxRec(A, s, mid, A, mid + 1, e, C, 0, e - s);
    for (int i = 0; i < e - s + 1; i++)
    {
        A[s + i] = C[i];
    }
    free(C);
}

void mergeIter(int A[], int s, int mid, int e)
{
    int *C = (int *)malloc(sizeof(int) * (e - s + 1));
    mergeAuxIter(A, s, mid, A, mid + 1, e, C, 0, e - s);
    for (int i = 0; i < e - s + 1; i++)
    {
        A[s + i] = C[i];
    }
    free(C);
}

void mergeSortIter(int A[], int st, int en)
{
    if (en - st < 1)
        return;
    int mid = (st + en) / 2;   // mid is the floor of (st+en)/2
    mergeSortIter(A, st, mid);     // sort the first half
    mergeSortIter(A, mid + 1, en); // sort the second half
    mergeIter(A, st, mid, en);     // merge the two halves
}
void mergeSortRec(int A[], int st, int en)
{
    if (en - st < 1)
        return;
    int mid = (st + en) / 2;   // mid is the floor of (st+en)/2
    mergeSortRec(A, st, mid);     // sort the first half
    mergeSortRec(A, mid + 1, en); // sort the second half
    mergeRec(A, st, mid, en);     // merge the two halves
}

int main()
{
    FILE *fp = fopen("numbers5000.txt", "r");
    int numbers[5000];
    int i = 0;
    while (fscanf(fp, "%d", &numbers[i]) != EOF)
    {
        i++;
    }
    fclose(fp);
    gettimeofday(&t1,NULL);
    mergeSortRec(numbers,0,5000-1);
    gettimeofday(&t2,NULL);

    time_taken = (t2.tv_sec - t1.tv_sec) * 1e6;
	time_taken = (time_taken + (t2.tv_usec - t1.tv_usec)) * 1e-6;

	printf("Recursive Merge Sort %f seconds to execute\n", time_taken);

    fp = fopen("numbers5000.txt", "r");
    i = 0;
    while (fscanf(fp, "%d", &numbers[i]) != EOF)
    {
        i++;
    }
    fclose(fp);
    gettimeofday(&t1,NULL);
    mergeSortIter(numbers,0,5000-1);
    gettimeofday(&t2,NULL);

    time_taken = (t2.tv_sec - t1.tv_sec) * 1e6;
    time_taken = (time_taken + (t2.tv_usec - t1.tv_usec)) * 1e-6;

    printf("Iterative Merge Sort %f seconds to execute\n", time_taken);
}