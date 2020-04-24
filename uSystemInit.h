/*
 * $Id: uSystemInit.h  001  2020.4.2 11:04:55 yangap $
 */

#ifndef __USYSTEM_INIT_H__
#define __USYSTEM_INIT_H__


#define WDTClear() do{WDT->EN = 0xbb;}while(0)

#ifdef _cplusplus
    extern "C" {
#endif

#include "definesystem.h"
#include "sysctrl.h"

void uSystemInit(void);
        
#ifdef _cplusplus
}
#endif

#endif   /* __USYSTEM_INIT_H__ */

