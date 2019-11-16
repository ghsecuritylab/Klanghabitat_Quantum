/*
 * UART_IO.c
 *
 *  Created on: 16.11.2019
 *      Author: christiansager
 */
#include "main.h"
#include "UART_IO.h"

void UARTRECIVER(){

	 int start = 0;
	 int offset = 0;
	   	    	     for(int i = 0; i<10;i++){
	   	    	    	 if (UART_RECIVE[i] == 0xFF){
	   	    	    		   start = i; //found start index @start
	   	    	    		   break;
	   	    	    	 }
	   	    	     }

	   	    	     if (start == 0){
	   	    	    	 for (int i = 0; i< 10;i++){
	   	    	    		UARTDATA[i] = UART_RECIVE[i];
	   	    	    	 }
	   	    	     }
	   	    	     else if (start != 0){
	   	        	     for (int i = 0; i< 10;i++){
	   	        	    	UARTDATA[i] = UART_RECIVE[i+start];
	   	        	    	 offset = i+1;
	   	        	    	 if (i+start == 9){
	   	        	    		 break;
	   	        	    	 }
	   	        	     }
	   	        	     for (int i = 0; i< 10;i++){
	   	        	    	UARTDATA[i+offset] = UART_RECIVE[i];
	   	        	    	 if (i+offset == 9){
	   	        	    		 break;
	   	        	    	 }
	   	        	     }
	   	    	     }

}
