#include "xoshiro.h"

/* Test Stuff (Don't touch that)
   This is just for debugging purposes... and stuff.

   IN THE 1.0 RELEASE THIS FILE WILL BE REPLACED BY PROPER DOCUMENTATION */
int main() {
	// 10-111-00000001-00000001-00000000001
	uint32_t ParamA = XSRParamA(256, XSR_RANDOM_ALL, 1, 1, 1);
	uint32_t ParamB = XSRParamB(XSR_RANDOM_SM, 1);
	pXSRT test = fnAllocXSR(13167812262513478261, ParamA, ParamB);

	uint64_t a = 0;
	for (uint32_t i = 0; i < (uint16_t)-1; i++)
		a = XSRGen(XSR_SS, test);
	for (uint32_t i = 0; i < (uint16_t)-1; i++)
		a = XSRUDist(XSR_D64, 9000, 4, XSR_SS, test);

	double b = 0;
	for (uint32_t i = 0; i < (uint16_t)-1; i++)
		b = XSRFDist(XSR_DDIST, test);

	XSRJump(XSR_LJUMP, test);
	XSRJump(XSR_SJUMP, test);

	fnDeAllocXSR(test);
	return 0;
}