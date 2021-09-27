#include "EncoderPower.hpp"
#include <cstdio>


EncoderPower::EncoderPower(PinName int_a):bat_in(int_a)
{
    // if (bat_in)
    //  {printf("EncoderPower on");}
    // else{printf("EncoderPower off");}
    EncoderPower::Nothing();
}
 
 void EncoderPower::Nothing(void){
     //nothing
 }
