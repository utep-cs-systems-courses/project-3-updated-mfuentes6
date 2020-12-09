COMMON_OBJECTS =
CPU		= msp430g2553
CFLAGS		= -mmcu=${CPU} -Os -I../h
LDFLAGS		= -L../lib -L/opt/ti/msp430_gcc/include/


CC		= msp430-elf-gcc
AS		= msp430-elf-gcc -mmcu=${CPU} -c
AR		= msp430-elf-ar


all: main.elf


main.elf: ${COMMON_OBJECTS} main.o state_machine.o P2_Interupt_Handler.o WD_Interupt.o buzzer.o led.o switches.o lcddraw.o lcdutils.o font-5x7.o font-11x16.o ../lib/libTimer.a
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ -lTimer

load: main.elf
	msp430loader.sh $^

clean:
	rm -f *.o *.elf

led.o: led.c led.h

buzzer.o: buzzer.c buzzer.h

switches.o: switches.c switches.h

main.o: main.c

WD_Interupt.o: state_machine.h buzzer.h

P2_Interupt_Handler.o: P2_Interupt_Handler.c switches.h

state_machine.o: led.h state_machine.h

