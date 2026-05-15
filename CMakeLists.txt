cmake_minimum_required(VERSION 4.1)
project(anotherBashShell C)

set(CMAKE_C_STANDARD 11)

add_executable(anotherBashShell main.c
        helpers/join_str.c
        helpers/join_str.h
        commands/current_working_dir/current_working_dir.c
        commands/current_working_dir/current_working_dir.h
        commands/list_directory/list_directory.c
        commands/list_directory/list_directory.h
        helpers/error_another_bash_shell.h
        commands/file_attributes/file_attributes.c
        commands/file_attributes/file_attributes.h
        helpers/readable_bytes.c
        helpers/readable_bytes.h
        helpers/b_tree.c
        helpers/b_tree.h
        commands/cache/cache.c
        commands/cache/cache.h
        commands/walking_dir/walking_dir.c
        commands/walking_dir/walking_dir.h
)

add_executable(tests
        tests/join_str_test.c
        helpers/join_str.c
        helpers/join_str.h
        commands/file_attributes/file_attributes.c
        commands/file_attributes/file_attributes.h
        commands/cache/cache.c
        commands/cache/cache.h
        commands/list_directory/list_directory.h
        commands/list_directory/list_directory.c
        tests/file_attributes_test.c
)
