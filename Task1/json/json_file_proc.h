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
 * @return cJSON* if ok, NULL if syntax error
 */
cJSON* parse(const char* fname);
bool get_test_data(cJSON* test_set, int itemNo, char** name, int** data, int* size, int* result);

#endif /* TASK1_JSON_FILE_PROC_H */
