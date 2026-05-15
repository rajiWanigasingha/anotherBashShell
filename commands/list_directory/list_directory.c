//
// Created by rajindawanigasingha on 5/10/26.
//

#include "list_directory.h"

#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "../../helpers/join_str.h"

ListDirectoryResult list_directory(const char* dir_path) {
    DIR* dir_stream = opendir(dir_path);

    if (dir_stream == NULL) {
        switch (errno) {
        case EACCES:
            return (ListDirectoryResult){
                .is_ok = 0,
                .error = ERR_PERMISSION_DENIED_FOLDER
            };
        case ENOENT:
            return (ListDirectoryResult){
                .is_ok = 0,
                .error = ERR_PATH_NOT_FOUND
            };
        case ENOTDIR:
            return (ListDirectoryResult){
                .is_ok = 0,
                .error = ERR_NOT_A_DIRECTORY
            };
        default:
            return (ListDirectoryResult){
                .is_ok = 0,
                .error = ERR_FAILED_TO_OPEN_DIR
            };
        }
    }

    struct dirent * dir_entry;

    ListDirectoryResult result = {.is_ok = 1};

    ContentOfDirectory* content = malloc(sizeof(ContentOfDirectory));
    int size_of_content = sizeof(ContentOfDirectory);
    int current_file_index = 0;

    errno = 0;

    while ((dir_entry = readdir(dir_stream)) != NULL) {

        enum FileType type;

        if (dir_entry->d_type == DT_REG) {
            type = FILETYPE_FILE;
        } else if (dir_entry->d_type == DT_DIR) {
            type = FILETYPE_DIRECTORY;
        } else {
            continue;
        }

        const ContentOfDirectory entry = {
            .name = strdup(dir_entry->d_name),
            .path = join_str(2 ,'/' ,dir_path ,dir_entry->d_name),
            .fileType = type
        };

        size_of_content += sizeof(entry);

        ContentOfDirectory *temp = realloc(content , size_of_content);

        if (temp == NULL) {
            continue;
        }

        content = temp;

        content[current_file_index] = entry;

        current_file_index++;
    }

    if (errno == EBADF) {
        free(content);
        result.is_ok = 0;
        result.error = ERR_FAILED_TO_READ_DIR;
        return result;
    }

    if (closedir(dir_stream) == -1) {
        free(content);
        result.is_ok = 0;
        result.error = ERR_FAILED_TO_READ_DIR;
    }

    result.content = content;
    result.content_size = current_file_index;

    return result;
}
