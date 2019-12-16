cmake_minimum_required(VERSION 3.0)
project(Task2 C)

set(CMAKE_C_STANDARD 99)

set(REQUIRED_LIBRARIES
        m
        )

include_directories (../cjson)


add_executable(Task2
        main.c
        n_swaps.c
        ../cjson/cJSON.c
        ../cjson/json_file_proc.c)

target_link_libraries(Task2 ${REQUIRED_LIBRARIES})