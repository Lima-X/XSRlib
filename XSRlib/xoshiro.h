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
	#define XSRParam(mod, ran, lj, sj, ns) (uint32_t)(((mod/128)<<30)|\
										   (ran<<27)|(lj<<19)|(sj<<11)|ns)
	#define XSR_RANDOM_LJUMP 4
	#define XSR_RANDOM_SJUMP 2
	#define XSR_RANDOM_NEXTS 1
	#define XSR_RANDOM_ALL 7

	#define XSRGen(fn, x) (x->fn(x->pS))
	#define XSR_SS fnSS
	#define XSR_PP fnPP

	#define XSRUDist(dist, max, min, fn, x) dist(max, min, x->fn, x->pS)
	#define XSR_D64 fn64URngDist
	#define XSR_D32 fn64URngDist
	#define XSRFDist(dist, x) dist(x)
	#define XSR_DDIST fnDURngDist
	#define XSR_FDIST fnFURngDist

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

	#endif
#endif