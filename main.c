//In darkness it takes more time to discharge and hence, the blink rate reduces.
// The code was adapted from:
//http://playground.arduino.cc/Learning/LEDSensor
//Coded by: Rohit Gupta on 16th June`13 at 0127hrs
//Uses seperate LED for detection and blinking
//EDITS: Now it can display the effect and response on the same LED!
// Adapted from the design idea-http://www.edn.com/design/power-management/4315194/Video-Design-Idea-LED-senses-and-displays-ambient-light-intensity
#include<msp430g2452.h>
#define LEDN BIT0
#define LEDP BIT1
void LEDF()
{
	P1DIR|=(LEDP+LEDN);
	P1OUT&=~(LEDP+LEDN);
	P1OUT|=LEDP;
	P1OUT&=~LEDN;
}
void LEDR()
{
	P1OUT|=LEDN;
	P1OUT&=~LEDP;
}
void delay_ms(unsigned int ms ) //Delay_MS
{
      unsigned int i;
      for (i = 0; i<= ms; i++)
        __delay_cycles(1000); //Built-in function that suspends the execution for 500 cycles
}
void main()
{   int k=0;
	WDTCTL = WDTPW + WDTHOLD;
	P1DIR|=BIT0;
	P1OUT&=~BIT0;

	while(1)
	{
    P1DIR|=(LEDP+LEDN);
	P1OUT&=~(LEDP+LEDN);
	LEDR();
	P1DIR&=~LEDN;
	for ( k = 0; k < 50000; k++)
	{
	    if ( (P1IN&LEDN)==0)
	    	break;
	}
	LEDF();
	delay_ms(k/20);
	P1OUT=0;
	delay_ms(k/20);
	
	}
}
