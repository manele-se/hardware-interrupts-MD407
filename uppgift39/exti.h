#ifndef EXTI_H
#define EXTI_H

#include "types.h"

/*structen innehåller EXTI register*/
typedef struct EXTI_table {
	uint32_t imr;
	uint32_t emr;
	uint32_t rtsr;
	uint32_t ftsr;
	uint32_t swier;
	uint32_t pr;
} EXTI_TABLE, *PEXTI_TABLE;

#define EXTI_R_ADDRESS 0x40013c00
#define EXTI_R ((PEXTI_TABLE)EXTI_R_ADDRESS)
#define EXTI (*EXTI_R)

#endif
