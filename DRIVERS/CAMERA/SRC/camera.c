/**
 *	 @file  camera.c
 *	 @brief Functions to interface with the serial digital camera camera
 *
 */

#include "camera.h"
#include "uart.h"
//#include "common.h"

void CameraSnapPic(void)	
{
    UART3_Sendchar(0x55);	 
    UART3_Sendchar(0x48);	 
    UART3_Sendchar(0x00);
    UART3_Sendchar(0x32);
    UART3_Sendchar(0x00);
    UART3_Sendchar(0x02);
    UART3_Sendchar(0x23);

}

void CameraGetSpecificPackage(UINT8 packageNumber)
{
	UART3_Sendchar(0x55);	 //85
    UART3_Sendchar(0x45);	 //
    UART3_Sendchar(0x00);
    UART3_Sendchar(packageNumber);
   	UART3_Sendchar(0x00);
   	UART3_Sendchar(0x23);		
}

/*
//Valid only for 115200 baud rate we will get continoud data in these command
void snapPicLatest()
{
 	unsigned char count;
 
 for(count=0;count<16;count++)
	{
		UART3_Sendchar(0x5A);	 
	}

	 for(count=0;count<16;count++)
	{
		UART3_Sendchar(0x4D);	 
	}


		
	UART3_Sendchar(0x5A);	 //85
    UART3_Sendchar(0x4D);	 //
    UART3_Sendchar(0x01);
    UART3_Sendchar(0x01);
   UART3_Sendchar(0x01);
   UART3_Sendchar(0x5A);
   UART3_Sendchar(0x23);
}
*/