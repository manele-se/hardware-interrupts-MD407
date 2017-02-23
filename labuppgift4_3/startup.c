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

volatile static uint8_t counter = 0;
volatile static uint8_t blink = 0;

static void exti_line0_handler(void)
{
	++counter;            /*öka talet på displayen*/
	EXTI.pr |= (1 << 0);  /*kvittera avbrott på EXTI0*/
}

static void exti_line1_handler(void)
{
	counter = 0;          /* nollställa talet på displayen*/
	EXTI.pr |= (1 << 1);  /*kvittera avbrott på EXTI1*/
}

static void exti_line2_handler(void)
{
    if (blink == 0) blink = 0xff;
    else            blink = 0;
    
	EXTI.pr |= (1 << 2);  /*kvittera avbrott på EXTI2*/
}

/*display port D, FlipFlop port E*/
static void app_init(void)
{
	/* PD0-15 : utport för två visningsenheter */
	/* PE0-15 : ingångar */
	GPIO_D.moder = 0x55555555;
	GPIO_E.moder = 0x00000000;
	
	/* PD0-15 : push/pull */
	GPIO_D.otyper = 0x0000;
    
    /*Aktivera klockan för SYSCFGbit 15 som aktivera klockan för modulen SYSCFG vilken hanterar externa innterrupt*/
    RCC_APB2ENR|= 0x4000; 
     
	/* Koppla pinne 0,1,2 på port E till avbrottsvektorerna EXTI0, EXTI1, EXTI2 */
	SYSCFG.exticr1 &= 0xf000;   /*rensa bitarna för bit 0-11, behåll bit 12-15*/ 
	SYSCFG.exticr1 |= 0x0444;   /*lägg till '0100'för port E på EXTI0, EXTI1, EXTI2*/
	
	/* Konfigurera EXTI0, EXTI1, EXTI2 för att generera avbrott */
	EXTI.imr |= (1 << 0); /*bit 0*/ 
	EXTI.imr |= (1 << 1); /*bit 1*/ 
	EXTI.imr |= (1 << 2); /*bit 2*/ 
	
	/* Konfigurera EXTI0, EXTI1, EXTI2 för avbrott på negativ flank */
	EXTI.ftsr |= (1 << 0); 
	EXTI.ftsr |= (1 << 1); 
	EXTI.ftsr |= (1 << 2); 
	
	/* Registrera tre avbrottsvektorer */
	IRQ.extiLine0 = exti_line0_handler;
	IRQ.extiLine1 = exti_line1_handler;
	IRQ.extiLine2 = exti_line2_handler;
	
	/* Konfigurera de bitar i NVIC som kontrollerar de
	 * avbrottslinor som EXTI0, EXTI1, EXTI2 kopplats till */
     
	nvic_set_enable(6);
    /*nvic_set_priority(6, 16);
	 * Verkar inte behövas */
     
	nvic_set_enable(7);
    /*nvic_set_priority(7, 16);
	 * Verkar inte behövas */
     
	nvic_set_enable(8);
    /*nvic_set_priority(8, 16);
	 * Verkar inte behövas */
	
	/* Kvittera interrupt EXTI0, EXTI1, EXTI2 */
	EXTI.pr |= ((1<<0) | (1<<1) | (1<<2));
}

void main(void)
{
	app_init();
	enable_interrupt();
	while (1) {
		GPIO_D.odr_low = counter;   /*skriv counter till en display*/
		GPIO_D.odr_high = blink;    /*skriv blink till bargraph-displayen*/
	}
	disable_interrupt();
}

