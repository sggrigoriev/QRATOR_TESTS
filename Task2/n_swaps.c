/*
 Created by gsg on 09/12/2019.
*/

#include "n_swaps.h"

#define NS_ASC true
#define NS_DESC false

typedef struct {
    int ops;
    size_t idx;
} res_t;

res_t n_min(const int *a, size_t size) {
    res_t res = {0};

    const int* min = a; res.ops++;
    for(size_t i = 1; i < size; i++) {
        if(a[i] < *min) {
            min = a+i;
             res.ops++;      //min = a[i]
        }
        res.ops++;         //a[i] < min,
    }
    res.idx = min-a;
    return res;
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
                swap(a+i, a+i+1);
                if(forward) plc = i;
                forward = false;
                if (i != 0) i -= 2;
                ret += 4;
            }
            else {
                if(!forward) {
                    i = plc;
                    forward = true;
                }
                ret++;
            }
        }
        else {
            if (a[i] < a[i + 1]) {
                swap(a+i, a+i+1);
                if(forward) plc = i;
                forward = false;
                if (i != 0) i -= 2;
                ret += 4;
            }
            else {
                if(!forward) {
                    i = plc;
                    forward = true;
                }
                ret++;
            }
        }
    }
    return ret;
}

static int n_shaker(int* a, size_t size, bool ascending) {
    int ret = 0;

    if (size <= 1) return ret;
    bool b = true;
    int* start = a - 1;
    int* end = a + size - 1;
    while (b) {
        b = false;
        start++;
        for (int* i = start; i < end; i++) {
            if(ascending) {
                if (*i > *(i + 1)) {
                    swap(i, (i + 1));
                    b = true;
                    ret += 4;
                }
                else {
                    ret++;
                }
            }
            else {
                if (*i < *(i + 1)) {
                    swap(i, (i + 1));
                    b = true;
                    ret += 4;
                }
                else {
                    ret++;
                }
            }
        }
        if (!b) break;
        end--;
        for (int* i = end; i > start; i--) {
            if(ascending) {
                if (*i < *(i - 1)) {
                    swap(i, (i - 1));
                    b = true;
                    ret += 4;
                }
                else {
                    ret++;
                }
            }
            else {
                if (*i > *(i - 1)) {
                    swap(i, (i - 1));
                    b = true;
                    ret += 4;
                }
                else {
                    ret++;
                }
            }
        }
    }
    return ret;
}

static int x_swaps(int *a, size_t size, int(*proc)(int*, size_t, bool)) {
    if(!a || size < 3) return -1;

    res_t k = n_min(a, size);
    return k.ops + proc(a, k.idx, NS_DESC) + proc(a+k.idx+1, size-k.idx-1, NS_ASC);
}
int n_swaps(int *a, size_t size) {
    return x_swaps(a, size, n_gnome);
}
int n_swaps_shaker(int *a, size_t size) {
    return x_swaps(a, size, n_shaker);
}



