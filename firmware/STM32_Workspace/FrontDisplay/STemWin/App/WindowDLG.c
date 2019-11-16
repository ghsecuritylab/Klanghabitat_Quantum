/*********************************************************************
*                                                                    *
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
*                                                                    *
**********************************************************************
*                                                                    *
* C-file generated by:                                               *
*                                                                    *
*        GUI_Builder for emWin version 5.40                          *
*        Compiled Jun 22 2017, 10:13:26                              *
*        (c) 2017 Segger Microcontroller GmbH & Co. KG               *
*                                                                    *
**********************************************************************
*                                                                    *
*        Internet: www.segger.com  Support: support@segger.com       *
*                                                                    *
**********************************************************************
*/

// USER START (Optionally insert additional includes)
// USER END
#include "GUI_App.h"
#include "DIALOG.h"
#include "usb_device.h"
#include "math.h"
#include "main.h"
#include "settings.h"
#include "GUI.h"
#include "stm32f4xx_hal.h"
#include "GuiElements/AudioMeter.h"
#include "GuiElements/Controlls.h"
#include "UART_IO.h"
/*********************************************************************
*
*       Defines
*
**********************************************************************
*/

char Value;
#define ID_WINDOW_0  (GUI_ID_USER + 0x00)

uint8_t byte;

UART_HandleTypeDef huart6;
//UART_HandleTypeDef huart6;
// USER START (Optionally insert additional defines)
// USER END



TS_StateTypeDef TS_State;

uint32_t avCH1;
uint32_t maxCH1;

int16_t  ringBufferSim[810];
uint16_t samples[250];
int p = 0;


//Interface Variablen
int X = 0; //TOUCH X
int Y = 0; //TOUCH Y

int adc1 = 0;
float adc1_ist = 0;
float adc1_volt = 0;
float adc1_db = 0;
float adc1_db_negative = 0;



int adc2 = 0;
int watchdog= 0;
int left = 0;
int right = 0;
int pots[6];



char str[12];

begin = 0;
int refresh =0;
float smooth= 0;
float peaksmooth= 0;
int once = 0;
int Y_Right = 0;
int Y_Left = 0;

int levelIN1 = 0;
int levelIN2 = 0;
uint8_t buffer[10];
/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _GetImageById
*/


// USER START (Optionally insert additional static code)


// USER END

/*********************************************************************
*
*       _cbDialog
*///

static void _cbDialog(WM_MESSAGE * pMsg) {


	HAL_GPIO_TogglePin(GPIOA, LAMP1_Pin);
    HAL_GPIO_TogglePin(GPIOG, LAMP2_Pin);


    UARTRECIVER(); //Recive Data from UART --> UARTDATA

    adc1 = UARTDATA[3];


  // USER END


  switch (pMsg->MsgId) {
  case WM_PAINT:
    break;
  default:
    WM_DefaultProc(pMsg);

  }

	  GUI_SetBkColor(GUI_DARKGRAY);
	  GUI_DCACHE_Clear(0);
	  GUI_Clear();


     drawWaveFormUartRight(0,240,adc1);
     drawWaveFormUartLeft(450,240,adc1);

     adc1_ist = adc1;
	 adc1_volt = (adc1/255.00)*3.6;
	 adc1_db = 10*log(adc1_volt/3.0);

	 if (adc1_db<=-300.0) {adc1_db = -300;}


	 if(adc1_db-smooth<0){
		 smooth = smooth+(0.1*(adc1_db-smooth));
	 }
	 else {
		 smooth = smooth+(0.15*(adc1_db-smooth));
	 }

	 if(adc1_db-peaksmooth<0){
		 peaksmooth = peaksmooth+(0.01*(adc1_db-peaksmooth));
	 }
	 else {
		 peaksmooth = peaksmooth+(1*(adc1_db-peaksmooth));
	 }




  	  BSP_TS_GetState(&TS_State);
  	  	  if(TS_State.touchX[0]>30 && TS_State.touchX[0]<750 && TS_State.touchY[0] > 30 && TS_State.touchY[0] < 450){
     	      X = TS_State.touchX[0];
     		  Y = TS_State.touchY[0];
     		  HAL_GPIO_TogglePin(GPIOG, LAMP4_Pin);

     		 if(X<400){
     		  Y_Left  = Y;
     		 }
     		 if(X>400){
     		  Y_Right  = Y;
     		 }
  	  	  }


	 drawBar (390, 90,300+peaksmooth,300+smooth, "");
	 drawBar (440, 90,300+peaksmooth,300+smooth, "");

	 drawDashedLine(10, Y_Left, 350, Y_Left);
	 drawDashedLine(450, Y_Right, 790, Y_Right);

	 ENCODER_UPDATE(); //Display Encoder Values


/*==================================================*/

GUI_SetFont(&GUI_Font24B_1);

GUI_SetColor(GUI_GRAY);

}





/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       CreateWindow
*/



WM_HWIN CreateWindow(void) {
  //WM_HWIN hWin;
  WM_HWIN hParent;

 // hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
  //hParent = WM_CreateWindow(0, 0, 1, 1, WM_CF_SHOW, _cbDialog, 0); //THIS IS WORKING QUITE OK!!!
  hParent = WM_CreateWindow(200, 0, 1, 1,WM_CF_SHOW, _cbDialog, 0);
 // WM_Paint(hWin);

  WM_MULTIBUF_Enable(1);

  //return hWin;
  return hParent;
}

// USER START (Optionally insert additional public code)


// USER END

/*************************** End of file ****************************/
