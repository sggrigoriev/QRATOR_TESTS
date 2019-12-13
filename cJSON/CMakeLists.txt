cmake_minimum_required(VERSION 3.15)
project(cJSON C)

set(CMAKE_C_STANDARD 99)

include_directories(.)

add_library(cJSON STATIC
        cJSON.c
        cJSON.h)
