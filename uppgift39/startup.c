#include "gpio.h"
#include "interrupts.h"
#include "exti.h"
#include "irq.h"
#include "nvic.h"
#include "syscfg.h"
#include "scb.h"

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

static uint8_t counter = 0;

static void exti_line3_handler(uint32_t num)
{
	++counter;            /*öka telet på displayen*/
	EXTI.pr |= (1 << 3);  /*kvittera avbrott på EXTI3*/
}

/*display port D, FlipFlop port E*/
static void app_init(void)
{
	/* PD0-7 : utport för visningsenhet */
	GPIO_D.moder &= 0xffff0000;
	GPIO_D.moder |= 0x00005555;
	
	/* PD0-7 : push/pull */
	GPIO_D.otyper &= 0xff00;
    
    /*Aktivera klockan för SYSCFGbit 15 som aktivera klockan för modulen SYSCFG vilken hanterar externa innterrupt*/
     RCC_APB2ENR|= 0x4000; 
     
	/* Koppla pinne 3 på port E till avbrotsvektorn EXTI3 */
	SYSCFG.exticr1 &= 0x0fff;   /*rensa de fyra högsta bittarna*/ 
	SYSCFG.exticr1 |= 0x4000;   /*lägg till '0100'för port E på EXTI3*/
	
	/* Konfigurera EXTI3 för att generera avbrott */
	EXTI.imr |= (1 << 3); /*bit 3*/ 
	
	/* Konfigurera EXTI3 för avbrott på negativ flank */
	EXTI.ftsr |= (1 << 3); 
	
	/* Registrera avbrottsvektor */
	IRQ.extiLine3 = exti_line3_handler;
	
	/* Konfigurera de bitar i NVIC som kontrollerar den
	 * avbrottslina som EXTI3 kopplats till */
	nvic_set_enable(9);
    //nvic_set_priority(9, 16);
}

void main(void)
{
	app_init();
	enable_interrupt();
	while (1) {
		GPIO_D.odr_low = counter;   /*skriv counter till en display*/
	}
	disable_interrupt();
}

