#include <stdio.h>
#include <assert.h>

#include "json_file_proc.h"
#include "n_swaps.h"

static bool get_test_data(cJSON* test_set, int itemNo, char** name, int** data, int* size);


int main(int argc, char* argv[]) {
    if (argc < 2)  {
        printf("Usage: %s <JSON test data file>\n\n", argv[0]);
        return 0;
    }
    cJSON* test_set = cj_parse(argv[1]);
    if(!test_set) return -1;

    for(int i = 5; i < 6/*cJSON_GetArraySize(test_set)*/; i++) {
        char* test_name;
        int* test_array;
        int array_size;
        printf("\nTest# %d:\n", i);
        if(!get_test_data(test_set, i, &test_name, &test_array, &array_size)) {
            printf("\tfailed\n");
            continue;
        }
        printf("Name: %s\n\t\t\t", test_name);
        print_array(test_array, array_size);

        int ops = n_swaps(test_array, array_size);

        printf("Sorted Array");
        print_array(test_array, array_size);
        printf("Operations = %d\n", ops);

        free(test_array);
    }
    cj_free(test_set);
    return 0;
}

static const char* t_name = "name";
static const char* t_data = "data";

static const char* data_bad = "Wrong test data:";

static bool get_test_data(cJSON* test_set, int itemNo, char** name, int** data, int* size) {

    cJSON* item = cJSON_GetArrayItem(test_set, itemNo);
    assert(item != NULL);

    if(!get_string(item, itemNo, t_name, name)) {
        printf("%s item '%s' in test# %d not found or not a string.\n", data_bad, t_name, itemNo);
        return false;
    }
    if(!get_int_array(item, itemNo, t_data, data, size)) {
        printf("%s item '%s' in test# %d not found or not an int array or empty.\n", data_bad, t_data, itemNo);
        return false;
    }
    return true;
}

