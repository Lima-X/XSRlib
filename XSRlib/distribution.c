#include "xoshiro.h"

/* After testing these methods it turns out that they aren't truly random.
   The results that these functions provide don't satisfy me.
   So they will be replaced by the functions that are now already provided in xoshiro.c.
   They will be kept in the source just in case if someone is curious,
   but they aren't compatible with the current source anymore.

   IN THE 1.0 RELEASE THIS FILE WILL BE DELETED */
double dURngDist(double dMax, double dMin, pXSRT64 xsrT64) {
	const double dRange = (dMax - dMin) + (1 / 0x20000000000000p0);
	const double dScale = 1 / dRange;
	const double dLimit = dRange * dScale;

	double dRet;
	do {
		dRet = ((uint64_t)(xsrT64->fn(xsrT64->xsr) >> 11) * (1 / 0x20000000000000p0));
	} while (dRet >= dLimit);

	dRet /= dScale;
	return dRet + dMin;
}
float fURngDist(float fMax, float fMin, pXSRT32 xsrT32) {
	const float fRange = (fMax - fMin) + (1 / 0x1000000p0);
	const float fScale = 1 / fRange;
	const float fLimit = fRange * fScale;

	float fRet;
	do {
		fRet = ((uint32_t)(xsrT32->fn(xsrT32->xsr) >> 8) * (1 / 0x1000000p0));
	} while (fRet >= fLimit);

	fRet /= fScale;
	return fRet + fMin;
}