#include <mbed.h>

// #include "sysinfo.hpp"
// #include "top.hpp"
// #include "threadinfo.hpp"

// #include "cli_appereance.hpp"

#ifndef COMMAND_LINE
#define COMMAND_LINE

void cli2(Serial *serial);

enum __command 
        {
            cmd_return,
            cmd_top,
            cmd_sys_info,
            cmd_thread_info,
            cmd_clear,
            cmd_help,
            cmd_invalid,
        };

__command handleInput(Serial *serial);
void help(void);





#endif