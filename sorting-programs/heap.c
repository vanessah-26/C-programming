#include "stats.h"

//function to find the index of the maximum child
int max_child(int *A, int first, int last, Stats *stats) {
    int left = 2 * first + 1;
    int right = 2 * first + 2;

    if (right <= last && cmp(stats, A[right], A[left]) > 0) {
        return right;
    } else {
        return left;
    }
}

//function to fix the max heap property
void fix_heap(int *A, int first, int last, Stats *stats) {
    int done = 0;
    int parent = first;

    while (2 * parent + 1 <= last && !done) {
        int largest_child = max_child(A, parent, last, stats);

        if (cmp(stats, A[parent], A[largest_child]) < 0) {
            swap(stats, &A[parent], &A[largest_child]);

            parent = largest_child;
        } else {
            done = 1;
        }
    }
}

//function for building a max heap
void build_heap(int *A, int first, int last, Stats *stats) {
    if (last > 0) {
        for (int parent = (last - 1) / 2; parent >= first; parent--) {
            fix_heap(A, parent, last, stats);
        }
    }
}

//main heapsort function
void heap_sort(Stats *stats, int *A, int n) {
    int first = 0;
    int last = n - 1;

    build_heap(A, first, last, stats);

    for (int leaf = last; leaf > first; leaf--) {
        swap(stats, &A[first], &A[leaf]);

        //fix the heap from root up to leaf - 1
        fix_heap(A, first, leaf - 1, stats);
    }
}

