/*
 Created by gsg on 09/12/2019.
*/
#include <memory.h>

/**
 * Find the first (from the left) max value in a
 * @param a     - pointer to array if integers
 * @param size  - a size
 * @return      - index of min element in a
 */
const int* n_max(const int* a, size_t size) {
    const int* max = a;
    if(size < 2) return max;
    for(size_t i = 1; i < size; i++) {
        if(*max < a[i]) max = a+i;
    }
    return max;
}

static void swap(int* a, int* b) { //XOR makes 1+ writes into array...
    int t = *a;
    *a = *b;
    *b = t;
}
/**
 * Shift element in a from old_plc to new_plc
 * @param a         - integer array
 * @param old_plc   - element's index
 * @param new_plc   - place to shift
 */
static void shift(int* a, size_t old_plc, size_t new_plc) {
    if(old_plc > new_plc) for(;old_plc > new_plc; old_plc--) swap(a+old_plc, a+old_plc-1); //to the left
    else for(;old_plc < new_plc; old_plc++) swap(a+old_plc, a+old_plc+1);    //to the right
}

int n_swaps(int *a, size_t size) {
    if(!a || size < 3) return -1;

    size_t sz = size;
    int* left_border = a;
    size_t ops = 0;

    while (sz > 0) {
        const int* max_addr = n_max(left_border, sz);
        size_t max_idx = max_addr-left_border;

        if(max_idx > (sz-max_idx-1)) { //Right shift
            shift(left_border, max_idx, sz-1);
            ops+= (sz-max_idx -1);
        }
        else { //Left shift
            shift(left_border, max_idx, 0);
            ops += max_idx;
            left_border++;
        }
         sz--;
    }
    return ops;
}




