#include <stdio.h>
#include <stdlib.h>
typedef struct node *NODE;
struct node
{
	int ele;
	NODE next;
};
typedef struct linked_list *LIST;
struct linked_list
{
	int count;
	NODE head;
};
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
	return myNode;
}
void insertAfter(int searchEle, NODE n1, LIST l1)
{
	if (l1->head == NULL)
	{
		l1->head = n1;
		n1->next = NULL;
		l1->count++;
	}
	else
	{
		NODE temp = l1->head;
		NODE prev = temp;
		while (temp != NULL)
		{
			if (temp->ele == searchEle)
				break;
			prev = temp;
			temp = temp->next;
		}
		if (temp == NULL)
		{
			printf("Element not found\n");
			return;
		}
		else
		{
			if (temp->next == NULL)
			{
				temp->next = n1;
				n1->next = NULL;
				l1->count++;
			}
			else
			{
				prev = temp;
				temp = temp->next;
				prev->next = n1;
				n1->next = temp;
				l1->count++;
			}
			return;
		}
	}
	return;
}
void deleteAt(int ind, NODE n1, LIST l1)
{
	if (l1->head == NULL)
	{
		printf("\nEmpty List");
	}
	else
	{
		NODE temp = l1->head;
		ind--;
		while(ind--){
			if(temp->next==NULL){
				printf("\nIndex out of bounds");
				return;
			}
			else{
				temp=temp->next;
			}
		}
		if(temp->next==NULL){
			printf("\nIndex out of bounds\n");
		}
		else if(temp->next->next==NULL){
			temp->next==NULL;
		}
		else{
			temp->next=temp->next->next;
			return;
		}
	}
	return;
}
void deleteFirst(LIST list)
{
	list->head = list->head->next;
	list->count -= 1;
}
void insertFirst(NODE first, LIST list)
{
	if (list->head == NULL)list->head=first;
	else
	{	
		NODE temp = list->head;
		list->head = first;
		first->next = temp;
	}
	list->count++;
}
void search(int ele, LIST l1)
{
	NODE temp = l1->head;
	int index = -1;
	while (temp != NULL)
	{
		index++;
		if (temp->ele == ele)
		{
			printf("\nIndex of %d = %d\n",ele, index+1);
			return;
		}
		else
		{
			if(temp->next==NULL){
				printf("\n-1\n");
				return;
			}
			temp = temp->next;
		}
	}
	
}
void printList(LIST l1)
{
	NODE temp = l1->head;
	printf("[HEAD] ->");
	while (temp != NULL)
	{
		printf(" %d ->", temp->ele);
		temp = temp->next;
	}
	printf(" [NULL]\n");
}

void main(){
	LIST l1 = createNewList();
	NODE n1 = createNewNode(4);
	insertFirst(n1,l1);
	n1 = createNewNode(3);
	insertFirst(n1,l1);
	n1 = createNewNode(2);
	insertFirst(n1,l1);
	n1 = createNewNode(1);
	insertFirst(n1,l1);
	printList(l1);
	search(1,l1);
	search(5,l1);
	deleteFirst(l1);
	printList(l1);
	deleteAt(1,n1,l1);
	printList(l1);
}