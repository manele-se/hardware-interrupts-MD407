/*sätt prioritet på en interrupt*/
void nvic_set_priority (NVIC_ID index, uint8_t priority)
{
    const uint32_t nvic_ipr= 0xe000e400; 
	uint8_t offset, shift;
    uint32_t mask;
	uint32_t *pointer;
	
	get_offset_and_shift((int)index * 8, &offset, &shift); /*indexet: vrje del är 8 bits*/
	pointer = (uint32_t *)( nvic_ipr + offset);
    mask = ~(0xff << shift);
	
	*pointer &= mask;
    *pointer |= (priority << shift);
}