#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>

#include "helpers/join_str.h"

int main(void){

    int size_of_cwd = 50;
    char *current_working_dir = malloc(size_of_cwd);

    while (1) {
        const char *dir = getcwd(current_working_dir ,size_of_cwd);

        if (dir == NULL) {
            if (errno == ERANGE) {
                size_of_cwd *= 2;
                char* temp = realloc(current_working_dir, size_of_cwd);
                if (temp == NULL) {
                    printf("Error: %s\n", strerror(errno));
                    break;
                }
                current_working_dir = temp;
            } else {
                fprintf(stderr, "Error: %s\n", strerror(errno));
                break;
            }
        } else {
            break;
        }
    }

    printf("current working dir -> %s\n", current_working_dir);

    DIR * dir_stream = opendir(current_working_dir);

    if (dir_stream == NULL) {
        if (errno == EACCES) {
            printf("Don't have permission to open this folder.");
            free(current_working_dir);
            exit(1);
        }
        printf("Error: %s\n", strerror(errno));
        free(current_working_dir);
        exit(1);
    }

    printf("___________________________________________________\n");

    struct dirent * dir_entry;

    errno = 0;

    while ((dir_entry = readdir(dir_stream)) != NULL) {

        if (dir_entry->d_type != DT_REG) continue;

        struct stat file_stat;

        char *temp = current_working_dir;

        char *current_file_or_folder_name = join_str(2 ,'/' ,temp ,dir_entry->d_name);

        printf("Current file or folder name -> %s\n" ,current_file_or_folder_name);

        if (stat(current_file_or_folder_name ,&file_stat) == -1) {
            printf("Error: %s\n", strerror(errno));
            continue;
        }

        char *size_extension = "Bytes";
        double size_of_file_in_readable_format;
        size_t size_of_file_in_bytes = file_stat.st_size;

        if (size_of_file_in_bytes < 1024) {
            size_of_file_in_readable_format = (double)size_of_file_in_bytes;
        } else if (size_of_file_in_bytes < 1024 * 1024) {
            size_of_file_in_readable_format = (double)size_of_file_in_bytes / 1024;
            size_extension = "KB";
        } else if (size_of_file_in_bytes < 1024 * 1024 * 1024) {
            size_of_file_in_readable_format = (double)size_of_file_in_bytes / (1024 * 1024);
            size_extension = "MB";
        } else {
            size_of_file_in_readable_format = (double)size_of_file_in_bytes / (1024 * 1024 * 1024);
            size_extension = "GB";
        }

        printf("File name -> %s\n" ,dir_entry->d_name);
        printf("File permission -> %o\n" ,file_stat.st_mode);
        printf("File belong to -> %d\n" ,file_stat.st_uid);
        printf("File size -> %.3f %s\n" ,size_of_file_in_readable_format ,size_extension);
        printf("___________________________________________________\n");

        free(current_file_or_folder_name);
    }

    if (errno == EBADF) {
        printf("Couldn't open the directory.\n");
        free(current_working_dir);
        exit(1);
    }

    if (closedir(dir_stream) == -1) {
        printf("Closing the directory failed.");
        free(current_working_dir);
        exit(1);
    }

    free(current_working_dir);

    return 0;
}
