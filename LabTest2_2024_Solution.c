#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct linked_list *LIST;
typedef struct node *NODE;
struct node
{
    int ele;
    NODE next;
    LIST list;
};
struct linked_list
{
    int count;
    NODE head;
};

struct heapNode
{
    int id;
    int freq;
};
typedef struct heapNode heapNode;
struct heap
{
    heapNode *data;
    int size;
    int capacity;
    int depth;
};
typedef struct heap *Heap;

Heap heap_create()
{
    Heap h = malloc(sizeof(struct heap));
    h->data = malloc(100*sizeof(heapNode));
    h->size = 100;
    return h;
}

int left_child(Heap h, int node)
{
    return node * 2 + 1;
}
int right_child(Heap h, int node)
{
    return node * 2 + 2;
}

void max_heapify(Heap h, int index)
{
    int left = left_child(h, index);
    int right = right_child(h, index);
    int largest = index;
    if (left < h->size && h->data[left].freq > h->data[largest].freq)
    {
        largest = left;
    }
    if (right < h->size && h->data[right].freq > h->data[largest].freq)
    {
        largest = right;
    }
    if (largest != index)
    {
        heapNode temp = h->data[index];
        h->data[index] = h->data[largest];
        h->data[largest] = temp;
        max_heapify(h, largest);
    }
}

LIST createNewList()
{
    LIST myList;
    myList = (LIST)malloc(sizeof(struct linked_list));
    myList->count = 0;
    myList->head = NULL;
    return myList;
}

NODE createNewNode(int value)
{
    NODE myNode;
    myNode = (NODE)malloc(sizeof(struct node));
    myNode->ele = value;
    myNode->next = NULL;
    myNode->list = createNewList();
    return myNode;
}

void insertLL(LIST l1, NODE node)
{
    NODE temp = l1->head;
    if (temp == NULL)
    {
        l1->head = node;
        return;
    }

    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = node;
}

void printList(LIST l1)
{
    NODE temp = l1->head;
    printf("[HEAD] ->");
    while (temp != NULL)
    {
        NODE temp2 = temp->list->head;
        while (temp2 != NULL)
        {
            printf("%d ", temp2->ele);
            temp2 = temp2->next;
        }
        printf("-> ");
        temp = temp->next;
    }
    printf(" [NULL]\n");
}

LIST createData()
{
    // Hardcoding The Transactions for this function
    int n = 20;
    int **arr = malloc(20 * sizeof(int *));
    int size[20] = {4, 3, 5, 7, 5, 9, 1, 4, 4, 7, 5, 8, 6, 9, 6, 6, 11, 2, 1, 3};

    int transactions[][20] = {{1, 5, 7, 11}, {74, 65, 62}, {64, 94, 100, 35, 1}, {67, 87, 94, 100, 45, 68, 23}, {89, 46, 73, 85, 90}, {83, 74, 82, 2, 5, 94, 10, 32, 25}, {67}, {68, 56, 93, 92}, {94, 89, 72, 40}, {98, 94, 68, 95, 100, 57, 48}, {97, 89, 94, 56, 72}, {100, 99, 98, 97, 6, 5, 94, 76}, {87, 94, 92, 98, 90, 99}, {64, 28, 47, 95, 10, 75, 38, 36, 100}, {73, 49, 48, 20, 19, 17}, {18, 17, 16, 15, 19, 94}, {86, 84, 83, 82, 81, 80, 89, 98, 96, 95, 94}, {66, 76}, {94}, {98, 64, 27}};

    for (int i = 0; i < 20; i++)
    {
        arr[i] = transactions[i];
    }

    LIST list = createNewList();
    NODE n1;
    for (int i = 0; i < n; i++)
    {
        n1 = createNewNode(-1);
        for (int j = 0; j < size[i]; j++)
        {
            insertLL(n1->list, createNewNode(arr[i][j]));
        }
        insertLL(list, n1);
    }
    return list;
}

Heap representData(LIST list)
{
    Heap h = heap_create();
    int frequencies[100] = {0};

    NODE temp = list->head;

    while (temp != NULL)
    {
        NODE temp2 = temp->list->head;
        while (temp2 != NULL)
        {
            frequencies[temp2->ele - 1]++;
            temp2 = temp2->next;
        }
        temp = temp->next;
    }

    for (int i = 0; i < 100; i++)
    {
        h->data[i].id = i + 1;
        h->data[i].freq = frequencies[i];
    }
    for (int i = 99; i >= 0; i--)
    {
        max_heapify(h, i);
    }
    return h;
}

int getMax(Heap h)
{
    return h->data[0].id;
}

int main(int argc, char **argv)
{
    LIST list = createData();
    // printList(list); // Testing Function For Task a).
    Heap h = representData(list);
    // Testing Function For Task b).
    // for (int i = 0; i < 100; i++)
    // {
    //     printf(" %d ", h->data[i].id);
    // }
    int id = getMax(h);
    printf("Most Sold Item Index: %d\n", id);
}