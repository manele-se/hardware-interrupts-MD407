#include "gpio.h"
#include "delay.h"
#include "irq.h"

#ifdef SIMULATOR
#define DELAY_COUNT 2000
#else
#define DELAY_COUNT 1000000
#endif
/*
 * 	startup.c
 *
 */
void startup(void) __attribute__((naked)) __attribute__((section (".start_section")) );

void startup ( void )
{
asm volatile(
	" LDR R0,=0x2001C000\n"		/* set stack */
	" MOV SP,R0\n"
	" BL main\n"				/* call main */
	".L1: B .L1\n"				/* never return */
	) ;
}

void init_app(void)
{
	/* om vektortabellen inte är relokerad, görs relokeringen
      *((int*)0xe000ed08)=0x2001c000 eller med struct SCB_VTOR = IRQ_R_ADDRESS;*/
	
	/* Pinnar 0-7 är output */
	GPIO_D.moder &= 0xffff0000;
	GPIO_D.moder |= 0x00005555;
	
	/* Output pins 0-7 are push/pull */
	GPIO_D.otyper &= 0xff00;
}

void main(void)
{
	init_app();
	
	while (1) {
		GPIO_D.odr_low = 0xff;  /*tända pinnarna 0 till 7*/
		delay(DELAY_COUNT);
		GPIO_D.odr_low = 0x00;  /*släcka*/
		delay(DELAY_COUNT);
	}
}

