#ifndef  _UVECTOR_H
#define  _UVECTOR_H

#include "definesystem.h"

#define	AllIint_Vector_Offset		FLASH_BOOTLOAD_SIZE
#define	Rst_Handler_Offset 			4
#define	NMI_Handler_Offset 			8
#define	HardFault_Handler_Offset 	12
#define	SVC_Handler_Offset 			44
#define	PendSV_Handler_Offset 		56
#define	SysTick_Handler_Offset 		60
#define	CMP_HANDLER_Offset 			68
#define	VCH_HANDLER_Offset 			72
#define	RTC_HANDLER_Offset 			76
#define	EMU_HANDLER_Offset 			80
#define	MADC_HANDLER_Offset 		84
#define	UART0_HANDLER_Offset 		88
#define	UART1_HANDLER_Offset 		92
#define	UART2_HANDLER_Offset 		96
#define	UART3_HANDLER_Offset 		100
#define	SPI_HANDLER_Offset 			104
#define	I2C_HANDLER_Offset 			108
#define	ISO78160_HANDLER_Offset 	112
#define	ISO78161_HANDLER_Offset 	116
#define	TC0_HANDLER_Offset 			120
#define	TC1_HANDLER_Offset 			124

#define	UART5_HANDLER_Offset 		132
#define	WDT_HANDLER_Offset 			136
#define	KBI_HANDLER_Offset 			140
#define	LCD_HANDLER_Offset 			144


#define	EXT0_HANDLER_Offset 		160
#define	EXT2_HANDLER_Offset 		168

#define	EXT6_HANDLER_Offset 		184
#define	EXT7_HANDLER_Offset 		188

#endif   /* _UVECTOR_H*/



