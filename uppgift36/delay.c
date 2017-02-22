#include "gpio.h"
#include "delay.h"
#include "timer.h"
#include "irq.h"

const int COUNTVALUE = 42;

static volatile int systick_flag;

static void systick_irq_handler(uint32_t num)
{
    SYS_TICK.ctrl = 0;  /*nollställa CTRL. Deaktivera klockan*/
	systick_flag = 1;   /*lägga ett meddelande*/
}

static void start_delay_250ns(void)
{
                                        
	IRQ.sysTick = systick_irq_handler;  /*registrera en funktion som ska anropas vid systick interrupt*/
	systick_flag = 0;                   /*inget meddelande*/
    SYS_TICK.ctrl = 0;                  /*nollställa CTRL-stoppa klockan*/
    SYS_TICK.load = COUNTVALUE - 1;     /*1 microsec/4 -1 för en cykel-startvärde*/
    SYS_TICK.val = 0x00;                /*nollställa räknaren*/
    SYS_TICK.ctrl = 0x07;               /* bit 0,1,2.Bit 0: klockan är aktiv. Bit 1: genereras ett avbrott. Bit 2: full hastighet*/
}

void delay(uint32_t count)
{
    
	for(int i=0; i< count; i++) {  /*vänta antal gånger*/
		start_delay_250ns();
		while (systick_flag == 0) ; /*så länge inte finns något meddelande, vänta*/
	}
}

