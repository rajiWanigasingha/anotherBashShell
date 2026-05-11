//
// Created by rajindawanigasingha on 5/11/26.
//

#include "readable_bytes.h"

ReadableBytes readable_bytes(const size_t bytes){

    ReadableBytes readable_bytes = {};

    if (bytes < 1024) {
        readable_bytes.bytes = (double)bytes;
        readable_bytes.readable_formate = "Bytes";
    } else if (bytes < 1024 * 1024) {
        readable_bytes.bytes = (double)bytes / 1024;
        readable_bytes.readable_formate = "KB";
    } else if (bytes < 1024 * 1024 * 1024) {
        readable_bytes.bytes = (double)bytes / (1024 * 1024);
        readable_bytes.readable_formate = "MB";
    } else {
        readable_bytes.bytes = (double)bytes / (1024 * 1024 * 1024);
        readable_bytes.readable_formate = "GB";
    }

    return readable_bytes;
}
