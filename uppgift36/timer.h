#ifndef TIMER_H
#define TIMER_H

typedef struct sys_tick
{
    uint32_t ctrl; 
    uint32_t load; 
    uint32_t val; 
    uint32_t calib;
    
}Sys_tick; 


typedef volatile Sys_tick* systickptr; 

#define SYS_TICK (*((systickptr)0xe000e010))

#endif