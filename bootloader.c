/*
 * $Id: bootloader.c  001  2020.4.2 11:04:55 yangap $
 */

#include "bootloader.h"


int32_t StoreIapParam(uint8_t *pbuf, uint8_t len)
{
    MakeCheck(pbuf, len);
    uFlashWriteSub(FLASH_BOOT_PARAM1, pbuf, len);
    uFlashWriteSub(FLASH_BOOT_PARAM2, pbuf, len);
    return 1;
}

int32_t LoadIapParam(uint8_t *pbuf, uint16_t len)
{
    uint8_t i;
    
    for(i=0; i<2; i++)
    {
        if(1 == uFlashRead(FLASH_BOOT_PARAM1, pbuf, len))
        {
            if(CheckData(pbuf, len))
            {
                return 1;
            }
        }
        DelayMs(5);
    }

    for(i=0; i<2; i++)
    {
        if(1 == uFlashRead(FLASH_BOOT_PARAM2, pbuf, len))
        {
            if(CheckData(pbuf, len))
            {
                return 1;
            }
        }
        DelayMs(5);
    }    

    return 0;
}


void ClearIapParam(void)
{
    sIapParam tmpIap;

    memset((uint8_t *)&tmpIap, 0, sizeof(sIapParam));
    StoreIapParam((uint8_t *)&tmpIap, sizeof(sIapParam));
}


int32_t StoreBitMap(uint8_t *pbuf, uint16_t len)
{
    MakeCheck(pbuf, len);
    uFlashWrite(FLASH_BOOT_PARAM1_BIT, pbuf, len);
    uFlashWrite(FLASH_BOOT_PARAM2_BIT, pbuf, len);
    return 1;
}

int32_t GetIapBitMap(uint8_t *pbuf, uint16_t len)
{
    if(1 == uFlashRead(FLASH_BOOT_PARAM1_BIT, pbuf, len))
    {
        if(CheckData(pbuf, len))
        {
            return 1;
        }
    }
    DelayMs(5);

    if(1 == uFlashRead(FLASH_BOOT_PARAM1_BIT, pbuf, len))
    {
        if(CheckData(pbuf, len))
        {
            return 1;
        }
    }
    DelayMs(5);
    
    if(1 == uFlashRead(FLASH_BOOT_PARAM2_BIT, pbuf, len))
    {
        if(CheckData(pbuf, len))
        {
            return 1;
        }
    }
    DelayMs(5); 

    if(1 == uFlashRead(FLASH_BOOT_PARAM2_BIT, pbuf, len))
    {
        if(CheckData(pbuf, len))
        {
            return 1;
        }
    }

    return 0;
}


int32_t ClearIapBitMap(void)
{
    sIapBitMap tmpBitMap;
    
    memset((uint8_t *)&tmpBitMap, 0, sizeof(sIapBitMap)-2);
    StoreBitMap((uint8_t *)&tmpBitMap, sizeof(sIapBitMap));
    return 1;
}

int32_t CheckAppRomData(uint16_t packlen, uint16_t packsize, uint16_t crc, uint8_t bkflag)
{
    uint32_t tmpbuf[PAGE_UNIT>>2];
    uint16_t tmpcrc = 0xFFFF;
    uint32_t tmpaddr;
    uint16_t tmpsize = (packlen*packsize)/PAGE_UNIT;      // 校验时化成128字节作为一部分的形式
    uint8_t tmplen = (packlen*packsize)%PAGE_UNIT;
    uint16_t i;
    
    if(0x55 == bkflag)
    {
        tmpaddr = FLASH_APP_BACK_BASE;
    }
    else
    {
        tmpaddr = FLASH_APP_BASE;
    }
    
    for(i=0; i<tmpsize; i++)
    {
        WDTClear();
        uFlashRead(tmpaddr, (uint8_t *)tmpbuf, PAGE_UNIT);
        tmpcrc = Caculfcs16((uint8_t *)tmpbuf, PAGE_UNIT, tmpcrc);
        tmpaddr += PAGE_UNIT;
    }
    if(0 != tmplen)
    {
        uFlashRead(tmpaddr, (uint8_t *)tmpbuf, tmplen);               // 不足128个字节的部分
        tmpcrc = Caculfcs16((uint8_t *)tmpbuf, tmplen, tmpcrc);
        tmpaddr += tmplen;
    }
    tmpcrc ^= 0xFFFF;
    if(crc == tmpcrc)
    {
        return 1;
    }
    
    return 0;
}

int32_t UpdateAppData(uint16_t packlen, uint16_t packsize)
{
    uint32_t tmpbuf[PAGE_UNIT>>2];
    uint32_t tmpaddrdes = FLASH_APP_BASE;
    uint32_t tmpaddrsrc = FLASH_APP_BACK_BASE;
    uint16_t tmpsize = (packlen*packsize)/PAGE_UNIT;      // 校验时化成128字节作为一部分的形式
    uint8_t tmplen = (packlen*packsize)%PAGE_UNIT;

    for(uint16_t i=0; i<tmpsize; i++)
    {   
        WDTClear();
        uFlashRead(tmpaddrsrc, (uint8_t *)tmpbuf, PAGE_UNIT);
        uFlashWriteSub(tmpaddrdes, (uint8_t *)tmpbuf, PAGE_UNIT);
        tmpaddrsrc += PAGE_UNIT;
        tmpaddrdes += PAGE_UNIT;
    }
    if(0 != tmplen)
    {
        uFlashRead(tmpaddrsrc, (uint8_t *)tmpbuf, tmplen);
        uFlashWriteSub(tmpaddrdes, (uint8_t *)tmpbuf, tmplen);
        tmpaddrsrc += tmplen;
        tmpaddrdes += tmplen;
    }
    return 1;
}


int32_t IapBootProcess(void)
{
    sIapParam tmpIap;
    
    if(LoadIapParam((uint8_t *)&tmpIap, sizeof(sIapParam)))
    {
        if(IAP_FLAG_RECEIVED != tmpIap.IapFlag)
        {
            return 0;
        }
        
        if(tmpIap.packlen*tmpIap.packsize > FLASH_APP_SIZE)
        {
            
            return 0;
        }

        if(0 == CheckAppRomData(tmpIap.packlen, tmpIap.packsize, tmpIap.softcrc, 0x55))
        {
            ClearIapParam();
            return 0;
        }
        
        UpdateAppData(tmpIap.packlen, tmpIap.packsize);    // 搬运代码
        
        if(1 == CheckAppRomData(tmpIap.packlen, tmpIap.packsize, tmpIap.softcrc, 0x00))
        {
            ClearIapParam();
            return 1;         // 正常升级程序返回
        }        
    }
    return 0;   // 升级参数校验不正确，认为没有升级操作
}


int32_t IapReceiveStart(uint8_t *pbuf, uint8_t len)
{
    uint16_t tmplen = pbuf[0]|(pbuf[1]<<8);
    uint16_t tmpsize = pbuf[2]|(pbuf[3]<<8);
    sIapParam tmpIap;
    
    if((tmpsize > IAP_PACK_MAX_SIZE) || (tmpsize*tmplen > FLASH_APP_SIZE))   // 升级参数不合理
    {
        return 0;
    }
    tmpIap.IapFlag = IAP_FLAG_START;
    tmpIap.packlen = tmplen;
    tmpIap.packsize = tmpsize;
    tmpIap.softcrc = pbuf[4]|(pbuf[5]<<8);
    tmpIap.ackflag = pbuf[6];
    StoreIapParam((uint8_t *)&tmpIap, sizeof(sIapParam));
    
    ClearIapBitMap();
    return 1;
}


int32_t ReceiveAppData(uint8_t *pbuf, uint8_t len, uint8_t *ack)
{
    sIapBitMap tmpBitMap;
    sIapParam tmpIap;
    uint8_t *tmpp = (uint8_t *)&tmpBitMap;
    uint16_t tmppacks = pbuf[0]|(pbuf[1]<<8);
    uint16_t tmpbyte;
    uint8_t tmpbit;
    uint8_t i, j;
    
    if((0 == LoadIapParam((uint8_t *)&tmpIap, sizeof(sIapParam))) && (IAP_FLAG_START != tmpIap.IapFlag))   // 未发起升级请求
    {
        return 0;
    }  
    *ack = tmpIap.ackflag;

    if((tmppacks >= tmpIap.packsize) || ((len-2) != tmpIap.packlen))
    {
        return 0;
    }

    if(0 == GetIapBitMap((uint8_t *)&tmpBitMap, sizeof(sIapBitMap)))  // BitMap
    {
//        ClearIapBitMap();
        return 0;
    }
    
    tmpbyte = tmppacks/8;
    tmpbit = tmppacks%8;    
    if(tmpp[tmpbyte] & (0x01<<tmpbit))          // 此包数据已经接收，不再处理
    {
        return 1;
    }

    if(uFlashWrite(FLASH_APP_BACK_BASE+tmppacks*tmpIap.packlen, &pbuf[2], tmpIap.packlen))
    {
        tmpp[tmpbyte] |= (0x01<<tmpbit);
        tmpBitMap.packs++;
        StoreBitMap((uint8_t *)&tmpBitMap, sizeof(sIapBitMap));
    }
    
    if(tmpBitMap.packs >= tmpIap.packsize)
    {
        tmpbyte = (tmpIap.packsize-1)/8;
        tmpbit = tmpIap.packsize%8;            
        for(i=0; i<tmpbyte; i++)
        {
            if(0xFF != tmpp[i])
            {
                break;
            }
        }
        if(i >= tmpbyte)
        {
            
            for(j=0; j<tmpbit; j++)
            {
                if(0 == (tmpp[tmpbyte] & (0x01<<j)))
                {
                    break;
                }
            }
            if(j >= tmpbit)
            {
                if(1 == CheckAppRomData(tmpIap.packlen, tmpIap.packsize, tmpIap.softcrc, 0x55))
                {
                    tmpIap.IapFlag = IAP_FLAG_RECEIVED;
                    StoreIapParam((uint8_t *)&tmpIap, sizeof(sIapParam));
                    return 2;            // 判断所有数据包接收完毕 且程序备份区数据校验正确
                }
                else
                {
                    ClearIapParam();    // 程序校验区数据校验不正确，初始化升级参数
                }            
            }
        }
//        ClearIapParam();    // 程序校验区数据校验不正确，初始化升级参数
    }
    
    return 1;
}

