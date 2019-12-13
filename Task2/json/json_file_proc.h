/*
 Created by gsg on 12/12/2019.
*/

#ifndef TASK1_JSON_FILE_PROC_H
#define TASK1_JSON_FILE_PROC_H

#include <stdbool.h>

#include "cJSON.h"
/**
 * Parse JSON dile with test data. All err messages are inside
 * @param fname
 * @return cJSON* if ok, NULL if syntax error. NB! call cj_free to free!
 */
cJSON* cj_parse(const char* fname);
/**
 * Get all the data for one test from test_set array. All err messages are inside
 * @param test_set  - cJSON* pointer to parsed tests
 * @param itemNo    - test number
 * @param name      - test name
 * @param data      - data array NB! should be freed after use outside!
 * @param size      - data array size
 * @param result    - expected index number
 * @return          - true if Ok, false if not
 */
bool cj_get_test_data(cJSON* test_set, int itemNo, char** name, int** data, int* size, int* result);

void cj_free(cJSON* cfg);

void print_array(const int* arr, size_t size);

#endif /* TASK1_JSON_FILE_PROC_H */
