#include "stack.h"

#include "messages.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int stack_size = 0;
double stack[STACK_CAPACITY];

bool stack_push(double item) {
    if (stack_size < STACK_CAPACITY) {
        stack[stack_size] = item;
        stack_size++;
        return true;
    } else {
        // Stack is full, cannot push more items
        //fprintf(stderr, ERROR_NO_SPACE, item);
        return false;
    }
}

bool stack_peek(double *item) {
    if (stack_size != 0) {
        *item = stack[stack_size - 1];
        return true;
    }
    return false;
}

bool stack_pop(double *item) {
    if (stack_size == 0) {
        return false;
    }
    //cp the first item of the stack_arr to a mem loc pointed to by *item
    *item = stack[stack_size - 1];
    stack_size--; //decrement stack_sz after popping

    return true;
}

void stack_clear(void) {
    stack_size = 0; //not ==!!, == set value, = indicates an empty stack
}

void stack_print(void) {
    //make sure we don't print stack_arr[0] when it's empty
    if (stack_size == 0 || stack_size == STACK_CAPACITY) {
        return;
    }
    // print the first element with 10 decimal places
    printf("%.10f", stack[0]);
    // print the remaining elements (if any), with a space before each one
    for (int i = 1; i < stack_size; i++) {
        printf(" %.10f", stack[i]);
    }
}
