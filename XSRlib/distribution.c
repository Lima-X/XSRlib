#include "xoshiro.h"

#if (defined(UNIDIST) && (UNIDIST == 1))
	#if (defined(UNIDIST_UINT) && (UNIDIST_UINT == 1))
		#ifdef UNIDIST_UINT64
		uint64_t ui64URngDist(uint64_t ui64Max, uint64_t ui64Min, pXSRT64 xsrT64) {
			uint64_t ui64Ret;
			const uint64_t ui64Range = (ui64Max - ui64Min) + 1;
			const uint64_t ui64Scale = (-1) / ui64Range;
			const uint64_t ui64Limit = ui64Range * ui64Scale;

			do {
				ui64Ret =  xsrT64->fn(xsrT64->xsr);
			} while (ui64Ret >= ui64Limit);

			ui64Ret /= ui64Scale;
			return ui64Ret + ui64Min;
		}
		#endif
		#ifdef UNIDIST_UINT32
		uint32_t ui32URngDist(uint32_t ui32Max, uint32_t ui32Min, pXSRT32 xsrT32) {
			uint32_t ui32Ret;
			const uint32_t ui32Range = (ui32Max - ui32Min) + 1;
			const uint32_t ui32Scale = (-1) / ui32Range;
			const uint32_t ui32Limit = ui32Range * ui32Scale;

			do {
				ui32Ret = xsrT32->fn(xsrT32->xsr);
			} while (ui32Ret >= ui32Limit);

			ui32Ret /= ui32Scale;
			return ui32Ret + ui32Min;
		}
		#endif
	#endif

// Double 52 bits resolution:
// return ((uint64_t)(ui64Ret >> 11) * (1. / 0x20000000000000p0)); // (r >> 11) * 2^(-53)
// 52 bits resolution:
// return ((uint64_t)(ui64Ret >> 12) * (1. / 0x10000000000000p0)); // (r >> 12) * 2^(-52)
// Float 24 bits resolution:
// return ((uint32_t)(ui32Ret >> 8) * (1. / 0x1000000p0)); // (r >> 8) * 2^(-24)
// 23 bits resolution:
// return ((uint32_t)(ui32Ret >> 9) * (1. / 0x800000p0));  // (r >> 9) * 2^(-23)

	/* After testing these methods it turns out that they aren't truly random.
	   The results that these functions provide don't satisfy me.
	   So they will be replaced by the lowerstanding functions,
	   They will be kept in the source just in case tho but disabled. */
	#if 0
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
	#endif

	#if (defined(UNIDIST_REAL) && (UNIDIST_REAL == 1))
	double fnDURngDist(pXSRT64 xsrT64) {
		// 53 bits resolution:
		return (uint64_t)(xsrT64->fn(xsrT64->xsr) >> 11) * (1 / 0x20000000000000p0); // (r >> 11) * 2^(-53)
		// 52 bits resolution:
		return (uint64_t)(xsrT64->fn(xsrT64->xsr) >> 12) * (1 / 0x10000000000000p0);  // (r >> 12) * 2^(-52)
	}
	float fnFURngDist(pXSRT32 xsrT32) {
		// 24 bits resolution:
		return (uint32_t)(xsrT32->fn(xsrT32->xsr) >> 8) * (1. / 0x1000000p0); // (r >> 8) * 2^(-24)
	    // 23 bits resolution:
		return (uint32_t)(xsrT32->fn(xsrT32->xsr) >> 9) * (1. / 0x800000p0);  // (r >> 9) * 2^(-23)
	}
	#endif
#endif