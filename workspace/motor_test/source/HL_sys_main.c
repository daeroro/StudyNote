/** @file HL_sys_main.c 
*   @brief Application main file
*   @date 07-July-2017
*   @version 04.07.00
*
*   This file contains an empty main function,
*   which can be used for the application.
*/

/* 
* Copyright (C) 2009-2016 Texas Instruments Incorporated - www.ti.com  
* 
* 
*  Redistribution and use in source and binary forms, with or without 
*  modification, are permitted provided that the following conditions 
*  are met:
*
*    Redistributions of source code must retain the above copyright 
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the 
*    documentation and/or other materials provided with the   
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


/* USER CODE BEGIN (0) */
/* USER CODE END */

/* Include Files */

#include "HL_sys_common.h"

/* USER CODE BEGIN (1) */
#include "HL_gio.h"
#include "HL_system.h"
#include "HL_sci.h"
#include "HL_etpwm.h"
#include <stdio.h>
#include <string.h>
/* USER CODE END */

/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/

/* USER CODE BEGIN (2) */


#define     UART    sciREG1
#define     ETPWM   etpwmREG1

uint32 value;
uint32 pwm_duty[3] = {1000, 1500, 2000};
uint32 receive_data;
uint32 tmp;

void sci_display(sciBASE_t *sci, uint8 *text, uint32 len);
void pwm_init(void);
void wait(int delay);

/* USER CODE END */

int main(void)
{
/* USER CODE BEGIN (3) */
    char buf[256];
    unsigned int buf_len;



    gioInit();
 //   etpwmInit();
    sciInit();

    sprintf(buf, "SCI configure Success!\n\r\0");
    buf_len = strlen(buf);
    sci_display(UART, (uint8 *)buf, buf_len);

    etpwmStartTBCLK();
    wait(10000);

    for(;;)
    {
        sprintf(buf, "PWM Success!\n\r\0");
        buf_len = strlen(buf);
        sci_display(UART, (uint8 *)buf, buf_len);

        tmp = sciReceiveByte(UART);

 //       pwm_init();

        sprintf(buf, "PWM Duty = %d\n\r\0", value);
        buf_len = strlen(buf);
        sci_display(UART, (uint8 *)buf, buf_len);
    }


/* USER CODE END */

    return 0;
}


/* USER CODE BEGIN (4) */

void wait(int delay)
{
    int i;

    for(i = 0; i < delay; i++)
        ;
}

void pwm_init(void)
{
    if(tmp == 1000)
    {
        etpwmSetCmpA(ETPWM, pwm_duty[0]);
        wait(10000);
    }
    if(tmp == 1500)
    {
        etpwmSetCmpA(ETPWM, pwm_duty[1]);
        wait(10000);
    }
    if(tmp == 2000)
    {
        etpwmSetCmpA(ETPWM, pwm_duty[2]);
        wait(10000);
    }
}

void sci_display(sciBASE_t *sci, uint8 *text, uint32 len)
{
    while(len--)
    {
        while((UART->FLR & 0x4) == 4)
            ;
        sciSendByte(UART, *text++);
    }
}

/* USER CODE END */
