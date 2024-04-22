#include <stdio.h>

int main(void)
{
    // Reads the numbers stored in numbers1000.txt and stores them into an integer array
    FILE *fp = fopen("numbers1000.txt", "r");
    int numbers[1000];
    int i = 0;
    while (fscanf(fp, "%d", &numbers[i]) != EOF)
    {
        i++;
    }
    fclose(fp);

    // Perform some operation on the numbers
    // ...

    // Example operation: Print the numbers stored in the array
    for (int i = 0; i < 1000; i++)
    {
        printf("%d ", numbers[i]);
    }
}