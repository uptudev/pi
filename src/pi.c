/*  
 *  Author: uptu <uptu@uptu.dev>
 *
 *  This file is part of the `pi` project.
 *  `pi` is licensed under the MIT license.
 *  Please see the LICENSE file for more information.
 *  Copyright (c) 2024 uptu
 */

#include "./input_handler.h"
#include "./lang_scripts.h"

void free_project(struct Project* project) {
    if (!(project->stack_arg_flags & 1)) {
        free(project->name);
    }

    if (!(project->stack_arg_flags & 2)) {
        free(project->lang);
    }

    if (!(project->stack_arg_flags & 4)) {
        free(project->init_args);
    }
}

int main(int argc, char** argv) {
    /*
     *  Takes the input args and returns them as a Project struct, 
     *  getting values not already provided by the user in the process. 
     *  If the input is invalid, exit with result `1` during parsing.
     *  If the input is valid, return the parsed arguments as a Project struct
     */
    struct Project parsed = handle(argc, argv);

    /*
     *  Route the response based off of the string in `parsed.lang`.
     *  If the language is not supported, exit with result `2`.
     *  If the language is supported, run the appropriate initialization function.
     */
    int res = route(parsed.name, parsed.lang, parsed.init_args);
    char* name = parsed.name ?
        strcpy(malloc(length(parsed.name) + 1), parsed.name)
        : NULL;

    // If the initialization function returns `1`,
    // the router has to re-route a new response
    while (res == 1) {
        free_project(&parsed);
        parsed = handle(0, &name);
        res = route(parsed.name, parsed.lang, parsed.init_args);
    }

    /*
     *  All parsed arguments are pointers that must be freed after use.
     *  `name` and `lang` may be stack-allocated if given as CLI args,
     *  so this may do nothing in those cases, but prevents memory leaks
     *  when they are heap-allocated/queried.
     *
     *  `init_args` is always heap-allocated, so it must be freed every time.
     */
    free_project(&parsed);
    free(name);

    return res;
}
