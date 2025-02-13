/*  
 *  Author: uptu <uptu@uptu.dev>
 *
 *  This file is part of the `pi` project.
 *  `pi` is licensed under the MIT license.
 *  Please see the LICENSE file for more information.
 *  Copyright (c) 2024 uptu
 */

// * Table of Contents
// *
// * Search for these symbols to navigate this file:
// *
// *  Includes
// *  String Constants
// *  Utility Functions
// *  Language Initialization Functions
// *  Main Routing Function

// Includes
#include "./lang_scripts.h"
#include "./uptu_libs.h"

/* String Constants */
#define README "# %s\n\
\n\
**[Short, memorable description of your project]**\n\
\n\
## Contents\n\
\n\
* [Installation](#installation)\n\
* [Usage](#usage)\n\
* [Contributing](#contributing)\n\
* [License](#license)\n\
* [Miscellaneous](#miscellaneous)\n\
\n\
## Installation\n\
\n\
**Describe how to install your project.**\n\
This may involve specifying dependencies, prerequisites, and build instructions.\n\
Use code blocks, links, and step-by-step guides for clarity.\n\
\n\
## Usage\n\
\n\
**Offer clear and concise instructions on how to use your project.**\n\
Explain its functionalities, features, and common use cases.\n\
Include examples, screenshots, or animated images if helpful.\n\
\n\
**Tips:**\n\
\n\
* Break down instructions into logical steps.\n\
* Use bullet points for succinct explanations.\n\
* Consider creating a separate \"Getting Started\" guide for beginners.\n\
\n\
## Contributing\n\
\n\
**Outline your contribution guidelines.**\n\
Explain how users can contribute to your project,\n\
whether through code, bug reports, or documentation improvements.\n\
Specify preferred code style, pull request format, and testing procedures.\n\
\n\
## License\n\
\n\
**Specify the license that you plan to distribute your project under.**\n\
Use clear and concise language, and link to the full license text.\n\
\n\
## Miscellaneous\n\
\n\
**Include any other relevant information you want to share.**\n\
This could be links to related projects, documentation,\n\
support channels, or your contact information.\n\
\n\
**Remember:**\n\
\n\
* Keep your README.md file concise and focused.\n\
* Use clear headings, formatting, and visuals for readability.\n\
* Update your README.md file regularly to reflect changes in your project.\n"
#define LIST_LANGS "\
\x1b[0;1;31mLanguage not supported\x1b[0m.\n\
\x1b[0;1;33mSupported languages\x1b[0m: \n\
    - \x1b[0;94mBun\x1b[0m\n\
    - \x1b[0;94mC\x1b[0m\n\
    - \x1b[0;94mC++\x1b[0m\n\
    - \x1b[0;94mGo\x1b[0m\n\
    - \x1b[0;94mHaskell\x1b[0m\n\
    - \x1b[0;94mLua\x1b[0m\n\
    - \x1b[0;94mNode.js\x1b[0m\n\
    - \x1b[0;94mOCaml\x1b[0m\n\
    - \x1b[0;94mRuby\x1b[0m\n\
    - \x1b[0;94mRust\x1b[0m\n\
    - \x1b[0;94mV\x1b[0m\n\
    - \x1b[0;94mZig\x1b[0m\n"
#define C_MAIN "#include <stdio.h>\n\nint main() {\n\tputs(\"Hello, World!\");\n\treturn 0;\n}\n"
#define C_TEST "#include \"%s.h\"\n\nint main() {\n\t/* This is a testing executable linked to src/%s.c */\n\treturn 0;\n}\n"
#define CPP_MAIN "#include <iostream>\n\nint main() {\n\tstd::cout << \"Hello, World!\\n\";\n\treturn 0;\n}\n"
#define CPP_TEST "#include \"%s.h\"\n\nint main() {\n\t/* This is a testing executable linked to src/%s.cpp */\n\treturn 0;\n}\n"
#define C_HEADER "/*\n *  %s.h\n *\n *  See LICENSE file for licensing information.\n */\n\n#ifndef _%s_H\n#define _%s_H\n// DECLARATIONS GO HERE\n#endif  // _%s_H"
#define CMAKELISTS "# See LICENSE file for license information.\ncmake_minimum_required(VERSION 3.10)\nproject(\n\t%s\n\tVERSION 0.0.1\n\tDESCRIPTION \"Put your program description here.\")\n\n# Add shared library\nadd_library(\n\t${PROJECT_NAME}\n\tSHARED src/%s.c)\nset_property(\n\tTARGET ${PROJECT_NAME}\n\tPROPERTY POSITION_INDEPENDENT_CODE ON)\ntarget_include_directories(\n\t${PROJECT_NAME}\n\tPUBLIC include)\n\n# Add static library\nadd_library(\n\t${PROJECT_NAME}_static\n\tSTATIC src/%s.c)\ntarget_include_directories(\n\t${PROJECT_NAME}_static\n\tPUBLIC include)\n\n# Add test executable\nadd_executable(\n\ttest\n\tsrc/test.c)\ntarget_include_directories(\n\ttest\n\tPRIVATE include)\ntarget_link_libraries(\n\ttest\n\t${PROJECT_NAME}_static)\n\n# Library installation rules\ninstall(\n\tTARGETS ${PROJECT_NAME} ${PROJECT_NAME}_static\n\tRUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin\n\tLIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib\n\tARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/${PROJECT_NAME})\n\n# Header installation rules\ninstall(\n\tFILES include/%s.h\n\tDESTINATION ${CMAKE_INSTALL_PREFIX}/include)"
#define CPPMAKELISTS "# See LICENSE file for license information.\ncmake_minimum_required(VERSION 3.10)\nproject(\n\t%s\n\tVERSION 0.0.1\n\tDESCRIPTION \"Put your program description here.\")\n\n# Add shared library\nadd_library(\n\t${PROJECT_NAME}\n\tSHARED src/%s.cpp)\nset_property(\n\tTARGET ${PROJECT_NAME}\n\tPROPERTY POSITION_INDEPENDENT_CODE ON)\ntarget_include_directories(\n\t${PROJECT_NAME}\n\tPUBLIC include)\n\n# Add static library\nadd_library(\n\t${PROJECT_NAME}_static\n\tSTATIC src/%s.cpp)\ntarget_include_directories(\n\t${PROJECT_NAME}_static\n\tPUBLIC include)\n\n# Add test executable\nadd_executable(\n\ttest\n\tsrc/test.cpp)\ntarget_include_directories(\n\ttest\n\tPRIVATE include)\ntarget_link_libraries(\n\ttest\n\t${PROJECT_NAME}_static)\n\n# Library installation rules\ninstall(\n\tTARGETS ${PROJECT_NAME} ${PROJECT_NAME}_static\n\tRUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin\n\tLIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib\n\tARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/${PROJECT_NAME})\n\n# Header installation rules\ninstall(\n\tFILES include/%s.h\n\tDESTINATION ${CMAKE_INSTALL_PREFIX}/include)"
#define BUILDSH "#!/bin/sh\n\n# build.sh\n# ^^^^^^^^\n# This script is used to build the project.\n# It does the following in sequence:\n# 1.a) Cleans the build directory if it exists.\n#   b) Creates a new build directory if it does not exist.\n# 2. Changes the working directory to the build directory.\n# 3. Runs cmake to generate the build files.\n# 4. Runs make to build the project.\n# 5. Deletes the build artifacts.\n# 6. Hardlinks the header file to the build directory.\n#\n# If any of the steps fail, the script will print an error message and exit.\n# The script will print a success message if the build is successful.\n# The script is intended to be run from the root of the project directory.\n# The script is intended to be run on a Unix-like system with a bash shell, GNU Make, and CMake.\n# For other systems, manual execution of the substituted commands is required.\n# See LICENSE file for license information.\n\n# * Constants *\n\n# Info log strings\nreadonly CLEAN_STR=\"Cleaning build directory...\"\nreadonly BUILD_DIR_STR=\"Creating build directory...\"\nreadonly CMAKE_STR=\"Running CMake...\"\nreadonly BUILD_STR=\"Building...\"\nreadonly COPY_STR=\"Hardlinking header to build directory...\"\nreadonly DEL_ART_STR=\"Deleting build artifacts...\"\n\n# Query log string\nreadonly ASK_INSTALL=\"Install the library?\"\n\n# Success log string\nreadonly BUILD_COMPLETE=\"Build complete!\"\n\n# Error log strings\nreadonly CLEAN_FAIL=\"Failed to clean build directory!\"\nreadonly BUILD_DIR_FAIL=\"Failed to create build directory!\"\nreadonly CMAKE_FAIL=\"Failed to run CMake!\"\nreadonly BUILD_FAIL=\"Failed to build using the default build tool (usually GNU Make)!\"\nreadonly COPY_FAIL=\"Failed to hardlink header to build directory!\"\nreadonly INSTALL_FAIL=\"Failed to install the library!\"\nreadonly DEL_ART_FAIL=\"Failed to delete build artifacts!\"\n\n# * Procedure *\nprint_info() { printf \"\\x1b[0m[\\x1b[34m*\\x1b[0m] \\x1b[34m%%s\\x1b[0m\n\" \"$1\"; }\nprint_query() { printf \"\\x1b[0m\\x1b[33m%%s\\x1b[0m [\\x1b[32m%%s\\x1b[0m/\\x1b[31m%%s\\x1b[0m]: \" \"$1\" \"$2\" \"$3\"; }\nprint_success() { printf \"\\x1b[0m[\\x1b[32;1m+\\x1b[0m] \\x1b[32;1m%%s\\x1b[0m\n\" \"$1\"; }\nprint_error() { printf \"\\x1b[0m[\\x1b[37;41;1m%%%%\\x1b[0m] \\x1b[37;41;1m%%s\\x1b[0m\n\" \"$1\"; }\n\n# Clean build directory if anything is present within it\nprint_info \"$CLEAN_STR\"\nrm -rf ./build/* || \n\t{ print_error \"$CLEAN_FAIL\" && exit 1; }\n# Create build directory if it does not exista and change working directory to it\nprint_info \"$BUILD_DIR_STR\"\n{ mkdir -p build && cd ./build; } || \n\t{ print_error \"$BUILD_DIR_FAIL\" && exit 1; }\n# Run cmake to generate build files\nprint_info \"$CMAKE_STR\"\ncmake .. || \n\t{ print_error \"$CMAKE_FAIL\" && exit 1; }\n# Run make to build the project\nprint_info \"$BUILD_STR\"\ncmake --build . --config Release ||\n\t{ print_error \"$BUILD_FAIL\" && exit 1; }\n# Hardlink the header file to the build directory\nprint_info \"$COPY_STR\"\nln ../include/%s.h . || \n\t{ print_error \"$COPY_FAIL\" && exit 1; }\n# Ask user if they want to install the library to their system\nprint_query \"$ASK_INSTALL\" \"y\" \"N\"\nread -r QUERY_INSTALL\ncase $QUERY_INSTALL in\n\ty|Y) sudo cmake --install . || \n\t\t{ print_error \"$INSTALL_FAIL\" && exit 1; } ;;\n\t*) ;;\nesac\n# Delete build artifacts\nprint_info \"$DEL_ART_STR\"\nrm -rf ./CMakeFiles ./CMakeCache.txt ./Makefile ./cmake_install.cmake ./build.ninja ./.ninja* || \n\t{ print_error \"$DEL_ART_FAIL\" && exit 1; }\n# Print build success message\nprint_success \"$BUILD_COMPLETE\"\nexit 0"

#define C_GITIGNORE "\
# executable shouldn't be in the repo\n\
%s\n\
\n\
# no coredumps \n\
CORE-*\n\
\n\
# Makefile should be configured to use the correct compiler\n\
Makefile\n"
#define GO_MAIN "package main\n\nimport \"fmt\"\n\nfunc main() {\n\tfmt.Println(\"Hello, World!\")\n}\n"
#define LUA_MAIN "-- %s\n\nprint(\"Hello, World!\")\n"
#define DIR_CREATE "\x1b[0;90mCreating directory \x1b[0;1;33m%s%s\x1b[0;90m...\x1b[0m\n"
#define FILE_CREATE "\x1b[0;90mCreating \x1b[0;1;33m%s%s\x1b[0;90m...\x1b[0m\n"
#define ENTRY_CREATE "\x1b[0;90mCreating entry point \x1b[0;1;33m%s%s\x1b[0;90m...\x1b[0m\n"
#define FILE_CREATE_FAILURE "\x1b[0;1;31mFailed to create file\x1b[0m \x1b[0;1;37;41m%s\x1b[0m. \n"
#define FILE_CHMOD_FAILURE "\x1b[0;1;31mFailed to change permissions on file\x1b[0m \x1b[0;1;37;41m%s\x1b[0m. \n"
#define PROJECT_INIT "\x1b[0;90mInitializing %s project \x1b[0;1;33m%s\x1b[0;90m...\x1b[0m\n"
#define BAD_YN_INPUT "\x1b[0;1;31mInvalid input\x1b[0m. Please enter either \x1b[0;1;37;41my\x1b[0m or \x1b[0;1;37;41mn\x1b[0m.\n"
#define BAD_Q_INPUT "\x1b[0;1;31mInvalid input\x1b[0m. Please enter either \x1b[0;1;37;41mBUN\x1b[0m or \x1b[0;1;37;41mNODE\x1b[0m.\n"
#define DIR_EXISTS "\x1b[0;1;31mDirectory\x1b[0m \x1b[0;1;37;41m%s\x1b[0m \x1b[0;1;31malready exists\x1b[0m. \n"
#define SUCCESS "\x1b[0;32mProject \x1b[0;1;32m%s\x1b[0;32m initialized successfully\x1b[0m.\n"
/* Utility Functions */
char* create_dir(char *name) {
    char* cwd = malloc(512);
    snprintf(cwd, 512, "./%s/", name);
    for (unsigned int i = 0; i < 512; i++) {
        if (cwd[i] == '\0') {
            cwd = realloc(cwd, i);
            break;
        }
    }

    /* Create the parent directory and `cd` into it*/
    printf(
        DIR_CREATE,
        cwd,
        "");
    make_dir(name);
    chdir(cwd);

    return cwd;
}

int create_readme(char *name, char* cwd) {
    /* Create the default README.md file */
    printf(
        FILE_CREATE,
        cwd,
        "README.md");
    chdir(cwd);
    FILE* readme = fopen("README.md", "w");
    if (!readme) {
        printf(FILE_CREATE_FAILURE, "README.md");
        free(cwd);
        exit(1);
    }
    fprintf(readme, README, name);
    fclose(readme);
    return 0;
}

/* Language Initialization Functions */

// If a build tool can create a project in place with a single command,
// use this function instead of a specialized one.
int simple_init(char *name, char* cmd, char* cwd) {
    system(cmd);

    /* Create README.md file */
    create_readme(name, cwd);

    printf(
        SUCCESS,
        name);
    return 0;
}

int bun_init(char *name, char *args) {
    /* Create the directory */
    char* cwd = create_dir(name);

    /* Initialize the bun project, using bun create if args exist */
    if (args) {
        char* str = malloc(512);
        snprintf(str, 512, "bun create %s", args);
        system(str);
        free(str);
    } else {
        loop: {
            char* str = query(
                "\x1b[0;1mWould you like to use TypeScript\x1b[0m? (y/n) ");
            lower(str);
            if (strcmp(str, "y") == 0) {
                free(str);
                system("bun init -y");
            } else if (strcmp(str, "n") == 0) {
                free(str);
                printf(
                    ENTRY_CREATE,
                    cwd,
                    "index.js");
                FILE *f = fopen("index.js", "w");
                if (!f) {
                    printf(
                        FILE_CREATE_FAILURE,
                        "index.js");
                    free(cwd);
                    return 1;
                }
                fprintf(f, "console.log(\"Hello, World!\");\n");
                fclose(f);
                system("bun init -y");
            } else {
                free(str);
                puts(BAD_YN_INPUT);
                goto loop;
            }
        }
    }

    /* Create README.md file */
    create_readme(name, cwd);
    free(cwd);
    return 0;
}

// if is_cpp == 0, then it is not C++; if is_cpp != 0, then it is C++
int c_init(char *name, char* args, int is_cpp) {
    char* cwd = create_dir(name);
    char* upper = strcpy(malloc(length(name) + 1), name);
    for (int i = 0; i < length(name); i++) {
        if (upper[i] >= 'a' && upper[i] <= 'z') upper[i] = toupper(upper[i]);
    }

    /* Create the subdirectories */
    printf(DIR_CREATE, cwd, "src");
    make_dir("src");
    printf(DIR_CREATE, cwd, "include");
    make_dir("include");

    /* Create the build script */
    printf(
        FILE_CREATE,
        cwd,
        "build.sh");
    FILE* buildsh = fopen("build.sh", "w");
    if (!buildsh) {
        printf(FILE_CREATE_FAILURE, "build.sh");
        free(cwd);
        free(upper);
        return 1;
    }
    fprintf(buildsh, BUILDSH, name);
    if (chmod("build.sh", 493) < 0) {
        printf(FILE_CHMOD_FAILURE, "build.sh");
        free(cwd);
        free(upper);
        return 1;
    }
    fclose(buildsh);

    /* Create the header */
    char* header_name = malloc(512);
    snprintf(header_name, 512, "include/%s.h", name);
    printf(
        FILE_CREATE,
        cwd,
        header_name);
    FILE* header = fopen(header_name, "w");
    if (!header) {
        printf(
            FILE_CREATE_FAILURE,
            header_name);
        free(header_name);
        free(cwd);
        free(upper);
        return 1;
    }
    free(header_name);
    fprintf(header, C_HEADER, name, upper, upper, upper);
    free(upper);
    fclose(header);

    if (is_cpp) {
        /* Create the CMakeLists */
        printf(
            FILE_CREATE,
            cwd,
            "CMakeLists.txt");
        FILE* makelists = fopen("CMakeLists.txt", "w");
        if (!makelists) {
            printf(FILE_CREATE_FAILURE, "CMakeLists.txt");
            free(cwd);
            return 1;
        }
        fprintf(makelists, CPPMAKELISTS, name, name, name, name);
        fclose(makelists);

        char* cpp_main = malloc(512);
        snprintf(cpp_main, 512, "src/%s.cpp", name);
        printf(
            ENTRY_CREATE,
            cwd,
            cpp_main);
        FILE* cpp = fopen(cpp_main, "w");
        if (!cpp) {
            printf(
                FILE_CREATE_FAILURE,
                cpp_main);
            free(cpp_main);
            free(cwd);
            return 1;
        }
        free(cpp_main);
        fprintf(cpp, CPP_MAIN);
        fclose(cpp);

        printf(
            FILE_CREATE,
            cwd,
            "src/test.cpp");
        FILE* test = fopen("src/test.cpp", "w");
        if (!test) {
            printf(FILE_CREATE_FAILURE, "src/test.cpp");
            free(cwd);
            return 1;
        }
        fprintf(test, CPP_TEST, name, name);
        fclose(test);
    } else {
        /* Create the CMakeLists */
        printf(
            FILE_CREATE,
            cwd,
            "CMakeLists.txt");
        FILE* makelists = fopen("CMakeLists.txt", "w");
        if (!makelists) {
            printf(FILE_CREATE_FAILURE, "CMakeLists.txt");
            fclose(buildsh);
            free(cwd);
            free(upper);
            return 1;
        }
        fprintf(makelists, CMAKELISTS, name, name, name, name);
        fclose(makelists);

        char* c_main = malloc(512);
        snprintf(c_main, 512, "src/%s.c", name);
        printf(
            ENTRY_CREATE,
            cwd,
            c_main);
        FILE* c = fopen(c_main, "w");
        if (!c) {
            printf(
                FILE_CREATE_FAILURE,
                c_main);
            free(c_main);
            free(cwd);
            return 1;
        }
        free(c_main);
        fprintf(c, C_MAIN);
        fclose(c);

        printf(
            FILE_CREATE,
            cwd,
            "src/test.c");
        FILE* test = fopen("src/test.c", "w");
        if (!test) {
            printf(FILE_CREATE_FAILURE, "src/test.c");
            free(cwd);
            return 1;
        }
        fprintf(test, C_TEST, name, name);
        fclose(test);
    }

    /* Create README.md file */
    create_readme(name, cwd);

    /* Create .gitignore file */
    printf(
        FILE_CREATE,
        cwd,
        ".gitignore");
    FILE* gitignore = fopen(".gitignore", "w");
    if (!gitignore) {
        printf(
            FILE_CREATE_FAILURE,
            ".gitignore");
        free(cwd);
        return 1;
    }
    fprintf(gitignore, C_GITIGNORE, name);
    fclose(gitignore);

    printf(
        SUCCESS,
        name);
    free(cwd);
    return 0;
}

int go_init(char *name, char* args) {
    char* cwd = create_dir(name);

    printf(
        PROJECT_INIT,
        "Go",
        name);
    char *str = malloc(512);
    if (args) {
        snprintf(str, 512, "go mod init %s %s", name, args);
    } else {
        snprintf(str, 512, "go mod init %s", name);
    }
    system(str);
    free(str);

    /* Create README.md file */
    create_readme(name, cwd);

    /* Create the entry point file */
    char* go_main = malloc(512);
    snprintf(go_main, 512, "%s.go", name);
    printf(
        ENTRY_CREATE,
        cwd,
        go_main);
    FILE* go = fopen(go_main, "w");
    free(go_main);
    if (!go) {
        printf(
            FILE_CREATE_FAILURE,
            go_main);
        free(cwd);
        return 1;
    }
    fprintf(go, GO_MAIN);
    fclose(go);
    free(cwd);
    return 0;
}

int haskell_init(char *name, char* args) {
    printf(
        PROJECT_INIT,
        "Haskell",
        name);

    char* cmd = malloc(512);
    char* cwd = create_dir(name);
    if (args) {
        snprintf(cmd, 512, "cabal init --main-is=%s.hs %s", name, args);
    } else {
        snprintf(cmd, 512, "cabal init --main-is=%s.hs", name);
    }
    int res = simple_init(
        name,
        cmd,
        cwd);
    free(cmd);
    free(cwd);
    return res;
}

int lua_init(char *name, char* args) {
    /* Create the directories */
    char* cwd = create_dir(name);

    /* Create the README.md file */
    create_readme(name, cwd);

    /* Create the entry point file */
    free(cwd);
    cwd = create_dir("src");
    char* lua_ptr = malloc(512);
    snprintf(lua_ptr, 512, "%s.lua", name);
    printf(
        ENTRY_CREATE,
        cwd,
        lua_ptr);
    free(cwd);
    FILE* lua = fopen(lua_ptr, "w");
    free(lua_ptr);
    fprintf(lua, LUA_MAIN, name);
    fclose(lua);

    printf(
        SUCCESS,
        name);
    return 0;
}

int node_init(char *name, char* args) {
    /* Create base directory */
    char* cwd = create_dir(name);

    /* Initialize the node project, using npm create if args exist */
    if (args) {
        char* str = malloc(512);
        snprintf(str, 512, "npm create %s", args);
        system(str);
        free(str);
    } else {
        system("npm init -y");
    }

    /* Create README.md file */
    create_readme(name, cwd);
    free(cwd);

    printf(
        SUCCESS,
        name);
    return 0;
}

int ocaml_init(char *name, char* args) {
    printf(
        PROJECT_INIT,
        "Ocaml",
        name);

    char* cmd = malloc(512);
    char* cwd = malloc(512);
    snprintf(cwd, 512, "./%s/", name);
    if (args) {
        snprintf(cmd, 512, "dune init project %s %s", name, args);
    } else {
        snprintf(cmd, 512, "dune init project %s", name);
    }
    int res = simple_init(
        name,
        cmd,
        cwd);
    free(cmd);
    free(cwd);
    return res;
}

int ruby_init(char *name, char* args) {
    printf(
        PROJECT_INIT,
        "Ruby",
        name);
    char* cmd = malloc(512);
    char* cwd = malloc(512);
    snprintf(cwd, 512, "./%s/", name);
    if (args) {
        snprintf(cmd, 512, "bundle gem %s %s", name, args);
    } else {
        snprintf(cmd, 512, "bundle gem %s", name);
    }
    int res = simple_init(
        name,
        cmd,
        cwd);
    free(cmd);
    free(cwd);
    return res;
}

int rust_init(char *name, char* args) {
    printf(
        PROJECT_INIT,
        "Rust",
        name);
    char* cmd = malloc(512);
    char* cwd = malloc(512);
    snprintf(cwd, 512, "./%s/", name);
    if (args) {
        snprintf(cmd, 512, "cargo init %s %s", name, args);
    } else {
        snprintf(cmd, 512, "cargo init %s", name);
    }
    int res = simple_init(
        name,
        cmd,
        cwd);
    free(cmd);
    free(cwd);
    return res;
}

int v_init(char *name, char* args) {
    printf(
        PROJECT_INIT,
        "V",
        name);
    char* cmd = malloc(512);
    char* cwd = create_dir(name);
    if (args) {
        snprintf(cmd, 512, "v init %s %s", name, args);
    } else {
        snprintf(cmd, 512, "v init %s", name);
    }
    int res = simple_init(
        name,
        cmd,
        cwd);
    free(cmd);
    free(cwd);
    return res;
}

int zig_init(char *name, char* args) {
    printf(
        PROJECT_INIT,
        "Zig",
        name);
    char* cmd = malloc(512);
    char* cwd = create_dir(name);
    if (args) {
        snprintf(cmd, 512, "zig init %s", args);
    } else {
        snprintf(cmd, 512, "zig init");
    }
    int res = simple_init(
        name,
        cmd,
        cwd);
    free(cmd);
    free(cwd);
    return res;
}

/* Main Routing Function */

int route(char *name, char *lang, char* args) {
    if (!lang) {
        puts(LIST_LANGS);
        return 2;
    }
    struct stat st = {0};

    if (stat(name, &st) != -1) {
        printf(DIR_EXISTS, name);
        return 1;
    }

    lower(lang);
    if (strcmp(lang, "ls") == 0) {
        puts(LIST_LANGS);
        return 1;
    } else if (strcmp(lang, "bun") == 0) {
        return bun_init(name, args);
    } else if (strcmp(lang, "c") == 0) {
        return c_init(name, args, 0);
    } else if (
        strcmp(lang, "cpp") == 0 
        || strcmp(lang, "c++") == 0
    ) {
        return c_init(name, args, 1);
    } else if (strcmp(lang, "go") == 0) {
        return go_init(name, args);
    } else if (strcmp(lang, "haskell") == 0) {
        return haskell_init(name, args);
    } else if (strcmp(lang, "js") == 0
        || strcmp(lang, "javascript") == 0
        || strcmp(lang, "ts") == 0
        || strcmp(lang, "typescript") == 0) {
        loop: {
            char* str = query(
                "\x1b[0;1mWould you like to use Bun.sh or Node.js\x1b[0m? ");
            lower(str);
            if (strcmp(str, "bun") == 0) {
                free(str);
                return bun_init(name, args);
            } else if (strcmp(str, "node") == 0) {
                free(str);
                return node_init(name, args);
            } else {
                free(str);
                puts(BAD_Q_INPUT);
                goto loop;
            }
        }
    } else if (strcmp(lang, "lua") == 0) {
        return lua_init(name, args);
    } else if (strcmp(lang, "node") == 0
        || strcmp(lang, "nodejs") == 0) {
        return node_init(name, args);
    } else if (strcmp(lang, "ocaml") == 0) {
        return ocaml_init(name, args);
    } else if (strcmp(lang, "rust") == 0) {
        return rust_init(name, args);
    } else if (strcmp(lang, "ruby") == 0) {
        return ruby_init(name, args);
    } else if (strcmp(lang, "v") == 0) {
        return v_init(name, args);
    } else if (strcmp(lang, "zig") == 0) {
        return zig_init(name, args);
    } else {
        puts(LIST_LANGS);
        return 2;
    }
}
