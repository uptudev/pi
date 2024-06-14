/*  
 *  Author: uptu <uptu@uptu.dev>
 *
 *  This file is part of the `pi` project.
 *  `pi` is licensed under the MIT license.
 *  Please see the LICENSE file for more information.
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "uptu_libs.h"

#if (defined(_WIN32) || defined(__WIN32__))
/* 
 *  Windows does not have a built-in `getline` function, so we must define it here.
 *  This is a modified version of the GNU `getline` function.
 *  It was written by Song on StackOverflow: https://stackoverflow.com/a/74611379
 *
 *  Complexity
 *    Time: O(n)
 *    Space: O(n)
 */
size_t getline(char **lineptr, size_t *n, FILE *stream) {
    char *bufptr = NULL;
    char *p = bufptr;
    size_t size;
    int c;

    if (lineptr == NULL) {
        return -1;
    }

    if (stream == NULL) {
        return -1;
    }

    if (n == NULL) {
        return -1;
    }

    bufptr = *lineptr;
    size = *n;
    c = fgetc(stream);

    if (c == EOF) {
        return -1;
    }

    if (bufptr == NULL) {
        bufptr = malloc(128);

        if (bufptr == NULL) {
            return -1;
        }

        size = 128;
    }

    p = bufptr;

    while (c != EOF) {
        if ((p - bufptr) > (size - 1)) {
            size = size + 128;
            bufptr = realloc(bufptr, size);

            if (bufptr == NULL) {
                return -1;
            }

            p = bufptr + (size - 128);
        }
        *p++ = c;
        if (c == '\n') {
            break;
        }
        c = fgetc(stream);
    }

    *p++ = '\0';
    *lineptr = bufptr;
    *n = size;

    return p - bufptr - 1;
}
#endif

/*
 *  Queries the user with a prompt and returns the result as a perfectly sized char* 
 *  Note that this must be freed after use.
 *
 *  Complexity
 *    Time: O(n)
 *    Space: O(n)
 */
char* query(char* prompt) {
    char* result = NULL;
    printf("%s", prompt);
    getline(&result, &(size_t){0}, stdin);
    result[strlen(result) - 1] = '\0';
    return result;
}

/* 
 *  Convert a string to lowercase 
 *
 *  Complexity
 *      Time: O(n)
 *      Space: O(1)
 */
void lower(char* str) {
    for ( ; *str; ++str) *str = tolower(*str);
}


/*
 *  Returns the length of a string
 *
 *  Complexity 
 *      Time: O(n)
 *      Space: O(1)
 */
unsigned int length(char* str) {
    // empty string
    if (!str) return 0;
    unsigned int i = 0;
    for ( ; str[i]; i++);
    return i;
}

/*
 *  Returns the length of a string vector
 *
 *  Complexity
 *    Time: O(n)
 *    Space: O(1)
 */
unsigned int lengthv(char** strv) {
    if (!strv) return 0;
    unsigned int i = 0;
    for ( ; strv[i]; i++);
    return i;
}

/*
 *  Returns a substring of a string from start to end
 *  Must be freed after use.
 *
 *  Complexity
 *    Time: O(n)
 *    Space: O(n)
 */
char* substring(char* str, unsigned int start, unsigned int end) {
    unsigned int res_len = end - start;
    unsigned int len = length(str);
    if (start > len || end > len || start > end) {
        return (void*)0;
    }
    char* result = malloc((res_len) * sizeof(char));
    for (unsigned int i = 0; i < res_len; i++) {
        result[i] = str[i + start];
    }
    result[res_len] = '\0';
    return result;
}

/*
 *  Returns a substring of a string excluding a range from start to end
 *  Must be freed after use.
 *
 *  Complexity
 *    Time: O(n)
 *    Space: O(n)
 */
char* exclude(char* str, unsigned int start, unsigned int end) {
    unsigned int len = length(str);
    if (start > len || end > len || start > end) {
        return (void*)0;
    }
    char* result = malloc((len - (end - start)) * sizeof(char));
    for (unsigned int i = 0; i < start; i++) {
        result[i] = str[i];
    }
    for (unsigned int i = end; i < len; i++) {
        result[i - (end - start)] = str[i];
    }
    result[len - (end - start)] = '\0';
    return result;
}

/*
 *  Splits a string into an array of strings based on a delimiter character
 *  Must be freed after use.
 *
 *  Complexity
 *    Time: O(n)
 *    Space: O(n)
 */
char** split(char* str, char delim) {
    unsigned int len = length(str);
    unsigned int res_index = 0;
    unsigned int start_index = 0;
    char** result = malloc(sizeof(char*) * len);

    for (unsigned int i = 0; i < len; i++) {
        if (str[i] == delim) {
            result[res_index++] = substring(str, start_index, i);
            start_index = i + 1;
        }
    }

    result[res_index] = substring(str, start_index, len);
    result = (char**)realloc(result, (res_index + 1) * sizeof(char*));
    result[res_index + 1] = (void*)0;
    return result;
}

/*
 *  Joins an array of strings into a single string with a delimiter character
 *  Must be freed after use.
 *
 *  Complexity
 *    Time: O(n)
 *    Space: O(n)
 */
char* join(char** str, char delim) {
    unsigned int len = lengthv(str);
    unsigned int res_len = 0;

    for (int i = 0; i < len; i++) {
        unsigned int len = length(str[i]);
        res_len += len + 1;
    }

    char* result = (char*)malloc(res_len * sizeof(char));

    for (int i = 0; i < len; i++) {
        strcat(result, str[i]);
        if (i == len - 1) {
            break;
        }
        strcat(result, &delim);
    }
    return result;
}

/*
 *  Makes a directory with the given path, using the correct system command.
 *
 *  Complexity
 *  Time: O(1)
 *  Space: O(1)
 */
void make_dir(char* path) {
    #if (defined(_WIN32) || defined(__WIN32__))
        mkdir(path);
    #else
        mkdir(path, 0700);
    #endif
}
