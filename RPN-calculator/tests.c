#include "mathlib.h"
#include "messages.h"
#include "operators.h"
#include "stack.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

int main() {
    //Test1: check that the stack is empty
    assert(stack_size == 0);

    // Test2: push and pop elements from the stack
    stack_push(3.0);
    stack_push(4.0);
    double popped_value;
    assert(stack_pop(&popped_value));
    assert(popped_value == 4.0);

    // Test3: perform binary and unary operations
    stack_push(3.0);
    stack_push(4.0);
    apply_binary_operator(operator_add);
    assert(stack_pop(&popped_value));
    assert(popped_value == 7.0);

    stack_push(16.0);
    apply_unary_operator(Sqrt);
    assert(stack_pop(&popped_value));
    assert(popped_value == 4.0);

    //add more test cases as needed

    printf("All tests passed!\n");
    return 0;
}
