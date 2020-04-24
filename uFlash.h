/*
 * $Id: uflash.h 001 2020.4.2 11:04:50 yangap $
 */

#ifndef  __UFLASH_H__
#define  __UFLASH_H__

#ifdef _cplusplus
    extern "C" {
#endif

#include "bootloader.h"
#include "nvm.h"


#define FLASH_PROG_NO_BOOT 0
#define FLASH_PROG_BOOT    1
#define FLASH_PROG_TYPE FLASH_PROG_BOOT

#define PAGE_UNIT 128
#define PAGE_SIZE 1024

#ifndef FLASH_MEMORY_BASE
#define FLASH_MEMORY_BASE 0x00000000
#endif

#ifndef FLASH_MEMORY_SIZE
#define FLASH_MEMORY_SIZE 0x00020000
#endif

#define FLASH_BOOTLOAD_BASE     FLASH_MEMORY_BASE

#if FLASH_PROG_TYPE == FLASH_PROG_BOOT
#define FLASH_BOOTLOAD_SIZE     0x00002800
#else
#define FLASH_BOOTLOAD_SIZE     0x00000000
#endif


#define FLASH_APP_BASE          (FLASH_BOOTLOAD_SIZE)
#define FLASH_APP_SIZE          ((FLASH_MEMORY_SIZE - FLASH_BOOTLOAD_SIZE)/2)

#define FLASH_APP_BACK_BASE     (FLASH_BOOTLOAD_SIZE + FLASH_APP_SIZE)

#define FLASH_BOOT_PARAM1       (FLASH_BOOTLOAD_SIZE-0x400)     // 升级参数存储区
#define FLASH_BOOT_PARAM2       (FLASH_BOOTLOAD_SIZE-0x200)     // 升级参数存储备份区
#define FLASH_BOOT_PARAM1_BIT   (FLASH_BOOTLOAD_SIZE-0x300)     // 数据包bit标志区
#define FLASH_BOOT_PARAM2_BIT   (FLASH_BOOTLOAD_SIZE-0x100)     // 数据包bit标志备份区

// yangap_test
//#define FLASH_BOOT_PARAM1       (FLASH_MEMORY_SIZE-0x400)     // 升级参数存储区
//#define FLASH_BOOT_PARAM2       (FLASH_MEMORY_SIZE-0x200)     // 升级参数存储备份区
//#define FLASH_BOOT_PARAM1_BIT   (FLASH_MEMORY_SIZE-0x300)     // 数据包bit标志区
//#define FLASH_BOOT_PARAM2_BIT   (FLASH_MEMORY_SIZE-0x100)     // 数据包bit标志备份区
// yangap_test

#define	AllIint_Vector_Offset		FLASH_BOOTLOAD_SIZE

#define	READ_FLASH				((uint8_t *) FLASH_MEMORY_BASE)

int32_t uFlashRead(uint32_t addr,uint8_t* pbuf,  uint32_t len);
int32_t uFlashErasePage(uint32_t pg);
int32_t uFlashWriteSub(uint32_t addr, uint8_t* pbuf, uint32_t len);
int32_t uFlashWrite(uint32_t addr, uint8_t* pbuf, uint32_t len);


#ifdef _cplusplus
}
#endif

#endif  /* __UFLASH_H__*/


