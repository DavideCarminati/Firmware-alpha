/* Copyright (c) 2018 Arm Limited
*
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/
#include "top.hpp"

#if !defined(MBED_CPU_STATS_ENABLED) || !defined(DEVICE_LPTICKER) || !defined(DEVICE_SLEEP)
#error [NOT_SUPPORTED] test not supported
#endif

#define MAX_THREAD_STACK 384
#define SAMPLE_TIME_MS   1000
#define LOOP_TIME_MS     3000

uint64_t prev_idle_time = 0;
int32_t wait_time_ms = 5000;

Timer tim;
bool exit_flag;

void print_cpu_stats()
{
    mbed_stats_cpu_t stats;
    mbed_stats_cpu_get(&stats);

    // Calculate the percentage of CPU usage
    uint64_t diff_usec = (stats.idle_time - prev_idle_time);
    uint8_t idle = (diff_usec * 100) / (SAMPLE_TIME_MS*1000);
    uint8_t usage = 100 - ((diff_usec * 100) / (SAMPLE_TIME_MS*1000));
    prev_idle_time = stats.idle_time;

    printf("\033[5;1H\033[5K"); // Set cursor to row 2 column 1 and clear that line
    printf(GREEN("||"));
    printf(" Time(us): Up: %lld", stats.uptime);
    printf("   Idle: %lld", stats.idle_time);
    printf("   Sleep: %lld", stats.sleep_time);
    printf("   DeepSleep: %lld", stats.deep_sleep_time);
    printf("\033[5;118H");
    printf(GREEN("||\n"));
    printf(GREEN("||===================================================================================================================||\n"));
    printf(GREEN("|| "));
    printf("\033[0K"); //7k
    printf(RED("Idle: %d%% Usage: %d%%"), idle, usage);
    uint8_t usage_bar = usage/10 + 1;
    printf(" %d \033[50G", usage);
    
    for(uint8_t cnt = 1; cnt <= usage_bar; cnt++)
    {
        if(cnt >= 6 && cnt < 8)
        {
            printf("\033[93m##");
            // printf("\033[%dC", 1);
        }
        else if(cnt >= 8)
        {
            printf("\033[31m##");
            // printf("\033[%dC", 1);
        }
        else if(cnt < 6)
        {
            printf("\033[38;5;34m##");
            // printf("\033[%dC", 1);
        }
        // if(cnt > 10) break;
    }
    
    
    printf("\033[118G");
    printf(GREEN("||\n"));
}

int top(Serial *serial)
{
    exit_flag = 0;
    tim.reset();
    printf("\033[2J\033[1;1H"); // Clear terminal (2J) and set cursor to 1,1 (1;1H) --> CSI codes wikipedia!!!
    printf(GREEN("                                                          ___\n"));
    printf(GREEN("_________________________________________________________/   \\_________________________________________________________\n"));
    printf(GREEN("##======================================================= TOP =======================================================##\n"));
    printf(GREEN("##=======================================================\\___/=======================================================##\n"));
    printf("\033[8;1H"); // Set cursor to 5,1
    printf(GREEN("##======================================================= ~~~ =======================================================##\n"));
                

    // Request the shared queue
    EventQueue *stats_queue = mbed_event_queue();
    int id;

    id = stats_queue->call_every(SAMPLE_TIME_MS, print_cpu_stats);

    while(1)
    {
        if (serial->readable())
            {
                char k = serial->getc();
                exit_flag = 1;
                break;
            }
        ThisThread::sleep_for(11);
    }
    stats_queue->cancel(id);
    // thread->terminate();
    return 0;
}