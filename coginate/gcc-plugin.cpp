#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "gcc-plugin.h"
#include "print-tree.h"
#include "plugin-version.h"
#include "tree.h"

#ifdef _WIN32
__declspec(dllexport)
#endif
int plugin_is_GPL_compatible;

#ifdef _WIN32
__declspec(dllexport)
#endif
void finish_type(void* event_data, void* user_data)
{
    printf("a declaration finished\n");
}

#ifdef _WIN32
__declspec(dllexport)
#endif
int plugin_init(struct plugin_name_args* plugin_info,
                struct plugin_gcc_version* version)
{
    register_callback("example", PLUGIN_FINISH_DECL, finish_type, NULL);

    printf("%d\n", version->datestamp);

    printf("hello\n");

    return 0;
}
