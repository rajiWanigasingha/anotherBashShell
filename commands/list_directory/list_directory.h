//
// Created by rajindawanigasingha on 5/10/26.
//

#ifndef ANOTHERBASHSHELL_LIST_DIRECTORY_H
#define ANOTHERBASHSHELL_LIST_DIRECTORY_H

#include "../../helpers/error_another_bash_shell.h"

enum FileType {
    FILETYPE_FILE,
    FILETYPE_DIRECTORY,
};

struct ContentOfDirectory {
    char *name;
    char *path;
    char fileType;
};

typedef struct ContentOfDirectory ContentOfDirectory;

/**
 * @brief Represents the result of listing the contents of a directory.
 *
 * @details
 * This struct contains information about the status of the directory listing
 * operation. It includes whether the operation was successful, the size of
 * the contents retrieved, details about any errors that occurred, and the
 * actual contents of the directory.
 *
 * - `is_ok`: Indicates if the operation was successful (1 for success, 0 for failure).
 * - `content_size`: The number of items retrieved in the directory listing.
 * - `error`: Contains error details if the operation failed.
 * - `content`: A pointer to the directory's content data.
 */
struct ListDirectoryResult {
    int is_ok;
    int content_size;
    ErrorAnotherBashShell error;
    ContentOfDirectory* content;
};

typedef struct ListDirectoryResult ListDirectoryResult;


/**
 * @brief List all files and folders in a given directory
 *
 * @details
 * This will give back a ListDirectoryResult that will have a list of files or directories. This struct will have is_ok to tell if it failed or passed, if it 0 it failed and set error on
 * the error field.
 *
 * @param dir_path a path to a directory that wants to be listed.
 * @return [ListDirectoryResult]
 */
ListDirectoryResult list_directory(const char *dir_path);

#endif //ANOTHERBASHSHELL_LIST_DIRECTORY_H