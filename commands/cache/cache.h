//
// Created by rajindawanigasingha on 5/14/26.
//

#ifndef ANOTHERBASHSHELL_CACHE_H
#define ANOTHERBASHSHELL_CACHE_H

#include "../list_directory/list_directory.h"

int create_cache_dir();

void cache_files(const char *result);

int update_cache(const char* dir_path ,const char *file_name);

void read_from_cache(const char* dir_path);

#endif //ANOTHERBASHSHELL_CACHE_H