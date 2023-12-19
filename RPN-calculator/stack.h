#ifndef __STACK_H__
#define __STACK_H__

#include <stdbool.h>

#define STACK_CAPACITY 64

extern double stack[STACK_CAPACITY];

extern int stack_size;

bool stack_push(double item);

bool stack_peek(double *item);

bool stack_pop(double *item);

void stack_clear(void);

void stack_print(void);

#endif
