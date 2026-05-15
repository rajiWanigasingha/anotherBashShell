//
// Created by rajindawanigasingha on 5/14/26.
//

#include "cache.h"

#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "../../helpers/join_str.h"
#include "../list_directory/list_directory.h"

int create_cache_dir(){
    const char* cache_files[] = {
        "a.bin", "b.bin", "c.bin", "d.bin", "e.bin", "f.bin",
        "g.bin", "h.bin", "i.bin", "j.bin", "k.bin", "l.bin",
        "m.bin", "n.bin", "o.bin", "p.bin", "q.bin", "r.bin",
        "s.bin", "t.bin", "u.bin", "v.bin", "w.bin", "x.bin",
        "y.bin", "z.bin", "special.bin",NULL
    };
    char* cache_dir = getenv("HOME");

    if (cache_dir == NULL) {
        printf("HOME is not set.\n");
        return 0;
    }

    cache_dir = join_str(2, '/', cache_dir, ".cache");

    const char* cache_location = join_str(2, '/', cache_dir, "find-cache");

    if (cache_dir == NULL) {
        return 0;
    }

    const int made_dir = mkdir(cache_location,S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

    if (made_dir == -1) {
        if (errno != EEXIST) return 0;
    }

    int i = 0;

    while (cache_files[i] != NULL) {
        FILE* file = fopen(join_str(2, '/', cache_location, cache_files[i]), "w");
        if (file == NULL) {
            i++;
            continue;
        }
        fwrite("", 1, 0, file);
        fclose(file);
        i++;
    }

    return 1;
}

void cache_files(char* dir_path){

    char* cache_dir = getenv("HOME");

    if (cache_dir == NULL) {
        printf("HOME is not set.\n");
        return;
    }

    cache_dir = join_str(2, '/', cache_dir, ".cache");

    const char* cache_location = join_str(2, '/', cache_dir, "find-cache");

    ListDirectoryResult results = list_directory(dir_path);

    for (int index = 0; index < results.content_size; index++) {
        ContentOfDirectory content = results.content[index];

        if (strcmp(content.name, ".") == 0 || strcmp(content.name, "..") == 0 || strcmp(content.name, "") == 0) {
            continue;
        }


        switch (content.name[0]) {
        case 'a':
        case 'A':
            update_cache(join_str(2, '/', cache_location, "a.bin"), content.name);
            break;
        case 'b':
        case 'B':
            update_cache(join_str(2, '/', cache_location, "b.bin"), content.name);
            break;
        case 'c':
        case 'C':
            update_cache(join_str(2, '/', cache_location, "c.bin"), content.name);
            break;
        case 'd':
        case 'D':
            update_cache(join_str(2, '/', cache_location, "d.bin"), content.name);
            break;
        case 'e':
        case 'E':
            update_cache(join_str(2, '/', cache_location, "e.bin"), content.name);
            break;
        case 'f':
        case 'F':
            update_cache(join_str(2, '/', cache_location, "f.bin"), content.name);
            break;
        case 'g':
        case 'G':
            update_cache(join_str(2, '/', cache_location, "g.bin"), content.name);
            break;
        case 'h':
        case 'H':
            update_cache(join_str(2, '/', cache_location, "h.bin"), content.name);
            break;
        case 'i':
        case 'I':
            update_cache(join_str(2, '/', cache_location, "i.bin"), content.name);
            break;
        case 'j':
        case 'J':
            update_cache(join_str(2, '/', cache_location, "j.bin"), content.name);
            break;
        case 'k':
        case 'K':
            update_cache(join_str(2, '/', cache_location, "k.bin"), content.name);
            break;
        case 'l':
        case 'L':
            update_cache(join_str(2, '/', cache_location, "l.bin"), content.name);
            break;
        case 'm':
        case 'M':
            update_cache(join_str(2, '/', cache_location, "m.bin"), content.name);
            break;
        case 'n':
        case 'N':
            update_cache(join_str(2, '/', cache_location, "n.bin"), content.name);
            break;
        case 'o':
        case 'O':
            update_cache(join_str(2, '/', cache_location, "o.bin"), content.name);
            break;
        case 'p':
        case 'P':
            update_cache(join_str(2, '/', cache_location, "p.bin"), content.name);
            break;
        case 'q':
        case 'Q':
            update_cache(join_str(2, '/', cache_location, "q.bin"), content.name);
            break;
        case 'r':
        case 'R':
            update_cache(join_str(2, '/', cache_location, "r.bin"), content.name);
            break;
        case 's':
        case 'S':
            update_cache(join_str(2, '/', cache_location, "s.bin"), content.name);
            break;
        case 't':
        case 'T':
            update_cache(join_str(2, '/', cache_location, "t.bin"), content.name);
            break;
        case 'u':
        case 'U':
            update_cache(join_str(2, '/', cache_location, "u.bin"), content.name);
            break;
        case 'v':
        case 'V':
            update_cache(join_str(2, '/', cache_location, "v.bin"), content.name);
            break;
        case 'w':
        case 'W':
            update_cache(join_str(2, '/', cache_location, "w.bin"), content.name);
            break;
        case 'x':
        case 'X':
            update_cache(join_str(2, '/', cache_location, "x.bin"), content.name);
            break;
        case 'y':
        case 'Y':
            update_cache(join_str(2, '/', cache_location, "y.bin"), content.name);
            break;
        case 'z':
        case 'Z':
            update_cache(join_str(2, '/', cache_location, "z.bin"), content.name);
            break;
        default:
            update_cache(join_str(2, '/', cache_location, "special.bin"), content.name);
            break;
        }
    }

    read_from_cache(join_str(2, '/', cache_location, "a.bin"));

}

int update_cache(const char* dir_path ,const char *file_name){
    FILE *f = fopen(dir_path, "ab");
    fwrite(file_name, 1, strlen(file_name), f);
    fwrite("\n", 1, 1, f);
    fclose(f);
}

void read_from_cache(const char* dir_path){

    printf("Reading from cache in %s\n" ,dir_path);

    char buffer[100];

    FILE *f = fopen(dir_path, "rb");

    while (fgets(buffer,sizeof(buffer) ,f) != NULL) {
        printf("%s" ,buffer);
    }

    fclose(f);
}