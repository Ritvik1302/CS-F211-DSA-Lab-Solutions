#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include"personMerge.h"

#define CHUNK_SIZE 1000000

void mergeSort(person A[], int st, int en)
{
    if (en - st < 1)
        return;
    int mid = (st + en) / 2;   // mid is the floor of (st+en)/2
    mergeSort(A, st, mid);     // sort the first half
    mergeSort(A, mid + 1, en); // sort the second half
    merge(A, st, mid, en);     // merge the two halves
}

void externalMergeSort(FILE *inputFile, int numChunks) {
    char filename[20];
    for (int chunk = 1; chunk <= numChunks; chunk++) {
        person *chunkData = malloc(CHUNK_SIZE * sizeof(person));
        int readCount = fread(chunkData, sizeof(person), CHUNK_SIZE, inputFile);


        mergeSort(chunkData, 0, readCount - 1);

        sprintf(filename, "sorted%d.csv", chunk);
        FILE *sortedFile = fopen(filename, "w");
        fwrite(chunkData, sizeof(person), readCount, sortedFile);
        fclose(sortedFile);

        free(chunkData);
    }

    for (int i = 2; i <= numChunks; i *= 2) {
        for (int j = 1; j <= numChunks; j += i * 2) {
            sprintf(filename, "sorted%d.csv", j);
            FILE *file1 = fopen(filename, "r");
            sprintf(filename, "sorted%d.csv", j + i - 1);
            FILE *file2 = fopen(filename, "r");

            sprintf(filename, "sorted%d.csv", j / i * 2);
            FILE *mergedFile = fopen(filename, "w");

            person record1, record2;
            while (fread(&record1, sizeof(person), 1, file1) && fread(&record2, sizeof(person), 1, file2)) {
                if (record1.id < record2.id) {
                    fwrite(&record1, sizeof(person), 1, mergedFile);
                    fseek(file2, -sizeof(person), SEEK_CUR);
                } else {
                    fwrite(&record2, sizeof(person), 1, mergedFile);
                    fseek(file1, -sizeof(person), SEEK_CUR);
                }
            }

            while (fread(&record1, sizeof(person), 1, file1)) {
                fwrite(&record1, sizeof(person), 1, mergedFile);
            }

            while (fread(&record2, sizeof(person), 1, file2)) {
                fwrite(&record2, sizeof(person), 1, mergedFile);
            }

            fclose(file1);
            fclose(file2);
            fclose(mergedFile);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE *inputFile = fopen(argv[1], "r");
    if (inputFile == NULL) {
        printf("Error opening input file\n");
        return 1;
    }

    fseek(inputFile, 0, SEEK_END);
    long fileSize = ftell(inputFile);
    rewind(inputFile);
    int numChunks = (fileSize + CHUNK_SIZE - 1) / CHUNK_SIZE;

    struct timeval t1, t2;
    double elapsedTime;

    gettimeofday(&t1, NULL);
    externalMergeSort(inputFile, numChunks);
    gettimeofday(&t2, NULL);

    elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      
    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;
    printf("Total time taken for sorting: %.2f ms\n", elapsedTime);

    fclose(inputFile);
    return 0;
}
