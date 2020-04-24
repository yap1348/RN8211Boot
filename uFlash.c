/*
 * $Id: uflash.c 001 2020.4.2 11:04:50 yangap $
 */

#include "uflash.h"
#include "uSystemInit.h"

int32_t uFlashCheck(uint32_t addr, uint8_t* pbuf, uint32_t len)
{
    uint8_t tmpdata;
    uint32_t i;
    
    for(i=0; i<len; i++)
    {
        tmpdata = *(READ_FLASH + addr + i);
        if(tmpdata != pbuf[i])
        {
            return 0;
        }
    }
    return 1;
}


int32_t uFlashReadSub(uint32_t addr, uint8_t* pbuf, uint32_t len)
{
    uint32_t i;
    
    for(i=0; i<len; i++)
    {
        pbuf[i] = *(READ_FLASH + addr + i);
    }
    return 1;
}

int32_t uFlashRead(uint32_t addr, uint8_t* pbuf, uint32_t len)
{
    uint8_t i;
    
    if((0==len) || (addr+len >= FLASH_MEMORY_SIZE))
    {
        return 0;
    }
    
    for(i=0; i<3; i++)
    {
        WDTClear();
        uFlashReadSub(addr, pbuf, len);
        if(1 == uFlashCheck(addr, pbuf, len))
        {
            break;
        }
        else
        {
            DelayMs(5);
        }
    }
    if(i >= 3)
    {
        return 0;
    }    
    return 1;
}


//int32_t uFlashErasePage(uint32_t pg)
//{
//    uint8_t i, j, tmprpt, ret;
//    uint8_t tmpdata;
//    uint32_t tmpaddr = pg*PAGE_UNIT;
//    
//    if(pg >= PAGE_SIZE)
//    {
//        return 0;
//    }

//    for(i=0; i<PAGE_UNIT; i++)
//    {
//        tmpdata = *(READ_FLASH+tmpaddr + i);    // �˵�Ƭ��������Ϊ00
//        if(0x00 != tmpdata)
//        {
//            break;
//        }
//    }
//    if(i < PAGE_UNIT)    // ��ҳδ������ִ�в�������,����ֱ�ӷ���
//    {
//        for(tmprpt=0; tmprpt<3; tmprpt++)
//        {
//            WDTClear();
//            if(flashPageErase(pg))
//            {
//                DelayMs(5);
//                continue;
//            }
//            for(j=0; j<PAGE_UNIT; j++)
//            {
//                tmpdata = *(READ_FLASH + tmpaddr + j);
//                if(0x00 != tmpdata)    // �˵�Ƭ��������Ϊ00
//                {
//                    break;
//                }
//            }
//            if(j >= PAGE_UNIT)
//            {
//                break;
//            }
//        }
//        if(tmprpt >= 3)
//        {
//            return 0;
//        }      
//    }

//    return 1;
//}

int32_t uFlashErasePage(uint32_t pg)
{
    uint8_t tmprpt;
//    uint8_t tmpdata;
//    uint32_t tmpaddr = pg*PAGE_UNIT;
    
    if(pg >= PAGE_SIZE)
    {
        return 0;
    }

    for(tmprpt=0; tmprpt<3; tmprpt++)
    {
        WDTClear();
        if(flashPageErase(pg))
        {
            DelayMs(5);
            continue;
        }
    }
    if(tmprpt >= 3)
    {
        return 0;
    }      

    return 1;
}


// ֻ֧��ҳ��̵�flashд�뺯��
int32_t uFlashWriteSub(uint32_t addr, uint8_t* pbuf, uint32_t len)
{
    uint8_t i;

    if((0 == len) || (len > PAGE_UNIT) || (0 != (addr&(PAGE_UNIT-1))))
    {
        return 0;
    }
    
    for(i=0; i<3; i++)
    {
        WDTClear();
        if(uFlashErasePage(addr >> 7))
        {
            continue;
        }
        if(flashProgram(addr , (uint32_t)pbuf , len))
        {
            continue;
        }
        if(1 == uFlashCheck(addr, pbuf, len))
        {
            break;
        }
    }
    if(i >= 3)
    {
        return 0;
    }
    return 1;
}


#if 0
// ֧���ֽڱ�� �ֱ�̵�flash��д�뺯�� 
int32_t uFlashWriteSub(uint32_t addr, uint8_t* pbuf, uint32_t len)
{
    uint8_t i;

    if((0 == len) || (len > PAGE_UNIT))
    {
        return 0;
    }
    
    for(i=0; i<3; i++)
    {
        WDTClear();

        if(flashProgram(addr , (uint32_t)pbuf , len))
        {
            continue;
        }
        if(1 == uFlashCheck(addr, pbuf, len))
        {
            break;
        }
    }
    if(i >= 3)
    {
        return 0;
    }
    return 1;
}
#endif


// ֻ֧��ҳ��̵�flashд�뺯��
int32_t uFlashWrite(uint32_t addr, uint8_t *pbuf, uint32_t len)
{
    uint8_t *tmpp = pbuf;
    uint32_t tmpaddr = addr;
    uint32_t tmplen = len;
    uint8_t tmppos;
    uint8_t tmplens;
    uint8_t tmparry[PAGE_UNIT];
    
    if((0==tmplen) || (tmpaddr+tmplen >= FLASH_MEMORY_SIZE))
    {
        return 0;
    }

    while(tmplen)
    {
        WDTClear();
        if(0 == (tmpaddr&(PAGE_UNIT-1)))       // ��ʼ��ַΪ1ҳ����ʼ��ַ
        {
            if(tmplen > PAGE_UNIT)
            {
                tmplens = PAGE_UNIT;
            }
            else
            {
                tmplens = tmplen;
            }

            if(uFlashWriteSub(tmpaddr, tmpp, tmplens))
            {
                tmpaddr += tmplens;
                tmplen -= tmplens;
                tmpp += tmplens;
            }
            else
            {
                return 0;
            }
        }
        else             // ��ʼ��ַ����1ҳ����ʼ��ַ
        {
            tmppos = tmpaddr&(PAGE_UNIT-1);
            if((tmpaddr&(0xFFFFFFFF-PAGE_UNIT+1)) != ((tmpaddr+tmplen)&(0xFFFFFFFF-PAGE_UNIT+1)))
            {
                tmplens = PAGE_UNIT - (tmpaddr&(PAGE_UNIT-1));
            }
            else
            {
                tmplens = tmplen;
            }
            if(0 == uFlashRead(tmpaddr&(0xFFFFFFFF-PAGE_UNIT+1), tmparry, tmppos))
            {
                return 0;
            }
            memcpy(&tmparry[tmppos], tmpp, tmplens);
            if(uFlashWriteSub(tmpaddr&(0xFFFFFFFF-PAGE_UNIT+1), tmparry, PAGE_UNIT))
            {
                tmpaddr += tmplens;
                tmplen -= tmplens;
                tmpp += tmplens;
            } 
            else
            {
                return 0;
            }
        }
    }
    return 1;
}


#if 0
// ֧���ֽڱ�� �ֱ�̵�flash��д�뺯��
int32_t uFlashWrite(uint32_t addr, uint8_t *pbuf, uint32_t len)
{
    uint8_t *tmpp = pbuf;
    uint32_t tmpaddr = addr;
    uint32_t tmplen = len;
    uint8_t tmppos;
    uint8_t tmplens;
    
    if((0==tmplen) || (tmpaddr+tmplen >= FLASH_MEMORY_SIZE))
    {
        return 0;
    }

    while(tmplen)
    {
        WDTClear();
        if(0 == (tmpaddr&(PAGE_UNIT-1)))       // ��ʼ��ַΪ1ҳ����ʼ��ַ
        {
            if(tmplen > PAGE_UNIT)
            {
                tmplens = PAGE_UNIT;
            }
            else
            {
                tmplens = tmplen;
            }
            if(0 == uFlashErasePage(addr >> 7)) 
            {
                return 0;
            }
            if(uFlashWriteSub(tmpaddr, tmpp, tmplens))
            {
                tmpaddr += tmplens;
                tmplen -= tmplens;
                tmpp += tmplens;
            }
            else
            {
                return 0;
            }
        }
        else             // ��ʼ��ַ����1ҳ����ʼ��ַ
        {
            tmppos = tmpaddr&(PAGE_UNIT-1);
            if((tmpaddr&(0xFFFFFFFF-PAGE_UNIT+1)) != ((tmpaddr+tmplen)&(0xFFFFFFFF-PAGE_UNIT+1)))
            {
                tmplens = PAGE_UNIT - (tmpaddr&(PAGE_UNIT-1));
            }
            else
            {
                tmplens = tmplen;
            }

            if(uFlashWriteSub(tmpaddr, tmpp, tmplens))
            {
                tmpaddr += tmplens;
                tmplen -= tmplens;
                tmpp += tmplens;
            } 
            else
            {
                return 0;
            }
        }
    }
    return 1;
}
#endif

