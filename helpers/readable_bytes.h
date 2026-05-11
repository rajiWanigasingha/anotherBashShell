//
// Created by rajindawanigasingha on 5/11/26.
//

#ifndef ANOTHERBASHSHELL_READABLE_BYTES_H
#define ANOTHERBASHSHELL_READABLE_BYTES_H
#include <stddef.h>

struct ReadableBytes {
    double bytes;
    char *readable_formate;
};

typedef struct ReadableBytes ReadableBytes;

ReadableBytes readable_bytes(size_t bytes);

#endif //ANOTHERBASHSHELL_READABLE_BYTES_H