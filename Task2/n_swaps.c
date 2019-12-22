/*
 Created by gsg on 09/12/2019.
*/
#include <memory.h>
#include <stdio.h>

#include "json_file_proc.h"

/**
 * Find the first (from the left) min value in a
 * @param a     - pointer to array if integers
 * @param size  - a size
 * @return      - index of min element in a
 */
size_t n_min(const int *a, size_t size) {
    size_t ret = 0;

    const int* min = a;
    for(size_t i = 1; i < size; i++) {
        if(a[i] < *min) {
            min = a+i;
        }
    }
    ret = min-a;
    return ret;
}
/**
 * Swap to elements
 * @param a
 * @param b
 */
static void swap(int* a, int* b) { //XOR makes 1+ writes into array...
    int t = *a;
    *a = *b;
    *b = t;
}

int n_swaps(int* a, size_t size) {
    if(!a || size < 3) return -1;

    int min = a[n_min(a, size)];

    int ops = 0;
    int new_ops;
    do {
//Up
        new_ops = 0;
        for(size_t i = 0; i < size-1; i++) {
            if(i+1 > size - i -1) { //Right shift
                if(a[i] > a[i+1]) {
                    if(a[i+1] != min) {
                        swap(a + i, a + i + 1);
                        new_ops++;
                    }
                    else if(i > 0 && a[i-1]<a[i]) {
                        swap(a + i, a + i + 1);
                        new_ops++;
                    }
                }
            }
            else { // Left shift
                if(a[i] < a[i+1]) {
                    swap(a+i, a+i+1);
                    new_ops++;
                }
            }
        }
        printf("F");print_array(a, size);
        ops += new_ops;
//Down
        if(!new_ops) break;
        new_ops = 0;
        for(size_t i = size-1; i > 1; i--) {
            if (i > size - i - 1) { //Right shift
                if (a[i] < a[i-1]) {
                    swap(a + i, a + i - 1);
                    new_ops++;
                }
            }
            else if (a[i] > a[i-1]) {
                swap(a + i, a + i - 1);
                new_ops++;
            }
        }
        ops += new_ops;
        print_array(a, size);
    } while(new_ops);
    return ops;
}



