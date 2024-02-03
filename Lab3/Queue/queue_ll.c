#include"queue.h"
#include"linked_list.h"
#include<stdlib.h>
struct Queue{
    NODE head;
    NODE tail;
    LIST data;
};
Queue *createQueue(){
    Queue* myQueue = malloc(sizeof(Queue));
    myQueue->data=createNewList();
    myQueue->head=NULL;
    myQueue->tail=NULL;
    return myQueue;
}
bool enqueue(Queue *queue, Element element){
    NODE new = createNewNode(element);
    if(new==NULL)return false;
    insertNodeAtEnd(new,queue->data);
    return true;
}
bool dequeue(Queue *queue){
    if (isEmpty(queue)) {
        return false;
    }
    removeFirstNode(queue->data);
    return true;
}
Element * front(Queue *queue){
    return &queue->head->data;
}
int size(Queue *queue){
    if(queue->head==NULL)return 0;
    NODE temp = queue->head;
    int size=0;
    while(temp->next!=NULL){
        temp=temp->next;
        size++;
    }
    return size+1;
}
bool isEmpty(Queue *queue){
    if(queue->head==NULL)return true;
    return false;
}
void destroyQueue(Queue *queue){
    destroyList(queue->data);
    free(queue);
}