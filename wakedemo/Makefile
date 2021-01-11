# makfile configuration
CPU             	= msp430g2553
CFLAGS          	= -mmcu=${CPU} -Os -I../h
LDFLAGS		= -L../lib -L/opt/ti/msp430_gcc/include/ 

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-gcc -mmcu=${CPU} -c
AR 		= msp430-elf-ar

all:wakedemo.elf

#additional rules for files
wakedemo.elf: ${COMMON_OBJECTS} wakedemo.o wdt_handler.o selector.o state_machine.o P2_Interupt_Handler.o buzzer.o led.o switches.o lcddraw.o lcdutils.o font-5x7.o font-11x16.o ../lib/libTimer.a
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ -lTimer

load: wakedemo.elf
	msp430loader.sh $^

clean:
	rm -f *.o *.elf
led.o: led.c led.h

buzzer.o: buzzer.c buzzer.h

switches.o: switches.c switches.h

P2_Interupt_Handler.o: P2_Interupt_Handler.c switches.h

state_machine.o: led.h state_machine.h
