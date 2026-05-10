#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#include "commands/current_working_dir/current_working_dir.h"
#include "commands/list_directory/list_directory.h"

int main(void){

    char * current_working_dir_value = current_working_dir();

    if (current_working_dir_value == NULL) {
        printf("Failed to get current working directory.\n");
        return 1;
    }

    const ListDirectoryResult results = list_directory(current_working_dir_value);

    if (!results.is_ok) {
        free(current_working_dir_value);
        printf("%s\n" ,results.error.error_message);
        return 1;
    }

    for (int i = 0; i < results.content_size; i++) {
        printf("File name -> %s/%s\n" ,current_working_dir_value ,results.content[i].name);
        if (results.content[i].fileType == FILETYPE_FILE) {
            printf("File type -> a regular file\n");
        } else if (results.content[i].fileType == FILETYPE_DIRECTORY) {
            printf("File type -> a directory\n");
        }
        printf("___________________________________________________\n");
    }

    free(current_working_dir_value);
    free(results.content);

    return 0;
}
