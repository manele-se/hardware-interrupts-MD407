#ifndef IRQ_H
#define IRQ_H

#include "gpio.h"

typedef void(*IRQ_FUNCPTR)(uint32_t);

typedef struct irq_vectors {
	IRQ_FUNCPTR reserved00;
	IRQ_FUNCPTR reset;
	IRQ_FUNCPTR nmi;
	IRQ_FUNCPTR hardFault;
	IRQ_FUNCPTR memManage;
	IRQ_FUNCPTR busFault;
	IRQ_FUNCPTR usageFault;
	IRQ_FUNCPTR reserved1c;
	IRQ_FUNCPTR reserved20;
	IRQ_FUNCPTR reserved24;
	IRQ_FUNCPTR reserved28;
	IRQ_FUNCPTR svCall;
	IRQ_FUNCPTR debugMonitor;
	IRQ_FUNCPTR reserved34;
	IRQ_FUNCPTR pendSv;
	IRQ_FUNCPTR sysTick;
} IRQ_VECTORS, *PIRQ_VECTORS;

#define IRQ_R_ADDRESS 0x2001c000
#define IRQ (*((PIRQ_VECTORS)IRQ_R_ADDRESS))

#define SCB_VTOR *((int*)0xe000ed08)




#endif
