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
        int a = array[i];           //This is optimizer work not to read the same variable twice,
        int b = array[i+1];         //so please take it as reassurance
        if((a < b) && down) return i;
        down = (a > b);
    } while (++i < (size-1));
    return (down)?size-1:-1;
}






