#include "operators.h"

#include "messages.h"
#include "stack.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

//add
double operator_add(double lhs, double rhs) {
    double res = lhs + rhs;
    return res;
}
//subtract
double operator_sub(double lhs, double rhs) {
    double res = lhs - rhs;
    return res;
}
//multiply
double operator_mul(double lhs, double rhs) {
    double res = lhs * rhs;
    return res;
}
//division
double operator_div(double lhs, double rhs) {
    double res = lhs / rhs;
    return res;
}

//apply binary op//
//

bool apply_binary_operator(binary_operator_fn op) {
    if (stack_size < 2) {
        // fprintf(stderr, ERROR_BINARY_OPERATOR);
        return false;
    }

    double rhs, lhs;

    if (stack_pop(&rhs) && stack_pop(&lhs)) {
        double res = op(lhs, rhs);
        if (stack_push(res)) {
            return true;
        }
    }

    fprintf(stderr, ERROR_NO_SPACE, 0.0); // Update to zero
    return false;
}

//apply unary operator//

bool apply_unary_operator(unary_operator_fn op) {
    if (stack_size < 1) {
        //fprintf(stderr, ERROR_UNARY_OPERATOR);
        return false;
    }
    double x; //x holds the popped value
    //to ensure that stack_pop doesn't fail
    assert(stack_pop(&x));

    double res = op(x);
    //calculate the value should be put back to stack by applying operator

    assert(stack_push(res));

    return true;
}

//parsing double-precision floating point num from str s
bool parse_double(const char *s, double *d) {
    char *endptr;
    double res = strtod(s, &endptr);
    if (endptr != s) {
        *d = res;
        return true;
    } else {
        return false;
    }
}
