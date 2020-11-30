#include <msp430.h>
#include "state_machine.h"
#include "buzzer.h"
#include "led.h"
#include "switches.h"
#include "lcdutils.h"
#include "lcddraw.h"

char do_dim = 0;


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
      blink_count = 0;
    }
    if(do_dim == 1){
      speed_selection();
      blink_count = 0;
    }
    else if(button == 2){
      clearScreen(COLOR_RED);
      green_on = 1;
      leds_changed =1;
      led_update();
      drawSomething();
      green_on = 0;
      led_update();
      blink_count = 0;
    }
    else if (button == 3);{
      green_on = 1;
      led_update();
      //put draw string call for font 8 x 12
      blink_count = 0;
      green_on = 0;
      led_update();
    }
    else{
      state_advance();
      clearScreen(COLOR_BLUE);
      drawString5x7(20,80, "No buttons pressed yet", COLOR_BLACK, COLOR_BLUE);
      blink_count = 0;
    }
  }

}
