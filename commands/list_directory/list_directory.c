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
            .name = dir_entry->d_name,
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


        // struct stat file_stat;
        //
        // char *temp = current_working_dir_value;
        //
        // char *current_file_or_folder_name = join_str(2 ,'/' ,temp ,dir_entry->d_name);
        //
        // printf("Current file or folder name -> %s\n" ,current_file_or_folder_name);
        //
        // if (stat(current_file_or_folder_name ,&file_stat) == -1) {
        //     printf("Error: %s\n", strerror(errno));
        //     continue;
        // }
        //
        // char *size_extension = "Bytes";
        // double size_of_file_in_readable_format;
        // size_t size_of_file_in_bytes = file_stat.st_size;
        //
        // if (size_of_file_in_bytes < 1024) {
        //     size_of_file_in_readable_format = (double)size_of_file_in_bytes;
        // } else if (size_of_file_in_bytes < 1024 * 1024) {
        //     size_of_file_in_readable_format = (double)size_of_file_in_bytes / 1024;
        //     size_extension = "KB";
        // } else if (size_of_file_in_bytes < 1024 * 1024 * 1024) {
        //     size_of_file_in_readable_format = (double)size_of_file_in_bytes / (1024 * 1024);
        //     size_extension = "MB";
        // } else {
        //     size_of_file_in_readable_format = (double)size_of_file_in_bytes / (1024 * 1024 * 1024);
        //     size_extension = "GB";
        // }
        //
        // printf("File name -> %s\n" ,dir_entry->d_name);
        // printf("File permission -> %o\n" ,file_stat.st_mode);
        // printf("File belong to -> %d\n" ,file_stat.st_uid);
        // printf("File size -> %.3f %s\n" ,size_of_file_in_readable_format ,size_extension);
        // printf("___________________________________________________\n");
        //
        // free(current_file_or_folder_name);
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
