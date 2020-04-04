#ifndef XSR_HIG
#define XSR_HIG

	#define XSR512 0 // Enables Xoshiro512-64Bit (Default: 0)
	#if (defined(XSR512) && (XSR512 == 1))
		#define UINT 1
		#define REAL 0
		#define JUMP512 0  // Enables Jumpfunctions
	#endif
	#define XSR256 1 // Enables Xoshiro256-64Bit (Default: 1)
	#if (defined(XSR256) && (XSR256 == 1))
		#define UINT 1
		#define REAL 0
		#define JUMP256 0
	#endif
	#define XSR128 1 // Enables Xoshiro128-32Bit (Default: 1)
	#if (defined(XSR128) && (XSR128 == 1))
		#define UINT 1
		#define REAL 0
		#define JUMP128 0
	#endif

	#if ((defined(XSR512) && (XSR512 == 1)) ||\
		 (defined(XSR256) && (XSR256 == 1)) ||\
		 (defined(XSR128) && (XSR128 == 1)))
		#define XSR

		#define UNIDIST 1
		#if ((defined(UINT) && (UINT == 1)) &&\
			 (defined(UNIDIST) && (UNIDIST == 1)))
			#define UNIDIST_UINT 1
			#if ((defined(XSR512) && (XSR512 == 1)) ||\
				 (defined(XSR256) && (XSR256 == 1)))
			#define UNIDIST_UINT64
			#endif
			#if (defined(XSR128) && (XSR128 == 1))
				#define UNIDIST_UINT32
			#endif

			#define UNIDIST_REAL 0
			#if ((defined(XSR512) && (XSR512 == 1)) ||\
				 (defined(XSR256) && (XSR256 == 1)))
				#define UNIDIST_REAL53
			#endif
			#if (defined(XSR128) && (XSR128 == 1))
			#define UNIDIST_REAL24
			#endif
		#endif
	#endif

	#ifdef XSR
	#include "stdint.h"

	enum XSR {
		Gen128,
		Gen256,
		Gen512
	};
	#endif
#endif