//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <SI_EFM8BB3_Register_Enums.h>                  // SFR declarations
#include "InitDevice.h"
// $[Generated Includes]
// [Generated Includes]$

//-----------------------------------------------------------------------------
// forward declarations for pin writes and delay
// ----------------------------------------------------------------------------
void writeOpcodePin0(bool);
void writeOpcodePin1(bool);
void writeParamPin0(bool);
void writeParamPin1(bool);
void writeParamPin2(bool);
void writeParamPin3(bool);
void writeClockPin(bool);
void delayBS(int);
// amount of loops to delay, by default (changed by buttons)
int delayconstant = 2250;
// Delay by spinning
void delayBS(int delay) {
	int max = delay * delayconstant;
	int i = 0;
	for (i = 0; i <= max; i++) {

	}
}
// Actually write to each pin's bit-addressable-memory location
void writeParamPin0(bool i) {
	P3_B1 = i;
}
void writeParamPin1(bool i) {
	P3_B2 = i;
}
void writeParamPin2(bool i) {
	P3_B3 = i;
}
void writeParamPin3(bool i) {
	P3_B4 = i;
}
void writeOpcodePin0(bool i) {
	P2_B4 = i;
	//P1_B4 = i;
}
void writeOpcodePin1(bool i) {
	P2_B5 = i;
	//P1_B5 = i;
}
void writeClockPin(bool i) {
	P1_B6 = i;
}
// instruction latency is two cycles, so this outputs two clock cycles while driving the control lines
void issueInstruction(char opcode, char param) {
	delayBS(2);
	// falling edge if necessary
	writeClockPin(false);
	delayBS(1);
	// delay of 1 to put the data transition in the middle of the low time
	writeOpcodePin0(opcode & 1);
	writeOpcodePin1(opcode & 2);
	writeParamPin0(param & 1);
	writeParamPin1(param & 2);
	writeParamPin2(param & 4);
	writeParamPin3(param & 8);
	delayBS(1);
	// rising edge 1
	writeClockPin(true);
	delayBS(2);
	writeClockPin(false);
	// the second rising and falling edge pair
	delayBS(2);
	writeClockPin(true);
}
int main(void) {
	int i;
	// Call hardware initialization routine provided by configurator.
	// this routine sets output drivers to push-pull mode
	enter_DefaultMode_from_RESET();
	// enable output through the crossbar
	XBR2 |= 0x40;
	while (1) {
		// buttons are active low, so this is a pressed button condition
		if (!P0_B2) {
			// slow by increasing the delay time
			delayconstant = delayconstant + 1000;
			// LED debugging
			P1_B4 = 0;
			P0_B2 = 1;
		// ditto but it's the speed up button
		} else if (!P0_B3) {
			delayconstant = delayconstant - 1000;
			// LED debugging
			P1_B5 = 0;
			P0_B3 = 1;
		}
//		issueInstruction(0x00, 0x00); // acc now 0x00 AND 0		//0
//		issueInstruction(0x03, 0x01); // acc now 0x01 CONST 1	//0
//		issueInstruction(0x01, 0x02); // acc now 0x11 OR 2		//2
//		issueInstruction(0x02, 0x02); // acc now 0x10 PLUS 2	//4
//		issueInstruction(0x03, 0x01); // acc now 0x11 (again); CONST 1 // 0
		// a running rabbit. Clear the accumulator, then set bits in succession
		issueInstruction(0x03, 0x00); // 0000
		issueInstruction(0x01, 0x01); // 0001
		issueInstruction(0x01, 0x02); // 0011
		issueInstruction(0x01, 0x04); // 0111
		issueInstruction(0x01, 0x08); // 1111
		issueInstruction(0x03, 0x00); // 0000 (clear again)
// $[Generated Run-time code]
// [Generated Run-time code]$
	}
}
