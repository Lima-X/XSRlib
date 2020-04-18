#ifndef _XSR_HIG
#define _XSR_HIG

/* XoShiRo Settings / Configuration *////////////////////////////////////////////////
	#define _XSR_512 1 // Enables Xoshiro512-64Bit (Default: 0)
	#define _XSR_256 1 // Enables Xoshiro256-64Bit (Default: 1)
	#define _XSR_128 1 // Enables Xoshiro128-32Bit (Default: 1)
	#if ((defined(_XSR_512) && (_XSR_512 == 1)) ||\
		(defined(_XSR_256) && (_XSR_256 == 1)) ||\
		(defined(_XSR_128) && (_XSR_128 == 1)))
		#define _XSR_		// ! Internal, don't modify !
		#define _XSR_JUMP 1 // Enables Jumpfunctions (Default: 1)
		#define _XSR_UINT 1 // Enables uniform Integer distrubution functions (Default: 1)
		#define _XSR_REAL 1 // Enables uniform floatingpoint distrubution functions (Default: 0)
	#endif

/* XoShiRo Internal *////////////////////////////////////////////////////////////////
	#ifdef _XSR_
		#include <stdint.h>
		#include <string.h>
		#include <stdlib.h>

		/* MACRO XSRParamA */
		#define XSRParamA(mod, ran, lj, sj, ns) (uint32_t)((mod << 30) | ((ran & 0x7) << 27) |\
												((lj & 0xff) << 19) | ((sj & 0xff) << 11) |\
												(ns & 0x7ff))
		#if (defined(_XSR_512) && (_XSR_512 == 1))
			#define XSR_512 3
		#endif
		#if (defined(_XSR_512) && (_XSR_512 == 1))
			#define XSR_256 2
		#endif
		#if (defined(_XSR_512) && (_XSR_512 == 1))
			#define XSR_128 1
		#endif
		#if (defined(_XSR_JUMP) && (_XSR_JUMP == 1))
			#define XSR_RANDOM_LJUMP 4
			#define XSR_RANDOM_SJUMP 2
			#define XSR_RANDOM_ALL 7
		#else
			#define XSR_RANDOM_ALL 1
		#endif
		#define XSR_RANDOM_NEXTS 1

		/* MACRO XSRParamB */
		#define XSRParamB(mod, ns) (uint16_t)((mod << 7) | (ns & 0x7f))
		#define XSR_RANDOM_SM 1

		/* MACRO XSRPGen */
		#define XSRGen(fn, xsr) (xsr->fn(xsr->pS))
		#define XSR_SS fnSS
		#define XSR_PP fnPP

		/* MACRO XSRJump */
		#if (defined(_XSR_JUMP) && (_XSR_JUMP == 1))
			#define XSRJump(fn, xsr) (xsr->fn(xsr->pS))
			#define XSR_LJUMP fnLJ
			#define XSR_SJUMP fnSJ
		#endif

		/* MACRO XSRDist */
		#if (defined(_XSR_UINT) && (_XSR_UINT == 1))
			#define XSRUDist(dis, max, min, fn, xsr) dis(max, min, xsr->fn, xsr->pS)
			#if ((defined(_XSR_512) && (_XSR_512 == 1)) ||\
				(defined(_XSR_256) && (_XSR_256 == 1)))
				#define XSR_D64 fnURID64
			#endif
			#if (defined(_XSR_128) && (_XSR_128 == 1))
				#define XSR_D32 fnURID32
			#endif
		#endif
		#if (defined(_XSR_UINT) && (_XSR_UINT == 1))
			#define XSRFDist(dis, xsr) dis(xsr)
			#if ((defined(_XSR_512) && (_XSR_512 == 1)) ||\
				(defined(_XSR_256) && (_XSR_256 == 1)))
				#define XSR_DDIST fnURRD53
			#endif
			#if (defined(_XSR_128) && (_XSR_128 == 1))
				#define XSR_FDIST fnURRD24
			#endif
		#endif

		#ifdef __cplusplus
		extern "C" {
		#endif
			typedef void* pXSR;
			typedef struct {
				struct {
					uint64_t(*fnSS)(pXSR);
					uint64_t(*fnPP)(pXSR);
					uint64_t(*fnP)(pXSR);
					#if (defined(_XSR_JUMP) && (_XSR_JUMP == 1))
						void (*fnLJ)(pXSR);
						void (*fnSJ)(pXSR);
					#endif
				};
				pXSR pS;
			} sXSRT, * pXSRT;

			#if (defined(_XSR_UINT) && (_XSR_UINT == 1))
				#if ((defined(_XSR_512) && (_XSR_512 == 1)) ||\
					(defined(_XSR_256) && (_XSR_256 == 1)))
					uint64_t fnURID64(uint64_t ui64Max, uint64_t ui64Min, uint64_t(*fnXSR)(pXSR), pXSR pS);
				#endif
				#if (defined(_XSR_128) && (_XSR_128 == 1))
					uint32_t fnURID32(uint32_t ui32Max, uint32_t ui32Min, uint32_t(*fnXSR)(pXSR), pXSR pS);
				#endif
			#endif
			#if (defined(_XSR_REAL) && (_XSR_REAL == 1))
				#if ((defined(_XSR_512) && (_XSR_512 == 1)) ||\
					(defined(_XSR_256) && (_XSR_256 == 1)))
					double fnURRD53(pXSRT xsr);
				#endif
				#if (defined(_XSR_128) && (_XSR_128 == 1))
					float fnURRD24(pXSRT xsr);
				#endif
			#endif

			pXSRT fnAllocXSR(uint64_t ui64Seed, uint32_t ui32XSR, uint8_t ui8SM);
			void fnRelocXSR(pXSRT xsr, uint64_t ui64Seed, uint32_t ui32XSR, uint8_t ui8SM);
			pXSRT fnCopyXSR(pXSRT xsr);
			void fnDelocXSR(pXSRT xsr);
		#ifdef __cplusplus
		}
		#endif
	#endif
#endif