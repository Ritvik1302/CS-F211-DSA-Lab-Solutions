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
void search(int ele, LIST l1)
{
	NODE temp = l1->head;
	int index=-1;
	while(temp != NULL)
	{
	index++;
	if(temp->ele==ele)
	{
		printf("Index = %d",index);
	}
	else
	{
		temp = temp->next;
	}
	}
	if(index==-1)printf("-1");
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

void shiftLeft(LIST l1, int k)
{
    int count=0;
    NODE curr = l1->head;
	while (curr->next != NULL)
	{
		curr = curr->next;
        count++;
	}
    curr->next=l1->head;

    int index = k%(count)-1;
	curr = l1->head;
	while (index--)
	{
		curr = curr->next;
	}
    l1->head=curr->next;

    int ind= count-k%count;
    curr->next = NULL;
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
    printList(new);
    shiftLeft(new,2);
    printList(new);
        shiftLeft(new,3);
    printList(new);
}