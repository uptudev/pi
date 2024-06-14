/*  
 *  Author: uptu <uptu@uptu.dev>
 *
 *  uptu_libs.h
 *
 *  Contains QOL functions for mostly string manipulation
 *  and user input handling.
 *
 *  This file is part of the `pi` project.
 *  `pi` is licensed under the MIT license.
 *  Please see the LICENSE file for more information.
 */

#ifndef UPTU_LIBS_H
#define UPTU_LIBS_H
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char* query(char* prompt);
void lower(char* str);
unsigned int length(char* str);
unsigned int lengthv(char** strv);
char** split(char* str, char delim);
char* join(char** arr, char delim);
char* substring(char* str, unsigned int start, unsigned int end);
char* exclude(char* str, unsigned int start, unsigned int end);
void concat(char* str1, char* str2);
void concat_space(char* str1, char* str2);
void make_dir(char* path);

#endif // UPTU_LIBS_H
