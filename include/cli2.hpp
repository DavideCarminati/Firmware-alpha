#include <mbed.h>

#include "sysinfo.hpp"
#include "top.hpp"
#include "threadinfo.hpp"

#include "cli_appereance.hpp"

// #include <string.h>
// #include <stdio.h>

// #ifndef COMMAND_LINE_INTERFACE
// #define COMMAND_LINE_INTERFACE

// #define INFO_TRACE(_class, _string, ...)    diag_printf( "%15s : " _string, _class, ##__VA_ARGS__)
// #define DEBUG_TRACE(_lvl, _class, _string, ...)    dbg_printf(_lvl, "%15s : " _string, _class, ##__VA_ARGS__)
// #define PRINT_REG(_base, _x)    diag_printf(#_x": 0x%08X\n", *((volatile CYG_WORD32 *)(_base + _x)));

// #ifndef VT100_OFF
// #define COLOR(__c,__x)    "\x1b[3" #__c "m" __x "\x1b[0m"
// #define COLOR_BOLD(__c,__x)    "\x1b[3" #__c ";1m" __x "\x1b[0m"
// #define UNDERLINE(__x) "\x1b[4m" __x "\x1b[0m"
// #define CLEAR_SCREEN    "\x1b[2J\x1b[H"
// #else
// #define COLOR(__c,__x)    __x
// #define COLOR_BOLD(__c,__x) __x
// #define UNDERLINE(__x) __x
// #define CLEAR_SCREEN
// #endif
// #define RED(__x)        COLOR(1, __x )
// #define GREEN(__x)        COLOR(2, __x )
// #define YELLOW(__x)        COLOR(3, __x )
// #define BLUE(__x)        COLOR(4, __x )
// #define MAGENTA(__x)    COLOR(5, __x )
// #define CYAN(__x)        COLOR(6, __x )
// #define RED_B(__x)        COLOR_BOLD(1, __x )
// #define GREEN_B(__x)        COLOR_BOLD(2, __x )
// #define YELLOW_B(__x)        COLOR_BOLD(3, __x )
// #define BLUE_B(__x)        COLOR_BOLD(4, __x )
// #define MAGENTA_B(__x)    COLOR_BOLD(5, __x )
// #define CYAN_B(__x)        COLOR_BOLD(6, __x )
// #endif

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
// __command resolveCmd(std::string *inString, Serial *serial);





#endif