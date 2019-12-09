cmake_minimum_required(VERSION 3.15)
project(Task3)

set(CMAKE_CXX_STANDARD 98)

set(REQUIRED_LIBRARIES
        m
        pthread
)

include_directories(
        ./thread_pool
)

add_executable(Task3
        main.cpp
        tests_set.cpp
        thread_pool/thread_pool.cpp
        thread_pool/tp_queue.cpp thread_pool/sync.cpp
        thread_pool/thread_starter.cpp
        thread_pool/manager.cpp
        thread_pool/workers.cpp
        )

target_link_libraries(Task3 ${REQUIRED_LIBRARIES})