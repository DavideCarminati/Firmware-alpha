
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

SDBlockDevice sd(PTE3, PTE1, PTE2, PTE4);
// std::vector<int> myvector; // use vectors!!!
DigitalOut formatPinOut(D12,0); // Setting to high
DigitalIn formatPinIn(D13);

#include "FATFileSystem.h"
FATFileSystem fs("fs");

FILE *f_calib_read;

char f_read_buff[100], f_read_temp[100], values_str[100], data_out_str[100], temp_char_read;
char *values_str_buf;
int space_count = 0;
bool force_reformat = false;

void massStorage() {
    printf("--- Mbed OS filesystem example ---\n");

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
    fflush(calib);
    fclose(calib);
    fflush(stdout);
    // closedir(param);

}

// Deletes and rewrites the file in which parameters are stored updating their values e.g. after a calibration
int parametersUpdate(float *data_in, const char *field_name)
{
    ifstream calibration_file("/fs/calib.txt");
    std::string line;//, data_in_str;//, temp_buffer;
    // Make a copy of the original calib file into a string buffer that'll be modified

    std::stringstream buffer;
    buffer << calibration_file.rdbuf();

    std::string temp_buffer(buffer.str());

    // printf("Content of the file:\n");
    // std::string texteditor(buffer.str());
    // printf(texteditor.c_str());
    // printf("\n\nEnd content of the file.\n\n");
    
    // Here I find which is entry I'm interested in and I replace the values

    /*
    Magnetometer calibration values.
    */

    if(!strcmp(field_name, "Magnetometer extremes [minXYZ; maxXYZ]\n"))
    {
        // Checking if the required field exists
        size_t posMag = temp_buffer.find(field_name);
        if(posMag == string::npos)
        {
            printf("Required field doesn't exist. Try formatting.\n");
            return -1;
        }
        // Converting floats to strings
        std::ostringstream ss;
        for(int kk = 0; kk < 6; kk++)
        {
            // printf("qui %d", kk);
            ss << data_in[kk];
            ss << " ";
        }
        std::string data_in_str(ss.str()); // String in which num values are put
        data_in_str.insert(data_in_str.begin(),'\t');
        // Overwriting file with new values
        size_t posNewline = temp_buffer.find("\n", posMag + sizeof("Magnetometer extremes [minXYZ; maxXYZ]\n"));
        if(posNewline == string::npos)
        {
            temp_buffer.insert(temp_buffer.end(), ' ');
            temp_buffer.replace(temp_buffer.end()-1, temp_buffer.end(), data_in_str);
        }
        else
        {
            temp_buffer.replace(posMag + sizeof("Magnetometer extremes [minXYZ; maxXYZ]\n"), \
                posNewline - posMag + sizeof("Magnetometer extremes [minXYZ; maxXYZ]\n"), " ");
            temp_buffer.replace(posMag + sizeof("Magnetometer extremes [minXYZ; maxXYZ]\n") - 1, sizeof(data_in_str), data_in_str);
        }
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
    printf("Reading file...\n");
    fflush(stdout);
    rewind(f_calib_read);
    long line_begin = ftell(f_calib_read); // Beginning of the line
    while(1) // Now writing into the file on the SD card
    {
        // printf("Getting char... \n");
        temp_char_read = fgetc(f_calib_read);
        fflush(stdout);
        if (temp_char_read == '#' || temp_char_read == '\t')  // Skip the line
        {
            fgets(f_read_temp,100,f_calib_read); // Discard the line
            line_begin = ftell(f_calib_read);    // Set new beginning of the line
            // printf("Line discarded\n");
            // memset(f_buff,0,sizeof(f_buff));
            // fflush(stdout);
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
            // printf("buffer\n");
            // printf(f_read_buff);
            // printf("qui\n");
            // fflush(stdout);
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
                    // printf("Found a tab\n");
                    // fflush(stdout);
                    while(field_char == '\t')                       // I read as many set of values as tabs in the next lines of the txt
                    {
                        fgets(values_str, 100, f_calib_read);
                        // printf(values_str);
                        // fflush(stdout);
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
                                // printf("whtspaces: %d\n",space_count);
                                // fflush(stdout);
                            }
                        }
                        for (int ii = 0; ii < space_count; ii++)    // discard the first \t by doing a -1 on the numb of whitespaces
                        {
                            // sscanf(values_str,"%s", data_out_str);
                            data_out[ii] = strtof(values_str,&values_str_buf);
                            strcpy(values_str,values_str_buf);
                            // printf("data out: %f\n",data_out[ii]);
                        }
                        field_char = fgetc(f_calib_read); // checking if also the next line has values to be taken!
                    }
                    printf("Done reading!!\n");
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