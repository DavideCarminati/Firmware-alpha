#include <mbed.h>

#include "prognostic.hpp"
#include "global_vars.hpp"

AnalogIn voltagePin(A0);       // analog pin for voltage reading
DigitalOut warnLed(LED1,1);    // warning LED
float R1 = 33000.0;             // Upper resistor voltage divider 
float R2 = 8200.0;              // lower resistor voltage divider
float vout = 0.0;               // voltage divider output voltage - sensed by the board
float vin = 0.0;                // voltage divider input voltage  - battery voltage
float MIN_VOLTAGE = 14.9;       // minimum battery voltage
uint64_t startPrognosticLed;
DigitalOut controllerLedPrognosticThread(LED3,1);

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
                    led_lock.lock();
                    controllerLedPrognosticThread = 1;  // Turn off blue controller led
                    startPrognosticLed = Kernel::get_ms_count();
                    while(startPrognosticLed + 1000 > Kernel::get_ms_count())
                    {
                        warnLed = 0;
                        ThisThread::sleep_for(100);
                        // wait(0.5);
                        warnLed = 1;
                        ThisThread::sleep_for(100);
                        // wait(0.5);
                    }
                    led_lock.unlock();
                    ThisThread::sleep_for(5000);
                }
                
            }
        }
        

}