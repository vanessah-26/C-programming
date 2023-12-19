#ifndef __OPERATIONS_H__
#define __OPERATIONS_H__

#include "mathlib.h"

#include <math.h>
#include <stdbool.h>

typedef double (*binary_operator_fn)(double lhs, double rhs);

typedef double (*unary_operator_fn)(double x);

double operator_add(double lhs, double rhs);

double operator_sub(double lhs, double rhs);

double operator_mul(double lhs, double rhs);

double operator_div(double lhs, double rhs);

static const binary_operator_fn binary_operators[256] = {
    ['+'] = operator_add,
    ['-'] = operator_sub,
    ['*'] = operator_mul,
    ['/'] = operator_div,
    ['%'] = fmod,
};

static const unary_operator_fn my_unary_operators[256] = {
    ['s'] = Sin,
    ['c'] = Cos,
    ['t'] = Tan,
    ['a'] = Abs,
    ['r'] = Sqrt,
};

static const unary_operator_fn libm_unary_operators[256] = {
    ['s'] = sin,
    ['c'] = cos,
    ['t'] = tan,
    ['a'] = fabs,
    ['r'] = sqrt,
};

// return false if there are fewer than 2 items on the stack. otherwise, pop rhs, then pop lhs, then
// pass them into op, then push the result. and return true
bool apply_binary_operator(binary_operator_fn op);

// return false if the stack is empty, otherwise pop an item, call op on it, and push the result
bool apply_unary_operator(unary_operator_fn op);

// this function should be given to students
bool parse_double(const char *s, double *d);

#endif
