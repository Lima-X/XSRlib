#ifndef XSR_HIG
#define XSR_HIG

/* XoShiRo Settings / Configuration *////////////////////////////////////////////////

	#define XSR_512 1 // Enables Xoshiro512-64Bit (Default: 0)
	#if (defined(XSR_512) && (XSR_512 == 1))
		#define UINT 1
		#define REAL 1
		#define JUMP512 1  // Enables Jumpfunctions
	#endif
	#define XSR_256 1 // Enables Xoshiro256-64Bit (Default: 1)
	#if (defined(XSR_256) && (XSR_256 == 1))
		#define UINT 1
		#define REAL 1
		#define JUMP256 1
	#endif
	#define XSR_128 1 // Enables Xoshiro128-32Bit (Default: 1)
	#if (defined(XSR_128) && (XSR_128 == 1))
		#define UINT 1
		#define REAL 1
		#define JUMP128 1
	#endif

/* XoShiRo Configuration Logic */////////////////////////////////////////////////////

	#if ((defined(XSR_512) && (XSR_512 == 1)) ||\
		 (defined(XSR_256) && (XSR_256 == 1)) ||\
		 (defined(XSR_128) && (XSR_128 == 1)))
		#define XSR_

		#define UNIDIST 1
		#if ((defined(UINT) && (UINT == 1)) &&\
			 (defined(UNIDIST) && (UNIDIST == 1)))
			#define UNIDIST_UINT 1
			#if ((defined(XSR_512) && (XSR_512 == 1)) ||\
				 (defined(XSR_256) && (XSR_256 == 1)))
			#define UNIDIST_UINT64
			#endif
			#if (defined(XSR_128) && (XSR_128 == 1))
				#define UNIDIST_UINT32
			#endif

			#define UNIDIST_REAL 1
			#if ((defined(XSR_512) && (XSR_512 == 1)) ||\
				 (defined(XSR_256) && (XSR_256 == 1)))
				#define UNIDIST_REAL53
			#endif
			#if (defined(XSR_128) && (XSR_128 == 1))
			#define UNIDIST_REAL24
			#endif
		#endif
	#endif

/* XoShiRo General */////////////////////////////////////////////////////////////////

	#ifdef XSR_
	#include <stdint.h>
	#include <string.h>
	#include <stdlib.h>

	typedef void *pXSR, *pSM64;
	typedef struct {
		struct {
			uint64_t (*fnSS)(pXSR);
			uint64_t (*fnPP)(pXSR);
			uint64_t (*fnP)(pXSR);
			void (*fnLJ)(pXSR);
			void (*fnSJ)(pXSR);
		};
		pXSR pS;
	} sXSRT, *pXSRT;




	typedef struct {
		uint64_t(*fn)(pXSR);
		pXSR xsr;
	} sXSRT64, *pXSRT64;
	typedef struct {
		uint32_t(*fn)(pXSR);
		pXSR xsr;
	} sXSRT32, *pXSRT32;

	#endif
#endif