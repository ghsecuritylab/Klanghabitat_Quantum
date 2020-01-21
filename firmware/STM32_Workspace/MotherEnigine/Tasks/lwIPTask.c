/*
 * lwIPTask.c
 *
 *  Created on: 08.11.2019
 *      Author: christiansager
 */

#include "main.h"
#include "lwip/apps/httpd.h"
#include "lwip.h"
#include <string.h>
#include "UDP_SEND_RECIVE.h"
#include "webserver.h"
#include "MY_FLASH.h"
#include "RelaisControl.h"
uint8_t IP_READ[4];
DAC_HandleTypeDef hdac;
UART_HandleTypeDef huart6;

uint8_t errors= 0;

void lwIPTask(void const * argument){
/*
	MY_FLASH_SetSectorAddrs(11, 0x081C0000);
	MY_FLASH_ReadN(0,IP_READ,4,DATA_TYPE_8);
*/
  //==========CREATE & START all lwIP Services========//
	 MX_LWIP_Init(192,168,1,205); //SetUp with IP ADRESS read from Flash
	 UDP_init(192,168,1,42); //INIT the UDP Session (Partner IP ADRESS)
	 httpd_init();//start the web Server
	 myCGIinit();//initialise the CGI handlers
	 mySSIinit();//initialise the SSI handlers
   //================================================//

char UART_IN[10];



	  /* Infinite loop */
	  for(;;)
	  {







		  //HAL_UART_Transmit(&huart6, UART_transmit,10,10);
		  UART_IN;
		  //UART_transmit[0]=0xFF;
		  //UART_transmit[1]=0x01;
		  //UART_transmit[2]=0x02;
		  //UART_transmit[3]=voltageIn1MAX*100;
		  //UART_transmit[4]=voltageIn2MAX*100;
		  //UART_transmit[5]=0x10;
		  //UART_transmit[6]=0x10;
		  //UART_transmit[7]=0x10;
		  //UART_transmit[8]=0x10;
		  //UART_transmit[9]=0x10;

		 if (UDP_RECIVE[11] == 1){
			 Bypass(bypass);
		 }
		 if (UDP_RECIVE[11] == 0){
			 Bypass(activate);
		 }

		OSCmessageINTSend("/VALUE/Level/CH1/RMS",  20, voltageRMS[0]*30);
		OSCmessageINTSend("/VALUE/Level/CH2/RMS",  20, voltageRMS[1]*30);
		OSCmessageINTSend("/VALUE/Level/CH3/RMS",  20, voltageRMS[2]*30);
		OSCmessageINTSend("/VALUE/Level/CH4/RMS",  20, voltageRMS[3]*30);
		OSCmessageINTSend("/VALUE/Level/CH5/RMS",  20, voltageRMS[4]*30);
		OSCmessageINTSend("/VALUE/Level/CH6/RMS",  20, voltageRMS[5]*30);


		OSCmessageINTSend("/VALUE/ERROR/ER1____",  20, errors);
		//OSCmessageINTSend("/VALUE/Level/CH1/postVCA", 24, analogIN[0]);
		//OSCmessageINTSend("/VALUE/Level/CH2/postVCA", 24, analogIN[1]);

	    osDelay(10);
	  }

}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
	errors = errors+1;

  /* Prevent unused argument(s) compilation warning */
	  HAL_UART_Receive_DMA(&huart6, UART_recive,10);
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_UART_ErrorCallback can be implemented in the user file.
   */
}
