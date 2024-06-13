/*  
 *  Author: uptu <uptu@uptu.dev>
 *
 *  This file is part of the `pi` project.
 *  `pi` is licensed under the MIT license.
 *  Please see the LICENSE file for more information.
 */

#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uptu_libs.h"

struct Project handle(int argc, char **argv);

struct Project {
    char* name;
    char* lang;
    char* init_args;
    unsigned int stack_arg_flags;
};

#endif
