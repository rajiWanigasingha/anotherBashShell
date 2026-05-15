#include "walking_dir.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../cache/cache.h"
#include "../list_directory/list_directory.h"

struct FilePointer *walking_dir(const char *dir_path) {

    const ListDirectoryResult results = list_directory(dir_path);

    if (!results.is_ok) {
        return NULL;
    }

    struct FilePointer *file = malloc(sizeof(struct FilePointer));

    if (file == NULL) {
        return NULL;
    }

    file->amount = 0;
    file->path = NULL;

    for (int i = 0; i < results.content_size; i++) {

        if (strcmp(results.content[i].name, ".") == 0 ||
            strcmp(results.content[i].name, "..") == 0) {
            continue;
            }

        if (results.content[i].fileType == FILETYPE_DIRECTORY) {

            struct FilePointer *list =
                walking_dir(results.content[i].path);

            if (list != NULL) {

                char **tmp = realloc(
                    file->path,
                    sizeof(char *) * (file->amount + list->amount)
                );

                if (tmp == NULL) {
                    free(file);
                    return NULL;
                }

                file->path = tmp;

                memcpy(
                    file->path + file->amount,
                    list->path,
                    sizeof(char *) * list->amount
                );

                file->amount += list->amount;

                free(list->path);
                free(list);
            }

        } else {

            char **tmp = realloc(
                file->path,
                sizeof(char *) * (file->amount + 1)
            );

            if (tmp == NULL) {
                free(file);
                return NULL;
            }

            file->path = tmp;

            file->path[file->amount] = strdup(results.content[i].path);

            file->amount++;
        }
    }

    return file;
}