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
#include "HL_sci.h"
#include "HL_gio.h"
#include "HL_etpwm.h"
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
#define UART sciREG1
#define TSIZE   7
uint8 txt_buf[32];
int tb_len;
uint8 txt;

void wait(uint32);
void sciSendText(sciBASE_t * , uint8*, uint32);
/* USER CODE END */

int main(void)
{
/* USER CODE BEGIN (3) */
    sciInit();
    wait(10000);

    gioInit();
    wait(10000);

    etpwmInit();
    wait(10000);

    gioSetDirection(gioPORTA, 0xffffffff);

    for(;;)
    {
//        txt = sciReceiveByte(sciREG1);

        txt = sciReceiveByte(sciREG1);
//        txt_buf[tb_len++] = sciReceiveByte(sciREG1);

            switch(txt)
            {
            case '1':
                //red
                etpwmREG1->CMPA = 0;
                wait(1000);
                //gioSetPort(gioPORTA, 0x01);
                break;
            case '2':
                //yellow
                etpwmREG1->CMPA = 2000;
                wait(1000);
                //gioSetPort(gioPORTA,0x02);
                break;
            case '3':
                //green
                etpwmREG1->CMPA = 500;
                wait(1000);
                //gioSetPort(gioPORTA, 0x04);
                break;
            default:
                break;
            }
            sciSendText(sciREG1, &txt_buf[0], TSIZE);
        //    tb_len = 0;
        //    memset(txt_buf, 0x0, sizeof(txt_buf));


        wait(33333);
    }

/* USER CODE END */

    return 0;
}


/* USER CODE BEGIN (4) */
void wait(uint32 delay)
{
    int i;
    for(i=0; i<delay; i++)
        ;
}

void sciSendText(sciBASE_t* sci, uint8 * text, uint32 len)
{
    while(len--)
    {
        while((sci->FLR & 0x04)==4)
            ;
        sciSendByte(sci, *text++);
    }

}
/* USER CODE END */
