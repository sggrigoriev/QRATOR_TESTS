/*
 Created by gsg on 13/12/2019.
*/

#ifndef TASK3_TEST_HELPERS_H
#define TASK3_TEST_HELPERS_H

#include <stddef.h>
#include <stdbool.h>

typedef struct {
    int* ar;
    size_t size;
} array_t;

array_t a_create(size_t si);
void a_delete(array_t ar);

bool a_compare(array_t a1, array_t a2, bool with_order);
bool a_add_ith(array_t a, int val, size_t idx);

typedef struct {

};

typedef struct {
    array_t* data;
    const char* test_name;

};

#endif /* TASK3_TEST_HELPERS_H */
