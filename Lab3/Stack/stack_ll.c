#include "linked_list.h"
#include "stack.h"
#include "stdlib.h"
#include "heap_usage.h"
#include "stdio.h"

struct Stack{
	int top;
	LIST data;
};

Stack *newStack(){
	LIST myList = createNewList();
	Stack * stack = (Stack* )myalloc(sizeof(struct Stack));
	stack->top = -1;
	stack->data = myList;
	return stack;
}

bool push(Stack *stack, Element element){
	NODE newNode = createNewNode(element);
	if(newNode==NULL)return false;
	insertNodeIntoList(newNode,stack->data);
	stack->top++;
	return true;
}

Element *top(Stack *stack){
	if(stack->top==-1)return NULL;
	else {
		return &stack->data->head->data;
	}
}

bool pop(Stack *stack){
	if(stack->top==-1){
		return false;
	}
	else{
		removeFirstNode(stack->data);
		stack->top--;
		return true;
	}
} 


bool isEmpty(Stack *stack){
	if(stack->top==-1)return true;
	else return false;
}


void freeStack(Stack *stack){
	free(stack);
	return;
}