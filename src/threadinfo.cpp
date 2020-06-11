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
#include "threadinfo.hpp"
 
#if !defined(MBED_THREAD_STATS_ENABLED)
#error "Stats not enabled"
#endif
 
#define MAX_THREAD_STATS    0x8
 
int threadinfo()
{
    mbed_stats_thread_t *stats = new mbed_stats_thread_t[MAX_THREAD_STATS];
    int count = mbed_stats_thread_get_each(stats, MAX_THREAD_STATS);

    printf(GREEN("||||||||||||||||||||||||||||||||||||||||||||||||||||| THREAD INFO |||||||||||||||||||||||||||||||||||||||||||||||||||||\n"));
    printf(GREEN("||"));
    // printf("\033[44m");
    // printf("                                                      \033[0mTHREAD INFO\033[44m                                                      \n");
    // printf("                                                                                                                       \n");
    // printf("  ");
    // printf("\033[0m");
    printf(" ID          Name                           State       Priority    Stack size  Stack space      ");
    // printf("\033[44m");
    printf("\033[118G");
    printf(GREEN("||\n"));
    // printf("\033[0m");

    // for(int i = 0; i < count; i++) {
    //     printf(GREEN("||"));
    //     printf("0x%x        %s          %d          %d          %d          %d", stats[i].id, stats[i].name, stats[i].state, stats[i].priority, stats[i].stack_size, stats[i].stack_space);
    //     printf(GREEN("||"));
    //     printf("\n");
    // }
    // printf(GREEN("||||||||||||||||||||||||||||||||| ~~~~~~~~~~~ |||||||||||||||||||||||||||||||||"));
    
    for(int i = 0; i < count; i++) {
        printf(GREEN("||"));
        // printf("\033[44m  \033[0m");
        printf(" 0x%x", stats[i].id);
        printf("\033[16G");
        printf("%s", stats[i].name);
        printf("\033[47G");
        printf("%d", stats[i].state);
        printf("\033[59G");
        printf("%d", stats[i].priority);
        printf("\033[71G");
        printf("%d", stats[i].stack_size);
        printf("\033[83G");
        printf("%d", stats[i].stack_space);
        printf("\033[118G");
        printf(GREEN("||\n"));
        // printf("\033[44m  \033[0m\n");
    }
    printf(GREEN("||||||||||||||||||||||||||||||||||||||||||||||||||||| ~~~~~~~~~~~ |||||||||||||||||||||||||||||||||||||||||||||||||||||"));
    // printf("\033[44m");
    // printf("                                                      \033[0m~~~~~~~~~~~\033[44m                                                      \n");
    // printf("\033[0m");
    return 0;
}
// 26 thread name
// 10 thread ID