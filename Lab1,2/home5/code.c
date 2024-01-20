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
void insertAfter(int searchEle, NODE n1, LIST l1)
{
	if(l1->head==NULL)
	{
	l1->head = n1;
	n1->next = NULL;
	l1->count++;
	}
	else
	{
	NODE temp = l1->head;
	NODE prev = temp;
	while(temp!=NULL)
	{
	if (temp->ele == searchEle)
	break;
	prev = temp;
	temp = temp->next;
	}
	if(temp==NULL)
	{
	printf("Element not found\n");
	return;
	}
	else
	{
	if(temp->next == NULL)
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
void deleteAt(int searchEle, NODE n1, LIST l1)
{
	if(l1->head==NULL)
	{
		printf("Empty List");
	}
	else
	{
	NODE temp = l1->head;
	NODE prev = temp;
	while(temp!=NULL)
	{
	if (temp->ele == searchEle)
	break;
	prev = temp;
	temp = temp->next;
	}
	if(temp==NULL)
	{
	printf("Element not found\n");
	return;
	}
	else
	{
	if(temp->next == NULL)
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
void deleteFirst(LIST list)
{
	list->head->next = list->head->next->next;
	list->count-=1;
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

void reverseList(LIST list){
    NODE prev = NULL;
    NODE curr = list->head;
    NODE next = NULL;

    while (curr != NULL) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    list->head=prev;
}

int main(){
    LIST new = createNewList();
    NODE n1 = createNewNode(3);
    NODE n2 = createNewNode(2);
    NODE n3 = createNewNode(1);
    insertFirst(n1,new);
    insertFirst(n2,new);
    insertFirst(n3,new);
    printList(new);
    reverseList(new);
    printList(new);
}