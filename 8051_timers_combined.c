#include <reg51.h>		

/*
* Program Description:
* This program utilizes Timer Mode 1 (16-bit Timer) in 8051 microcontroller.
* Timer 1 and Timer 0 are configured for 16-bit mode, with maximum count of 65536.
*/

// Bit positions for Timer 1 (TR1) and Timer 0 (TR0)
#define TCON_TR1_POS 6	
#define TCON_TR0_POS 4

// Definitions for 16-bit mode
#define TMOD_TIMER0_M0 0	
#define TMOD_TIMER1_M0 4
 
// Global interrupt enable
#define IE_EA 7

// Enable Timer 1 & 0 overflow interrupt
#define IE_ET1 3	
#define IE_ET0 1	


/* 
* Function: initializeTimers
* Configures Timer 0 and Timer 1 for 16-bit mode and sets initial values.
*/
void initializeTimers() {
	/* Configure Timer 0 and Timer 1 for 16-bit mode */
	TMOD |= (1 << TMOD_TIMER0_M0) | (1 << TMOD_TIMER1_M0);

	// Set initial values for Timers: higher and lower bits 
	TH1 = 0xCC;	
	TL1 = 0xCC;	
	TH0 = 0xA0;	
	TL0 = 0xA1;	

	// Start both timers 
	TCON |= (1 << TCON_TR1_POS) | (1 << TCON_TR0_POS);
}

void main() {
	// Clear bit 0 of Port 1
	P1 &= ~(1 << 0); 
	// Initialize Port 1 output to 0
	P1 = 0; 
	
	P2 &= ~(1 << 0);
	P2 = 0; 
	
//enable global interrupt and timers overflow interrupt
	IE |= (1 << IE_EA); 
	IE |= (1 << IE_ET1); 
	IE |= (1 << IE_ET0); 
	
 // Initialize and start timers
	initializeTimers();

	while (1) {
		// Do other tasks here
	}
}

// ISR for Timer 1 overflow
void Timer1_ISR() interrupt 3 {
	// Toggle LED on Port 1, bit 0
	P1 ^= (1 << 0); 

	// Reload Timer 1 count values 
	TH1 = 0xCC;
	TL1 = 0xCC;
}

void Timer0_ISR() interrupt 1 {
	P2 ^= (1 << 0);
	TH0 = 0xA0;
	TL0 = 0xA1;
}