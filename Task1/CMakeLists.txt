cmake_minimum_required(VERSION 3.15)
project(Task1 C)

set(REQUIRED_LIBRARIES
        m
        )

include_directories (../cjson)

add_executable(Task1
        main.c
        local_min.c
        ../cjson/cJSON.c
        ../cjson/json_file_proc.c)

target_link_libraries(Task1 ${REQUIRED_LIBRARIES})