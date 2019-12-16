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
/*
	MY_FLASH_SetSectorAddrs(11, 0x081C0000);
	MY_FLASH_ReadN(0,IP_READ,4,DATA_TYPE_8);
*/
  //==========CREATE & START all lwIP Services========//
	 MX_LWIP_Init(192,168,1,205); //SetUp with IP ADRESS read from Flash
	 UDP_init(192,168,1,38); //INIT the UDP Session (Partner IP ADRESS)
	 httpd_init();//start the web Server
	 myCGIinit();//initialise the CGI handlers
	 mySSIinit();//initialise the SSI handlers
   //================================================//

char UART_IN[10];

	  /* Infinite loop */
	  for(;;)
	  {

		  UART_recive;





		  //HAL_UART_Transmit(&huart6, UART_transmit,10,10);
		  UART_IN;
		  UART_transmit[0]=0xFF;
		  UART_transmit[1]=0x01;
		  UART_transmit[2]=0x02;
		  UART_transmit[3]=analogIN[0];
		  UART_transmit[4]=analogIN[1];
		  UART_transmit[5]=0x10;
		  UART_transmit[6]=0x10;
		  UART_transmit[7]=0x10;
		  UART_transmit[8]=0x10;
		  UART_transmit[9]=0x10;



		OSCmessageINTSend("/VALUE/Level/CH1/preVCA",  23, analogIN[0]);
		OSCmessageINTSend("/VALUE/Level/CH2/preVCA",  23, analogIN[1]);
		OSCmessageINTSend("/VALUE/Level/CH1/postVCA", 24, analogIN[0]);
		OSCmessageINTSend("/VALUE/Level/CH2/postVCA", 24, analogIN[1]);

	    osDelay(10);
	  }

}

