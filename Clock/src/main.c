
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
int delayvalue = 4500;

void fakeassdelay(){
	int i = 0;
	for(i=0;i<=delayvalue;i++){

	}
}
int main (void)
{
	XBR2 |= 0x40;
	P1_B4 = 0;
	P1_B5 = 0;
	P1_B6 = 0;
	while (1) {
		P1_B4 = 1;
		P1_B5 = 1;
		P1_B6 = 1;
		if (!P0_B2){
			delayvalue = delayvalue + 1000;
			P1_B4 = 0;
		}
		else if (!P0_B3){
			delayvalue = delayvalue - 1000;
			P1_B5 = 0;
		}
			fakeassdelay();
			P1_B4 = 1;
			P1_B5 = 1;
			P1_B6 = 1;
			fakeassdelay();
			P1_B6 = 0;
			fakeassdelay();
	}
}






//hay raffi sexy mama
