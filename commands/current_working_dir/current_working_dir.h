//
// Created by rajindawanigasingha on 5/10/26.
//

#ifndef ANOTHERBASHSHELL_CURRENT_WORKING_DIR_H
#define ANOTHERBASHSHELL_CURRENT_WORKING_DIR_H

/**
 * @brief get the current working directory program run on.
 * @details
 * This function will give back the current working directory this program will run on, like pwd command in bash.
 * Must use free() to free this memory
 * @return Pointer to an array of characters or NULL pointer
 */
char *current_working_dir();

#endif //ANOTHERBASHSHELL_CURRENT_WORKING_DIR_H