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

void cache_files(const char* result){
    char* cache_dir = getenv("HOME");

    if (cache_dir == NULL) {
        printf("HOME is not set.\n");
        return;
    }

    cache_dir = join_str(2, '/', cache_dir, ".cache");

    const char* cache_location = join_str(2, '/', cache_dir, "find-cache");

    const char *last = strrchr(result, '/');

    if (last == NULL) {
        return;
    }

    switch ((last + 1)[0]) {
    case 'a':
    case 'A':
        update_cache(join_str(2, '/', cache_location, "a.bin"), result);
        break;
    case 'b':
    case 'B':
        update_cache(join_str(2, '/', cache_location, "b.bin"), result);
        break;
    case 'c':
    case 'C':
        update_cache(join_str(2, '/', cache_location, "c.bin"), result);
        break;
    case 'd':
    case 'D':
        update_cache(join_str(2, '/', cache_location, "d.bin"), result);
        break;
    case 'e':
    case 'E':
        update_cache(join_str(2, '/', cache_location, "e.bin"), result);
        break;
    case 'f':
    case 'F':
        update_cache(join_str(2, '/', cache_location, "f.bin"), result);
        break;
    case 'g':
    case 'G':
        update_cache(join_str(2, '/', cache_location, "g.bin"), result);
        break;
    case 'h':
    case 'H':
        update_cache(join_str(2, '/', cache_location, "h.bin"), result);
        break;
    case 'i':
    case 'I':
        update_cache(join_str(2, '/', cache_location, "i.bin"), result);
        break;
    case 'j':
    case 'J':
        update_cache(join_str(2, '/', cache_location, "j.bin"), result);
        break;
    case 'k':
    case 'K':
        update_cache(join_str(2, '/', cache_location, "k.bin"), result);
        break;
    case 'l':
    case 'L':
        update_cache(join_str(2, '/', cache_location, "l.bin"), result);
        break;
    case 'm':
    case 'M':
        update_cache(join_str(2, '/', cache_location, "m.bin"), result);
        break;
    case 'n':
    case 'N':
        update_cache(join_str(2, '/', cache_location, "n.bin"), result);
        break;
    case 'o':
    case 'O':
        update_cache(join_str(2, '/', cache_location, "o.bin"), result);
        break;
    case 'p':
    case 'P':
        update_cache(join_str(2, '/', cache_location, "p.bin"), result);
        break;
    case 'q':
    case 'Q':
        update_cache(join_str(2, '/', cache_location, "q.bin"), result);
        break;
    case 'r':
    case 'R':
        update_cache(join_str(2, '/', cache_location, "r.bin"), result);
        break;
    case 's':
    case 'S':
        update_cache(join_str(2, '/', cache_location, "s.bin"), result);
        break;
    case 't':
    case 'T':
        update_cache(join_str(2, '/', cache_location, "t.bin"), result);
        break;
    case 'u':
    case 'U':
        update_cache(join_str(2, '/', cache_location, "u.bin"), result);
        break;
    case 'v':
    case 'V':
        update_cache(join_str(2, '/', cache_location, "v.bin"), result);
        break;
    case 'w':
    case 'W':
        update_cache(join_str(2, '/', cache_location, "w.bin"), result);
        break;
    case 'x':
    case 'X':
        update_cache(join_str(2, '/', cache_location, "x.bin"), result);
        break;
    case 'y':
    case 'Y':
        update_cache(join_str(2, '/', cache_location, "y.bin"), result);
        break;
    case 'z':
    case 'Z':
        update_cache(join_str(2, '/', cache_location, "z.bin"), result);
        break;
    default:
        update_cache(join_str(2, '/', cache_location, "special.bin"), result);
        break;
    }


    // read_from_cache(join_str(2, '/', cache_location, "a.bin"));
}

int update_cache(const char* dir_path, const char* file_name){
    FILE* f = fopen(dir_path, "ab");
    fwrite(file_name, 1, strlen(file_name), f);
    fwrite("\n", 1, 1, f);
    fclose(f);
    return 1;
}

void read_from_cache(const char* dir_path){
    printf("Reading from cache in %s\n", dir_path);

    char buffer[100];

    FILE* f = fopen(dir_path, "rb");

    while (fgets(buffer, sizeof(buffer), f) != NULL) {
        printf("%s", buffer);
    }

    fclose(f);
}
