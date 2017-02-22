#include "interrupts.h"

/*processorn accepterar avbrott- CPSIE: instruktion som aktiverar interrupt, det finns bara som assembler*/
void enable_interrupt(void)
{
	asm ( " CPSIE i\n" );
}


void disable_interrupt(void)
{   
    asm ( " CPSID i\n" );
}


