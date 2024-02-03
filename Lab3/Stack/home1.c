#include "stack.h"
#include "stdlib.h"
#include "heap_usage.h"
#include <stdio.h>
Element itoe (int i);
int main()
{
    Element e = itoe(1);
    Stack * s = newStack();

    printf("%d ", isEmpty(s));

    push(s,e);
    printf("%d ", isEmpty(s));

    e = itoe(2);
    push(s,e);
    printf("%d ",top(s)->int_value);

    e = itoe(3);
    push(s,e);
    printf("%d ",pop(s));

    freeStack(s);
    return 0;
}
Element itoe (int i)
{
    Element e;
    e.int_value = i;
    e.float_value = 0;
    return e;
}