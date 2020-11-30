#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include "buzzer.h"
#include "switches.h"
#include "lcdutils.h"
#include "lcddraw.h"

void main(void){
  configureClocks();
  lcd_init();
  led_init();
  switch_init();
  buzzer_init();
  enableWDTInterrupts();
  or_sr(0x18);

}
