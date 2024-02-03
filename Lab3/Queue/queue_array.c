#include "element.h"
#include "queue.h"
#include <stdlib.h>
#include "heap_usage.h"
#define ARRAY_SIZE 1000

struct Queue
{
    int front;
    int rear;
    Element data[ARRAY_SIZE];
};

Queue *createQueue()
{
    Queue *q = (Queue *)myalloc(sizeof(Queue));
    if (q != NULL)
    {
        (q->front) = 0;
        (q->rear) = -1;
        return q;
    }
}

bool enqueue(Queue *queue, Element element)
{
    if (size(queue) == ARRAY_SIZE)
    {
        return false;
    }
    else
    {
        queue->rear = (queue->rear + 1) % ARRAY_SIZE;
        queue->data[queue->rear] = element;
        return true;
    }
}

bool dequeue(Queue *queue)
{
    if (queue->rear == -1)
        return false;
    queue->front=queue->front%ARRAY_SIZE;
    return true;
}
Element *front(Queue *queue)
{
    if (queue->rear == -1)
        return NULL;
    return &queue->data[queue->front];
}
int size(Queue *queue)
{
    if (queue->rear > queue->front)
        return queue->rear - queue->front + 1;
    else if (queue->rear == queue->front)
        return 0;
    else
        return ARRAY_SIZE - queue->front + queue->rear + 1;
}
bool isEmpty(Queue *queue)
{
    if (queue->rear == -1)
        return true;
    else
        return false;
}
void destroyQueue(Queue *queue)
{
    free(queue);
}