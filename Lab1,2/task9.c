#include <stdio.h>
#include <stdlib.h>

typedef struct node* NODE;
struct node{
	int ele;
	NODE next;
};
typedef struct linked_list* LIST;
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

void insertFirst(NODE first,LIST list)
{
	if(list->head == NULL){
        list->head=first;
    }
    else{
        NODE temp = list->head;
	    list->head=first;
	    first->next=temp;
    }
}

void printList(LIST l1)
{
	NODE temp = l1->head;
	printf("[HEAD] ->");
	while(temp != NULL)
	{
	printf(" %d ->", temp->ele);
	temp = temp->next;
	}
	printf(" [NULL]\n");
}


void detectCycle(LIST l1){

    NODE slow = l1->head;
    NODE fast = l1->head;
    int i=0;
    while(slow!=NULL&&fast!=NULL){
        if(slow==fast&&i!=0){
            printf("\nCycle Detected\n");
            return;
        }
        else if(slow->next!=NULL&&fast->next!=NULL&&fast->next->next!=NULL){
            slow=slow->next;
            fast=fast->next->next;
            i++;
        }
        else{
            printf("\nNo Cycle Detected\n");
            return;
        }
    }
    printf("\nNo Cycle Detected\n");
    return;
}

int main(){
    LIST new = createNewList();
    NODE n1 = createNewNode(5);
    NODE n2 = createNewNode(4);
    NODE n3 = createNewNode(3);
    NODE n4 = createNewNode(2);
    NODE n5 = createNewNode(1);
    insertFirst(n1,new);
    insertFirst(n2,new);
    insertFirst(n3,new);
    insertFirst(n4,new);
    insertFirst(n5,new);

    printf("\nAcyclic List\n");
    printList(new);
    detectCycle(new);

    printf("\nCyclic List\n");
    new->head->next=new->head;
    detectCycle(new);

    printf("\nCircular List\n");
    new = createNewList();
     n1 = createNewNode(5);
     n2 = createNewNode(4);
     n3 = createNewNode(3);
     n4 = createNewNode(2);
     n5 = createNewNode(1);
    insertFirst(n1,new);
    insertFirst(n2,new);
    insertFirst(n3,new);
    insertFirst(n4,new);
    insertFirst(n5,new);
    new->head->next->next->next->next=new->head;
    detectCycle(new);
}