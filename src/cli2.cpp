#include "cli2.hpp"

int ii;

const char* prompt = "user@k64f >> ";

char cli_buff[128];

__command cmd_enum, command;

void cli2(Serial *serial)
{
    serial->getc();
    printf("\033[2J\033[1;1H");
    printf(GREEN_B("New Terminal\n"));
    printf("%s",prompt);

    while (1)
    {
        command = handleInput(serial);

        switch (command)
        {
        case cmd_top:
            printf("\033[8m"); // Blink off
            top(serial);
            printf("\033[28m"); // Blink on
            printf("\n%s",prompt);
            break;
            
        case cmd_sys_info:
            sysinfo();
            printf("\n%s",prompt);
            break;

        case cmd_thread_info:
            threadinfo();
            printf("\n%s",prompt);
            break;

        case cmd_return:
            printf("\n%s",prompt);
            break;

        case cmd_clear:
            printf("\033[2J\033[1;1H");
            printf("%s",prompt);
            break;

        case cmd_help:
            help();
            printf("\n%s",prompt);
            break;

        case cmd_invalid:
            printf(RED("\nType a valid command\n"));
            printf("%s",prompt);
            break;
        }
    }
    

}

// TODO: add cases for soft reboot (NVIC_SystemReset()), for help listing available commands and for displaying values from sensors!
// define a function in the sensor values struct that prints its fields
__command handleInput(Serial *serial)
{
    memset(cli_buff,'\0', sizeof(cli_buff));
    cmd_enum = cmd_return; // By default, the enter command is set.
    ii = 0;
        while (ii < 127)
        {
            char byte = serial->getc();
            serial->putc(byte);
            
            if (byte == '\r') // if pressed enter do:
            {
                ii = 0;
                break;
            }
            cli_buff[ii] = (char)byte;
            ii++;
        }
        if(!strcmp(cli_buff,"top"))                     cmd_enum = cmd_top;
        else if(!strcmp(cli_buff,"info"))               cmd_enum = cmd_sys_info;
        else if(!strcmp(cli_buff,"thread"))             cmd_enum = cmd_thread_info;
        else if(!strcmp(cli_buff,(const char*)'\0'))    cmd_enum = cmd_return;
        else if(!strcmp(cli_buff,"clear"))              cmd_enum = cmd_clear;
        else if(!strcmp(cli_buff,"help"))               cmd_enum = cmd_help;
        else                                            cmd_enum = cmd_invalid;
    
        memset(cli_buff,'\0', sizeof(cli_buff)); // emptying the buffer

        return cmd_enum;
}

void help(void)
{
    printf(GREEN("                                                     _____________\n"));
    printf(GREEN("____________________________________________________/             \\____________________________________________________\n"));
    printf(GREEN("##================================================== COMMAND  LIST ==================================================##\n"));
    printf(GREEN("##==================================================\\_____________/==================================================##\n"));

    printf(GREEN("|| "));
    printf("Available commands:");
    printf("\033[118G");
    printf(GREEN("||\n"));

    printf(GREEN("|| "));
    printf("\033[7m");
    printf("top");
    printf("\033[0m\033[15G");
    printf("Show CPU usage");
    printf("\033[118G");
    printf(GREEN("||\n"));

    printf(GREEN("|| "));
    printf("\033[7m");
    printf("info");
    printf("\033[0m\033[15G");
    printf("Show HW information");
    printf("\033[118G");
    printf(GREEN("||\n"));

    printf(GREEN("|| "));
    printf("\033[7m");
    printf("thread");
    printf("\033[0m\033[15G");
    printf("Show active threads");
    printf("\033[118G");
    printf(GREEN("||\n"));

    printf(GREEN("|| "));
    printf("\033[7m");
    printf("clear");
    printf("\033[0m\033[15G");
    printf("Clear the screen");
    printf("\033[118G");
    printf(GREEN("||\n"));

    printf(GREEN("|| "));
    printf("\033[7m");
    printf("help");
    printf("\033[0m\033[15G");
    printf("Show this help");
    printf("\033[118G");
    printf(GREEN("||\n"));

    printf(GREEN("##=================================================== ~~~~~~~~~~~ ===================================================##\n"));
}