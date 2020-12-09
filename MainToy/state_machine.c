#include <msp430.h>
#include "state_machine.h"
#include "led.h"
#include "buzzer.h"
#include "switches.h"
#include "lcdutils.h"
#include "lcddraw.h"

char draw = 0;
char dimmer;
char dim_state = 0;
char dimmerOne = 0;

char toggle_red()
{
  static char state = 0;
  switch(state) {
  case 0:
    red_on = 1;
    state = 1;
    break;
  case 1:
    red_on = 0;
    state = 0;
    break;
  }
  return 1;
}

char toggle_green()
{
  char changed = 0;
  if(red_on){
    green_on ^= 1;
    changed = 1;
  }
  return changed;
}

void state_advance()
{
  char changed = 0;
  static enum{R = 0, G = 1} color = G;
  switch(color) {
  case R: changed = toggle_red(); color = G; break;
  case G: changed = toggle_green(); color = R; break;
  }

  leds_changed = changed;
  led_update();
}


void buzzer_advance()
{
  static char second_count = 0;
  switch(second_count){
  case 0: buzzer_set_period(1000); second_count = 1; break;
  case 1: buzzer_set_period(5000); second_count = 2; break;
  case 2: buzzer_set_period(3000); second_count = 3; break;
  case 3: buzzer_set_period(7000); second_count = 4; break;
  default: second_count = 0;
  }

}


void dim_advance()
{
  
  switch(dimmerOne){
  case 0: red_on = 1; leds_changed = 1; led_update(); break;
  case 1: dim25(); break;
  case 2: dim50(); break;
  case 3: dim75(); break;
  default: break;
  }
}

void speed_selection(){

  switch(dimmerOne){
  case 0: dimmerOne = 1; break;
  case 1: dimmerOne = 2; break;
  case 2: dimmerOne = 3; break;
  case 3: dimmerOne = 0; break;
  default: dimmerOne = 0; break;
  }
  //dimmerOne++;
}
void dim25(){
  switch(dim_state){
  case 0: red_on = 0; break;
  case 1: red_on = 0; break;
  case 2: red_on = 0; break;
  case 3: red_on = 1; break;
  default: dim_state = 0; break;

  }
  leds_changed = 1;
  led_update();
  

}


void dim50(){
  switch(dim_state){
  case 0: red_on = 0; break;
  case 1: red_on = 1; break;
  case 2: red_on = 0; break;
  case 3: red_on = 1; break;
  default: dim_state = 0; break;
  }
  leds_changed = 1;
  led_update();


}


void dim75(){
  switch(dim_state){
  case 0: red_on = 1; break;
  case 1: red_on = 1; break;
  case 2: red_on = 1; break;
  case 3: red_on = 0; break;
  default: dim_state = 0; break;
  }
  leds_changed = 1;
  led_update();
}

void drawSomething(){
  clearScreen(COLOR_RED);
  switch(draw){
  case 0:
    draw = 1;
    drawHouse();
    break;
  case 1:
    draw = 2;
    drawStar();
    break;
  case 2:
    draw = 3;
    drawGrid();
    break;
  case 3:
    draw = 0;
    drawTriangles();
    break;
  default: draw = 0; drawString5x7(20,20, "default string", COLOR_BLACK, COLOR_RED); break;
  }
  
}

void drawHouse(){
  int offset = 0;
  int row = 63;
  while(offset != 10){
    for(int middle = 0; middle <= offset){
      drawPixel(63, row, COLOR_BLACK);
      drawPixel(63+middle, row, COLOR_BLACK);
      drawPixel(63-middle, row, COLOR_BLACK);
    }
    offset++;
    row++;
  }
  fillRectangle(53,73,73,93,COLOR_BLACK);
  fillRectangle(60,88,68,93, COLOR_GREEN);

}

void drawStar(){
  for(int i = 0; i < 128; i++){
    drawPixel(63,i,COLOR_BLACK);
  }
  for(int j = 0; j < 128; j++){
    drawPixel(i,63,COLOR_BLACK);
  }
  for(int k = 0; k<128; k++){
    drawPixel(k,k,COLOR_BLACK);
  }
  int col = 0;
  for(int l = 127; l >= 0;l--){
    drawPixel(col,l,COLOR_BLACK);
    col++;
  }
}

void drawGrid(){
  fillRectangle(32,40,96,120,COLOR_BLACK);
  for(int i = 60; i <= 100; i += 20){
    for(int j = 32; j<= 96; j++){
      drawPixel(j,i,COLOR_GREEN);
    }
  }
  for(int k = 48; k <= 70; k+= 16){
    for(int h = 40; h<= 120; h++){
      drawPixel(k,h,COLOR_GREEN);
    }
  }
}


void drawTriangles(){

  int col = 30;
  int row = 60;
  for(int i = 0; i<= 30; i++){
    drawPixel(col,row,COLOR_BLACK);
    col++;
    row--;
  }
  for(int j = 0; j<=30; j++){
    drawPixel(col,row,COLOR_BLACK);
    col++;
    row++;
  }
  for(int k = 0; k<= 60; k++){
    drawPixel(col,row, COLOR_BLACKE);
    col--;
  }
  col = 45;
  row = 45;
  for(int i = 0; i<=15; i++){
    drawPixel(col,row,COLOR_BLACK);
    col++;
    row++;
  }
  for(int k = 0; k <=15; k++){
    drawPixel(col,row,COLOR_BLACK);
    col++;
    row--;
  }
  for(int l = 0; l <= 30; l++){
    drawPixel(col,row,COLOR_BLACK);
    col--;
  }

}
