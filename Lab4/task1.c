#include <stdio.h>
#include <stdlib.h>

struct person
{
	int id;
	char *name;
	int age;
	int height;
	int weight;
};
typedef struct person person;

void insertInOrder(person v, person A[], int last)
{
	int j = last - 1;
	while (j >= 0 && v.height < A[j].height)
	{
		A[j + 1] = A[j];
		j--;
	}
	A[j + 1] = v;
}

void insertionSort(person A[], int n)
{
	for (int j = 1; j < n; j++)
	{
		insertInOrder(A[j], A, j);
	}
}

int main()
{
	person arr[5] = {{1, "Sokka", 15, 150, 45}, {2, "Aang", 112, 137, 35}, {3, "Zuko", 16, 160, 50}, {4, "Katara", 14, 145, 38}, {5, "Toph", 12, 113, 30}};
	insertionSort(arr, 5);
	printf("Sorted Persons By Height\n");
	for (int i = 0; i < 5; i++)
	{
		printf("%d %s %d %d %d\n", arr[i].id, arr[i].name, arr[i].age, arr[i].height, arr[i].weight);
	}
}