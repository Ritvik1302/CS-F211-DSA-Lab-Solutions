#include "queue.h"
#include "heap_usage.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

struct timeval t1, t2, t3;
double time_taken;
Element iftoe (int i, float f);
int main(int argc, char *argv[])
{
    FILE *fp;
    fp = fopen(argv[1], "r");
    if(fp == NULL)
    {
        printf("Error opening file");
        exit(1);
    }

    char *line = malloc(100); 
    Queue *queue = createQueue();
    gettimeofday(&t1, NULL);
    gettimeofday(&t3, NULL);

    int score = 0;
    float cg = 0;
    int i = 0;
    while(fgets(line, 100, fp) != NULL)
    {
        char *token;
        token = strtok(line, ",");
        score = atoi(token);
        token = strtok(NULL, ",");
        cg = atof(token);
        enqueue(queue, iftoe(score,cg));
        i++;
    }
    fclose(fp);
    printf("\nHeap Memory Used: %ld", heapMemoryAllocated);
    gettimeofday(&t2, NULL);
    time_taken = (t2.tv_sec - t1.tv_sec) * 1e6;
    time_taken = (time_taken + (t2.tv_usec - t1.tv_usec)) * 1e-6;
    printf("\nInserting in Queue took %f seconds to execute\n", time_taken);

    gettimeofday(&t1, NULL);
    destroyQueue(queue);
    gettimeofday(&t2, NULL);
    time_taken = (t2.tv_sec - t1.tv_sec) * 1e6;
    time_taken = (time_taken + (t2.tv_usec - t1.tv_usec)) * 1e-6;
    printf("\nDeleting from Queue took %f seconds to execute\n", time_taken);

    gettimeofday(&t2, NULL);
    time_taken = (t2.tv_sec - t3.tv_sec) * 1e6;
    time_taken = (time_taken + (t2.tv_usec - t3.tv_usec)) * 1e-6;
    printf("\nEntire Operation took %f seconds to execute\n", time_taken);

}
Element iftoe (int i, float f)
{
    Element e;
    e.int_value = i;
    e.float_value = f;
    return e;
}