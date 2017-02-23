#ifndef SYSCFG_H
#define SYSCFG_H

#include "types.h"

/*struct som innehåller SYSCFG register-4 bytes par register*/
typedef struct syscfg_table {
	uint32_t memrmp;
	uint32_t pmc;
	uint32_t exticr1;
	uint32_t exticr2;
	uint32_t exticr3;
	uint32_t exticr4;
	uint32_t reserved18;
	uint32_t reserved1c;
	uint32_t cmpcr;
} SYSCFG_TABLE, *PSYSCFG_TABLE;

#define SYSCFG_R_ADDRESS 0x40013800   /*startadressen för SYSFG modulen*/
#define SYSCFG_R ((PSYSCFG_TABLE)SYSCFG_R_ADDRESS)  /*pekare till modulen*/
#define SYSCFG (*SYSCFG_R)  /*dereferens av pekaren*/

#endif
