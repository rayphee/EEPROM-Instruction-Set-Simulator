
//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <SI_EFM8BB3_Register_Enums.h>                // SFR declarations

//-----------------------------------------------------------------------------
// main() Routine
// ----------------------------------------------------------------------------
//
// Note: the software watchdog timer is not disabled by default in this
// example, so a long-running program will reset periodically unless
// the timer is disabled or your program periodically writes to it.
//
// Review the "Watchdog Timer" section under the part family's datasheet
// for details. To find the datasheet, select your part in the
// Simplicity Launcher and click on "Data Sheet".
//
//-----------------------------------------------------------------------------
#include "InitDevice.c";
void writeOpcodePin0(bool);
void writeOpcodePin1(bool);
void writeParamPin0(bool);
void writeParamPin1(bool);
void writeParamPin2(bool);
void writeParamPin3(bool);
void writeClockPin(bool);
void delayBS(int);

int delayvalue = 4500;

void delayBS(){
	int i = 0;
	for(i=0;i<=delayvalue;i++){

	}
}
void writeParamPin0(bool i){
	P3_B1 = i;
}
void writeParamPin1(bool i){
	P3_B2 = i;
}
void writeParamPin2(bool i){
	P3_B3 = i;
}
void writeParamPin3(bool i){
	P3_B4 = i;
}
void writeOpCodePin0(bool i){
	P2_B4 = i;
}
void writeOpCodePin1(bool i){
	P2_B5 = i;
}
void writeClockPin(bool i){
	P1_B6 = i;
}
void issueInstruction(char opcode, char param){
	delayBS(4500);
	writeClockPin(false);
	delayBS(2250);
	writeOpcodePin0(opcode & 1);
	writeOpcodePin1(opcode & 2);
	writeParamPin0(param & 1);
	writeParamPin1(param & 2);
	writeParamPin2(param & 4);
	writeParamPin3(param & 8);
	delayBS(2250);
	writeClockPin(true);
	delayBS(4500);
	writeClockPin(false);
	delayBS(4500);
	writeClockPin(true);
}

void main(){
	issueInstruction(0x00, 0x00); // acc now 0x00
	issueInstruction(0x03, 0x01); // acc now 0x01
	issueInstruction(0x01, 0x02); // acc now 0x11
	issueInstruction(0x02, 0x02); // acc now 0x10
	issueInstruction(0x03, 0x01); // acc now 0x11 (again);
}
int main (void)
{
	while (1) {}                             // Spin forever
}
