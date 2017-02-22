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

void svc0_handler(void)
{
}

void hard_fault_handler(void)
{
	while (1);
}

void main(void)
{
	volatile int i, *ip;
	
	/* SimServer relokerar inte!!! */
	#ifdef SIMULATOR
	*((int*)0xe000ed08) = 0x2001c000;
	#endif
	
    /*testa beetende med usage_fault_handler*/
	*((void(**)(void))0x2001c00c) = hard_fault_handler;
	*((void(**)(void))0x2001c02c) = svc0_handler;
	
	/* This should invoke the svc0_handler */
	asm volatile ( " .hword 0xdf00\n" );
	
	/* This invokes the hard_fault_handler - NOT the usage_fault_handler */
	ip = (volatile int *)0x20001001;
	i = *ip;
	
	while (1) {
	}
}

