#pragma once

/*
* DO NOT MODIFY THIS FILE.
*
* For documentation, see stats.c .
*/

#include <inttypes.h>

typedef struct {
    uint64_t moves;
    uint64_t compares;
} Stats;

int cmp(Stats *stats, int x, int y);

int move(Stats *stats, int x);

void swap(Stats *stats, int *x, int *y);

void reset(Stats *stats);

void print_stats(Stats *stats, const char *algorithm_name, int num_elements);
