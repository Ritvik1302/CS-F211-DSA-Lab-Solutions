#include "stack.h"
#include "string.h"
#include <stdio.h>
#include <stdlib.h>

Element itoe(int i);

int main() {
    Stack *s = newStack();

    char str[100];
    int ans;
    printf("Enter String\n");
    scanf(" %s", str);

    for (int i = 0; i < strlen(str); i++) {
        if ('0' <= str[i] && str[i] <= '9') {
            push(s, itoe(str[i] - '0'));
        } else if (str[i] == '-') {
            int b = top(s)->int_value;
            pop(s);
            int a = top(s)->int_value;
            pop(s);
            push(s, itoe(a - b));
        } else if (str[i] == '+') {
            int b = top(s)->int_value;
            pop(s);
            int a = top(s)->int_value;
            pop(s);
            push(s, itoe(a + b));
        } else if (str[i] == '*') {
            int b = top(s)->int_value;
            pop(s);
            int a = top(s)->int_value;
            pop(s);
            push(s, itoe(a * b));
        } else if (str[i] == '/') {
            int b = top(s)->int_value;
            pop(s);
            int a = top(s)->int_value;
            pop(s);
            if (b != 0) {
                push(s, itoe(a / b));
            } else {
                // Handle division by zero error
                printf("Error: Division by zero\n");
                // You might want to add more error handling or exit the program
            }
        }
    }

    printf("%d\n", top(s)->int_value);
    freeStack(s);
    return 0;
}

Element itoe(int i) {
    Element e;
    e.int_value = i;
    e.float_value = 0;
    return e;
}
