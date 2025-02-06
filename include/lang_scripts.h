/*  
 *  Author: uptu <uptu@uptu.dev>
 *
 *  This file is part of the `pi` project.
 *  `pi` is licensed under the MIT license.
 *  Please see the LICENSE file for more information.
 */

#ifndef LANG_SCRIPTS_H
#define LANG_SCRIPTS_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

int route(char *name, char *lang, char* args);

#endif // LANG_SCRIPTS_H
