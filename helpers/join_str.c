//
// Created by rajindawanigasingha on 5/10/26.
//

#include "join_str.h"

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

char* join_str(int join_amount, char join_char, ...) {
    va_list args;
    va_start(args, join_amount);
    char *joined_str = malloc(sizeof(char) * join_amount);
    int current_index = 0;

    if (joined_str == NULL) {
        printf("Failed to allocate memory for joined string.\n");
        return NULL;
    }

    for (int i = 0; i < join_amount; i++) {
        const char *temp = va_arg(args, char *);

        const size_t len_of_temp = strlen(temp);
        char *temp_alloc = realloc(joined_str , len_of_temp + strlen(joined_str) + 1);

        if (temp_alloc == NULL) {
            printf("Failed to allocate memory for joined string.\n");
            free(joined_str);
            return NULL;
        }

        joined_str = temp_alloc;

        for (int index = 0; index < len_of_temp; index++) {
            joined_str[current_index] = temp[index];
            current_index++;
        }

        joined_str[current_index] = join_char;
        current_index++;
    }

    va_end(args);

    joined_str[current_index - 1] = '\0';

    return joined_str;
}
