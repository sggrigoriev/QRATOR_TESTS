/*
 Created by gsg on 12/12/2019.
*/

#ifndef TASK1_JSON_FILE_PROC_H
#define TASK1_JSON_FILE_PROC_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>

#include "cJSON.h"
cJSON* find(cJSON* item, int testNo, const char* name, int cjson_type);

bool get_int(cJSON* item, int testNo, const char* name, int* val);
bool get_uint(cJSON* item, int testNo, const char* name, unsigned* val);
bool get_int_array(cJSON* item, int testNo, const char* name, int** val, int* size);
bool get_string(cJSON* item, int testNo, const char* name, char** val);
bool get_array(cJSON* item, int testNo, const char* name, cJSON** arr);

/**
 * Parse JSON dile with test data. All err messages are inside
 * @param fname
 * @return cJSON* if ok, NULL if syntax error. NB! call cj_free to free!
 */
cJSON* cj_parse(const char* fname);

void cj_free(cJSON* cfg);

void print_array(const int* arr, size_t size);

void print_bitmask(unsigned long mask, size_t size);

#ifdef __cplusplus
}
#endif
#endif /* TASK1_JSON_FILE_PROC_H */
