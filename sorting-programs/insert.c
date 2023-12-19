#include "stats.h"

void insertion_sort(Stats *stats, int *arr, int length) {
    for (int k = 1; k < length; k++) {
        int j = k;
        int tempt = move(stats, arr[k]);

        while (j >= 1 && cmp(stats, tempt, arr[j - 1]) < 0) {
            arr[j] = move(stats, arr[j - 1]);
            j--;
        }

        //if (j != k){
        //	arr[j] = move(stats, tempt);
        //}

        arr[j] = tempt;
        move(stats, tempt);
    }
}
