//
// Created by rajindawanigasingha on 5/10/26.
//

#include "file_attributes.h"

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>

#include "../../helpers/error_another_bash_shell.h"

Attributes file_attributes(const char* file_name){
    struct stat file_stat;

    if (stat(file_name, &file_stat) == -1) {
        switch (errno) {
        case EACCES:
            return (Attributes){
                .is_ok = 0,
                .error = ERR_PERMISSION_DENIED_FOR_PATH.error_message,
            };
        case ENOENT:
            return (Attributes){
                .is_ok = 0,
                .error = ERR_PATH_NOT_FOUND.error_message,
            };
        case ENOTDIR:
            return (Attributes){
                .is_ok = 0,
                .error = ERR_PATH_IS_NOT_A_ABSOLUTE_PATH.error_message,
            };
        default:
            return (Attributes){
                .is_ok = 0,
                .error = ERR_FAILED_TO_GET_FILE_ATTRIBUTES.error_message,
            };
        }
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

    const FilePermissions file_permissions = {
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

    const FileTime time = {
        .last_access = gmtime(&file_stat.st_atime),
        .last_modified = gmtime(&file_stat.st_mtime),
        .last_change = gmtime(&file_stat.st_ctime)
    };

    const FileOwnerId owner = {
        .owner = file_stat.st_uid,
        .group = file_stat.st_gid
    };

    const FileAttributes file_attributes = {
        .type = file_type_in_stat,
        .permissions = file_permissions,
        .size = file_stat.st_size,
        .time = time,
        .owner = owner
    };

    return (Attributes){
        .is_ok = 1,
        .error = NULL,
        .attributes = file_attributes
    };
}
