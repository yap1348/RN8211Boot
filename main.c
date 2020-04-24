/*
 * $Id: main.c 001 2020.4.2 11:04:50 yangap $
 */

#include "bootloader.h"
#include "uVector.h"  

int32_t main(void)
{
    NOP();
    NOP();
    NOP();
    NOP();
    DI();
    
    NOP();
    NOP();
    NOP();
    NOP();
    WDTClear();
    
    NOP();
    NOP();
    NOP();
    NOP();
    DelayMs(100);
    WDTClear();
    uSystemInit();
    DelayMs(10);
    WDTClear();
    IapBootProcess();

    uint32_t sp;
	void (*Int_Entry) (void);
	sp = *(uint32_t *)(FLASH_MEMORY_BASE + AllIint_Vector_Offset);
	__set_MSP(sp);
		
	Int_Entry = (void(*)())(*(uint32_t *)(FLASH_MEMORY_BASE + AllIint_Vector_Offset + Rst_Handler_Offset));
	(*Int_Entry)();   

	while(1);
}

