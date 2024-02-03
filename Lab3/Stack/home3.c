#include "stack.h"
#include "stdlib.h"
#include <stdio.h>
Element itoe (int i);
int main()
{
    int arr[5]={6,3,4,5,2};
    int A[5];
    Stack * s = newStack();

    for(int i=0;i<5;i++){
         
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
    for(int i=0;i<5;i++){
        printf("%d ", A[i]);
    }
    return 0;
}
Element itoe (int i)
{
    Element e;
    e.int_value = i;
    e.float_value = 0;
    return e;
}