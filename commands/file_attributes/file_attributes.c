//
// Created by rajindawanigasingha on 5/10/26.
//

#include "file_attributes.h"

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

#include "../../helpers/error_another_bash_shell.h"

FileAttributes file_attributes(char* file_name){
    struct stat file_stat;

    if (stat(file_name, &file_stat) == -1) {
        switch (errno) {
        case EACCES:
            ERR_PERMISSION_DENIED_FOR_PATH;
            printf("%s\n",ERR_PERMISSION_DENIED_FOR_PATH.error_message);
            break;
        case ENOENT:
            ERR_PATH_NOT_FOUND;
            printf("%s\n",ERR_PATH_NOT_FOUND.error_message);
            break;
        case ENOTDIR:
            ERR_PATH_IS_NOT_A_ABSOLUTE_PATH;
            printf("%s\n",ERR_PATH_IS_NOT_A_ABSOLUTE_PATH.error_message);
            break;
        default:
            ERR_FAILED_TO_GET_FILE_ATTRIBUTES;
            printf("%s\n",ERR_FAILED_TO_GET_FILE_ATTRIBUTES.error_message);
            break;
        }
        printf("Error: %s\n", strerror(errno));
    }

    FileTypeInStat file_type_in_stat = {};

    if (S_ISREG(file_stat.st_mode)) {
        file_type_in_stat = FILETYPE_REG_FILE;
    }
    else if (S_ISDIR(file_stat.st_mode)) {
        file_type_in_stat = FILETYPE_DIRECTORY;
    }
    else if (S_ISLNK(file_stat.st_mode)) {
        file_type_in_stat = FILETYPE_SYMLINK;
    }
    else if (S_ISSOCK(file_stat.st_mode)) {
        file_type_in_stat = FILETYPE_SOCKET;
    }
    else if (S_ISFIFO(file_stat.st_mode)) {
        file_type_in_stat = FILETYPE_FIFO;
    }

    FilePermissions file_permissions = {
        .owner = (PermissionBits){
            .read = file_stat.st_mode & S_IRUSR,
            .write = file_stat.st_mode & S_IWUSR,
            .execute = file_stat.st_mode & S_IXUSR,
        },
        .group = (PermissionBits){
            .read = file_stat.st_mode & S_IRGRP,
            .write = file_stat.st_mode & S_IWGRP,
            .execute = file_stat.st_mode & S_IXGRP
        },
        .others = (PermissionBits){
            .read = file_stat.st_mode & S_IROTH,
            .write = file_stat.st_mode & S_IWOTH,
            .execute = file_stat.st_mode & S_IXOTH
        }
    };

    return (FileAttributes){
        .type = file_type_in_stat,
        .permissions = file_permissions,
        .size = file_stat.st_size
    };
}
