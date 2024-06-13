/*  
 *  Author: uptu <uptu@uptu.dev>
 *
 *  This file is part of the `pi` project.
 *  `pi` is licensed under the MIT license.
 *  Please see the LICENSE file for more information.
 */

#include "uptu_libs.h"
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
uint length(char* str) {
    // empty string
    if (!str) return 0;
    uint i = 0;
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
uint lengthv(char** strv) {
    if (!strv) return 0;
    uint i = 0;
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
char* substring(char* str, uint start, uint end) {
    uint res_len = end - start;
    uint len = length(str);
    if (start > len || end > len || start > end) {
        return (void*)0;
    }
    char* result = malloc((res_len) * sizeof(char));
    for (uint i = 0; i < res_len; i++) {
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
char* exclude(char* str, uint start, uint end) {
    uint len = length(str);
    if (start > len || end > len || start > end) {
        return (void*)0;
    }
    char* result = malloc((len - (end - start)) * sizeof(char));
    for (uint i = 0; i < start; i++) {
        result[i] = str[i];
    }
    for (uint i = end; i < len; i++) {
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
    uint len = length(str);
    uint res_index = 0;
    uint start_index = 0;
    char** result = malloc(sizeof(char*) * len);

    for (uint i = 0; i < len; i++) {
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
    uint len = lengthv(str);
    uint res_len = 0;

    for (int i = 0; i < len; i++) {
        uint len = length(str[i]);
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
