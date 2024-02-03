// Include the stack implementation in your code. You can use either the linked list implementation or the array implementation.
#include <stdio.h>
#include "stack.h"
void computeSpans(int *inputs, int *spans, int n);

int main()
{
    int inputs[] = {6, 3, 4, 5, 2};
    int spans[5];
    computeSpans(inputs, spans, 5);
    for (int i = 0; i < 5; i++)
    {
        printf("%d ", spans[i]);
    }
    printf("\n");
    int inputs2[] = {100, 80, 60, 70, 60, 75, 85};
    int spans2[7];
    computeSpans(inputs2, spans2, 7);
    for (int i = 0; i < 7; i++)
    {
        printf("%d ", spans2[i]);
    }
    printf("\n");
    return 0;
}
Element itoe (int i)
{
    Element e;
    e.int_value = i;
    e.float_value = 0;
    return e;
}
void computeSpans(int *arr, int *A, int n)
{
    Stack * s = newStack();

    for(int i=0;i<n;i++){
         
        while(!isEmpty(s)&&arr[top(s)->int_value]<=arr[i]){
            pop(s);
        }
        if(isEmpty(s)){
            A[i] = i+1;
            push(s,itoe(i));
        }
        else{
            A[i]=i-top(s)->int_value;
            push(s,itoe(i));
        }
    }
    return;
}
