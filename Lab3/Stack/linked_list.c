#include "element.h"
#include "linked_list.h"
#include "stdlib.h"
#include "stdio.h"
#include "heap_usage.h"

LIST createNewList(){
	LIST myList;
	myList = (LIST) myalloc(sizeof(struct linked_list));
	myList->count=0;
	myList->head=NULL;
	return myList;
	}

NODE createNewNode(Element data)
{
	NODE myNode;
	myNode = (NODE) myalloc(sizeof(struct node));
	myNode->data=data;
	myNode->next=NULL;
	return myNode;
}

void insertNodeIntoList(NODE node, LIST list){
	if(list->head==NULL)list->head=node;
	else{
		NODE curr = list->head;
		list->head = node;
		node->next = curr;
	}
}
void removeFirstNode(LIST list){
	if(list->head==NULL){
		printf("No Node Present");
		return;
	}
	else if(list->head->next==NULL){
		NODE temp = list->head;
		list->head==NULL;
		myfree(temp);
	}
	else{
		NODE temp = list->head;
		list->head=list->head->next;
		myfree(temp);
	}
}
void insertNodeAtEnd(NODE node, LIST list){
	if(list->head==NULL){
		list->head=node;
		return;
	}
	else if(list->head->next==NULL){
		list->head->next=node;
	}
	else{
		NODE curr = list->head;
		while(curr->next!=NULL){
			curr=curr->next;
		}
		curr->next=node;
	}
}