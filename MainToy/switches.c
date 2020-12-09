#include <msp430.h>
#include "led.h"
#include "switches.h"
#include "libTimer.h"
#include "buzzer.h"
#include "state_machine.h"

char switch_state_changed;
char button = 0;
short note;

static char switch_update_interrupt_sense(){
  char p2 = P2IN;
  P2IES |= (p2 & SWITCHES);
  P2IES &= (p2 | ~SWITCHES);
  return p2;
}

void switch_init(){
  P2REN |= SWITCHES;
  P2IE = SWITCHES;
  P2OUT |= SWITCHES;
  P2DIR &= ~SWITCHES;
  switch_update_interrupt_sense();
  switch_interupt_handler();
  led_update();
}

void switch_interupt_handler(){
  char p2 = switch_update_interrupt_sense();

  char B1 = (p2 & SW1) ? 0:1;
  char B2 = (p2 & SW2) ? 0:1;
  char B3 = (p2 & SW3) ? 0:1;
  char B4 = (p2 & SW4) ? 0:1;


  if(B1){
    note = 2000; //buzzer note
    button = 1; 
    buzzer_set_period(note);
    do_dim = 0;
    seconds = 500;
  }

  if(B2){
    note = 7000; 
    button = 2;
    buzzer_set_period(note);
    do_dim = 0;
    seconds = 1000;
  }

  if(B3){
    button = 3;
    note = 1000;
    dimmer = 0;
    do_dim = 1;
    seconds = 150;
  }

  if(B4){
    buzzer_set_period(400);
    button = 4;
    do_dim = 0;
    seconds = 150;
  }
}
