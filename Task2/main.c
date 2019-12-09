#include <stdio.h>
#include "n_swaps.h"

#define TSZ(t) sizeof(t)/sizeof(int)

int a0[] = {1,2};
int a1[] = {1,2,3,4,5};
int a2[] = {5,4,3,2,1};
int a3[] = {1,1,1,};
int a4[] = {1,2,3,4,5,1,4,3,2,1};
int a5[] = {5,7,6,8,0,2,3,4,18,10};
int a6[] = {2,3,4,5,0,5,4,3,2,1};

static void print_array(const int* arr, size_t size) {
    if(!arr || !size) {
        printf("No array");
        return;
    }
    printf("Array=");
    for(size_t i = 0; i < size; i++)
        printf("%d ", arr[i]);
}
static void run_test(int* arr, size_t size) {
    print_array(arr, size);
    printf("\t\t\t\t\t");
    int ops = n_swaps(arr, size);
    print_array(arr, size);
    printf("Operations = %d", ops);
    printf("\n");
}

int main() {
    run_test(a0, TSZ(a0));
    run_test(a1, TSZ(a1));
    run_test(a2, TSZ(a2));
    run_test(a3, TSZ(a3));
    run_test(a4, TSZ(a4));
    run_test(a5, TSZ(a5));
    run_test(a6, TSZ(a6));

    return 0;
}
