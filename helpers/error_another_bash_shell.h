//
// Created by rajindawanigasingha on 5/10/26.
//

#ifndef ANOTHERBASHSHELL_ERROR_ANOTHER_BASH_SHELL_H
#define ANOTHERBASHSHELL_ERROR_ANOTHER_BASH_SHELL_H

struct ErrorAnotherBashShell {
    int error_code;
    char *error_message;
};

typedef struct ErrorAnotherBashShell ErrorAnotherBashShell;

#define ERR_PERMISSION_DENIED_FOLDER (ErrorAnotherBashShell){.error_code = 1, .error_message = "Don't have permission to access this folder."}
#define ERR_PATH_NOT_FOUND (ErrorAnotherBashShell){.error_code = 2, .error_message = "Invalid path, ether directory don't exist or path is empty."}
#define ERR_NOT_A_DIRECTORY (ErrorAnotherBashShell){.error_code = 3, .error_message = "Invalid path, given path is not a directory."}
#define ERR_FAILED_TO_OPEN_DIR (ErrorAnotherBashShell){.error_code = 4, .error_message = "Failed to open directory."}
#define ERR_FAILED_TO_READ_DIR (ErrorAnotherBashShell){.error_code = 5, .error_message = "Failed to read directory."}

#endif //ANOTHERBASHSHELL_ERROR_ANOTHER_BASH_SHELL_H