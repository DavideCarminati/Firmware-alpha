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
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>

#include "SDBlockDevice.h"

#include "massStorage.hpp"

// Maximum number of elements in buffer
#define BUFFER_MAX_LEN 10
#define FORCE_REFORMAT false
#define FILE_LINE_MAX_LENGTH 100
// This will take the system's default block device
SDBlockDevice sd(PTE3, PTE1, PTE2, PTE4);
std::vector<int> myvector; // TODO use vectors!!!
DigitalOut formatPinOut(D12,0); // Setting to high
DigitalIn formatPinIn(D13);

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
bool force_reformat = false;


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

    // Check if the format pin is enable
    if(!formatPinIn.read())
    {
        force_reformat = true;
        printf("Forcing format (pin = %d)\n",formatPinIn.read());
    }

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
    if (err || FORCE_REFORMAT || force_reformat) {
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
    // Creating entry for magnetometer calibration values...
    fprintf(calib,"Magnetometer extremes [minXYZ; maxXYZ]\n");
    // for(int ii = 0; ii < FILE_LINE_MAX_LENGTH; ii++)
    // {
    //     fprintf(calib," "); // These spaces are needed, they will be overwritten when updating parameters
    // }
    // fprintf(calib,"\n");

    fflush(calib);
    fclose(calib);
    fflush(stdout);
    // closedir(param);

}

// Deletes and rewrites the file in which parameters are stored updating their values e.g. after a calibration
int parametersUpdate(float *data_in, const char *field_name)
{
    ifstream calibration_file("/fs/calib.txt");
    std::string line, data_in_str;//, temp_buffer;
    // Make a copy of the original calib file into a string buffer that'll be modified
    // while(!calibration_file.eof())
    // {
    //     getline(calibration_file, line);
    //     temp_buffer.append(line);
    //     temp_buffer.append("\n");
    // }

    // PER QUALCHE CAZZO DI MOTIVO SE USO STRINGSTREAM LA MERDA DI K64F CRASHA --> forse perche' la queue in cui gira l'evento che contiene
    // questo script ha solo 2kb di memoria???

    std::stringstream buffer;
    buffer << calibration_file.rdbuf();

    std::string temp_buffer(buffer.str());

    // printf("Content of the file:\n");
    // std::string texteditor(buffer.str());
    // printf(texteditor.c_str());
    // printf("\n\nEnd content of the file.\n\n");

    // string::iterator it1 = temp_buffer.end(); // don't use iterators...
    printf("ecco\n");
    // temp_buffer.erase(temp_buffer.length(),1); // Delete last \n
    // temp_buffer.append(" "); // and append a whitespace
    // temp_buffer.replace(temp_buffer.length(), 1, " ");
    
    // Here I find which is entry I'm interested in and I replace the values

    /*
    Magnetometer calibration values.
    */

    if(!strcmp(field_name, "Magnetometer extremes [minXYZ; maxXYZ]\n"))
    {
        // Checking if the required field exists
        printf("cazzo\n");
        size_t posMag = temp_buffer.find(field_name);
        printf("cazzo2 %d\n", posMag);
        if(posMag == string::npos)
        {
            printf("Required field doesn't exist. Try formatting.\n");
            return -1;
        }
        // Converting floats to strings
        
        printf("qui -1\n");
        std::ostringstream ss;
        for(int kk = 0; kk < 6; kk++)
        {
            printf("qui %d", kk);
            
            ss << data_in[kk];
            ss << " ";
            // std::string s_temp(ss.str());
            // data_in_str.append(s_temp);
            // data_in_str.append(" ");
            // ss.flush();
        }
        // std::string s_temp(ss.str());
        printf("qui\n");
        // data_in_str.erase(data_in_str.end()); // Erase last whitespace
        data_in_str.insert(data_in_str.begin(),'\t');
        // Overwriting file with new values
        temp_buffer.replace(posMag + sizeof("Magnetometer extremes [minXYZ; maxXYZ]\n"), sizeof(data_in_str), data_in_str);
        printf("qui\n");
        printf("Content of the file:\n");
        printf(temp_buffer.c_str());
        printf("END\n");
    }
    calibration_file.close();

    // Create new empty calib.txt in which to copy the updated file temp_buff
    ofstream updated_calibration_file("/fs/calib.txt");
    updated_calibration_file << temp_buffer;
    updated_calibration_file.close();
    return MBED_SUCCESS;
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
    while(1) // Now writing into the file on the SD card
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
        else if (feof(f_calib_read) != 0)
        {
            printf("File is empty!\n");
            return -1;
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

                if (field_char == '\n' || feof(f_calib_read) != 0 || field_char == ' ')    // No value in the field I'm reading, returning...
                {
                    printf("No value in file!\n");
                    return -1;
                }
                else if (field_char == '\t')                    // I have a tab that indicates I have a value to read
                {
                    printf("Found a tab\n");
                    fflush(stdout);
                    while(field_char == '\t')                       // I read as many set of values as tabs in the next lines of the txt
                    {
                        fgets(values_str, 100, f_calib_read);
                        printf(values_str);
                        fflush(stdout);
                        /*
                        // Here using strtok() fnct
                        char * token = strtok(values_str, " ");
                        data_out[0] = strtof(token, nullptr);
                        printf("data out[0]: %f\n",data_out[0]);

                        //In subsequent calls to strtok, the first argument is NULL
                        int ii = 1;
                        while((token = strtok(NULL, " ")) != NULL)
                        {
                            data_out[ii] = strtof(token, nullptr);
                            printf("data out: %f\n",data_out[ii]);
                            ii++;
                        }
                        */
                        // Here old approach
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
                    printf("done reading\n");
                    fflush(stdout);
                    fclose(f_calib_read);
                    return MBED_SUCCESS;
                }
                else
                {
                    printf("Unexpected(?) error\n");
                    return -1;
                }
            }
        }
    }
}