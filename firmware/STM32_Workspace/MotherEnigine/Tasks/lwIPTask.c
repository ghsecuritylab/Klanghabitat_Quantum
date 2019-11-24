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

uint8_t IP_READ[4];
DAC_HandleTypeDef hdac;
DAC_HandleTypeDef huart6;

void lwIPTask(void const * argument){

	MY_FLASH_SetSectorAddrs(11, 0x081C0000);
	MY_FLASH_ReadN(0,IP_READ,4,DATA_TYPE_8);

  //==========CREATE & START all lwIP Services========//
	 MX_LWIP_Init(IP_READ[0],IP_READ[1],IP_READ[2],IP_READ[3]); //SetUp with IP ADRESS read from Flash
	 UDP_init(192,168,1,36); //INIT the UDP Session (Partner IP ADRESS)
	 httpd_init();//start the web Server
	 myCGIinit();//initialise the CGI handlers
	 mySSIinit();//initialise the SSI handlers
   //================================================//

char UART_IN[10];

	  /* Infinite loop */
	  for(;;)
	  {


		  HAL_UART_Receive(&huart6, UART_IN,10,10);
		  HAL_UART_Transmit(&huart6, UART_transmit,10,10);
		  UART_IN;
		  UART_transmit[0]=0xFF;
		  UART_transmit[1]=0x01;
		  UART_transmit[2]=0x02;
		  UART_transmit[3]=ADC1_RAW[0];
		  UART_transmit[4]=ADC1_RAW[1];
		  UART_transmit[5]=0x10;
		  UART_transmit[6]=0x10;
		  UART_transmit[7]=0x10;
		  UART_transmit[8]=0x10;
		  UART_transmit[9]=0x10;

		HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, 1000);

		OSCmessageINTSend("/VALUE/Level/CH1/preVCA",  23, ADC1_RAW[0]);
		OSCmessageINTSend("/VALUE/Level/CH2/preVCA",  23, ADC1_RAW[1]);
		OSCmessageINTSend("/VALUE/Level/CH1/postVCA", 24, ADC1_RAW[0]);
		OSCmessageINTSend("/VALUE/Level/CH2/postVCA", 24, ADC1_RAW[1]);

	    osDelay(10);
	  }

}

