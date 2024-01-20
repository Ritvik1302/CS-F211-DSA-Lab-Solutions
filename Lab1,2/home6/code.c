#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

LIST addLists(LIST l1, LIST l2){

    NODE curr1 = l1->head;
    NODE curr2 = l2->head;
    int borrow = 0;
    LIST added = createNewList();

    while(curr1!=NULL&&curr2!=NULL){
        if(curr1->ele+curr2->ele+borrow<=9){
            NODE n1=createNewNode(curr1->ele+curr2->ele+borrow);
            insertFirst(n1,added);
            curr1=curr1->next;
            curr2=curr2->next;
            borrow=0;
        }
        else{
            NODE n1=createNewNode(curr1->ele+curr2->ele+borrow-10);
            insertFirst(n1,added);
            borrow=1;
            curr1=curr1->next;
            curr2=curr2->next;
        }
    }
    
    if(curr1!=NULL){
        if(borrow+curr1->ele<=9)
        {
            NODE n1=createNewNode(curr1->ele);
            insertFirst(n1,added);
            curr1=curr1->next;
            borrow=0;
        }
        else{
            NODE n1=createNewNode(curr1->ele+borrow-10);
            insertFirst(n1,added);
            borrow=1;
            curr1=curr1->next;
        }
    }
    if(curr2!=NULL){
        if(borrow+curr2->ele<=9)
        {
            NODE n1=createNewNode(curr2->ele);
            insertFirst(n1,added);
            curr2=curr2->next;
            borrow=0;
        }
        else{
            NODE n1=createNewNode(curr2->ele+borrow-10);
            insertFirst(n1,added);
            borrow=1;
            curr2=curr2->next;
        }
    }
    if(borrow!=0){
        NODE n1 = createNewNode(borrow);
        insertFirst(n1,added);
    }
    return added;
}
int main(){
    LIST list1 = createNewList();
    LIST list2 = createNewList();
    char inp1[100];
    char inp2[100];

    printf("\nEnter Number 1: ");
    scanf("%s",inp1);
    printf("\nEnter Number 2: ");
    scanf("%s",inp2);

    for(int i=0;i<strlen(inp1);i++){
        NODE n1= createNewNode((int)(inp1[i]-'0'));
        insertFirst(n1,list1);
        list1->count++;
    }

    for(int i=0;i<strlen(inp2);i++){
        NODE n2= createNewNode((int)(inp2[i]-'0'));
        insertFirst(n2,list2);
        list2->count++;
    }
    LIST added=addLists(list1,list2);
    reverseList(added);
    printList(added);
}