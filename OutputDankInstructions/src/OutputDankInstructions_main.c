//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <SI_EFM8BB3_Register_Enums.h>                  // SFR declarations
#include "InitDevice.h"
// $[Generated Includes]
// [Generated Includes]$

//-----------------------------------------------------------------------------
// main() Routine
// ----------------------------------------------------------------------------
void writeOpcodePin0(bool);
void writeOpcodePin1(bool);
void writeParamPin0(bool);
void writeParamPin1(bool);
void writeParamPin2(bool);
void writeParamPin3(bool);
void writeClockPin(bool);
void delayBS(int);

int delayconstant = 2250;

void delayBS(int delay) {
	int max = delay * delayconstant;
	int i = 0;
	for (i = 0; i <= max; i++) {

	}
}
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
	P1_B4 = i;
}
void writeOpcodePin1(bool i) {
	P2_B5 = i;
	P1_B5 = i;
}
void writeClockPin(bool i) {
	P1_B6 = i;
}
void issueInstruction(char opcode, char param) {
	delayBS(2);
	writeClockPin(false);
	delayBS(1);
	writeOpcodePin0(opcode & 1);
	writeOpcodePin1(opcode & 2);
	writeParamPin0(param & 1);
	writeParamPin1(param & 2);
	writeParamPin2(param & 4);
	writeParamPin3(param & 8);
	delayBS(1);
	writeClockPin(true);
	delayBS(2);
	writeClockPin(false);
	delayBS(2);
	writeClockPin(true);
}
int main(void) {
	// Call hardware initialization routine
	enter_DefaultMode_from_RESET();
	XBR2 |= 0x40;
	while (1) {
		if (!P0_B2) {
			delayconstant = delayconstant + 1000;
			P1_B4 = 0;
		} else if (!P0_B3) {
			delayconstant = delayconstant - 1000;
			P1_B5 = 0;
		}
		issueInstruction(0x00, 0x00); // acc now 0x00
		issueInstruction(0x03, 0x01); // acc now 0x01
		issueInstruction(0x01, 0x02); // acc now 0x11
		issueInstruction(0x02, 0x02); // acc now 0x10
		issueInstruction(0x03, 0x01); // acc now 0x11 (again);
// $[Generated Run-time code]
// [Generated Run-time code]$
	}
}
