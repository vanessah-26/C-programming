
#include "gaps.h"
#include "stats.h"
void shell_sort(Stats *stats, int *A, int n) {
    for (int gapIdx = 0; gapIdx < GAPS; gapIdx++) {
        int gap = gaps[gapIdx];
        for (int k = gap; k < n; k++) {
            int j = k;
            int temp = move(stats, A[k]); // Possible mem-leak
            while (j >= gap && cmp(stats, temp, A[j - gap]) < 0) {
                A[j] = A[j - gap];
                move(stats, A[j - gap]);
                j -= gap;
            }
            A[j] = temp;
            move(stats, temp);
        }
    }
}
