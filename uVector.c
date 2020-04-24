#include "uVector.h"             
#include "uflash.h"

void NMI_Handler(void)
{
	
}

void HardFault_Handler(void)
{
	
}

void SVC_Handler(void)
{
	
}

void PendSV_Handler(void)
{
	
}

void SysTick_Handler(void)
{
	void (*Int_Entry) (void);
	Int_Entry = (void(*)())(*(uint32_t *)(FLASH_MEMORY_BASE + AllIint_Vector_Offset + SysTick_Handler_Offset));
  	(*Int_Entry)();
}

void CMP_HANDLER(void)
{
	void (*Int_Entry) (void);
	Int_Entry = (void(*)())(*(uint32_t *)(FLASH_MEMORY_BASE + AllIint_Vector_Offset + CMP_HANDLER_Offset));
  	(*Int_Entry)();
}

void VCH_HANDLER(void)
{
	void (*Int_Entry) (void);
	Int_Entry = (void(*)())(*(uint32_t *)(FLASH_MEMORY_BASE + AllIint_Vector_Offset + VCH_HANDLER_Offset));
  	(*Int_Entry)();
}

void RTC_HANDLER(void)
{
	void (*Int_Entry) (void);
	Int_Entry = (void(*)())(*(uint32_t *)(FLASH_MEMORY_BASE + AllIint_Vector_Offset + RTC_HANDLER_Offset));
  	(*Int_Entry)();
}

void EMU_HANDLER(void)
{
	void (*Int_Entry) (void);
	Int_Entry = (void(*)())(*(uint32_t *)(FLASH_MEMORY_BASE + AllIint_Vector_Offset + EMU_HANDLER_Offset));
  	(*Int_Entry)();
}

void MADC_HANDLER(void)
{
	void (*Int_Entry) (void);
	Int_Entry = (void(*)())(*(uint32_t *)(FLASH_MEMORY_BASE + AllIint_Vector_Offset + MADC_HANDLER_Offset));
  	(*Int_Entry)();
}

void UART0_HANDLER(void)
{
	void (*Int_Entry) (void);
	Int_Entry = (void(*)())(*(uint32_t *)(FLASH_MEMORY_BASE + AllIint_Vector_Offset + UART0_HANDLER_Offset));
  	(*Int_Entry)();
}

void UART1_HANDLER(void)
{
	void (*Int_Entry) (void);
	Int_Entry = (void(*)())(*(uint32_t *)(FLASH_MEMORY_BASE + AllIint_Vector_Offset + UART1_HANDLER_Offset));
  	(*Int_Entry)();
}

void UART2_HANDLER(void)
{
	void (*Int_Entry) (void);
	Int_Entry = (void(*)())(*(uint32_t *)(FLASH_MEMORY_BASE + AllIint_Vector_Offset + UART2_HANDLER_Offset));
  	(*Int_Entry)();
}

void UART3_HANDLER(void)
{
	void (*Int_Entry) (void);
	Int_Entry = (void(*)())(*(uint32_t *)(FLASH_MEMORY_BASE + AllIint_Vector_Offset + UART3_HANDLER_Offset));
  	(*Int_Entry)();
}

void SPI_HANDLER(void)
{
	void (*Int_Entry) (void);
	Int_Entry = (void(*)())(*(uint32_t *)(FLASH_MEMORY_BASE + AllIint_Vector_Offset + SPI_HANDLER_Offset));
  	(*Int_Entry)();
}

void I2C_HANDLER(void)
{
	void (*Int_Entry) (void);
	Int_Entry = (void(*)())(*(uint32_t *)(FLASH_MEMORY_BASE + AllIint_Vector_Offset + I2C_HANDLER_Offset));
  	(*Int_Entry)();
}

void ISO78160_HANDLER(void)
{
	void (*Int_Entry) (void);
	Int_Entry = (void(*)())(*(uint32_t *)(FLASH_MEMORY_BASE + AllIint_Vector_Offset + ISO78160_HANDLER_Offset));
  	(*Int_Entry)();
}

void ISO78161_HANDLER(void)
{
	void (*Int_Entry) (void);
	Int_Entry = (void(*)())(*(uint32_t *)(FLASH_MEMORY_BASE + AllIint_Vector_Offset + ISO78161_HANDLER_Offset));
  	(*Int_Entry)();
}

void TC0_HANDLER(void)
{
	void (*Int_Entry) (void);
	Int_Entry = (void(*)())(*(uint32_t *)(FLASH_MEMORY_BASE + AllIint_Vector_Offset + TC0_HANDLER_Offset));
  	(*Int_Entry)();
}

void TC1_HANDLER(void)
{
	void (*Int_Entry) (void);
	Int_Entry = (void(*)())(*(uint32_t *)(FLASH_MEMORY_BASE + AllIint_Vector_Offset + TC1_HANDLER_Offset));
  	(*Int_Entry)();
}

void UART5_HANDLER(void)
{
	void (*Int_Entry) (void);
	Int_Entry = (void(*)())(*(uint32_t *)(FLASH_MEMORY_BASE + AllIint_Vector_Offset + UART5_HANDLER_Offset));
  	(*Int_Entry)();
}

void WDT_HANDLER(void)
{
	void (*Int_Entry) (void);
	Int_Entry = (void(*)())(*(uint32_t *)(FLASH_MEMORY_BASE + AllIint_Vector_Offset + WDT_HANDLER_Offset));
  	(*Int_Entry)();
}

void KBI_HANDLER(void)
{
	void (*Int_Entry) (void);
	Int_Entry = (void(*)())(*(uint32_t *)(FLASH_MEMORY_BASE + AllIint_Vector_Offset + KBI_HANDLER_Offset));
  	(*Int_Entry)();
}



void LCD_HANDLER(void)
{
	void (*Int_Entry) (void);
	Int_Entry = (void(*)())(*(uint32_t *)(FLASH_MEMORY_BASE + AllIint_Vector_Offset + LCD_HANDLER_Offset));
  	(*Int_Entry)();
}

void EXT0_HANDLER(void)
{
	void (*Int_Entry) (void);
	Int_Entry = (void(*)())(*(uint32_t *)(FLASH_MEMORY_BASE + AllIint_Vector_Offset + EXT0_HANDLER_Offset));
  	(*Int_Entry)();
}

void EXT2_HANDLER(void)
{
	void (*Int_Entry) (void);
	Int_Entry = (void(*)())(*(uint32_t *)(FLASH_MEMORY_BASE + AllIint_Vector_Offset + EXT2_HANDLER_Offset));
  	(*Int_Entry)();
}

void EXT6_HANDLER(void)
{
	void (*Int_Entry) (void);
	Int_Entry = (void(*)())(*(uint32_t *)(FLASH_MEMORY_BASE + AllIint_Vector_Offset + EXT6_HANDLER_Offset));
  	(*Int_Entry)();
}

void EXT7_HANDLER(void)
{
	void (*Int_Entry) (void);
	Int_Entry = (void(*)())(*(uint32_t *)(FLASH_MEMORY_BASE + AllIint_Vector_Offset + EXT7_HANDLER_Offset));
  	(*Int_Entry)();
}




