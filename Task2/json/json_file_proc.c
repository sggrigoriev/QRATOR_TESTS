/*
 Created by gsg on 12/12/2019.
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>
#include <string.h>

#include "json_file_proc.h"

static const char* t_name = "name";
static const char* t_data = "data";
static const char* t_result = "result";

static const char* data_bad = "Wrong test data:";

static bool get_int(cJSON* item, const char* name, int* val) {
    cJSON* j_val = cJSON_GetObjectItem(item, name);
    if(!j_val || (j_val->type != cJSON_Number)) return false;
    *val = j_val->valueint;
    return true;
}

static bool get_int_array(cJSON* item, const char* name, int** val, int* size) {
    cJSON* j_val = cJSON_GetObjectItem(item, name);
    if(!j_val || j_val->type != cJSON_Array) return false;
    if(*size = cJSON_GetArraySize(j_val), !(*size)) return false;

    *val = (int *)calloc(*size, sizeof(int));
    for(int i = 0; i < *size; i++) {
        cJSON* arr_item = cJSON_GetArrayItem(j_val, i);
        if(arr_item->type != cJSON_Number) {
            free(*val);
            return false;
        }
        (*val)[i] = arr_item->valueint;
    }
   return true;
}

static bool get_string(cJSON* item, const char* name, char** val) {
    cJSON* j_val = cJSON_GetObjectItem(item, name);
    if(!j_val || (j_val->type != cJSON_String)) return false;
    *val = j_val->valuestring;
    return true;
}

cJSON* cj_parse(const char* fname) {
    assert(fname != NULL);

    FILE *f;
    char buffer[100];
    char* cfg = NULL;
    cJSON* ret = NULL;

    if(f = fopen(fname, "r"), f == NULL) {
        fprintf(stderr, "Config file %s open error %s(%d)\n", fname, strerror(errno), errno);
        return 0;
    }
    size_t ptr = 0;
    while (fgets(buffer, sizeof(buffer), f)) {
        cfg = realloc(cfg, strlen(buffer)+ptr);
        memcpy(cfg+ptr, buffer, strlen(buffer));
        ptr += strlen(buffer);
    }
    cfg = realloc(cfg, ptr+1);
    cfg[ptr] = '\0';
    fclose(f);

    if(!strlen(cfg)) {
        printf("Configuration file %s is empty\n", fname);
        free(cfg);
        return cJSON_Parse("{}");
    }

    ret = cJSON_Parse(cfg);
    if(ret == NULL) {
        printf("Error parsing %s. Error starts from: %s", fname, cJSON_GetErrorPtr());
    }
    free(cfg);
    return ret;
}

bool cj_get_test_data(cJSON* test_set, int itemNo, char** name, int** data, int* size, int* result) {

    cJSON* item = cJSON_GetArrayItem(test_set, itemNo);
    assert(item != NULL);

    if(!get_string(item, t_name, name)) {
        printf("%s item '%s' in test# %d not found or not a string.\n", data_bad, t_name, itemNo);
        return false;
    }
    if(!get_int_array(item, t_data, data, size)) {
        printf("%s item '%s' in test# %d not found or not an int array or empty.\n", data_bad, t_data, itemNo);
        return false;
    }
    if(!get_int(item, t_result, result)) {
        printf("%s item '%s' in test# %d not found or not an int.\n", data_bad, t_result, itemNo);
        return false;
    }
    return true;
}

void cj_free(cJSON* cfg) {
    if(cfg) cJSON_Delete(cfg);
}

void print_array(const int* arr, size_t size) {
    if(!arr || !size) {
        printf("No array");
        return;
    }
    printf("Array=[");
    for(size_t i = 0; i < size; i++)
        printf(" %d", arr[i]);
    printf(" ]\n");
}
