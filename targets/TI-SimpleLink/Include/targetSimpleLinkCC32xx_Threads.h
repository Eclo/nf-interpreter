//
// Copyright (c) 2019 The nanoFramework project contributors
// Portions Copyright (c) Texas Instruments Incorporated.  All rights reserved.
// See LICENSE file in the project root for full license information.
//

#ifndef _SIMPLELINK_CC32XX_THREADS_H_
#define _SIMPLELINK_CC32XX_THREADS_H_

#include <ti/drivers/net/wifi/simplelink.h>

/* POSIX Header files */
#include <semaphore.h>
#include <pthread.h>
#include <time.h>

#include <stdlib.h>
// #include <string.h>
// #include <stdint.h>


#define SL_STOP_TIMEOUT         (200)

#define UART_PRINT Report
#define DBG_PRINT  Report
// #define ERR_PRINT(x) Report("Error [%d] at line [%d] in function [%s]  \n\r",\
//                                                                 x, __LINE__, \
//                                                                  __FUNCTION__)
#define ERR_PRINT(x) 

/* check the error code and handle it */
#define ASSERT_ON_ERROR(error_code) \
    { \
        if(error_code < 0) \
        { \
            ERR_PRINT(error_code); \
            return error_code; \
        } \
    }
    
#define SET_STATUS_BIT(status_variable, bit) status_variable |= (1 << (bit))

#define CLR_STATUS_BIT(status_variable, bit) status_variable &= ~(1 << (bit))

#define GET_STATUS_BIT(status_variable, bit)    \
    (0 != (status_variable & (1 << (bit))))

#define APPS_WDT_START_KEY          0xAE42DB15
#define HWREG(x) (*((volatile unsigned long *)(x)))

typedef enum
{
    /* If this bit is set: Network Processor is powered up */
    AppStatusBits_NwpInit = 0,    
    /* If this bit is set: the device is connected to 
    the AP or client is connected to device (AP) */
    AppStatusBits_Connection = 1,  
    /* If this bit is set: the device has leased IP to
    any connected client */
    AppStatusBits_IpLeased = 2,   
    /* If this bit is set: the device has acquired an IP */
    AppStatusBits_IpAcquired = 3, 
    /* If this bit is set: the SmartConfiguration process is 
    started from SmartConfig app */
    AppStatusBits_SmartconfigStart = 4,   
    /* If this bit is set: the device (P2P mode) found any 
    p2p-device in scan */
    AppStatusBits_P2pDevFound = 5,       
    /* If this bit is set: the device (P2P mode) found any 
    p2p-negotiation request */
    AppStatusBits_P2pReqReceived = 6,    
    /* If this bit is set: the device(P2P mode) 
    connection to client(or reverse way) is failed */
    AppStatusBits_ConnectionFailed = 7,   
    /* If this bit is set: the device has completed the ping operation */
    AppStatusBits_PingDone = 8,   
    /* If this bit is set: the device has acquired an IPv6 address */
    AppStatusBits_Ipv6lAcquired = 9,  
    /* If this bit is set: the device has acquired an IPv6 address */
    AppStatusBits_Ipv6gAcquired = 10,  
    
    AppStatusBits_AuthenticationFailed = 11,
    AppStatusBits_ResetRequired = 12,
}AppStatusBits;

// nF Control block for SimpleLink
typedef struct nanoFramework_ControlBlock_t
{
    
    uint32_t status;/* SimpleLink Status */
    
    // uint32_t gatewayIP;/* Network Gateway IP address */
    
    // uint8_t connectionSSID[SL_WLAN_SSID_MAX_LENGTH + 1];/* Connection SSID */
    
    // uint8_t ssidLen;/* Connection SSID */
    
    // uint8_t connectionBSSID[SL_WLAN_BSSID_LENGTH];/* Connection BSSID */
    
}nanoFramework_CB;

extern nanoFramework_CB nF_ControlBlock;


#endif //_SIMPLELINK_CC32XX_THREADS_H_
