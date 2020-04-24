/*
 * $Id: uSystemInit.c 001 2020.4.2 11:04:50 yangap $
 */

#include "uSystemInit.h"

//void WDTClear(void)
//{
//    WDT->EN = 0xbb;
//}


void uSystemInit(void)
{
    uint8_t i;
    
    SYSCTL->SYS_PS = 0x82;   // ÅäÖÃ¿ªÆô
    NOP();
    NOP();
    NOP();
    NOP();  
    __DMB(); 
    
    SYSCTL->SYS_PD = 0x0CD7;
    SYSCTL->MOD0_EN = 0x0004;
    SYSCTL->MOD1_EN = 0x0C00;
    SYSCTL->INTC_EN = 0x0000;
    SYSCTL->KBI_EN = 0x0000;
    
    NOP();
    NOP();
    NOP();
    NOP();  
    __DMB();     
    SYSCTL->SYS_PS = 0x00;
    
    for(i=0; i<3; i++)
    {
        if(SysModeChg(2,1) == SYSCTRL_PASS) {break;}
    }
    if(i>=3) {SysModeChg(4, 0);}

    
}

