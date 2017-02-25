#ifndef NVIC_H
#define NVIC_H

#include "types.h"

void nvic_set_enable (uint8_t index);
void nvic_set_priority (uint8_t index, uint8_t priority);

#endif
