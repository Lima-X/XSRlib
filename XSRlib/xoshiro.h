#ifndef XSR_HIG
#define XSR_HIG

/////////////////////////////////////////////////////////////////////////////////////

	#define _XSR512 1 // Enables Xoshiro512-64Bit (Default: 0)
	#if (defined(_XSR512) && (_XSR512 == 1))
		#define UINT 1
		#define REAL 0
		#define JUMP512 0  // Enables Jumpfunctions
	#endif
	#define _XSR256 1 // Enables Xoshiro256-64Bit (Default: 1)
	#if (defined(_XSR256) && (_XSR256 == 1))
		#define UINT 1
		#define REAL 0
		#define JUMP256 0
	#endif
	#define _XSR128 1 // Enables Xoshiro128-32Bit (Default: 1)
	#if (defined(_XSR128) && (_XSR128 == 1))
		#define UINT 1
		#define REAL 0
		#define JUMP128 0
	#endif

/////////////////////////////////////////////////////////////////////////////////////

	#if ((defined(_XSR512) && (_XSR512 == 1)) ||\
		 (defined(_XSR256) && (_XSR256 == 1)) ||\
		 (defined(_XSR128) && (_XSR128 == 1)))
		#define XSR

		#define UNIDIST 1
		#if ((defined(UINT) && (UINT == 1)) &&\
			 (defined(UNIDIST) && (UNIDIST == 1)))
			#define UNIDIST_UINT 1
			#if ((defined(_XSR512) && (_XSR512 == 1)) ||\
				 (defined(_XSR256) && (_XSR256 == 1)))
			#define UNIDIST_UINT64
			#endif
			#if (defined(_XSR128) && (_XSR128 == 1))
				#define UNIDIST_UINT32
			#endif

			#define UNIDIST_REAL 0
			#if ((defined(_XSR512) && (_XSR512 == 1)) ||\
				 (defined(_XSR256) && (_XSR256 == 1)))
				#define UNIDIST_REAL53
			#endif
			#if (defined(_XSR128) && (_XSR128 == 1))
			#define UNIDIST_REAL24
			#endif
		#endif
	#endif

/////////////////////////////////////////////////////////////////////////////////////

	#ifdef XSR
	#include <stdint.h>
	#include <string.h>
	#include <stdlib.h>

	enum XSRT {
		XSR512,
		XSR256,
		XSR128
	};
	typedef void* pXSR;

	#endif
#endif