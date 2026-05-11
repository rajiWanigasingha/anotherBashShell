#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#include "commands/current_working_dir/current_working_dir.h"
#include "commands/file_attributes/file_attributes.h"
#include "commands/list_directory/list_directory.h"
#include "helpers/readable_bytes.h"

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
        printf("File name -> %s\n" ,results.content[i].name);
        printf("File path -> %s\n" ,results.content[i].path);
        Attributes file_att = file_attributes(results.content[i].path);
        if (file_att.is_ok) {
            printf("File type -> %d\n", file_att.attributes.type);
            ReadableBytes readable_bytes_name = readable_bytes(file_att.attributes.size);
            printf("File size -> %.2f %s\n", readable_bytes_name.bytes, readable_bytes_name.readable_formate);
            printf("Owner UID -> %u\n", file_att.attributes.owner.owner);
            printf("Group GID -> %u\n", file_att.attributes.owner.group);
            printf("Owner permissions -> r:%d w:%d x:%d\n",
                   file_att.attributes.permissions.owner.read != 0,
                   file_att.attributes.permissions.owner.write != 0,
                   file_att.attributes.permissions.owner.execute != 0);
            printf("Group permissions -> r:%d w:%d x:%d\n",
                   file_att.attributes.permissions.group.read != 0,
                   file_att.attributes.permissions.group.write != 0,
                   file_att.attributes.permissions.group.execute != 0);
            printf("Others permissions -> r:%d w:%d x:%d\n",
                   file_att.attributes.permissions.others.read != 0,
                   file_att.attributes.permissions.others.write != 0,
                   file_att.attributes.permissions.others.execute != 0);
        }
        else {
            printf("Error getting file attributes: %s\n", file_att.error);
        }

        printf("___________________________________________________\n");
    }

    free(current_working_dir_value);
    free(results.content);

    return 0;
}
