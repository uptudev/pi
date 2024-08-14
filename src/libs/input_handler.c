/*  
 *  Author: uptu <uptu@uptu.dev>
 *
 *  This file is part of the `pi` project.
 *  `pi` is licensed under the MIT license.
 *  Please see the LICENSE file for more information.
 *  Copyright (c) 2024 uptu
 */

#include "./input_handler.h"

/* String Constants */
#define USAGE "\
\x1b[0;1;4;35mPi\x1b[0m is a CLI \x1b[0;94mproject initializer\x1b[0m which uses per-language build tools to create project directories populated with a full project template.\n\
\n\
\x1b[0;1;33mUsage\x1b[0m:\n\
    \x1b[0;94mpi\x1b[0m \x1b[0;31m[OPTIONS]\x1b[0m\n\
    \x1b[0;94mpi\x1b[0m \x1b[0;32m<NAME>\x1b[0m \x1b[0;31m[OPTIONS]\x1b[0m\n\
    \x1b[0;94mpi\x1b[0m \x1b[0;32m<NAME>\x1b[0m \x1b[0;32m<LANG>\x1b[0m \x1b[0;31m[OPTIONS]\x1b[0m\n\
\n\
\x1b[0;1;33mOptions\x1b[0m:\n\
    \x1b[0;94m-n\x1b[0m, \x1b[0;94m--name\x1b[0m \x1b[0;32m<NAME>\x1b[0m\n\
            Set the project name\n\
    \x1b[0;94m-l\x1b[0m, \x1b[0;94m--lang\x1b[0m \x1b[0;32m<LANG>\x1b[0m\n\
            Set the project language\n\
    \x1b[0;94m-h\x1b[0m, \x1b[0;94m--help\x1b[0m\n\
            Display this message\n\
    \x1b[0;94m-v\x1b[0m, \x1b[0;94m--version\x1b[0m\n\
            Display the version\n"
#define VERSION "\
\x1b[0;90m┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┑\n\
│\x1b[1;4;96mpi v1.0.3\x1b[0m by \x1b[0;33muptu\x1b[0m <\x1b[0;93muptu@uptu.dev\x1b[0m>\x1b[0;90m│\n\
┕━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┙\x1b[0m"
#define NONTERM_FLAG_ERR "Flag \"%s\" was not followed by a non-flag value\n"
#define DOUBLE_FLAG_ERR "Flag \"%s\" was followed by another flag \"%s\"\n"

void print_usage() {
    puts(USAGE);
}

/*-----------*/
/* Tokenizer */
/*-----------*/

enum TokenType {
    FLAG,
    NON_FLAG,
};

struct Token {
    char* literal;
    enum TokenType type;
};

struct TokenArray {
    struct Token* tokens;
    unsigned int length;
};

/*
 * Create a token from a normal `char*` string.
 * If the string starts with a `-`, it is a flag, else it is a non-flag.
 * Returns the token.
 */
struct Token token(char* input) {
    struct Token t;
    t.literal = input;
    if (input[0] == '-') {
        t.type = FLAG;
    } else {
        t.type = NON_FLAG;
    }
    return t;
}

/* 
 *  Tokenize the input string vector (i.e. argv).
 *  Use the token function to create a token from a normal `char*` string instead.
 *  Return the subsequent array of unvalidated tokens.
 */
struct TokenArray tokenize(char** input, unsigned int length) {
    struct Token* tokens = malloc(sizeof(struct Token) * length);
    for (int i = 0; i < length; i++) {
        tokens[i] = token(input[i]);
    }
    struct TokenArray t;
    t.tokens = tokens;
    t.length = length;
    return t;
}

/*--------*/
/* Parser */
/*--------*/

/*
 *  Check the validity of the tokens 
 *  If a flag other than help or version is present, check if the next token is a non-flag
 *  If input is valid, returns, else prints error message and quits
 */
void check_validity(struct TokenArray tokenarr) {
    for (int i = 0; i < tokenarr.length; i++) {
        struct Token t = tokenarr.tokens[i];
        if (t.type == FLAG) {
            // do not parse init_args (anything following `--`)
            if (strcmp(t.literal, "--") == 0) {
                return;
            // help and version flags do not require validity checks
            } else if (
                strcmp(t.literal, "-h") == 0 ||
                strcmp(t.literal, "--help") == 0 ||
                strcmp(t.literal, "-v") == 0 ||
                strcmp(t.literal, "--version") == 0
            ) {
                return;
            } else if (
                i + 1 > tokenarr.length
            ) {
                printf(NONTERM_FLAG_ERR, t.literal);
                print_usage();
                free(tokenarr.tokens);
                exit(1);
            } else if (tokenarr.tokens[i + 1].type != NON_FLAG) {
                printf(
                    DOUBLE_FLAG_ERR,
                    t.literal,
                    tokenarr.tokens[i + 1].literal);
                print_usage();
                free(tokenarr.tokens);
                exit(1);
            }
        }
    }
}

/* 
 *  Flatten the tokens in `tokenarr` into a single string;
 *  starts from the `start` index and concatenates all the literals into a single string
 *  Returns the concatenated string
 */
char* flatten_tokens(struct TokenArray tokenarr, unsigned int start) {
    unsigned int len = 0;
    for (int i = start; i < tokenarr.length; i++) {
        len += length(tokenarr.tokens[i].literal) + 1;
    }
    unsigned int curr = 0;
    char* result = malloc(len * sizeof(char));
    for (int word = start; word < tokenarr.length; word++) {
        char* str = tokenarr.tokens[word].literal;
        for (int i = 0; str[i]; i++) {
            result[curr] = str[i];
            curr++;
        }
        if (word == tokenarr.length - 1) {
            result[curr] = '\0';
            curr = 0;
            break;
        }
        result[curr] = ' ';
        curr++;
    }
    return result;
}

/* 
 *  Parse the tokens in `tokenarr` into a Project struct
 *  If the project name or language is not provided, query the user for it
 *  If the project init_args are not provided, flatten the remaining tokens upon name and lang extraction into a single string
 *  Returns the parsed Project struct
 */
struct Project parse(struct TokenArray tokenarr) {
    /*  parser_state
     *  0b 0000 0000 - no flags set
     *  0b 0000 0001 - help flag
     *  0b 0000 0010 - version flag
     *  0b 0000 0100 - project name set
     *  0b 0000 1000 - project lang set
     *  0b 0001 0000 - project init_args set
     *  0b 0010 0000 - no flag args (quick parse)
     */
    char parser_state = 0x20;
    struct Project p;
    p.stack_arg_flags = 0;
    for (int i = 0; i < tokenarr.length; i++) {
        int exit = 0;
        struct Token t = tokenarr.tokens[i];
        if (t.type == FLAG) {
            if (
                strcmp(t.literal, "-h") == 0
                || strcmp(t.literal, "--help") == 0
            ) {
                // clear 'no flag args' flag and set 'help flag' flag
                parser_state &= 0xDF;
                parser_state |= 0x01;
            } else if (
                strcmp(t.literal, "-v") == 0
                || strcmp(t.literal, "--version") == 0
                ) {
                // clear 'no flag args' flag and set 'version flag' flag
                parser_state &= 0xDF;
                parser_state |= 0x02;
            } else if (
                strcmp(t.literal, "-n") == 0
                || strcmp(t.literal, "--name") == 0
            ) {
                // clear 'no flag args' flag and set 'project name set' flag
                parser_state &= 0xDF;
                parser_state |= 0x04;
                p.stack_arg_flags |= 0x01;
                p.name = tokenarr.tokens[i + 1].literal;
                for (int j = i; j < tokenarr.length - 2; j++) {
                    tokenarr.tokens[j] = tokenarr.tokens[j + 2];
                }
                tokenarr.length -= 2;
                tokenarr.tokens = (struct Token*)realloc(
                    tokenarr.tokens,
                    tokenarr.length * sizeof(struct Token));
                i--;
            } else if (
                strcmp(t.literal, "-l") == 0
                || strcmp(t.literal, "--lang") == 0
            ) {
                // clear 'no flag args' flag and set 'project lang set' flag
                parser_state &= 0xDF;
                parser_state |= 0x08;
                p.stack_arg_flags |= 0x02;
                p.lang = tokenarr.tokens[i + 1].literal;
                for (int j = i; j < tokenarr.length - 2; j++) {
                    tokenarr.tokens[j] = tokenarr.tokens[j + 2];
                }
                tokenarr.length -= 2;
                tokenarr.tokens = (struct Token*)realloc(
                    tokenarr.tokens, tokenarr.length * sizeof(struct Token));
                i--;
            } else if (strcmp(t.literal, "--") == 0) {
                // clear 'no flag args' flag
                // set 'project init_args set' flag
                parser_state &= 0xDF;
                parser_state |= 0x10;
                p.stack_arg_flags |= 0x04;
                p.init_args = flatten_tokens(tokenarr, i + 2);
                break;
            }
        } else if (parser_state & 0x20) {
            switch (i) {
                case 1:
                    p.name = t.literal;
                    parser_state |= 0x04;
                    p.stack_arg_flags |= 0x01;
                    break;
                case 2:
                    p.lang = t.literal;
                    parser_state |= 0x08;
                    p.stack_arg_flags |= 0x02;
                    if (
                        tokenarr.length > 3
                        && strcmp(tokenarr.tokens[3].literal, "--")
                    ) {
                        p.init_args = flatten_tokens(tokenarr, 3);
                        parser_state |= 0x10;
                    } else if (tokenarr.length > 4) {
                        p.init_args = flatten_tokens(tokenarr, 4);
                        parser_state |= 0x10;
                    }
                    exit = 1;
                    break;
                default:
                    // skip i = 0; it is the program name
                    // i > 2 is unreachable due to the exit flag
                    break;
            }
        }

        // exit early if the exit flag is set via having no flag args
        if (exit) {
            break;
        }
    }

    // if help or version flags are on,
    // print the respective message and exit early
    if (parser_state & 0x03) {
        if (parser_state & 2) {
            puts(VERSION);
        }
        if (parser_state & 1) {
            print_usage();
        }
        if (parser_state & 0x10) {
            free(p.init_args);
        }
        if (tokenarr.tokens) free(tokenarr.tokens);
        exit(0);
    }
    parser_state >>= 2;
    if (!(parser_state & 1)) {
        while (
            !p.name
            || !strcmp(p.name, "")
            || !strcmp(p.name, " ")
            || !strcmp(p.name, "\n")
            || !strcmp(p.name, "\t")
            || !strcmp(p.name, "\r")
            || !strcmp(p.name, "\0")
        ) {
            if (p.name) free(p.name);
            p.name = query("\x1b[0;1mEnter the project name\x1b[0m: ");
        }
        parser_state |= 1;
        p.stack_arg_flags &= 0xFE;
    }
    if (!(parser_state & 2)) {
        while (
            !p.lang
            || !strcmp(p.lang, "")
            || !strcmp(p.lang, " ")
            || !strcmp(p.lang, "\n")
            || !strcmp(p.lang, "\t")
            || !strcmp(p.lang, "\r")
            || !strcmp(p.lang, "\0")
        ) {
            if (p.lang) free(p.lang);
            p.lang = query("\x1b[0;1mEnter the project language\x1b[0m: ");
        }
        parser_state |= 2;
        p.stack_arg_flags &= 0xFD;
    }
    if (parser_state & 1 && parser_state & 2 && !(parser_state & 4)) {
        p.init_args = NULL;
        parser_state |= 4;
        p.stack_arg_flags &= 0xFB;
    }

    free(tokenarr.tokens);
    return p;
}

struct Project handle(int argc, char **argv) {
    struct TokenArray tokenarr = tokenize(argv, argc);
    check_validity(tokenarr);
    struct Project p = parse(tokenarr);
    return p;
}
