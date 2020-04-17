#include "xoshiro.h"
#include <chrono>
#include <iostream>
#include <Windows.h>

/* Test Stuff (Don't touch that)
   This is just for debugging purposes... and stuff.

   IN THE 1.0 RELEASE THIS FILE WILL BE REPLACED BY PROPER DOCUMENTATION */
int main() {
	auto cT0 = std::chrono::high_resolution_clock::now();
	// 10-111-00000001-00000001-00000000001 / 1-0000001
	uint32_t ParamA = XSRParamA(256, XSR_RANDOM_ALL, 1, 1, 1);
	uint32_t ParamB = XSRParamB(XSR_RANDOM_SM, 1);
	pXSRT test = fnAllocXSR(13167832262513478261, ParamA, ParamB);
	auto cT1 = std::chrono::high_resolution_clock::now();
	auto cDC = std::chrono::duration_cast<std::chrono::nanoseconds>(cT1 - cT0).count();
	std::cout << "Setuptime (ns): " << cDC << std::endl;

	// Normal 64bit Generator
	uint64_t a = 0;
	cT0 = std::chrono::high_resolution_clock::now();
	for (uint32_t i = 0; i < (uint32_t)-1; i++)
		a = XSRGen(XSR_SS, test);
	cT1 = std::chrono::high_resolution_clock::now();
	cDC = std::chrono::duration_cast<std::chrono::nanoseconds>(cT1 - cT0).count();
	std::cout << "Gen (ns avg): " << (double)cDC / (uint32_t)-1 << std::endl;

	// Dist 64bit Generator
	cT0 = std::chrono::high_resolution_clock::now();
	for (uint32_t i = 0; i < (uint32_t)-1; i++)
		a = XSRUDist(XSR_D64, 9000, 4, XSR_SS, test);
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
	std::cout << "fdist (ns avg): " << (double)cDC / (uint32_t)-1 << std::endl;

	XSRJump(XSR_LJUMP, test);
	XSRJump(XSR_SJUMP, test);

	fnDeAllocXSR(test);
	Sleep(100000000);
	return 0;
}