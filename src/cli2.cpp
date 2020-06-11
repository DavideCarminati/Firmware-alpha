#include "cli2.hpp"
// #include <iostream>

// std::string cli_buff;
// std::string *ptr = &cli_buff;
int ii;

// Timer tim;
// bool exit_flag;

const char* prompt = "user@k64f >> ";

char cli_buff[128];

// std::string top_str = "top", info_str = "info", thread_str = "thread";

__command cmd_enum, command;

void cli2(Serial *serial)
{
    // tim.reset();
    
    serial->getc();
    printf("\033[2J\033[1;1H");
    printf(GREEN_B("New Terminal\n"));
    // printf("Write a command (info,top,thread)\n");
    printf("%s",prompt);

    while (1)
    {
        // printf("awaiting command...");
        command = handleInput(serial);

        switch (command)
        {
        case cmd_top:
            // exit_flag = 0;
            // printf("\033[2J\033[1;1H"); // Clear terminal (2J) and set cursor to 1,1 (1;1H) --> CSI codes wikipedia!!!
            // printf(GREEN("|||||||||||||||||||||||||||||||||||||||||||||||||||| CPU  MONITOR |||||||||||||||||||||||||||||||||||||||||||||||||||||\n"));
            // printf(GREEN("||"));
            // printf("\033[5;1H"); // Set cursor to 5,1
            // printf(GREEN("|||||||||||||||||||||||||||||||||||||||||||||||||||| ~~~~~~~~~~~~ |||||||||||||||||||||||||||||||||||||||||||||||||||||\n"));
            // while(!exit_flag)
            // {
                
                // printf("\033[2;1H\033[2K"); // Set cursor to row 2 column 1 and clear that line
                printf("\033[8m"); // Blink off
                top(serial);
                
                // tim.start();
                // while (tim.read() < 0.5 && !exit_flag)
                // {
                //     if (serial->readable())
                //     {
                //         char k = serial->getc();
                //         exit_flag = 1;
                //         printf("\n%s",prompt);
                //         break;
                //     }
                //     ThisThread::sleep_for(10);
                // }
                // tim.reset();
            // }
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
    
    // scanf("%s", &cli_buff);
    memset(cli_buff,'\0', sizeof(cli_buff));
    cmd_enum = cmd_return; // By default, the enter command is set.
    ii = 0;
        while (ii < 127 /*cli_buff[ii] != '\n' || cli_buff[ii] != ' '*/)
        {
            char byte = serial->getc();
            serial->putc(byte);
            
            
            if (byte == '\r') // if pressed enter do:
            {
                // if (!strcmp(cli_buff,"\0") ) // given an empty enter now it works!
                // {
                //     printf("riprova\n");
                //     break;
                // }

                ii = 0;
                break;
            }
            cli_buff[ii] = (char)byte;//serial->getc();
            ii++;
        }
        // printf("cazzo2");

        // if (cli_buff[ii-1] == ' ') // handling arguments of commands
        // {
        //     ThisThread::sleep_for(10); /* parse command arguments */
        // };

        // cmd_enum = resolveCmd(ptr, serial);
        // cmd_enum = cmd_sys_info;

        // cout << cli_buff << endl;

        // printf("%d\n", strcmp(cli_buff,"top"));
        // printf("%d\n", cli_buff.compare(top_str));
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

// __command resolveCmd(std::string *inString, Serial *serial)
// {
//     printf("instring:\n");
//     if(!(inString->compare("info")))      return cmd_sys_info;
//     if(!inString->compare("top"))       return cmd_top;
//     if(!inString->compare("thread"))    return cmd_thread_info;
//     if(!inString->compare("\n"))        return cmd_return;
//     // fh->write((const void*)&inString, sizeof(inString));
//     std::string cazzo = *inString;
//     int len = sizeof(cazzo);
//     while (len--)
//                 {
//                     serial->putc(cazzo[len]);
//                 }
//     // printf("%s", inString);
//     printf("\nfine instring\n");
//     // write("%s",&cli_buff);
// }