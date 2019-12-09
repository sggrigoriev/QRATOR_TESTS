/*
 * Wrapper for ThreadPool exceptions
 *
 Created by gsg on 10/12/2019.
*/

#ifndef TASK3_TP_EXCEPTION_HPP
#define TASK3_TP_EXCEPTION_HPP

#include <stdexcept>

struct TP_exception : std::runtime_error {
    explicit TP_exception(const char* msg) : std::runtime_error(msg) {}
};

#endif /* TASK3_TP_EXCEPTION_HPP */
