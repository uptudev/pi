/*  
 *  Author: uptu <uptu@uptu.dev>
 *
 *  This file is part of the `pi` project.
 *  `pi` is licensed under the MIT license.
 *  Please see the LICENSE file for more information.
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

/* Includes */
#include "lang_scripts.h"
#include "uptu_libs.h"

/* String Constants */
#define README "# %s\n\
\n\
**[Short, memorable description of your project]**\n\
\n\
## Table of Contents\n\
\n\
* [Installation](#installation)\n\
* [Usage](#usage)\n\
* [Contributing](#contributing)\n\
* [License](#license)\n\
* [Additional Information](#additional-information)\n\
\n\
## Installation\n\
\n\
**Clearly describe how to install your project.** This may involve specifying dependencies, prerequisites, and build instructions. Use code blocks, links, and step-by-step guides for clarity.\n\
\n\
## Usage\n\
\n\
**Provide clear and concise instructions on how to use your project.** Explain its functionalities, features, and common use cases. Include examples, screenshots, or GIFs if helpful.\n\
\n\
**Tips:**\n\
\n\
* Break down instructions into logical steps.\n\
* Use bullet points for succinct explanations.\n\
* Consider creating a separate \"Getting Started\" guide for beginners.\n\
\n\
## Contributing\n\
\n\
**Outline your contribution guidelines.** Explain how users can contribute to your project, whether through code, bug reports, or documentation improvements. Specify preferred code style, pull request format, and testing procedures.\n\
\n\
## License\n\
\n\
**Specify the license under which your project is distributed.** Use clear and concise language, and link to the full license text in the `LICENSE` file.\n\
\n\
## Additional Information\n\
\n\
**Include any other relevant information you want to share.** This could be links to related projects, documentation, support channels, or your contact information.\n\
\n\
**Remember:**\n\
\n\
* Keep your README.md file concise and focused.\n\
* Use clear headings, formatting, and visuals for readability.\n\
* Update your README.md file regularly to reflect changes in your project.\n"
#define LIST_LANGS "\
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
#define CPP_MAIN "#include <iostream>\n\nint main() {\n\tstd::cout << \"Hello, World!\\n\";\n\treturn 0;\n}\n"
#define C_CONFIGURE_DEFAULT "\
#!/bin/bash\n\
\n\
# Checks for Zig, Clang, GCC, then CC in that order.\n\
# To override, set OVERRIDE to either 1, 2, 3, or 4.\n\
\n\
export OVERRIDE=0\n\
\n\
case \"$OVERRIDE\" in\n\
    1)\n\
        CC=\"zig cc\"\n\
        ;;\n\
    2)\n\
        CC=\"clang\"\n\
        ;;\n\
    3)\n\
        CC=\"gcc\"\n\
        ;;\n\
    4)\n\
        CC=\"cc\"\n\
        ;;\n\
    *)\n\
        if command -v zig &> /dev/null; then\n\
            CC=\"zig cc\"\n\
        elif command -v clang &> /dev/null; then\n\
            CC=\"clang\"\n\
        elif command -v gcc &> /dev/null; then\n\
            CC=\"gcc\"\n\
        else\n\
            echo \"No compiler found\"\n\
            echo \"Either install Zig, Clang, or GCC, or pester me to add your compiler.\"\n\
            exit 1\n\
        fi\n\
        ;;\n\
esac\n\
\n\
echo \"Using $CC as the compiler\"\n\
echo -e \"INSTALL_DIR:=/usr/local/bin\\n\\n%s:\\n\\t$CC -I include src/**/*.c src/%s.c -o %s\\n\\n.PHONY: install\\ninstall: %s\\n\\tinstall -m 755 %s \\${INSTALL_DIR}\" > Makefile\n"
#define CPP_CONFIGURE_DEFAULT "\
#!/bin/bash\n\
\n\
# Checks for Zig, Clang, then GCC in that order.\n\
# To override, set OVERRIDE to either 1, 2, or 3.\n\
\n\
export OVERRIDE=0\n\
\n\
case \"$OVERRIDE\" in\n\
    1)\n\
        CC=\"zig ++\"\n\
        ;;\n\
    2)\n\
        CC=\"clang\"\n\
        ;;\n\
    3)\n\
        CC=\"g++\"\n\
        ;;\n\
    *)\n\
        if command -v zig &> /dev/null; then\n\
            CC=\"zig ++\"\n\
        elif command -v clang &> /dev/null; then\n\
            CC=\"clang\"\n\
        elif command -v g++ &> /dev/null; then\n\
            CC=\"g++\"\n\
        else\n\
            echo \"No compiler found\"\n\
            echo \"Either install Zig, Clang, or GCC, or pester me to add your compiler.\"\n\
            exit 1\n\
        fi\n\
        ;;\n\
esac\n\
\n\
echo \"Using $CC as the compiler\"\n\
echo -e \"INSTALL_DIR:=/usr/local/bin\n\n%s:\n\t$CC -I include src/**/*.cpp src/%s.cpp -o %s\n\n.PHONY: install\ninstall: %s\n\tinstall -m 755 %s ${INSTALL_DIR}\" > Makefile\n"
#define C_GITIGNORE "\
# executable shouldn't be in the repo\n\
%s\n\
\n\
# no coredumps \n\
CORE-*\n\
\n\
# Makefile should be configured to use the correct compiler\n\
Makefile\n"

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
    printf("\x1b[0;90mCreating directory \x1b[0;1;33m%s\x1b[0;90m...\x1b[0m\n", cwd);
    make_dir(name);
    chdir(cwd);

    return cwd;
}

int create_readme(char *name, char* cwd) {
    /* Create the default README.md file */
    printf("\x1b[0;90mCreating \x1b[0;1;33m%sREADME.md\x1b[0;90m...\x1b[0m\n", cwd);
    FILE* readme = fopen("README.md", "w");
    if (!readme) {
        printf("\x1b[0;1;31mFailed to create file\x1b[0m \x1b[0;1;37;41mREADME.md\x1b[0m. \n");
        free(cwd);
        exit(1);
    }
    fprintf(readme, README, name);
    fclose(readme);
    return 0;
}

/* Language Initialization Functions */

// If a build tool can create a project in place with a single command, use this function
int simple_init(char *name, char* args, char* cmd, char* langstr) {
    char* cwd = create_dir(name);

    /* Initialize the project */
    printf("\x1b[0;90mInitializing %s project \x1b[0;1;33m%s\x1b[0;90m...\x1b[0m\n", langstr, name);
    char* str = malloc(512);
    if (args) {
        strcat(cmd, " %s");
        snprintf(str, 512, cmd, name, args);
    } else {
        snprintf(str, 512, cmd, name);
    }
    system(str);
    free(str);

    /* Create README.md file */
    create_readme(name, cwd);
    free(cwd);
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
            char* str = query("\x1b[0;1mWould you like to use TypeScript\x1b[0m? (y/n) ");
            lower(str);
            if (strcmp(str, "y") == 0) {
                free(str);
                system("bun init -y");
            } else if (strcmp(str, "n") == 0) {
                free(str);
                FILE *f = fopen("index.js", "w");
                if (!f) {
                    printf("\x1b[0;1;31mFailed to create file\x1b[0m \x1b[0;1;37;41mindex.js\x1b[0m. \n");
                    free(cwd);
                    return 1;
                }
                fprintf(f, "console.log(\"Hello, World!\");\n");
                fclose(f);
                system("bun init -y");
            } else {
                free(str);
                printf("\x1b[0;1;31mInvalid input\x1b[0m. Please enter either \x1b[0;1;37;41my\x1b[0m or \x1b[0;1;37;41mn\x1b[0m. \n");
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

    /* Create the subdirectories */
    printf("\x1b[0;90mCreating \x1b[0;1;33m%ssrc/\x1b[0;90m and \x1b[0;1;33m%sinclude/\x1b[0;90m...\x1b[0m\n", cwd, cwd);
    make_dir("src");
    make_dir("include");

    if (is_cpp) {
        printf("\x1b[0;90mCreating entry point \x1b[0;1;33m%ssrc/%s.cpp\x1b[0;90m...\x1b[0m\n", cwd, name);
        char* cpp_main = malloc(512);
        snprintf(cpp_main, 512, "src/%s.cpp", name);
        FILE* cpp = fopen(cpp_main, "w");
        free(cpp_main);
        if (!cpp) {
            printf("\x1b[0;1;31mFailed to create file\x1b[0m \x1b[0;1;37;41msrc/%s.cpp\x1b[0m. \n", name);
            free(cwd);
            return 1;
        }
        fprintf(cpp, CPP_MAIN);
        fclose(cpp);

        /* Create the Makefile configure script */
        printf("\x1b[0;90mCreating \x1b[0;1;33m%sconfigure\x1b[0;90m...\x1b[0m\n", cwd);
        FILE* configure = fopen("configure", "w");
        if (!configure) {
            printf("\x1b[0;1;31mFailed to create file\x1b[0m \x1b[0;1;37;41mconfigure\x1b[0m. \n");
            free(cwd);
            return 1;
        }
        fprintf(configure, CPP_CONFIGURE_DEFAULT, name, name, name, name, name);
        fclose(configure);
    } else {
        printf("\x1b[0;90mCreating entry point \x1b[0;1;33m%ssrc/%s.c\x1b[0;90m...\x1b[0m\n", cwd, name);
        char* c_main = malloc(512);
        snprintf(c_main, 512, "src/%s.c", name);
        FILE* c = fopen(c_main, "w");
        free(c_main);
        if (!c) {
            printf("\x1b[0;1;31mFailed to create file\x1b[0m \x1b[0;1;37;41msrc/%s.c\x1b[0m. \n", name);
            free(cwd);
            return 1;
        }
        fprintf(c, C_MAIN);
        fclose(c);

        /* Create the Makefile configure script */
        printf("\x1b[0;90mCreating \x1b[0;1;33m%sconfigure\x1b[0;90m...\x1b[0m\n", cwd);
        FILE* configure = fopen("configure", "w");
        if (!configure) {
            printf("\x1b[0;1;31mFailed to create file\x1b[0m \x1b[0;1;37;41mconfigure\x1b[0m. \n");
            free(cwd);
            return 1;
        }
        fprintf(configure, C_CONFIGURE_DEFAULT, name, name, name, name, name);
        fclose(configure);
    }

    /* Create README.md file */
    create_readme(name, cwd);

    /* Create .gitignore file */
    printf("\x1b[0;90mCreating \x1b[0;1;33m%s.gitignore\x1b[0;90m...\x1b[0m\n", cwd);
    FILE* gitignore = fopen(".gitignore", "w");
    if (!gitignore) {
        printf("\x1b[0;1;31mFailed to create file\x1b[0m \x1b[0;1;37;41m.gitignore\x1b[0m. \n");
        free(cwd);
        return 1;
    }
    fprintf(gitignore, C_GITIGNORE, name);
    fclose(gitignore);

    printf("\x1b[0;32mProject \x1b[0;1;32m%s\x1b[0;32m initialized successfully\x1b[0m.\n", name);
    free(cwd);
    return 0;
}

int go_init(char *name, char* args) {
    char* cwd = create_dir(name);

    printf("\x1b[0;90mInitializing Go module \x1b[0;1;33m%s\x1b[0;90m...\x1b[0m\n", name);
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
    printf("\x1b[0;90mCreating entry point \x1b[0;1;33m%s%s.go\x1b[0;90m...\x1b[0m\n", cwd, name);
    char* go_main = malloc(512);
    snprintf(go_main, 512, "%s.go", name);
    FILE* go = fopen(go_main, "w");
    free(go_main);
    if (!go) {
        printf("\x1b[0;1;31mFailed to create file\x1b[0m \x1b[0;1;37;41m%s.go\x1b[0m. \n", name);
        free(cwd);
        return 1;
    }
    fprintf(go, "package main\n\nimport \"fmt\"\n\nfunc main() {\n\tfmt.Println(\"Hello, World!\")\n}\n");
    fclose(go);

    free(cwd);
    return 0;
}

int haskell_init(char *name, char* args) {
    return simple_init(
        name, 
        args, 
        "cabal init --main-is=%s.hs", 
        "Haskell"
    );
}

int lua_init(char *name, char* args) {
    /* Create the directories */
    char* cwd = create_dir(name);

    /* Create the README.md file */
    create_readme(name, cwd);

    /* Create the entry point file */
    free(cwd);
    cwd = create_dir("src");
    printf("\x1b[0;90mCreating entry point \x1b[0;1;33m%ssrc/%s.lua\x1b[0;90m...\x1b[0m\n", cwd, name);
    free(cwd);
    char* lua_ptr = malloc(512);
    snprintf(lua_ptr, 512, "%s.lua", name);
    FILE* lua = fopen(lua_ptr, "w");
    free(lua_ptr);
    fprintf(lua, "-- %s\n\nprint(\"Hello, World!\")\n", name);
    fclose(lua);
   
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
    return 0;
}

int ocaml_init(char *name, char* args) {
    return simple_init(
        name, 
        args, 
        "dune init %s", 
        "OCaml"
    );
}

int ruby_init(char *name, char* args) {
    return simple_init(
        name, 
        args, 
        "bundle gem %s", 
        "Ruby"
    );
}

int rust_init(char *name, char* args) {
    return simple_init(
        name, 
        args, 
        "cargo init", 
        "Rust"
    );
}

int v_init(char *name, char* args) {
    return simple_init(
        name, 
        args, 
        "v init %s", 
        "V"
    );
    return 0;
}

int zig_init(char *name, char* args) {
    return simple_init(
        name, 
        args, 
        "zig init", 
        "Zig"
    );
    return 0;
}

/* Main Routing Function */

int route(char *name, char *lang, char* args) {
    if (!lang) {
        puts(LIST_LANGS);
        return 1;
    }
    struct stat st = {0};

    if (stat(name, &st) != -1) {
        printf("\x1b[0;1;31mDirectory\x1b[0m \x1b[0;1;37;41m%s\x1b[0m \x1b[0;1;31malready exists\x1b[0m. \n", name);
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
        printf("\x1b[0;1;31mLanguage not supported\x1b[0m. \n%s\n", LIST_LANGS);
        return 2;
    }
}
