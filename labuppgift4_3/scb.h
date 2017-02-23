#ifndef SCB_H
#define SCB_H

#include "irq.h"
#include "types.h"

typedef struct system_control_block {
	uint32_t cpuid;
	uint32_t icsr;
	PIRQ_VECTORS vtor;
	uint32_t aircr;
	uint32_t scr;
	uint32_t ccr;
	uint32_t shpr1;
	uint32_t shpr2;
	uint32_t shpr3;
	uint32_t shcsr;
	uint32_t cfsr;
	uint32_t hfsr;
	uint32_t reserved30;
	uint32_t mmar;
	uint32_t bfar;
	uint32_t afsr;
	
} SCB_TABLE, *PSCB_TABLE;

#define SCB_R_ADDRESS 0xe000ed00
#define SCB_R ((PSCB_TABLE)SCB_R_ADDRESS)
#define SCB (*SCB_R)

#endif
