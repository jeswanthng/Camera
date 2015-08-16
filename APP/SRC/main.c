/**
 *	 @mainpage Camera Monitor
 *	 @author Jeswanth NG (JNG)
 *
 */
#include "lpc17xx.h"
#include "type.h"
#include "uart.h"
#include "camera.h"

extern volatile uint32_t UART3Count;
extern volatile uint8_t UART3Buffer[BUFSIZE];
extern volatile uint32_t UART1Count;
extern volatile uint8_t UART1Buffer[BUFSIZE];

unsigned char pic[525];


void UART1_Sendchar(char c)
{
	while( (LPC_UART1->LSR & LSR_THRE) == 0 );	// Block until tx empty

	LPC_UART1->THR = c;
}

char UART1_Getchar()
{
	char c;
	while( (LPC_UART1->LSR & LSR_RDR) == 0 );  // Nothing received so just block
	c = LPC_UART1->RBR; // Read Receiver buffer register
	return c;
}
void UART1_PrintString(char *pcString)
{
	int i = 0;
	// loop through until reach string's zero terminator
	while (pcString[i] != 0)
	{
		UART1_Sendchar(pcString[i]); // print each character
		i++;
	}
}

void UART3_Sendchar(char c)
{
	while( (LPC_UART3->LSR & LSR_THRE) == 0 );	// Block until tx empty

	LPC_UART3->THR = c;
}

char UART3_Getchar()
{
	char c;
	while( (LPC_UART3->LSR & LSR_RDR) == 0 );  // Nothing received so just block
	c = LPC_UART3->RBR; // Read Receiver buffer register
	return c;
}
void UART3_PrintString(char *pcString)
{
	int i = 0;
	// loop through until reach string's zero terminator
	while (pcString[i] != 0)
	{
		UART3_Sendchar(pcString[i]); // print each character
		i++;
	}
}






/*****************************************************************************
**   Main Function  main()
This program has been test on Keil LPC1700 board.
*****************************************************************************/
int main (void)
{
  unsigned int i=0;
  unsigned char val,count=0;
  unsigned char respBuff[20];
  unsigned int bufferSize;
  SystemInit();

  UARTInit(3, 19200);	/* baud rate setting */
  UARTInit(1, 19200);	/* baud rate setting */

	//snapPicLatest();

//  snap();

  while(1)
  {
  	val = UART3_Getchar();
	respBuff[i]=val;
	if(val == 0x23 )
	{
		count++;
		if(count >= 2)
		break;
	}
	i++;
	
  }

   
 
  
 for(i=0x01;i<respBuff[11];i++)
  {
  	bufferSize = 525;
	GetSpecificPackage(i);
		
	while(bufferSize)
	{
		UART1_Sendchar(UART3_Getchar());
		bufferSize--;	
	}
	
  }

  GetSpecificPackage(respBuff[11]);
  while(1)
  {
  	val = UART3_Getchar();
	if(val ==0xFF)
	{
		UART1_Sendchar(val);
		val = UART3_Getchar();
		if(val == 0xD9)
		{
			UART1_Sendchar(val);
			break;
		}
	}	
  }
  
  
  while (1) 
  {				
	val = UART1_Getchar();
	UART1_Sendchar(val);		
  }
}

/*****************************************************************************
**                            End Of File
*****************************************************************************/
