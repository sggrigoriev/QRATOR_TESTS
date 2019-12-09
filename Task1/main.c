#include <stdio.h>

#include "local_min.h"

#define TSZ(t) sizeof(t)/sizeof(int)

#define TESTS_AMT 6

const char s0[] = "Array size < 2: ";
const int t0[] = {1};
#define a0 -1

const char s1[] = "No local min: all elements are equal: ";
const int t1[] = {1,1,1,1};
#define a1 -1

const char s2[] = "Local min on left border: ";
const int t2[] = {5,6};
#define a2 0

const char s3[] = "Local min on right border: ";
const int t3[] = {6,5};
#define a3 1

const char s4[] = "No local min: plateu: ";
const int t4[] = {7,6,5,4,4,4,5,6,7};
#define a4 -1

const char s5[] = "Several local mins - find the first one: ";
const int t5[] = {7,6,5,4,5,4,5,4,5};
#define a5 3

const char* s[TESTS_AMT] = {s0, s1, s2, s3, s4, s5};
const int* t[TESTS_AMT] = {t0, t1, t2, t3, t4, t5 };
const size_t sz[TESTS_AMT] = {TSZ(t0), TSZ(t1), TSZ(t2), TSZ(t3), TSZ(t4), TSZ(t5)};
const ssize_t a[TESTS_AMT] = {a0, a1, a2, a3, a4, a5};

static void print_array(const int* arr, size_t size);

int main() {
    printf("Task1: Local minimum finding\n\n");

    for(size_t i = 0; i < TESTS_AMT; i++) {
        print_array(t[i], sz[i]);
        printf("%s%s\n", s[i], (local_min(t[i], sz[i]) == a[i]?"passed":"!!!failed!!!"));
    }
    return 0;
}

static void print_array(const int* arr, size_t size) {
    if(!arr || !size) {
        printf("No array");
        return;
    }
    printf("Array=");
    for(size_t i = 0; i < size; i++)
        printf("%d ", arr[i]);
}