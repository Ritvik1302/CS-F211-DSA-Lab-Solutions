#include <stdio.h>
#include <sys/time.h>

struct timeval t1, t2;
double time_taken;

// recursive insertion sort
void insertionSortR(int *arr, int n)
{
	if (n <= 1) return;
	insertionSortR(arr, n-1);
	int last = arr[n-1];
	int j = n-2;
	while (j >= 0 && arr[j] > last)
	{
		arr[j+1] = arr[j];
		j--;
	}
	arr[j+1] = last;
}
// iterative insertion sort
void insertionSortI(int *arr, int n)
{
	for (int i = 1; i < n; i++)
	{
		int last = arr[i];
		int j = i-1;
		while (j >= 0 && arr[j] > last)
		{
			arr[j+1] = arr[j];
			j--;
		}
		arr[j+1] = last;
	}
}
int main(){

	FILE *fp = fopen("numbers50000.txt", "r");
    int numbers[50000];
    int i = 0;
    while (fscanf(fp, "%d", &numbers[i]) != EOF)
    {
        i++;
    }
    fclose(fp);

	gettimeofday(&t1, NULL);
	insertionSortI(numbers,50000);
	gettimeofday(&t2, NULL);
	time_taken = (t2.tv_sec - t1.tv_sec) * 1e6;
	time_taken = (time_taken + (t2.tv_usec - t1.tv_usec)) * 1e-6;
	printf("insertionSortI took %f seconds to execute\n", time_taken);

	fp = fopen("numbers50000.txt", "r");
	i = 0;
    while (fscanf(fp, "%d", &numbers[i]) != EOF)
    {
        i++;
    }
    fclose(fp);

	gettimeofday(&t1, NULL);
	insertionSortR(numbers,50000);
	gettimeofday(&t2, NULL);
	time_taken = (t2.tv_sec - t1.tv_sec) * 1e6;
	time_taken = (time_taken + (t2.tv_usec - t1.tv_usec)) * 1e-6;
	printf("insertionSortR took %f seconds to execute\n", time_taken);

}