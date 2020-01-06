cmake_minimum_required(VERSION 3.0)
project(Task3)

set(CMAKE_CXX_STANDARD 98)

set(REQUIRED_LIBRARIES
        m
        pthread
)

include_directories(
        ./thread_pool
        ../cjson
)

add_executable(Task3
        main.cpp
        thread_pool/thread_pool.cpp
        thread_pool/tp_queue.cpp
        thread_pool/workers.cpp
        ../cjson/json_file_proc.c
        ../cjson/cJSON.c
        test_helpers.cpp)

target_link_libraries(Task3 ${REQUIRED_LIBRARIES})