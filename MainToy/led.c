#include <msp430.h>
#include "led.h"
#include "switches.h"
#include "libTimer.h"
#include "buzzer.h"
#include "state_machine.h"

char switch_state_changed;
unsigned char red_on = 0, green_on = 0;
unsigned char leds_changed = 0;
short speed = 10;

static char redVal[] = {0,LED_RED}, greenVal[] = {0,LED_GREEN};

void led_init()
{
  P1DIR |= LEDS;
  leds_changed = 1;
  led_update();
}


void led_update()
{
  if(leds_changed){
    char ledFlags = redVal[red_on] | greenVal[green_on];
    P1OUT &= (0xff^LEDS) | ledFlags;
    P1OUT |= ledFlags;
    leds_changed = 0;
    buzzer_set_period(note);
  }
  //buzzer_set_period(note);
  //leds_changed = 0;
}
