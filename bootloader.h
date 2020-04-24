/*
 * $Id: bootloader.h  001  2020.4.2 11:04:55 yangap $
 */

#ifndef __BOOTLOADER_H__
#define __BOOTLOADER_H__

#ifdef _cplusplus
    extern "C" {
#endif

#include <string.h>
#include "RN8213.h"
#include "uflash.h"
#include "crc.h"
#include "uSystemInit.h"
        
#define IAP_PACK_MAX_SIZE     (1600)
#define IAP_PACK_MAX_UNIT     (250+2)

#define IAP_FLAG_IDLE       0xFFFFFFFF
#define IAP_FLAG_START      0x55513579
#define IAP_FLAG_RECEIVED   0xAAA02468

typedef struct
{
    uint32_t IapFlag;
    uint16_t packlen;
    uint16_t packsize;
    uint16_t softcrc;
    uint16_t ackflag;
    uint8_t resev[2];
    uint8_t crc[2];
}sIapParam;

typedef struct
{
    uint32_t map[49];    // bit map 最多49*4=196*8=1568包
    uint16_t packs;      // 包数
    uint8_t crc[2];
}sIapBitMap;


int32_t IapBootProcess(void);
int32_t GetIapBitMap(uint8_t *pbuf, uint16_t len);
int32_t IapReceiveStart(uint8_t *pbuf, uint8_t len);
int32_t ReceiveAppData(uint8_t *pbuf, uint8_t len, uint8_t *ack);

#ifdef _cplusplus
}
#endif

#endif   /* __BOOTLOADER_H__ */

