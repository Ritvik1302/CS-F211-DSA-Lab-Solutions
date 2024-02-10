#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/time.h>
struct timeval t1, t2;
double time_taken;
struct person
{
	long int id;
	char *name;
	int age;
	int height;
	int weight;
};
typedef struct person person;

void insertInOrder(person v, person A[], long int last)
{
	long int j = last - 1;
	while(j >= 0 && v.height < A[j].height)
	{
	A[j+1] = A[j];
	j--;
	}
	A[j+1] = v;
}

void insertionSort(person A[], long int n)
{
for(long int j = 1; j < n; j++)
	{
		insertInOrder(A[j], A, j);
	}
}

int main(int argc, char* argv[]){
	
	FILE *fp;
    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("Error opening file");
        exit(1);
    }

    long int id = 0;
    char name[50];
    int age = 0;
    int height = 0;
    int weight = 0;
    int ind = 0;

    char *line = malloc(1000);
    long int lines = 0;
    while (fscanf(fp, "%ld,%[^,],%d,%d,%d\n", &id, name, &age, &height, &weight) == 5) {
        lines++;
    }

    fclose(fp);

    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("Error opening file");
        exit(1);
    }
    printf("%ld\n", lines);
    long int len = lines;
    person *arr = malloc(lines * sizeof(person));

    while (len--) {
    	fscanf(fp, "%ld,%[^,],%d,%d,%d\n", &id, name, &age, &height, &weight);
    	
        arr[ind].id = id;
        arr[ind].age = age;
        arr[ind].name = malloc(50);
        strcpy(arr[ind].name,name);
        arr[ind].height = height;
        arr[ind].weight = weight;
        ind++;
        //printf("%ld %s %d\n",id,name,height);
    }
    fclose(fp);
    gettimeofday(&t1, NULL);
    insertionSort(arr,lines);
    gettimeofday(&t2,NULL);

    time_taken = (t2.tv_sec - t1.tv_sec) * 1e6;
	time_taken = (time_taken + (t2.tv_usec - t1.tv_usec)) * 1e-6;

	printf("Time to Sort %f seconds to execute\n", time_taken);
	
}