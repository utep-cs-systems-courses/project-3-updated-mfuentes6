#include <msp430.h>
#include "state_machine.h"
#include "buzzer.h"
#include "led.h"
#include "switches.h"
#include "lcdutils.h"
#include "lcddraw.h"

char do_dim = 0;
char seconds = 150;

void
__interrupt_vec(WDT_VECTOR) WDT(){
  
  static char blink_count = 0;
  if (do_dim == 1){
    dim_state++;
    dim_state %= 4;
    dim_advance();
  }


  if(++blink_count == seconds){
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
    else if (button == 1);{
      clearScreen(COLOR_RED);
      green_on = 1;
      led_update();
      drawString11x16(10,80,"I'm Batman", COLOR_BLACK, COLOR_YELLOW);
      blink_count = 0;
      green_on = 0;
      led_update();
    }
    else{// default state when loaded on to msp430
      state_advance();
      clearScreen(COLOR_BLUE);
      drawString11x16(10,80, "No buttons pressed yet", COLOR_BLACK, COLOR_BLUE);
      blink_count = 0;
    }
  }

}
