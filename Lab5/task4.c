#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

struct timeval t1, t2;
double time_taken;

typedef struct node * NODE;
struct node{
    int ele;
    NODE next;
};


typedef struct linked_list * LIST;
struct linked_list{
    int count;
    NODE head;
};

LIST createNewList()
{
    LIST myList;
    myList = (LIST) malloc(sizeof(struct linked_list));
    myList->count=0;
    myList->head=NULL;
    return myList;
}

NODE createNewNode(int value)
{
    NODE myNode;
    myNode = (NODE) malloc(sizeof(struct node));
    myNode->ele=value;
    myNode->next=NULL;
    return myNode;
}

// Recursive function to compute sum of integers in a linked list
int llSumNTR(NODE head)
{
    if (head == NULL)
        return 0;
    return head->ele + llSumNTR(head->next); // Pay close attention here
}

// This is just a wrapper function to take LIST as input, but run the recursive sum function on its NODEs starting from the head
int llSumNTRWrapper(LIST list)
{
    return llSumNTR(list->head);
}

int llSumTR(NODE head, int sum)
{
    if (head == NULL)
        return sum;
    return llSumTR(head->next,head->ele + sum);
}

int llSumTRWrapper(LIST list)
{
    return llSumTR(list->head, 0);
}

int llSumI(NODE head)
{
    if (head == NULL)
        return 0;
    NODE temp = head;
    int sum = 0;
    while(temp != NULL){
    	sum += temp->ele;
    	temp = temp->next;
    }
    return sum;
}

int llSumIWrapper(LIST list)
{
    return llSumI(list->head);
}

// Driver code
int main()
{
    // Reads the file numbers1000.txt and creates a linked list with those integers
    FILE *fp;
    fp = fopen("numbers100000.txt", "r");
    if (fp == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }
    int num;
    LIST myList = createNewList();
    while (fscanf(fp, "%d", &num) != EOF)
    {
        NODE myNode = createNewNode(num);
        myNode->next = myList->head;
        myList->head = myNode;
        myList->count++;
    }
    fclose(fp);

    gettimeofday(&t1, NULL);
	llSumNTRWrapper(myList);
	gettimeofday(&t2, NULL);
	time_taken = (t2.tv_sec - t1.tv_sec) * 1e6;
	time_taken = (time_taken + (t2.tv_usec - t1.tv_usec)) * 1e-6;
	printf("Non Tail Recursive LL Sum took %f seconds to execute\n", time_taken);

	gettimeofday(&t1, NULL);
	llSumTRWrapper(myList);
	gettimeofday(&t2, NULL);
	time_taken = (t2.tv_sec - t1.tv_sec) * 1e6;
	time_taken = (time_taken + (t2.tv_usec - t1.tv_usec)) * 1e-6;
	printf("Tail Recursive LL Sum took %f seconds to execute\n", time_taken);

	gettimeofday(&t1, NULL);
	llSumIWrapper(myList);
	gettimeofday(&t2, NULL);
	time_taken = (t2.tv_sec - t1.tv_sec) * 1e6;
	time_taken = (time_taken + (t2.tv_usec - t1.tv_usec)) * 1e-6;
	printf("Iterative LL Sum took %f seconds to execute\n", time_taken);

}