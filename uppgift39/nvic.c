#include "nvic.h"

/*funktion som beräknar vilket delregister (00,04,08) och vilken bit i det delregistret av NVIC modul*/
static void get_offset_and_shift(uint8_t index, uint8_t* p_offset, uint8_t *p_shift)
{
	*p_offset = 0;
	while (index > 31) {  /*varje delregister har 32 bits*/
		*p_offset += 4;
		index -= 32;    
	}
	/*t.ex. aktivering av bit 43: offsett: 04, shift: 43-32=11. Bit 11 i den andra delen av registret*/
	*p_shift = index;
}

/*generell funktion för att aktivera avbrott- skriv till den av 81 bitar som motsvarar
 * den interrupt som ska aktiveras*/
void nvic_set_enable (uint8_t index)
{
    const uint32_t nvic_iser= 0xe000e100; 
	uint8_t offset, shift;
	uint32_t *pointer;
	
	get_offset_and_shift(index, &offset, &shift);
	pointer = (uint32_t *)(nvic_iser + offset);
	*pointer |= 1 << shift;   /*sätt rätt bit*/
}

/*sätt prioritet på en interrupt*/
void nvic_set_priority (uint8_t index, uint8_t priority)
{
    const uint32_t nvic_ipr= 0xe000e400; 
	uint8_t offset, shift;
    uint32_t mask;
	uint32_t *pointer;
	
	get_offset_and_shift(index * 8, &offset, &shift); /*indexet: vrje del är 8 bits*/
	pointer = (uint32_t *)(nvic_ipr + offset);
    mask = ~(0xff << shift);
	
	*pointer &= mask;
    *pointer |= (priority << shift);
}

