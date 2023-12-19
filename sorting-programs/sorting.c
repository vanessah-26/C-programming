#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// getopt()
#include <unistd.h>

// Headers for sorting algorithms:
#include "batcher.h"
#include "heap.h"
#include "insert.h"
#include "quick.h"
#include "set.h"
#include "shell.h"
#include "stats.h"
//
// Define the set of enabled sorting algorithms.
Set enabledAlgo;

void enable_algorithm(int algoIdx) {
    enabledAlgo = set_insert(enabledAlgo, algoIdx);
}

// Array of sorting algorithm names
const char *Algonames[]
    = { "Insertion Sort", "Heap Sort", "Shell Sort", "Quick Sort", "Batcher Sort" };

int main(int argc, char *argv[]) {

    int n = 100; // Default array size
    int p = 100; // Default number of elements to print
    int randomSeed = 13371453;
    int track_Enabled = 0; // Track if any functions are enabled

    void (*sortingAlgo[])(Stats *, int *, int)
        = { insertion_sort, heap_sort, shell_sort, quick_sort, batcher_sort };

    // Initialize the set of enabled sorting algorithms.
    enabledAlgo = set_empty();

    // getopt()
    int option;
    while ((option = getopt(argc, argv, "Haihsqbn:p:r:")) != -1) {
        switch (option) {
        case 'a':
            // Enable all sorting algorithms
            for (unsigned int i = 0;
                 i < (unsigned int) (sizeof(sortingAlgo) / sizeof(sortingAlgo[0])); i++) {
                enable_algorithm(i);
            }
            track_Enabled = 1;
            break;
        case 'i':
            enable_algorithm(0); // Enable Insertion Sort
            track_Enabled = 1;
            break;
        case 's':
            enable_algorithm(2); // Enable Shell Sort
            track_Enabled = 1;
            break;
        case 'h':
            enable_algorithm(1); // Enable Heap Sort
            track_Enabled = 1;
            break;
        case 'q':
            enable_algorithm(3); // Enable Quick Sort
            track_Enabled = 1;
            break;
        case 'b':
            enable_algorithm(4); // Enable Batcher Sort
            track_Enabled = 1;
            break;
        case 'n': n = atoi(optarg); break;
        case 'p': p = atoi(optarg); break;
        case 'r': randomSeed = atoi(optarg); break;
        case 'H':
            // Display program help and usage
            printf("SYNOPSIS\n");
            printf("  A collection of comparison-based sorting algorithms.\n\n");
            printf("USAGE\n");
            printf("  ./sorting [-Hahbsqi] [-n length] [-p elements] [-r seed]\n\n");
            printf("OPTIONS\n");
            printf("  -H              Display program help and usage.\n");
            printf("  -a              Enable all sorts.\n");
            printf("  -h              Enable Heap Sort.\n");
            printf("  -b              Enable Batcher Sort.\n");
            printf("  -s              Enable Shell Sort.\n");
            printf("  -q              Enable Quick Sort.\n");
            printf("  -i              Enable Insertion Sort.\n");
            printf("  -n length       Specify the number of array elements (default: 100).\n");
            printf("  -p elements     Specify the number of elements to print (default: 100).\n");
            printf("  -r seed         Specify the random seed (default: 13371453).\n");
            return 0;
        default:
            // Invalid option
            printf("Invalid option -- '%c'\n", option);
            printf("SYNOPSIS\n");
            printf("   A collection of comparison-based sorting algorithms.\n\n");
            printf("USAGE\n");
            printf("   ./sorting [-Hahbsqi] [-n length] [-p elements] [-r seed]\n\n");
            printf("OPTIONS\n");
            printf("   -H              Display program help and usage.\n");
            printf("   -a              Enable all sorts.\n");
            printf("   -h              Enable Heap Sort.\n");
            printf("   -b              Enable Batcher Sort.\n");
            printf("   -s              Enable Shell Sort.\n");
            printf("   -q              Enable Quick Sort.\n");
            printf("   -i              Enable Insertion Sort.\n");
            printf("   -n length       Specify number of array elements (default: 100).\n");
            printf("   -p elements     Specify number of elements to print (default: 100).\n");
            printf("   -r seed         Specify random seed (default: 13371453).\n");
            return 1;
        }
    }

    // If no sorting algorithms are selected
    if (!track_Enabled) {
        printf("Select at least one sort to perform.\n");
        printf("SYNOPSIS\n");
        printf("   A collection of comparison-based sorting algorithms.\n\n");
        printf("USAGE\n");
        printf("   ./sorting [-Hahbsqi] [-n length] [-p elements] [-r seed]\n\n");
        printf("OPTIONS\n");
        printf("   -H              Display program help and usage.\n");
        printf("   -a              Enable all sorts.\n");
        printf("   -h              Enable Heap Sort.\n");
        printf("   -b              Enable Batcher Sort.\n");
        printf("   -s              Enable Shell Sort.\n");
        printf("   -q              Enable Quick Sort.\n");
        printf("   -i              Enable Insertion Sort.\n");
        printf("   -n length       Specify number of array elements (default: 100).\n");
        printf("   -p elements     Specify number of elements to print (default: 100).\n");
        printf("   -r seed         Specify random seed (default: 13371453).\n");
        return 1;
    }

    // Set the random seed for generating random elements in the array
    srandom(randomSeed);

    Stats stats; // Initialize stats

    // Allocate and initialize the array
    int *arr = (int *) calloc(n, sizeof(int));
    if (arr == NULL) {
        perror("Memory allocation failed");
        return 1;
    }
    for (int i = 0; i < n; i++) {
        arr[i] = random() & 0x3FFFFFFF; // Bit masked to fit 30 bits
    }

    unsigned int i;
    // Perform the selected sorting algorithms
    for (i = 0; i < (unsigned int) (sizeof(sortingAlgo) / sizeof(sortingAlgo[0])); i++) {
        if (set_member(enabledAlgo, i)) {
            reset(&stats);

            int *arr_cp = (int *) calloc(n, sizeof(int));
            if (arr_cp == NULL) {
                perror("Memeory allocation failed");
                return 1;
            }

            memcpy(arr_cp, arr, n * sizeof(int)); //cp the OG array

            //apply sorting algo to copied array
            sortingAlgo[i](&stats, arr_cp, n);

            print_stats(&stats, Algonames[i], n);

            if (p > 0) {
                int j;
                for (j = 0; j < n && j < p; j++) {
                    printf("%13d", arr_cp[j]);

                    if (j % 5 == 4) {
                        // if (j % 5 == 4 || j == n - 1) {
                        printf("\n");
                    }
                    //printf("\n");
                }
                if (j < 5) {
                    printf("\n");
                }
            }

            free(arr_cp);
        }

        //printf("\n");
    }

    free(arr);
    return 0;
}
