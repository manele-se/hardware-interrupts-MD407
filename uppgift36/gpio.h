#ifndef GPIO_H
#define GPIO_H
#include "types.h"

/*struct som innehåller definition av en gpio port
 * structuren som i boken s.67*/
typedef struct gpio
{
    uint32_t moder; 
    uint16_t otyper;
    uint16_t unused0;  /* vi hoppar över 16 bits, som i figuren*/
    uint32_t ospeedr; 
    uint32_t pupdr; 
    uint8_t idr_low;  
    uint8_t idr_high; 
    uint16_t unused1; 
    uint8_t odr_low;
    uint8_t odr_high; 
    uint16_t unused2; 
    uint32_t bsrr; 
    struct { unsigned int lckr : 17;} lckr;   /*bitfield: tilldela ett värde som har 17 bitar inuti en struct som tar 32 bitar*/
    uint32_t afrl;
    uint32_t afrh;
    
} GPIO; 

 /*alias pekare till a volatile struct gpio. Vid variabels deklaration, 
  * det skapas en pekare till en IO port som är volatile*/
typedef volatile GPIO* gpioptr;   

/*Definition för alla 5 portar, 1 kbyte från varandra.
 *Först kastas minnsadress. Minnessadressen är en heltal, så måste den kastas till en pekare:
 * i C kan man inte skriva direkt till en minnessadress.
 * Sen ska den derefereras för att läsa och skriva från och till minnet */
#define GPIO_A (*((gpioptr)0x40020000))  
#define GPIO_B (*((gpioptr)0x40020400))
#define GPIO_C (*((gpioptr)0x40020800)) 
#define GPIO_D (*((gpioptr)0x40020c00))
#define GPIO_E (*((gpioptr)0x40021000))

/* aktivera clockan
Start: 		LDR	R6,=0x00000018
		    LDR	R4,=0x40023830
            LDR	R5,[R4]
            ORR	R5,R5,R6
            STR	R5,[R4] */
#define RCC_AHB1ENR (*((uint32_t* ) 0x40023830))
/*bit 4, satt för aktivera clockan*/
#define RCC_GPIO_D 0x00000008
/*bit 5*/ 
#define RCC_GPIO_E 0x00000010 

/* bit 20, vet inte varför */
#define RCC_CCMDATARAMEN 0x00100000

#endif