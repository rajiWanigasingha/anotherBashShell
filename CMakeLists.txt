cmake_minimum_required(VERSION 4.1)
project(anotherBashShell C)

set(CMAKE_C_STANDARD 11)

add_executable(anotherBashShell main.c
        helpers/join_str.c
        helpers/join_str.h
)

add_executable(tests
        tests/join_str_test.c
        tests/join_str_test.h
        helpers/join_str.c
        helpers/join_str.h
)
