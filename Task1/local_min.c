/*
 Created by gsg on 09/12/2019.
*/

#include <stdbool.h>
#include "local_min.h"

ssize_t find_on_borders(const int* array, size_t size) {
    if(array[0] < array[1]) return 0;
    if(array[size-1] < array[size-2]) return size-1;
    return -1;

}

ssize_t find_in_the_middle(const int* array, size_t size) {
    bool down = true;
    ssize_t i = 0;
    do {
        int a = array[i];
        int b = array[i+1];
        if((a < b) && down) return i;
        down = (a > b);
    }
    while (++i < (size-1));
    return (down)?size-1:-1;
}

ssize_t local_min(const int* array, size_t size) {
    if(!array || size < 2) return -1;

    ssize_t res = find_on_borders(array, size);
    return (res < 0)?find_in_the_middle(array, size):res;
}






