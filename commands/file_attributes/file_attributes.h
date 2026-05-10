//
// Created by rajindawanigasingha on 5/10/26.
//

#ifndef ANOTHERBASHSHELL_FILE_ATTRIBUTES_H
#define ANOTHERBASHSHELL_FILE_ATTRIBUTES_H
#include <stddef.h>

enum FileTypeInStat {
    FILETYPE_REG_FILE,
    FILETYPE_DIRECTORY,
    FILETYPE_SYMLINK,
    FILETYPE_SOCKET,
    FILETYPE_FIFO,
};

typedef enum FileTypeInStat FileTypeInStat;

struct PermissionBits {
    size_t read;
    size_t write;
    size_t execute;
};

typedef struct PermissionBits PermissionBits;

struct FilePermissions {
    PermissionBits owner;
    PermissionBits group;
    PermissionBits others;
};

typedef struct FilePermissions FilePermissions;

struct FileAttributes {
    FileTypeInStat type;
    FilePermissions permissions;
    size_t size;
};

typedef struct FileAttributes FileAttributes;

FileAttributes file_attributes(char *file_name);

#endif //ANOTHERBASHSHELL_FILE_ATTRIBUTES_H