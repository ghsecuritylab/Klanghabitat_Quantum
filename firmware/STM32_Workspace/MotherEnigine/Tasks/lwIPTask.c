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
#include "OSC_Lib.h"


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


		 //=========================================================================//
		 //=================CONTROL RELAIS VIA OSC MEASSAGE=========================//
		 if (match("/MotherEngine/Relais/bypassLeft") && OSC_SIGNEDINTEGER ==  1){
			 BypassLeft(bypass);}
		 if (match("/MotherEngine/Relais/bypassLeft") && OSC_SIGNEDINTEGER == 0){
			 BypassLeft(activate);}

		 if (match("/MotherEngine/Relais/bypassRight") && OSC_SIGNEDINTEGER ==  1){
			 BypassRight(bypass);}
		 if (match("/MotherEngine/Relais/bypassRight") && OSC_SIGNEDINTEGER == 0){
			 BypassRight(activate);}

		 if (match("/MotherEngine/Relais/K5") && OSC_SIGNEDINTEGER == 1){
			 HAL_GPIO_WritePin(GPIOG, Relais3_Pin,GPIO_PIN_SET);}
		 if (match("/MotherEngine/Relais/K5") && OSC_SIGNEDINTEGER == 0){
			 HAL_GPIO_WritePin(GPIOG, Relais3_Pin,GPIO_PIN_RESET);}

		 if (match("/MotherEngine/Relais/K6") && OSC_SIGNEDINTEGER == 1){
			 HAL_GPIO_WritePin(GPIOG, Relais4_Pin,GPIO_PIN_SET);}
		 if (match("/MotherEngine/Relais/K6") && OSC_SIGNEDINTEGER == 0){
			 HAL_GPIO_WritePin(GPIOG, Relais4_Pin,GPIO_PIN_RESET);}

		 if (match("/MotherEngine/Relais/K7") && OSC_SIGNEDINTEGER == 1){
			 HAL_GPIO_WritePin(GPIOG, Relais5_Pin,GPIO_PIN_SET);}
		 if (match("/MotherEngine/Relais/K7") && OSC_SIGNEDINTEGER == 0){
			 HAL_GPIO_WritePin(GPIOG, Relais5_Pin,GPIO_PIN_RESET);}

		 if (match("/MotherEngine/Relais/K8") && OSC_SIGNEDINTEGER == 1){
			 HAL_GPIO_WritePin(GPIOG, Relais6_Pin,GPIO_PIN_SET);}
		 if (match("/MotherEngine/Relais/K8") && OSC_SIGNEDINTEGER == 0){
			 HAL_GPIO_WritePin(GPIOG, Relais6_Pin,GPIO_PIN_RESET);}
		 //=========================================================================//


		 if (match("/MotherEngine/VCA1/offset")){DAC_Control(1,2,OSC_SIGNEDINTEGER);}
		 if (match("/MotherEngine/VCA2/offset")){DAC_Control(2,2,OSC_SIGNEDINTEGER);}




		OSCmessageINTSend("/VALUE/Level/CH1/RMS",  20, voltageRMS[0]*30);
		OSCmessageINTSend("/VALUE/Level/CH2/RMS",  20, voltageRMS[1]*30);
		OSCmessageINTSend("/VALUE/Level/CH3/RMS",  20, voltageRMS[2]*30);
		OSCmessageINTSend("/VALUE/Level/CH4/RMS",  20, voltageRMS[3]*30);
		OSCmessageINTSend("/VALUE/Level/CH5/RMS",  20, voltageRMS[4]*30);
		OSCmessageINTSend("/VALUE/Level/CH6/RMS",  20, voltageRMS[5]*30);


		OSCmessageINTSend("/VALUE/ERROR/ER1____",  20, errors);


	    osDelay(10);
	  }

}

int match(char *matchString){
	int i=0;
	int OK=0;
	while(OSC_PATH[i]!='\0'){
		i++;
			if(OSC_PATH[i] == matchString[i]){
				OK = 1;
			}
			else{
				OK = 0;
				break;
			}
	}
	if (OK == 1) return 1;
	else if (OK == 0) return 0;
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
