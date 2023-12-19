#include "stats.h"

int partition(int *A, int lo, int hi, Stats *stats) {
    // use 'hi' as pivot
    int pivot = A[hi];
    int i = lo - 1;

    for (int j = lo; j < hi; j++) {
        // cmp A[j] w pivot
        if (cmp(stats, A[j], pivot) < 0) {
            i++;
            // swap elements A[i] and A[j]
            swap(stats, &A[i], &A[j]);
        }
    }
    //swap the pivot A[hi] w element at A[i+1]
    swap(stats, &A[i + 1], &A[hi]);
    //return idx where the pivot is now
    return i + 1;
}

//recursive func helper for quicksort
void quick_sorter(int *A, int lo, int hi, Stats *stats) {
    if (lo < hi) {
        int p = partition(A, lo, hi, stats);
        quick_sorter(A, lo, p - 1, stats);
        quick_sorter(A, p + 1, hi, stats);
    }
}

void quick_sort(Stats *stats, int *A, int n) {
    quick_sorter(A, 0, n - 1, stats);
}
