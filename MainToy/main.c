#include <msp430.h>
#include <libTimer.h>
#include "led.h"
#include "buzzer.h"
#include "switches.h"
#include "lcdutils.h"
#include "lcddraw.h"
#include "state_machine.h"

void main(void){
  configureClocks();
  lcd_init();
  led_init();
  switch_init();
  buzzer_init();
  enableWDTInterrupts();
  or_sr(0x8);

  while(1){
    if(button == 1){
      drawString11x16(10,60,"HELLO",COLOR_BLACK,COLOR_RED);
    }
    P1OUT &= ~LED_GREEN;
    or_sr(0x10);
    P1OUT |= LED_GREEN;
  }

}
