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
#include "sysinfo.hpp"

#if !defined(MBED_SYS_STATS_ENABLED)
#error [NOT_SUPPORTED] test not supported
#endif

int sysinfo()
{
    mbed_stats_sys_t stats;
    mbed_stats_sys_get(&stats);

    printf(GREEN("                                                      ___________\n"));
    printf(GREEN("_____________________________________________________/           \\_____________________________________________________\n"));
    printf(GREEN("##=================================================== SYSTEM INFO ===================================================##\n"));
    printf(GREEN("##===================================================\\___________/===================================================##\n"));
    printf(GREEN("||"));
    printf(" Mbed OS Version: %ld ", stats.os_version);
    printf("\033[118G");
    printf(GREEN("||\n"));

    /* CPUID Register information
    [31:24]Implementer      0x41 = ARM
    [23:20]Variant          Major revision 0x0  =  Revision 0
    [19:16]Architecture     0xC  = Baseline Architecture
                            0xF  = Constant (Mainline Architecture)
    [15:4]PartNO            0xC20 =  Cortex-M0
                            0xC60 = Cortex-M0+
                            0xC23 = Cortex-M3
                            0xC24 = Cortex-M4
                            0xC27 = Cortex-M7
                            0xD20 = Cortex-M23
                            0xD21 = Cortex-M33
    [3:0]Revision           Minor revision: 0x1 = Patch 1
    */
    printf(GREEN("||"));
    printf(" CPU ID: 0x%x", stats.cpu_id);
    printf("\033[118G");
    printf(GREEN("||\n"));

    /* Compiler IDs
        ARM     = 1
        GCC_ARM = 2
        IAR     = 3
    */
    printf(GREEN("||"));
    printf(" Compiler ID: %d", stats.compiler_id);
    printf("\033[118G");
    printf(GREEN("||\n"));

    /* Compiler versions:
       ARM: PVVbbbb (P = Major; VV = Minor; bbbb = build number)
       GCC: VVRRPP  (VV = Version; RR = Revision; PP = Patch)
       IAR: VRRRPPP (V = Version; RRR = Revision; PPP = Patch)
    */
    printf(GREEN("||"));
    printf(" Compiler Version: %d", stats.compiler_version);
    printf("\033[118G");
    printf(GREEN("||\n"));

    /* RAM / ROM memory start and size information */
    for (int i = 0; i < MBED_MAX_MEM_REGIONS; i++) {
        
        if (stats.ram_size[i] != 0) {
            printf(GREEN("||"));
            printf(" RAM%d: Start 0x%lx Size: %ld bytes", i, stats.ram_start[i], stats.ram_size[i]);
            printf("\033[118G");
            printf(GREEN("||\n"));
        }
        
    }
    for (int i = 0; i < MBED_MAX_MEM_REGIONS; i++) {
        
        if (stats.rom_size[i] != 0) {
            printf(GREEN("||"));
            printf(" ROM%d: Start 0x%lx Size: %ld bytes", i, stats.rom_start[i], stats.rom_size[i]);
            printf("\033[118G");
            printf(GREEN("||\n"));
        }
        
    }

    printf(GREEN("||"));
    printf(RED_B(" Firmware Version: (alpha)"));
    printf("\033[118G");
    printf(GREEN("||\n"));
//     printf("                                                  ,o88888\n"
// "                                               ,o8888888'\n"
// "                         ,:o:o:oooo.        ,8O88Pd8888\n"
// "                     ,.::.::o:ooooOoOoO. ,oO8O8Pd888'\n"
// "                   ,.:.::o:ooOoOoOO8O8OOo.8OOPd8O8O\n"
// "                  , ..:.::o:ooOoOOOO8OOOOo.FdO8O8'\n"
// "                 , ..:.::o:ooOoOO8O888O8O,COCOO'\n"
// "                , . ..:.::o:ooOoOOOO8OOOOCOCO'\n"
// "                 . ..:.::o:ooOoOoOO8O8OCCCC'o\n"
// "                    . ..:.::o:ooooOoCoCCC'o:o\n"
// "                    . ..:.::o:o:,cooooCo'oo:o:\n"
// "                 `   . . ..:.:cocoooo''o:o:::'\n"
// "                 .`   . ..::ccccoc''o:o:o:::'\n"
// "                :.:.    ,c:cccc'':.:.:.:.:.'\n"
// "              ..:.:''`::::c:''..:.:.:.:.:.'\n"
// "           ...:.'.:.::::''    . . . . .'\n"
// "           .. . ....:.''' `   .  . . ''\n"
// "         . . . ....''\n"
// "         .. . .''\n"
// "        .\n");
    printf(GREEN("||"));
    printf(" ____  _                            ");
    printf("\033[118G");
    printf(GREEN("||\n"));

    printf(GREEN("||"));
    printf("/ ___|| |_ _ __ ___  __ _ _ __ ___ ");
    printf("\033[118G");
    printf(GREEN("||\n"));

    printf(GREEN("||"));
    printf("\\___ \\| __| '__/ _ \\/ _` | '_ ` _ \\ ");
    printf("\033[118G");
    printf(GREEN("||\n"));

    printf(GREEN("||"));
    printf(" ___) | |_| | |  __/ (_| | | | | | |");
    printf("\033[118G");
    printf(GREEN("||\n"));

    printf(GREEN("||"));
    printf("|____/ \\__|_|  \\___|\\__,_|_| |_| |_|");
    printf("\033[118G");
    printf(GREEN("||\n"));
                                     
    printf(GREEN("##=================================================== ~~~~~~~~~~~ ===================================================##\n"));
    return 0;
}


  
 