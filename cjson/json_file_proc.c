/*
 Created by gsg on 12/12/2019.
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>
#include <string.h>

#include "json_file_proc.h"

static const char* data_bad = "Wrong test data:";


static bool check_type (cJSON* item, int testNo, const char* name, int cjson_type) {
    if(item->type != cjson_type) {
        printf("%s item '%s' in test# %d not not an int.\n", data_bad, name, testNo);
        return false;
    }
    return true;
}

cJSON* find(cJSON* item, int testNo, const char* name, int cjson_type) {
    cJSON* j_val = cJSON_GetObjectItem(item, name);
    if(!j_val) {
        printf("%s item '%s' in test# %d not found.\n", data_bad, name, testNo);
        return NULL;
    }
    if(!check_type(j_val, testNo, name, cjson_type)) return NULL;

    return j_val;
}

bool get_int(cJSON* item, int testNo, const char* name, int* val) {
    cJSON* j_val = find(item, testNo, name, cJSON_Number);
    if(!j_val) return false;

    *val = j_val->valueint;
    return true;
}

bool get_uint(cJSON* item, int testNo, const char* name, unsigned* val) {
    int int_val;
    if(!get_int(item, testNo, name, &int_val)) return false;
    if(int_val < 0) {
        printf("%s item '%s' in test# %d should be posotive.\n", data_bad, name, testNo);
        return false;
    }
    *val = int_val;
    return true;
}
bool get_int_array(cJSON* item, int testNo, const char* name, int** val, int* size) {
    cJSON* j_val = find(item, testNo, name, cJSON_Array);
    if(!j_val) return false;

    if(*size = cJSON_GetArraySize(j_val), !(*size)) return false;

    *val = (int *)calloc(*size, sizeof(int));
    for(int i = 0; i < *size; i++) {
        cJSON* arr_item = cJSON_GetArrayItem(j_val, i);
        if(!check_type(cJSON_GetArrayItem(j_val, i), testNo, name, cJSON_Number)) {
            free(*val);
            return false;
        }
        (*val)[i] = arr_item->valueint;
    }
   return true;
}

bool get_string(cJSON* item, int testNo, const char* name, char** val) {
    cJSON* j_val = find(item, testNo, name, cJSON_String);
    if(!j_val) return false;

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
