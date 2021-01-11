#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "switches.h"
#include "led.h"
#include "buzzer.h"
#include "state_machine.h"

#define LED_GREEN BIT6             // P1.6

char do_dim = 0;
short redrawScreen = 1;
u_int fontFgColor = COLOR_GREEN;

void wdt_c_handler()
{
  static int secCount = 0;

  secCount ++;
  if (secCount == 500) {		/* once/sec */
    secCount = 0;
    fontFgColor = (fontFgColor == COLOR_GREEN) ? COLOR_BLACK : COLOR_GREEN;

    switch(button){
    case 1: do_dim = 1; speed_selection(); break;
    case 2: do_dim = 0; buzzer_advance(); break;
    case 3: do_dim = 0; drawSomething(); drawSelection(); break;
    case 4: do_dim = 0; leds_changed = 1; state_advance(); break;
    default: break;

    }
  }
}
  

void main()
{
  P1DIR |= LED_GREEN;		/**< Green led on when CPU on */		
  P1OUT |= LED_GREEN;
  configureClocks();
  lcd_init();
  led_init();
  switch_init();
  buzzer_init();
  
  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);                 /**< GIE (enable interrupts) */
  
  clearScreen(COLOR_BLUE);
  while (1) {			/* forever */
    if (button == 0) {
      clearScreen(COLOR_BLUE);
      switch(redrawScreen){
      case 1: drawString11x16(10,20,"I am", COLOR_BLACK,COLOR_BLUE); break;
      case 2: drawString11x16(10,20, "the Batman", COLOR_BLACK,COLOR_BLUE); break;
      case 3: drawString11x16(10,20, "fear me!", COLOR_BLACK, COLOR_BLUE); break;
      default: redrawScreen = 0; break;
      }
      new_screen();
    }
    if(do_dim == 1){
      dim_state++;
      dim_state %= 4;
      dim_advance();
    }
    P1OUT &= ~LED_GREEN;	/* green off */
    or_sr(0x10);		/**< CPU OFF */
    P1OUT |= LED_GREEN;		/* green on */
  }
}
