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
		#define _XSR_SCON 1 // Enables special Constructors (Default: 1)
	#endif

/* XoShiRo Internal *////////////////////////////////////////////////////////////////
	#ifdef _XSR_
		#include <stdint.h>
		#include <string.h>
		#include <stdlib.h>

		/* MACRO XSRParamA */
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
			/* XoShiRo DataStructure */
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

			/* XoShiRo Parameter Structure */
			typedef struct {
				uint32_t mod : 2;
				uint32_t ran : 3;
				uint32_t lj : 8;
				uint32_t sj : 8;
				uint32_t ns : 11;
			} sXSRPA, * pXSRPA;
			typedef struct {
				uint8_t ran : 1;
				uint8_t ns : 7;
			} sXSRPB, * pXSRPB;

			/* XoShiRo Function Declarations */
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

			pXSRT fnAllocXSR(uint64_t ui64Seed, sXSRPA sParamA, sXSRPB sParamB);
			#if (defined(_XSR_SCON) && (_XSR_SCON == 1))
				void fnRelocXSR(pXSRT xsr, uint64_t ui64Seed, sXSRPA sParamA, sXSRPB sParamB);
				pXSRT fnCopyXSR(pXSRT xsr);
			#endif
			void fnDelocXSR(pXSRT xsr);
		#ifdef __cplusplus
		}
		#endif
	#endif
#endif