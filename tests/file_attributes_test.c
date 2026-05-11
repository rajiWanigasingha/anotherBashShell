//
// Created by rajindawanigasingha on 5/10/26.
//

#include "../commands/file_attributes/file_attributes.h"

#include <stdio.h>

int main() {

    FileAttributes file1 = file_attributes("/home/rajindawanigasingha/.bash_history");

    printf("File path -> /home/rajindawanigasingha/.bash_history\n");
    printf("File type -> %d\n" ,file1.type);
    printf("File size -> %lu\n" ,file1.size);
    printf("File owner permission -> %d %d %d\n", file1.permissions.owner.read != 0 , file1.permissions.owner.write != 0 , file1.permissions.owner.execute != 0 );
    printf("File last accessed time -> %d/%d/%d at %d:%d:%d\n", file1.time.last_access->tm_year + 1900 ,file1.time.last_access->tm_mon + 1 ,file1.time.last_access->tm_mday ,file1.time.last_access->tm_hour ,file1.time.last_access->tm_min ,file1.time.last_access->tm_sec);

    file_attributes("/home/rajindawanigasingha/anotherBashShell");

    return 0;
}
