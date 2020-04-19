#include "xoshiro.h"

#include <Windows.h>
#include <iostream>
#include <chrono>

#define LOOP1 0xfffffff
#define RETRY1 0x8

#define LOOP2 0xffffff
#define RETRY2 0x80

/* Test Stuff (Don't touch that)
   This is just for debugging purposes... and stuff.

   IN THE 1.0 RELEASE THIS FILE WILL BE REPLACED BY PROPER DOCUMENTATION */
int main() {
	std::cout << ":========: XSRlib Performance Test START :========:\n\n";

	// Chrono Declarations
	std::chrono::high_resolution_clock::time_point cT0, cT1;
	long long cDC;
	double dTAvg = 0;
	double dTAvg2 = 0;

	// XSR Test Declarations
	pXSRT test;
	uint64_t num;

	// Setup: 10-111-00000001-00000001-00000000001 / 1-0000001
	sXSRPA ParamA = { XSR_128, XSR_RANDOM_ALL, 1, 1, 1 };
	sXSRPB ParamB = { XSR_RANDOM_SM, 1 };
	test = fnAllocXSR(1316783262513478261, ParamA, ParamB);
	num = XSRGen(XSR_SS, test);

	fnRelocXSR(test, 35647173752273, ParamA, ParamB);
	num = XSRGen(XSR_SS, test);

	fnRelocXSR(test, 35647173752273, { XSR_512, XSR_RANDOM_ALL, 129, 129, 1025 } , ParamB);
	num = XSRGen(XSR_SS, test);
	fnDelocXSR(test);

	// Performance Test
	test = fnAllocXSR(13167832262513478261, ParamA, ParamB);
	std::cout << "XSR StdNumGen Slow Timer:\n";
	for (int i = 0; i < RETRY1; i++) {
		cT0 = std::chrono::high_resolution_clock::now();
		for (uint32_t i = 0; i < (uint32_t)LOOP1; i++)
			num = XSRGen(XSR_SS, test);

		cT1 = std::chrono::high_resolution_clock::now();
		cDC = std::chrono::duration_cast<std::chrono::nanoseconds>(cT1 - cT0).count();
		dTAvg += (double)cDC / (uint32_t)LOOP1;
		if (i % 4 == 0)
			std::cout << "\t" << (double)cDC / (uint32_t)LOOP1 << "ns, ";
		else if (i % 4 == 3)
			std::cout << (double)cDC / (uint32_t)LOOP1 << "ns,\n";
		else
			std::cout << (double)cDC / (uint32_t)LOOP1 << "ns, ";
	}
	dTAvg /= RETRY1;
	std::cout << "URID Time AVG: " << dTAvg << "ns\n\n";

	std::cout << "XSR StdNumGen Fast Timer:\n";
	for (int i = 0; i < RETRY2; i++) {
		cT0 = std::chrono::high_resolution_clock::now();
		for (uint32_t i = 0; i < (uint32_t)LOOP2; i++)
			num = XSRGen(XSR_SS, test);

		cT1 = std::chrono::high_resolution_clock::now();
		cDC = std::chrono::duration_cast<std::chrono::nanoseconds>(cT1 - cT0).count();
		dTAvg2 += (double)cDC / (uint32_t)LOOP2;
		if (i % 4 == 0)
			std::cout << "\t" << (double)cDC / (uint32_t)LOOP2 << "ns, ";
		else if (i % 4 == 3)
			std::cout << (double)cDC / (uint32_t)LOOP2 << "ns,\n";
		else
			std::cout << (double)cDC / (uint32_t)LOOP2 << "ns, ";
	}
	dTAvg2 /= RETRY2;
	std::cout << "URID Time AVG: " << dTAvg2 << "ns\n\n";
	std::cout << "URID Time EAVG: " << (dTAvg2 + dTAvg) / 2 << "ns\n";
	std::cout << "URID Time Diff: " << dTAvg2 - dTAvg << "ns\n\n";

/*	std::cout << "XSR Setup Timer:\n";
	for (int i = 0; i < RETRY; i++) {
		cT0 = std::chrono::high_resolution_clock::now();
		test = fnAllocXSR(1316783262513478261 * (i + 1), ParamA, ParamB);

		cT1 = std::chrono::high_resolution_clock::now();
		cDC = std::chrono::duration_cast<std::chrono::microseconds>(cT1 - cT0).count();
		dTAvg += cDC;
		fnDelocXSR(test);
		std::cout << "\tSetuptime: " << cDC << "us\n";
	}
	dTAvg /= RETRY;
	std::cout << "\t\tSetuptime AVG: " << dTAvg << "us\n\n";
	dTAvg = 0;	*/

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
	std::cout << ":========: XSRlib Performance Test END   :========:\n";
	system("pause");
	return 0;
}