#include "ManualSwitch.hpp"
#include <cstdio>


ManualSwitch::ManualSwitch(PinName int_a):bat_in(int_a)
{
    // if (bat_in)
    //  {printf("ManualSwitch on");}
    // else{printf("ManualSwitch off");}
    ManualSwitch::Nothing();
}
 
 void ManualSwitch::Nothing(void){
     //nothing
 }
