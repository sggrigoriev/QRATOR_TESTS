/*
 Created by gsg on 09/12/2019.
*/

#include <stdbool.h>
#include "local_min.h"

ssize_t local_min(const int* array, size_t size) {
    if(!array || size < 2) return -1;

    bool down = true;
    ssize_t i = 0;
    do {
        if((array[i] < array[i+1]) && down) return i;
        down = (array[i] > array[i+1]);
    } while (++i < (size-1));
    return (down)?size-1:-1;
}
