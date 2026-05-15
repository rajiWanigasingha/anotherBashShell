//
// Created by rajindawanigasingha on 5/10/26.
//

#include "../commands/file_attributes/file_attributes.h"

#include <stdio.h>

#include "../commands/cache/cache.h"
#include "../commands/walking_dir/walking_dir.h"

int main() {

    // FileAttributes file1 = file_attributes("/etc/localtime");
    //
    // printf("File path -> /etc\n");
    // printf("File type -> %d\n" ,file1.type);
    // printf("File size -> %lu\n" ,file1.size);
    // printf("File owner permission -> %d %d %d\n", file1.permissions.owner.read != 0 , file1.permissions.owner.write != 0 , file1.permissions.owner.execute != 0 );
    // printf("File last accessed time -> %d/%d/%d at %d:%d:%d\n", file1.time.last_access->tm_year + 1900 ,file1.time.last_access->tm_mon + 1 ,file1.time.last_access->tm_mday ,file1.time.last_access->tm_hour ,file1.time.last_access->tm_min ,file1.time.last_access->tm_sec);
    // printf("Owner -> %d\n" ,file1.owner.owner);
    //
    // file_attributes("/home/rajindawanigasingha/anotherBashShell");
    //
    // create_cache_dir();
    // cache_files("/home/rajindawanigasingha/");
    // cache_files("/home/rajindawanigasingha/dev");
    // cache_files("/home/rajindawanigasingha/.cache");
    // cache_files("/home/rajindawanigasingha/.config");

    // create_cache_dir();
    // const struct FilePointer *file = walking_dir("/home/rajindawanigasingha");
    //
    // for (int i = 0; i < file->amount; i++) {
    //     printf("File num : %d - now %d\n" ,i ,file->amount);
    //     cache_files(file->path[i]);
    // }

    read_from_cache("/home/rajindawanigasingha/.cache/find-cache/a.bin");

    return 0;
}
