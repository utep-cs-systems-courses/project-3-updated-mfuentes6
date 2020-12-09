#ifndef  state_machine_included
#define  state_machine_included

char button;
char do_dim;
char dimmer;
char dim_state;
char draw;
char seconds;

void state_advance();
void buzzer_advance();
void dim_advance();
void speed_selection();
void dim25();
void dim50();
void dim75();
void drawSomething();
void drawHouse();
void drawStar();
void drawGrid();
void drawTriangles();


#endif
