//
// Created by rajindawanigasingha on 5/10/26.
//

#include "../commands/file_attributes/file_attributes.h"

#include <stdio.h>

int main() {

    FileAttributes file1 = file_attributes("/home/rajindawanigasingha/");

    printf("File path -> /home/rajindawanigasingha/\n");
    printf("File type -> %d\n" ,file1.type);
    printf("File size -> %lu\n" ,file1.size);
    printf("File owner permission -> %d %d %d", file1.permissions.owner.read != 0 , file1.permissions.owner.write != 0 , file1.permissions.owner.execute != 0 );

    file_attributes("/home/rajindawanigasingha/anotherBashShell");

    return 0;
}
