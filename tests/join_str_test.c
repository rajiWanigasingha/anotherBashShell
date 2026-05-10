//
// Created by rajindawanigasingha on 5/10/26.
//

#include "../helpers/join_str.h"

#include <stdlib.h>

int main_test(){

    char * str = join_str(2 ,' ' , "hello" , "world");

    free(str);

    return 0;
}
