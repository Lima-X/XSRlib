#include "xoshiro.h"

#include <Windows.h>
#include <iostream>
#include <chrono>

#define LOOP 0x7fffffff
#define RETRY 16

/* Test Stuff (Don't touch that)
   This is just for debugging purposes... and stuff.

   IN THE 1.0 RELEASE THIS FILE WILL BE REPLACED BY PROPER DOCUMENTATION */
int main() {
	// Chrono Declarations
	std::chrono::high_resolution_clock::time_point cT0, cT1;
	long long cDC;
	double dTAvg = 0;
	pXSRT test;

	// Setup: 10-111-00000001-00000001-00000000001 / 1-0000001
	uint32_t ParamA = XSRParamA(256, XSR_RANDOM_ALL, 1, 1, 1);
	uint32_t ParamB = XSRParamB(XSR_RANDOM_SM, 1);
	std::cout << "XSR Setup Timer:\n";
	for (int i = 0; i < RETRY; i++) {
		cT0 = std::chrono::high_resolution_clock::now();
		test = fnAllocXSR(13167832262513478261 * i, ParamA, ParamB);

		cT1 = std::chrono::high_resolution_clock::now();
		cDC = std::chrono::duration_cast<std::chrono::microseconds>(cT1 - cT0).count();
		dTAvg += cDC;
		fnDelocXSR(test);
		std::cout << "\tSetuptime: " << cDC << "us\n";
	}
	dTAvg /= RETRY;
	std::cout << "\t\tSetuptime AVG: " << dTAvg << "us\n\n";
	dTAvg = 0;
	test = fnAllocXSR(13167832262513478261, ParamA, ParamB);

	// Normal 64bit Generator
	uint64_t num;
	std::cout << "XSR StdNumGen Timer:\n";
	for (int i = 0; i < 16; i++) {
		cT0 = std::chrono::high_resolution_clock::now();
		for (uint32_t i = 0; i < (uint32_t)LOOP; i++)
			num = XSRGen(XSR_SS, test);

		cT1 = std::chrono::high_resolution_clock::now();
		cDC = std::chrono::duration_cast<std::chrono::nanoseconds>(cT1 - cT0).count();
		dTAvg += (double)cDC / (uint32_t)LOOP;
		std::cout << "\tUInttime: " << (double)cDC / (uint32_t)LOOP << "ns\n";
	}
	dTAvg /= RETRY;
	std::cout << "\t\tUInttime AVG: " << dTAvg << "ns\n\n";
	dTAvg = 0;


/*	// Dist 64bit Generator
	cT0 = std::chrono::high_resolution_clock::now();
	for (uint32_t i = 0; i < (uint32_t)-1; i++)
		num = XSRUDist(XSR_D64, 9000, 4, XSR_SS, test);
	cT1 = std::chrono::high_resolution_clock::now();
	cDC = std::chrono::duration_cast<std::chrono::nanoseconds>(cT1 - cT0).count();
	std::cout << "dist (ns avg): " << (double)cDC / (uint32_t)-1 << std::endl;

	// FloatingPoint 53bit Generator
	double b = 0;
	cT0 = std::chrono::high_resolution_clock::now();
	for (uint32_t i = 0; i < (uint32_t)-1; i++)
		b = XSRFDist(XSR_DDIST, test);
	cT1 = std::chrono::high_resolution_clock::now();
	cDC = std::chrono::duration_cast<std::chrono::nanoseconds>(cT1 - cT0).count();
	std::cout << "fdist (ns avg): " << (double)cDC / (uint32_t)-1 << std::endl; */

//	XSRJump(XSR_LJUMP, test);
//	XSRJump(XSR_SJUMP, test);

	fnDelocXSR(test);
	Sleep(-1);
	return 0;
}