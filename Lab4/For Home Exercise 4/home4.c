#include "criminalMerge.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct crime
{
    char *str;
    int year;
    int id;
};
typedef struct crime crime;

void mergeSort(criminal A[], int st, int en)
{
    if (en - st < 1)
        return;
    int mid = (st + en) / 2;   // mid is the floor of (st+en)/2
    mergeSort(A, st, mid);     // sort the first half
    mergeSort(A, mid + 1, en); // sort the second half
    merge(A, st, mid, en);     // merge the two halves
}

int main()
{
    FILE *fp;
    fp = fopen("criminal_database.txt", "r");
    if (fp == NULL) {
        printf("Error opening file");
        exit(1);
    }

    long int lines = 0;
    fscanf(fp, "%ld\n", &lines);
    printf("%ld", lines);

    criminal arr[lines];

    int id;
    char *name = malloc(50);
    int age;

    int i = 0;
    while (i < lines && fscanf(fp, "%[^,],%d,%d\n", name, &age, &id) == 3) {
        arr[i].age = age;
        arr[i].id = id;
        arr[i].name = malloc(50);
        arr[i].criminality = 0;
        strcpy(arr[i].name, name);
        i++;
    }

    fclose(fp);

    fp = fopen("crimes.txt", "r");
    if (fp == NULL) {
        printf("Error opening file");
        exit(1);
    }
    int lines2;
    fscanf(fp, "%d\n", &lines2);
    printf(" %d", lines2);

    crime arr2[lines2];
    i = 0;
    while (i < lines2) {
        fscanf(fp, "%[^,],%d,%d\n", name, &age, &id);
        arr2[i].year = age;
        arr2[i].id = id;
        arr2[i].str = malloc(50);
        strcpy(arr2[i].str, name);
        //printf("%d,%d,%s",arr2[i].year,arr2[i].id,arr2[i].str);
        //printf("%d,%d,%s",age,id,name);
        i++;
    }
    fclose(fp);

    for (int i = 0; i < lines; i++) {
        int a = 2023 - arr[i].age;
        for (int j = 0; j < lines2; j++) {
            if (arr2[j].id == arr[i].id) {
                float coefficient = 0;
                if (strcmp(arr2[j].str, "ARSON") == 0)
                    coefficient = 10;
                else if (strcmp(arr2[j].str, "ASSAULT") == 0)
                    coefficient = 5;
                else if (strcmp(arr2[j].str, "BURGLARY") == 0)
                    coefficient = 5;
                else if (strcmp(arr2[j].str, "CRIMINAL MISCHIEF") == 0)
                    coefficient = 5;
                else if (strcmp(arr2[j].str, "GRAND LARCENY") == 0)
                    coefficient = 10;
                else if (strcmp(arr2[j].str, "GRAND THEFT AUTO") == 0)
                    coefficient = 5;
                else if (strcmp(arr2[j].str, "HOMICIDE") == 0)
                    coefficient = 20;
                else if (strcmp(arr2[j].str, "BREAKING AND ENTERING") == 0)
                    coefficient = 5;
                else if (strcmp(arr2[j].str, "ROBBERY") == 0)
                if (arr2[j].year - a < 18)
                    coefficient *= 0.5;
                arr[i].criminality += coefficient;
            }
        }
    }

    mergeSort(arr, 0, lines - 1);

    FILE *fp2 = fopen("sorted.txt", "w");
    if (fp2 == NULL) {
        printf("Error opening output file");
        exit(1);
    }
    for(int i = 0; i < lines; i++) {
        fprintf(fp2, "%s,%d,%d,%f\n", arr[i].name, arr[i].age, arr[i].id, arr[i].criminality);
    }
    fclose(fp2);
    return 0;
}