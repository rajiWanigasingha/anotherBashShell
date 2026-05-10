//
// Created by rajindawanigasingha on 5/10/26.
//

#include "current_working_dir.h"

#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

char* current_working_dir() {
    int size_of_cwd = 50;
    char *current_working_dir = malloc(size_of_cwd);

    while (1) {
        const char *dir = getcwd(current_working_dir ,size_of_cwd);

        if (dir == NULL) {
            if (errno == ERANGE) {
                size_of_cwd *= 2;
                char* temp = realloc(current_working_dir, size_of_cwd);
                if (temp == NULL) {
                    free(current_working_dir);
                    return NULL;
                }
                current_working_dir = temp;
            } else {
                return NULL;
            }
        } else {
            break;
        }
    }

    return current_working_dir;
}
