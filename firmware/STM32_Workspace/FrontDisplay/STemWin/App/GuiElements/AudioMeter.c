/*
 * AudioMeter.c
 *
 *  Created on: 16.11.2019
 *      Author: christiansager
 */
#include "GUI_App.h"
#include "DIALOG.h"
#include "GUI.h"

int16_t  ringBufferRight[400];
int16_t  ringBufferLeft[400];

void drawWaveFormUartRight(int x,int y, int adc){
	uint32_t lineStart,lineEnd;

	 for(int i=0; i<350;i++){
	    ringBufferRight[i] = ringBufferRight[i+1];
	    }

		for(int i=0; i<350;i++){

		    ringBufferRight[350] = adc;

		    GUI_SetColor( GUI_ORANGE );
	        lineStart = y - (ringBufferRight[i]/2);
	        lineEnd = lineStart + (ringBufferRight[i]);
	        GUI_DrawVLine(x+i,lineStart, lineEnd);
	     }
}

void drawWaveFormUartLeft(int x,int y, int adc){
	uint32_t lineStart,lineEnd;

	 for(int i=0; i<350;i++){
	    ringBufferLeft[i] = ringBufferLeft[i+1];
	    }

		for(int i=0; i<350;i++){
		    ringBufferLeft[350] = adc;

		    GUI_SetColor( GUI_ORANGE );
		    lineStart = y - (ringBufferLeft[i]/2);
	        lineEnd = lineStart + (ringBufferLeft[i]);
	        GUI_DrawVLine(350+x-i,lineStart, lineEnd);
	     }

}

void drawBar (int pos_x, int pos_y, float PeakVal,float AvVal,  const char * s ){
	/*DRAW RASTER*/
	int lastLine = 0;
	int bottomY = 0;
	int rednes = 0;

	GUI_SetColor(GUI_LIGHTGRAY);
	GUI_SetFont(&GUI_Font20_1);
	GUI_GotoXY(pos_x-40, pos_y-25);

    GUI_DispFloatMin((AvVal-200)/4, 2);


	for (int i=0; i<30; i++){
		lastLine = pos_y+(i*10);
		GUI_DrawHLine(lastLine+0,pos_x, pos_x+10);
		GUI_DrawHLine(lastLine+5,pos_x, pos_x+5);
	}
	GUI_DrawHLine(lastLine+10,pos_x, pos_x+10);
	bottomY = lastLine+10;

	rednes = AvVal *100 /bottomY;

	/*DRAW INDICATOR AV*/

	GUI_DrawGradientV(pos_x-30, pos_y, pos_x-1, bottomY- AvVal -1, 0xFF505050, 0xFF505050);
	GUI_DrawGradientV(pos_x-30, bottomY- AvVal, pos_x-1, bottomY, 0xFFFF6E00, 0xFFFFA500);

	if (PeakVal >298){PeakVal=298;}
	/*DRAW INDICATOR PEAK*/
	GUI_SetColor(GUI_RED);

	GUI_DrawHLine(bottomY-PeakVal-4,pos_x-30, pos_x-1);
	GUI_DrawHLine(bottomY-PeakVal-3,pos_x-30, pos_x-1);
	GUI_DrawHLine(bottomY-PeakVal-2,pos_x-30, pos_x-1);
	GUI_DrawHLine(bottomY-PeakVal-1,pos_x-30, pos_x-1);
	GUI_DrawHLine(bottomY-PeakVal,pos_x-30, pos_x-1);
}

void drawFloat (int pos_x, int pos_y, float val, const char * s, const char * h){
			  GUI_GotoXY(pos_x, pos_y);
	  		  GUI_DispFloatMin(val, 1);

			  GUI_SetFont(&GUI_Font24B_1);
	  		  if(val < 10.0 && val >= 0) {GUI_DispStringAt(s, 80+pos_x, 10+pos_y);}
	  		  else if (val >= 10.0 || val<0){GUI_DispStringAt(s, 105+pos_x, 10+pos_y);}
	  		  GUI_SetFont(&GUI_Font32B_1);
	  		  GUI_DispStringAt(h, pos_x, pos_y-35);

	  	  }
