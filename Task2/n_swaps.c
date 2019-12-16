/*
 Created by gsg on 09/12/2019.
*/
#include <memory.h>
#include <assert.h>
#include <stdio.h>

#include "json_file_proc.h"

#include "n_swaps.h"

#define NS_ASC true
#define NS_DEC false


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
size_t n_max(const int* a, size_t size) {
    const int* max = a;
    if(size < 2) return a-max;
    for(size_t i = 1; i < size; i++) {
        if(*max < a[i]) max = a+i;
    }
    return max-a;
}

static void swap(int* a, int* b) { //XOR makes 1+ writes into array...
    int t = *a;
    *a = *b;
    *b = t;
}

static int n_gnome(int* a, size_t size, bool ascending) {
    int ret = 0;
    int plc = 0;
    bool forward = true;
    for (ssize_t i = 0; i + 1 < size; i++) {
        if(ascending) {
            if (a[i] > a[i + 1]) {
                swap(a+i, a+i+1); ret++;
                if(forward) plc = i;
                forward = false;
                if (i != 0) i -= 2;
            }
            else {
                if(!forward) {
                    i = plc;
                    forward = true;
                }
            }
        }
        else {
            if (a[i] < a[i + 1]) {
                swap(a+i, a+i+1); ret++;
                if(forward) plc = i;
                forward = false;
                if (i != 0) i -= 2;
            }
            else {
                if(!forward) {
                    i = plc;
                    forward = true;
                }
             }
        }
    }
    return ret;
}

static void shift_center(int* a, size_t center, size_t new_center) {
    if(center > new_center) for(;center > new_center; center--) swap(a+center, a+center-1); //to the left
    else for(;center < new_center; center++) swap(a+center, a+center+1);    //to the right
}

static size_t calc_distance(size_t i1, size_t i2, size_t len) {
    return (i1>i2)?i1-i2:i2-i1;
}

int n_swaps_1(int *a, size_t size) {
    if(!a || size < 3) return -1;

    int* arr = calloc(size, sizeof(int));
    assert(arr);

    size_t k = n_min(a, size);  //Initial min element's position

    size_t min_swaps_amt = -1; // Max possible shifts amount + 1
    size_t min_swaps_amt_idx = 0; //swaps amount to shift the min to the left border - initial set

    size_t rigtht_shifts = size-1;
    size_t center = 0;
    //Go from left to right
    do {
        int swaps_amt = 0;

        memcpy(arr, a, size*sizeof(int));
        shift_center(arr, k, center);           //set the min element position (initial set done above)
        swaps_amt = n_gnome(arr, center, NS_DEC) + n_gnome(arr+center+1, size-center-1, NS_ASC) + calc_distance(k, center, size);

        if((min_swaps_amt < 0) || (swaps_amt < min_swaps_amt)) {
            min_swaps_amt = swaps_amt;
            min_swaps_amt_idx = center;
        }
        printf("Right center shift: idx = %zu ops = %d\n", center, swaps_amt);
        center++;
    }
    while (rigtht_shifts--);

//Restore the initial data to print results
    shift_center(a, k, min_swaps_amt_idx);
    n_gnome(a, min_swaps_amt_idx, NS_DEC); n_gnome(a+min_swaps_amt_idx+1, size-min_swaps_amt_idx-1, NS_ASC);

    printf("Shifts total: idx = %zu ops = %zu\n", min_swaps_amt_idx, min_swaps_amt);

    free(arr);
    return min_swaps_amt;
}

int n_swaps(int *a, size_t size) {
    if(!a || size < 3) return -1;

    size_t sz = size;
    int* left_border = a;
    size_t ops = 0;

    while (sz > 0) {
        size_t max_idx = n_max(left_border, sz);

        if(max_idx == (sz-1));
        else if(max_idx == 0) left_border++;
        else if(max_idx > sz/2) {
            shift_center(left_border, max_idx, sz-1);
            ops+= (sz-max_idx -1);
        }
        else {
            shift_center(left_border, max_idx, 0);
            ops += max_idx;
            left_border++;
        }
        sz--;
        printf(">"); print_array(a, size);
//        printf("\t\t\t\t\t\t\t\t"); print_array(left_border, sz);
    }
    return ops;
}



