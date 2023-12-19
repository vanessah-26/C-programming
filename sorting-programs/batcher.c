#include "stats.h"

void comparator(int *A, int x, int y, Stats *stats) {
    if (cmp(stats, A[x], A[y]) > 0) {
        swap(stats, &A[x], &A[y]);
    }
}

void batcher_sort(Stats *stats, int *A, int n) {
    if (n <= 1)
        return; //if array <1 => already sorted

    int t = 1;
    while ((1 << t) <= n) // calculate t, 2t <= n
        t++;

    int p, q, r, d;
    //iterate over p in decresing order
    for (p = (1 << (t - 1)); p > 0; p >>= 1) {
        q = (1 << (t - 1));
        r = 0;
        d = p;

        while (d > 0) {
            for (int i = 0; i < n - d; i++) {
                if ((i & p) == r)
                    comparator(A, i, i + d, stats); //cmp i and i+d if cond. holds
            }

            d = q - p; //update d and q for next iteration
            q >>= 1;
            r = p; //update r
        }
    }
}

