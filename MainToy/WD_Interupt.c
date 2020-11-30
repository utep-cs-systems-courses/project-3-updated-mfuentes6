#include <msp430.h>
#include "state_machine.h"
#include "buzzer.h"
#include "led.h"
#include "switches.h"

char do_dim = 0;
//short speed = 10;

void
__interrupt_vec(WDT_VECTOR) WDT(){
  
  static char blink_count = 0;
  if (do_dim == 1){
    dim_state++;
    dim_state %= 4;
    dim_advance();
  }


  if(++blink_count == 125){
    if(button == 4){
      do_dim = 0;
      buzzer_advance();
      //state_advance();
      blink_count = 0;
    }
    if(do_dim == 1){
      speed_selection();
      blink_count = 0;
    }
    else{
      
      state_advance();
    }
    blink_count = 0;
  }

}
