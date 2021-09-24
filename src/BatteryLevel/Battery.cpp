#include "Battery.hpp"
#include <cstdio>


Battery::Battery(PinName int_a):bat_in(int_a)
{
    // if (bat_in)
    //  {printf("Battery on");}
    // else{printf("Battery off");}
    Battery::Nothing();
}
 
 void Battery::Nothing(void){
     //nothing
 }
