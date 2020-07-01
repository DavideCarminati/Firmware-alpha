#include <mbed.h>

AnalogIn voltagePin(A0);       // analog pin for voltage reading
DigitalOut warnLed(LED1);       // warning LED
float R1 = 33000.0;             // Upper resistor voltage divider 
float R2 = 8200.0;              // lower resistor voltage divider
float vout = 0.0;               // voltage divider output voltage - sensed by the board
float vin = 0.0;                // voltage divider input voltage  - battery voltage
float MIN_VOLTAGE = 14.8;       // minimum battery voltage

void prognostic()
{
        while (1)
        {
            vout = voltagePin.read()*5;         // voltagePin returns a fraction of the board supply voltage - 5V in our case
            vin = vout *(R1+R2)/R2;             // voltage divider
            
            if (vin <= MIN_VOLTAGE)                
            {   
                while(1)                        // warning to the user
                {
                    warnLed = 1;
                    wait(0.2);
                    warnLed = 0;
                    wait(0.2);
                }
                
            }
        }
        

}