//
// Created by rajindawanigasingha on 5/15/26.
//

#ifndef ANOTHERBASHSHELL_WALKING_DIR_H
#define ANOTHERBASHSHELL_WALKING_DIR_H

struct FilePointer {
    char **path;
    int amount;
};

struct FilePointer *walking_dir(const char *dir_path);

#endif //ANOTHERBASHSHELL_WALKING_DIR_H