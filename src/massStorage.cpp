/* mbed Microcontroller Library
 * Copyright (c) 2006-2019 ARM Limited
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
#include "mbed.h"
#include <stdio.h>
#include <errno.h>
// #include <fstream>

#include "SDBlockDevice.h"

#include "massStorage.hpp"

// Maximum number of elements in buffer
#define BUFFER_MAX_LEN 10
#define FORCE_REFORMAT false
// This will take the system's default block device
SDBlockDevice sd(PTE3, PTE1, PTE2, PTE4);


// Instead of the default block device, you can define your own block device.
// For example: HeapBlockDevice with size of 2048 bytes, read size 1, write size 1 and erase size 512.
// #include "HeapBlockDevice.h"
// BlockDevice *bd = new HeapBlockDevice(2048, 1, 1, 512);


// This example uses LittleFileSystem as the default file system
// #include "LittleFileSystem.h"
// LittleFileSystem fs("fs");

// Uncomment the following two lines and comment the previous two to use FAT file system.
#include "FATFileSystem.h"
FATFileSystem fs("fs");

FILE *f_calib_read;

// ifstream calibration_file;

char f_read_buff[100], f_read_temp[100], values_str[100], data_out_str[100], temp_char_read;
char *values_str_buf;
int space_count = 0;


// Set up the button to trigger an erase
// InterruptIn irq(PTA4);
// void erase() {
//     printf("Initializing the block device... ");
//     fflush(stdout);
//     int err = sd.init();
//     printf("%s\n", (err ? "Fail :(" : "OK"));
//     if (err) {
//         error("error: %s (%d)\n", strerror(-err), err);
//     }

//     printf("Erasing the block device... ");
//     fflush(stdout);
//     err = sd.erase(0, sd.size());
//     printf("%s\n", (err ? "Fail :(" : "OK"));
//     if (err) {
//         error("error: %s (%d)\n", strerror(-err), err);
//     }

//     printf("Deinitializing the block device... ");
//     fflush(stdout);
//     err = sd.deinit();
//     printf("%s\n", (err ? "Fail :(" : "OK"));
//     if (err) {
//         error("error: %s (%d)\n", strerror(-err), err);
//     }
// }


// Entry point for the example
void massStorage() {
    printf("--- Mbed OS filesystem example ---\n");

    // Setup the erase event on button press, use the event queue
    // to avoid running in interrupt context
    // irq.fall(mbed_event_queue()->event(erase));

    // Call the SDBlockDevice instance initialisation method
    if (0 != sd.init()) {
        printf("Init failed \n");
        // return -1;
    }
    printf("sd size: %llu\n",         sd.size());
    printf("sd read size: %llu\n",    sd.get_read_size());
    printf("sd program size: %llu\n", sd.get_program_size());
    printf("sd erase size: %llu\n",   sd.get_erase_size());

    // Set the frequency
    if (0 != sd.frequency(5000000)) {
        printf("Error setting frequency \n");
    }

    // Try to mount the filesystem
    printf("Mounting the filesystem... ");
    fflush(stdout);
    int err = fs.mount(&sd);
    printf("%s\n", (err ? "Fail :(" : "OK"));
    if (err || FORCE_REFORMAT) {
        // Reformat if we can't mount the filesystem
        printf("formatting... ");
        fflush(stdout);
        err = fs.reformat(&sd);
        printf("%s\n", (err ? "Fail :(" : "OK"));
        if (err) {
            error("error: %s (%d)\n", strerror(-err), err);
        }
        populate(); // Write needed files and folders
    }

    // // Open the numbers file
    // printf("Opening \"/fs/numbers.txt\"... ");
    // fflush(stdout);
    // FILE *f = fopen("/fs/numbers.txt", "r+");
    // printf("%s\n", (!f ? "Fail :(" : "OK"));
    // if (!f) {
    //     // Create the numbers file if it doesn't exist
    //     printf("No file found, creating a new file... ");
    //     fflush(stdout);
    //     f = fopen("/fs/numbers.txt", "w+");
    //     printf("%s\n", (!f ? "Fail :(" : "OK"));
    //     if (!f) {
    //         error("error: %s (%d)\n", strerror(errno), -errno);
    //     }

    //     for (int i = 0; i < 10; i++) {
    //         printf("\rWriting numbers (%d/%d)... ", i, 10);
    //         fflush(stdout);
    //         err = fprintf(f, "    %d\n", i);
    //         if (err < 0) {
    //             printf("Fail :(\n");
    //             error("error: %s (%d)\n", strerror(errno), -errno);
    //         }
    //     }
    //     printf("\rWriting numbers (%d/%d)... OK\n", 10, 10);

    //     printf("Seeking file... ");
    //     fflush(stdout);
    //     err = fseek(f, 0, SEEK_SET);
    //     printf("%s\n", (err < 0 ? "Fail :(" : "OK"));
    //     if (err < 0) {
    //         error("error: %s (%d)\n", strerror(errno), -errno);
    //     }
    // }

    // // Go through and increment the numbers
    // for (int i = 0; i < 10; i++) {
    //     printf("\rIncrementing numbers (%d/%d)... ", i, 10);
    //     fflush(stdout);

    //     // Get current stream position
    //     long pos = ftell(f);

    //     // Parse out the number and increment
    //     char buf[BUFFER_MAX_LEN];
    //     if (!fgets(buf, BUFFER_MAX_LEN, f)) {
    //         error("error: %s (%d)\n", strerror(errno), -errno);
    //     }
    //     char *endptr;
    //     int32_t number = strtol(buf, &endptr, 10);
    //     if (
    //         (errno == ERANGE) || // The number is too small/large
    //         (endptr == buf) ||   // No character was read
    //         (*endptr && *endptr != '\n') // The whole input was not converted
    //     ) {
    //         continue;
    //     }
    //     number += 1;

    //     // Seek to beginning of number
    //     fseek(f, pos, SEEK_SET);
    
    //     // Store number
    //     fprintf(f, "    %d\n", number);

    //     // Flush between write and read on same file
    //     fflush(f);
    // }
    // printf("\rIncrementing numbers (%d/%d)... OK\n", 10, 10);

    // // Close the file which also flushes any cached writes
    // printf("Closing \"/fs/numbers.txt\"... ");
    // fflush(stdout);
    // err = fclose(f);
    // printf("%s\n", (err < 0 ? "Fail :(" : "OK"));
    // if (err < 0) {
    //     error("error: %s (%d)\n", strerror(errno), -errno);
    // }
    
    // // Display the root directory
    // printf("Opening the root directory... ");
    // fflush(stdout);
    // DIR *d = opendir("/fs/");
    // printf("%s\n", (!d ? "Fail :(" : "OK"));
    // if (!d) {
    //     error("error: %s (%d)\n", strerror(errno), -errno);
    // }

    // printf("root directory:\n");
    // while (true) {
    //     struct dirent *e = readdir(d);
    //     if (!e) {
    //         break;
    //     }

    //     printf("    %s\n", e->d_name);
    // }

    // printf("Closing the root directory... ");
    // fflush(stdout);
    // err = closedir(d);
    // printf("%s\n", (err < 0 ? "Fail :(" : "OK"));
    // if (err < 0) {
    //     error("error: %s (%d)\n", strerror(errno), -errno);
    // }

    // // Display the numbers file
    // printf("Opening \"/fs/numbers.txt\"... ");
    // fflush(stdout);
    // f = fopen("/fs/numbers.txt", "r");
    // printf("%s\n", (!f ? "Fail :(" : "OK"));
    // if (!f) {
    //     error("error: %s (%d)\n", strerror(errno), -errno);
    // }

    // printf("numbers:\n");
    // while (!feof(f)) {
    //     int c = fgetc(f);
    //     printf("%c", c);
    // }

    // printf("\rClosing \"/fs/numbers.txt\"... ");
    // fflush(stdout);
    // err = fclose(f);
    // printf("%s\n", (err < 0 ? "Fail :(" : "OK"));
    // if (err < 0) {
    //     error("error: %s (%d)\n", strerror(errno), -errno);
    // }

    // // Tidy up
    // printf("Unmounting... ");
    // fflush(stdout);
    // err = fs.unmount();
    // printf("%s\n", (err < 0 ? "Fail :(" : "OK"));
    // if (err < 0) {
    //     error("error: %s (%d)\n", strerror(-err), err);
    // }
        
    // printf("Mbed OS filesystem example done!\n");
}

void populate(void)
{
    printf("Creating folder structure...\n");
    // mkdir("params",0777);
    // printf("Opening folder params\n");
    // DIR *param = opendir("/fs/params/");
    printf("Opening file...\n");
    fflush(stdout);
    FILE *calib = fopen("/fs/calib.txt","w+");
    printf("Writing...\n");
    fprintf(calib, "## AUTOMATICALLY GENERATED FILE ##\n");
    fprintf(calib, "## This file stores the calibration parameters\n");
    fprintf(calib,"Magnetometer extremes\n");
    fflush(calib);
    fclose(calib);
    fflush(stdout);
    // closedir(param);

}

int readFromSD(float *data_out, const char *field_name)
{
    // calibration_file.open("calib.txt");
    f_calib_read = fopen("/fs/calib.txt","r");
    printf("Opening file in read mode... ");
    if (f_calib_read == NULL)
    {
        printf("Fail :(\n");
        return -1;
    }
    printf("OK\n");
    fflush(stdout);
    rewind(f_calib_read);
    long line_begin = ftell(f_calib_read); // Beginning of the line
    while(!feof(f_calib_read)) // Now writing into the file on the SD card
    {
        printf("Getting char... \n");
        temp_char_read = fgetc(f_calib_read);
        fflush(stdout);
        if (temp_char_read == '#' || temp_char_read == '\t')  // Skip the line
        {
            fgets(f_read_temp,100,f_calib_read); // Discard the line
            line_begin = ftell(f_calib_read);    // Set new beginning of the line
            printf("Line discarded\n");
            // memset(f_buff,0,sizeof(f_buff));
            fflush(stdout);
        }
        else // Here I look for the field I'm interested in and I read data
        {
            fseek(f_calib_read,line_begin,SEEK_SET);
            fgets(f_read_buff, 100, f_calib_read);
            printf(f_read_buff);
            printf("qui\n");
            fflush(stdout);
            if (!strcmp(f_read_buff,field_name))
            {
                line_begin = ftell(f_calib_read);
                char field_char = fgetc(f_calib_read);

                if (field_char == '\n' || field_char == EOF)    // No value in the field I'm reading, returning...
                {
                    printf("No value in file!\n");
                    return -1;
                }
                else if (field_char == '\t')                    // I have a tab that indicates I have a value to read
                {
                    while(field_char == '\t')                       // I read as many set of values as tabs in the next lines of the txt
                    {
                        fgets(values_str, 100, f_calib_read);
                        printf(values_str);
                        fflush(stdout);
                        for (uint ii = 0; ii < sizeof(values_str); ii++)
                        {
                            if (isspace(values_str[ii]))
                            {
                                space_count++;      // Counting how many whitespaces in the line to know how many values I got
                                printf("whtspaces: %d\n",space_count);
                                fflush(stdout);
                            }
                        }
                        for (int ii = 0; ii < space_count; ii++)    // discard the first \t by doing a -1 on the numb of whitespaces
                        {
                            // sscanf(values_str,"%s", data_out_str);
                            data_out[ii] = strtof(values_str,&values_str_buf);
                            strcpy(values_str,values_str_buf);
                            printf("data out: %f\n",data_out[ii]);
                        }
                        field_char = fgetc(f_calib_read); // checking if also the next line has values to be taken!
                    }
                }
                
                // fflush(stdout);
                printf("done reading\n");
                fflush(stdout);
                break;

            }
        }
    }
    fclose(f_calib_read);
    return MBED_SUCCESS;
}