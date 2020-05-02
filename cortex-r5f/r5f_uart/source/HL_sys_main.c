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
#include "HL_sci.h"
#include "HL_gio.h"
#include "stdio.h"
#include "time.h"
#include "stdlib.h"


/* USER CODE BEGIN (1) */
#define TSIZE   10
#define UART    sciREG1
/* USER CODE END */
uint8 text[TSIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
// 뒤에 2개가 들어있어야 끝인지 암

void sci_display(sciBASE_t *sci, uint8 *text, uint32 len);
void wait(uint32 time);
/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/

/* USER CODE BEGIN (2) */
/* USER CODE END */





int main(void)
{
    sciInit();
    gioInit();
    gioSetDirection(gioPORTA, 0xffffffff);
    srand(time(NULL));
#if 0
    UART에 값을 입력 받아서 LED를 키는 소스입니다.
#endif
/* USER CODE BEGIN (3) */

/* USER CODE END */

    for(;;)
    {
        sci_display(UART, &text[0], TSIZE);
         // 딜레이를 줘서 보냄(안정적을 처리하기 위해)
    }
    return 0;
}


void sci_display(sciBASE_t *sci, uint8 *text, uint32 len)
{
    uint8 rand_num = rand() % 10 + 1;
    while(len--)
    {
        while((UART->FLR & 0x4) == 4)
            ;
        switch (rand_num)
        {
        case 3:
            gioSetBit(gioPORTA, 4, 1);
            gioSetBit(gioPORTA, 5, 0);
            gioSetBit(gioPORTA, 6, 0);
            break;
        case 6:
            gioSetBit(gioPORTA, 4, 0);
            gioSetBit(gioPORTA, 5, 1);
            gioSetBit(gioPORTA, 6, 0);
            break;
        case 9:
            gioSetBit(gioPORTA, 4, 0);
            gioSetBit(gioPORTA, 5, 0);
            gioSetBit(gioPORTA, 6, 1);
            break;
        }
        sciSendByte(UART, *text++);
        wait(3333333);
    }
}

void wait(uint32 time) // 딜레이 함수 계산 : time이 200일때, (1 / 300000000)*200
{
    int i;
    for(i=0; i<time;i++)
        ;
}




/* USER CODE BEGIN (4) */
/* USER CODE END */
