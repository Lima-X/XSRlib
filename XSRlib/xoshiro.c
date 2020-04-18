#include "xoshiro.h"

/* XoShiRo Sub Tool's *//////////////////////////////////////////////////////////////
#ifdef _XSR_
	#if ((defined(_XSR_512) && (_XSR_512 == 1)) ||\
		(defined(_XSR_256) && (_XSR_256 == 1)))
		static inline uint64_t fnRotl64(const uint64_t ui64X, uint8_t ui8K) {
			return (ui64X << ui8K) | (ui64X >> (64 - ui8K));
		}
	#endif
	#if (defined(_XSR_128) && (_XSR_128 == 1))
		static inline uint32_t fnRotl32(const uint32_t ui32X, uint8_t ui8K) {
			return (ui32X << ui8K) | (ui32X >> (32 - ui8K));
		}
	#endif
	static uint64_t fnNextSM64(uint64_t* ui64SM) {
		uint64_t ui64Z = (*ui64SM += 0x9e3779b97f4a7c15);
		ui64Z = (ui64Z ^ (ui64Z >> 30)) * 0xbf58476d1ce4e5b9;
		ui64Z = (ui64Z ^ (ui64Z >> 27)) * 0x94d049bb133111eb;
		return ui64Z ^ (ui64Z >> 31);
	}
#endif

/* XoShiRo512-64Bit Algorithm *//////////////////////////////////////////////////////
#if (defined(_XSR_512) && (_XSR_512 == 1))
	static inline void fnNext512(pXSR xsr) {
		const uint64_t ui64T = ((uint64_t*)xsr)[1] << 11;
		((uint64_t*)xsr)[2] ^= ((uint64_t*)xsr)[0];
		((uint64_t*)xsr)[5] ^= ((uint64_t*)xsr)[1];
		((uint64_t*)xsr)[1] ^= ((uint64_t*)xsr)[2];
		((uint64_t*)xsr)[7] ^= ((uint64_t*)xsr)[3];
		((uint64_t*)xsr)[3] ^= ((uint64_t*)xsr)[4];
		((uint64_t*)xsr)[4] ^= ((uint64_t*)xsr)[5];
		((uint64_t*)xsr)[0] ^= ((uint64_t*)xsr)[6];
		((uint64_t*)xsr)[6] ^= ((uint64_t*)xsr)[7];
		((uint64_t*)xsr)[6] ^= ui64T;
		((uint64_t*)xsr)[7] = fnRotl64(((uint64_t*)xsr)[7], 21);
	}

	static uint64_t fnNext512ss(pXSR xsr) {
		const uint64_t ui64R = fnRotl64(((uint64_t*)xsr)[1] * 5, 7) * 9;
		fnNext512(xsr);
		return ui64R;
	}
	static uint64_t fnNext512pp(pXSR xsr) {
		const uint64_t ui64R = fnRotl64(((uint64_t*)xsr)[0] +
			((uint64_t*)xsr)[2], 17) + ((uint64_t*)xsr)[2];
		fnNext512(xsr);
		return ui64R;
	}
	static uint64_t fnNext512p(pXSR xsr) {
		const uint64_t ui64R = ((uint64_t*)xsr)[0] + ((uint64_t*)xsr)[2];
		fnNext512(xsr);
		return ui64R;
	}

	#if (defined(_XSR_JUMP) && (_XSR_JUMP == 1))
		static inline void fnJump512(const uint64_t ui64_8[], pXSR xsr) {
			uint64_t ui64T[8];
			memset(ui64T, 0, sizeof(ui64T));
			for (int i = 0; i < 8; i++)
				for (int j = 0; j < 64; j++) {
					if (ui64_8[i] & (1ULL << j))
						for (int n = 0; n < 8; n++)
							ui64T[n] ^= ((uint64_t*)xsr)[n];
					fnNext512(xsr);
				}
			memcpy(xsr, ui64T, sizeof(xsr));
		}

		static void fnLJump512(pXSR xsr) {
			static const uint64_t ui64Jump[] = {
				0x11467fef8f921d28, 0xa2a819f2e79c8ea8, 0xa8299fc284b3959a, 0xb4d347340ca63ee1,
				0x1cb0940bedbff6ce, 0xd956c5c4fa1f8e17, 0x915e38fd4eda93bc, 0x5b3ccdfa5d7daca5
			};
			fnJump512(ui64Jump, xsr);
		}
		static void fnSJump512(pXSR xsr) {
			static const uint64_t ui64Jump[] = {
				0x33ed89b6e7a353f9, 0x760083d7955323be, 0x2837f2fbb5f22fae, 0x4b8c5674d309511c,
				0xb11ac47a7ba28c25, 0xf1be7667092bcc1c, 0x53851efdb6df0aaf, 0x1ebbc8b23eaf25db
			};
			fnJump512(ui64Jump, xsr);
		}
	#endif
#endif

/* XoShiRo256-64Bit Algorithm *//////////////////////////////////////////////////////
#if (defined(_XSR_256) && (_XSR_256 == 1))
	static inline void fnNext256(pXSR xsr) {
		const uint64_t ui64T = ((uint64_t*)xsr)[1] << 17;
		((uint64_t*)xsr)[2] ^= ((uint64_t*)xsr)[0];
		((uint64_t*)xsr)[3] ^= ((uint64_t*)xsr)[1];
		((uint64_t*)xsr)[1] ^= ((uint64_t*)xsr)[2];
		((uint64_t*)xsr)[0] ^= ((uint64_t*)xsr)[3];
		((uint64_t*)xsr)[2] ^= ui64T;
		((uint64_t*)xsr)[3] = fnRotl64(((uint64_t*)xsr)[3], 45);
	}

	static uint64_t fnNext256ss(pXSR xsr) {
		const uint64_t ui64R = fnRotl64(((uint64_t*)xsr)[1] * 5, 7) * 9;
		fnNext256(xsr);
		return ui64R;
	}
	static uint64_t fnNext256pp(pXSR xsr) {
		const uint64_t ui64R = fnRotl64(((uint64_t*)xsr)[0] +
			((uint64_t*)xsr)[3], 23) + ((uint64_t*)xsr)[0];
		fnNext256(xsr);
		return ui64R;
	}
	static uint64_t fnNext256p(pXSR xsr) {
		const uint64_t ui64R = ((uint64_t*)xsr)[0] + ((uint64_t*)xsr)[3];
		fnNext256(xsr);
		return ui64R;
	}

	#if (defined(_XSR_JUMP) && (_XSR_JUMP == 1))
		static inline void fnJump256(const uint64_t ui64_4[], pXSR xsr) {
			uint64_t s0 = 0,
					 s1 = 0,
					 s2 = 0,
					 s3 = 0;
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 64; j++) {
					if (ui64_4[i] & (1ULL << j)) {
						s0 ^= ((uint64_t*)xsr)[0];
						s1 ^= ((uint64_t*)xsr)[1];
						s2 ^= ((uint64_t*)xsr)[2];
						s3 ^= ((uint64_t*)xsr)[3];
					}
					fnNext256(xsr);
				}

			((uint64_t*)xsr)[0] = s0;
			((uint64_t*)xsr)[1] = s1;
			((uint64_t*)xsr)[2] = s2;
			((uint64_t*)xsr)[3] = s3;
		}

		static void fnLJump256(pXSR xsr) {
			static const uint64_t ui64_4Jump[] = {
				0x76e15d3efefdcbbf, 0xc5004e441c522fb3, 0x77710069854ee241, 0x39109bb02acbe635
			};
			fnJump256(ui64_4Jump, xsr);
		}
		static void fnSJump256(pXSR xsr) {
			static const uint64_t ui64_4Jump[] = {
				0x180ec6d33cfd0aba, 0xd5a61266f0c9392c, 0xa9582618e03fc9aa, 0x39abdc4529b1661c
			};
			fnJump256(ui64_4Jump, xsr);
		}
	#endif
#endif

/* XoShiRo128-32Bit Algorithm *//////////////////////////////////////////////////////
#if (defined(_XSR_128) && (_XSR_128 == 1))
	static inline void fnNext128(pXSR xsr) {
		const uint32_t ui32T = ((uint32_t*)xsr)[1] << 9;
		((uint32_t*)xsr)[2] ^= ((uint32_t*)xsr)[0];
		((uint32_t*)xsr)[3] ^= ((uint32_t*)xsr)[1];
		((uint32_t*)xsr)[1] ^= ((uint32_t*)xsr)[2];
		((uint32_t*)xsr)[0] ^= ((uint32_t*)xsr)[3];
		((uint32_t*)xsr)[2] ^= ui32T;
		((uint32_t*)xsr)[3] = fnRotl32(((uint32_t*)xsr)[3], 11);
	}

	static uint32_t fnNext128ss(pXSR xsr) {
		const uint32_t ui32R = fnRotl32(((uint32_t*)xsr)[1] * 5, 7) * 9;
		fnNext128(xsr);
		return ui32R;
	}
	static uint32_t fnNext128pp(pXSR xsr) {
		const uint32_t ui32R = fnRotl32(((uint32_t*)xsr)[0] +
			((uint32_t*)xsr)[3], 7) + ((uint32_t*)xsr)[0];
		fnNext128(xsr);
		return ui32R;
	}
	static uint32_t fnNext128p(pXSR xsr) {
		const uint32_t ui32R = ((uint32_t*)xsr)[0] + ((uint32_t*)xsr)[3];
		fnNext128(xsr);
		return ui32R;
	}

	#if (defined(_XSR_JUMP) && (_XSR_JUMP == 1))
		static inline void fnJump128(const uint32_t ui32_4[], pXSR xsr) {
			uint32_t s0 = 0,
					 s1 = 0,
					 s2 = 0,
					 s3 = 0;
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 32; j++) {
					if (ui32_4[i] & (0x1U << j)) {
						s0 ^= ((uint32_t*)xsr)[0];
						s1 ^= ((uint32_t*)xsr)[1];
						s2 ^= ((uint32_t*)xsr)[2];
						s3 ^= ((uint32_t*)xsr)[3];
					}
					fnNext128(xsr);
				}

			((uint32_t*)xsr)[0] = s0;
			((uint32_t*)xsr)[1] = s1;
			((uint32_t*)xsr)[2] = s2;
			((uint32_t*)xsr)[3] = s3;
		}

		static void fnLJump128(pXSR xsr) {
			const uint32_t ui32_4Jump[] = {
				0xb523952e, 0x0b6f099f, 0xccf5a0ef, 0x1c580662
			};
			fnJump128(ui32_4Jump, xsr);
		}
		static void fnSJump128(pXSR xsr) {
			const uint32_t ui32_4Jump[] = {
				0x8764000b, 0xf542d2d3, 0x6fa035c3, 0x77f2db5b
			};
			fnJump128(ui32_4Jump, xsr);
		}
	#endif
#endif

/* Uniform Distribution Algorithms */////////////////////////////////////////////////
#if (defined(_XSR_UINT) && (_XSR_UINT == 1))
	#if ((defined(_XSR_512) && (_XSR_512 == 1)) ||\
		(defined(_XSR_256) && (_XSR_256 == 1)))
		uint64_t fnURID64(uint64_t ui64Max, uint64_t ui64Min, uint64_t (*fn)(pXSR), pXSR pS) {
			uint64_t ui64Ret;
			const uint64_t ui64Range = (ui64Max - ui64Min) + 1;
			const uint64_t ui64Scale = (-1) / ui64Range;
			const uint64_t ui64Limit = ui64Range * ui64Scale;

			do {
				ui64Ret = fn(pS);
			} while (ui64Ret >= ui64Limit);
			ui64Ret /= ui64Scale;

			return ui64Ret + ui64Min;
		}
	#endif
	#if (defined(_XSR_128) && (_XSR_128 == 1))
		uint32_t fnURID32(uint32_t ui32Max, uint32_t ui32Min, uint32_t (*fn)(pXSR), pXSR pS) {
			uint32_t ui32Ret;
			const uint32_t ui32Range = (ui32Max - ui32Min) + 1;
			const uint32_t ui32Scale = (-1) / ui32Range;
			const uint32_t ui32Limit = ui32Range * ui32Scale;

			do {
				ui32Ret = fn(pS);
			} while (ui32Ret >= ui32Limit);
			ui32Ret /= ui32Scale;

			return ui32Ret + ui32Min;
		}
	#endif
#endif
#if (defined(_XSR_REAL) && (_XSR_REAL == 1))
	#if ((defined(_XSR_512) && (_XSR_512 == 1)) ||\
		(defined(_XSR_256) && (_XSR_256 == 1)))
		double fnURRD53(pXSRT xsr) {
			// 53 bits resolution:
			return (uint64_t)(xsr->fnP(xsr->pS) >> 11) * (1 / 0x20000000000000p0); // (r >> 11) * 2^(-53)
			// 52 bits resolution:
			return (uint64_t)(xsr->fnP(xsr->pS) >> 12) * (1 / 0x10000000000000p0);  // (r >> 12) * 2^(-52)
		}
	#endif
	#if (defined(_XSR_128) && (_XSR_128 == 1))
		float fnURRD24(pXSRT xsr) {
			// 24 bits resolution:
			return (uint32_t)(xsr->fnP(xsr->pS) >> 8) * (1. / 0x1000000p0); // (r >> 8) * 2^(-24)
			// 23 bits resolution:
			return (uint32_t)(xsr->fnP(xsr->pS) >> 9) * (1. / 0x800000p0);  // (r >> 9) * 2^(-23)
		}
	#endif
#endif

/* XoShiRo Algorithm Interface Tool's *//////////////////////////////////////////////
#ifdef _XSR_
	/*	ui32XSR: 00-000-00000000-00000000-00000000000
		Bit: 31-30 (2Bit):  Binary  - GeneratorType:       11 = 512b; 10 = 256b; 01 = 128b;
			 29-27 (3Bit):  Bitwise - Random Initializers: 1XX = LJ; X1X = SJ; XX1 = NS;
			 26-19 (8Bit):  Binary  - Count of LongJumps:  0-255;
			 18-11 (8Bit):  Binary  - Count of ShortJumps: 0-255;
			 10-0  (11Bit): Binary  - Count of NextState:  0-2047;

		ui8SM: 0-0000000
		Bit: 7   (1Bit): Bitwise - Random Initializers: 1 = NS;
			 6-0 (7Bit): Binary  - Count of NextState:  0-127;	*/
	pXSRT fnAllocXSR(uint64_t ui64Seed, uint32_t ui32XSR, uint8_t ui8SM) {
		if (!(ui32XSR >> 30))
			return 0;

		/* SM64 Init */
		if (ui8SM >> 7)
			ui8SM |= (uint8_t)fnNextSM64(&ui64Seed) >> 1;
		for (int i = 0; i < (ui8SM & 0x7f); i++)
			fnNextSM64(&ui64Seed);

		/* XSR Init */
		#if (defined(_XSR_JUMP) && (_XSR_JUMP == 1))
			if ((ui32XSR >> 29) & 0x1)
				ui32XSR |= (uint8_t)fnNextSM64(&ui64Seed) << 19;
			if ((ui32XSR >> 28) & 0x1)
				ui32XSR |= (uint8_t)fnNextSM64(&ui64Seed) << 11;
		#endif
		if ((ui32XSR >> 27) & 0x1)
			ui32XSR |= (uint16_t)fnNextSM64(&ui64Seed) & 0x7ff;

		void
		#if (defined(_XSR_JUMP) && (_XSR_JUMP == 1))
			(*fnLJumpT)(pXSR) = 0,
			(*fnSJumpT)(pXSR) = 0,
		#endif
			(*fnNextT)(pXSR) = 0;

		pXSRT xsr = malloc(sizeof(sXSRT));
		switch (ui32XSR >> 30) {
		case 0b11:
		#if (defined(_XSR_512) && (_XSR_512 == 1))
			xsr->pS = malloc(sizeof(uint64_t) * 8);
			for (int i = 0; i < 8; i++)
				((uint64_t*)xsr->pS)[i] = fnNextSM64(&ui64Seed);
			#if (defined(_XSR_JUMP) && (_XSR_JUMP == 1))
				fnLJumpT = fnLJump512;
				fnSJumpT = fnSJump512;
			#endif
			fnNextT = fnNext512;
			xsr->fnSS = fnNext512ss;
			xsr->fnPP = fnNext512pp;
			xsr->fnP = fnNext512p;
			#if (defined(_XSR_JUMP) && (_XSR_JUMP == 1))
				xsr->fnLJ = fnLJump512;
				xsr->fnSJ = fnSJump512;
			#endif
			break;
		#else
			free(xsr);
			return 0;
		#endif
		case 0b10:
		#if (defined(_XSR_256) && (_XSR_256 == 1))
			xsr->pS = malloc(sizeof(uint64_t) * 4);
			for (int i = 0; i < 4; i++)
				((uint64_t*)xsr->pS)[i] = fnNextSM64(&ui64Seed);
			#if (defined(_XSR_JUMP) && (_XSR_JUMP == 1))
				fnLJumpT = fnLJump256;
				fnSJumpT = fnSJump256;
			#endif
			fnNextT = fnNext256;
			xsr->fnSS = fnNext256ss;
			xsr->fnPP = fnNext256pp;
			xsr->fnP = fnNext256p;
			#if (defined(_XSR_JUMP) && (_XSR_JUMP == 1))
				xsr->fnLJ = fnLJump256;
				xsr->fnSJ = fnSJump256;
			#endif
			break;
		#else
			free(xsr);
			return 0;
		#endif
		case 0b01:
		#if (defined(_XSR_128) && (_XSR_128 == 1))
			xsr->pS = malloc(sizeof(uint32_t) * 4);
			for (int i = 0; i < 4; i++)
				((uint32_t*)xsr->pS)[i] = (uint32_t)(fnNextSM64(&ui64Seed) >> 32);
			#if (defined(_XSR_JUMP) && (_XSR_JUMP == 1))
				fnLJumpT = fnLJump128;
				fnSJumpT = fnSJump128;
			#endif
			fnNextT = fnNext128;
			xsr->fnSS = (uint64_t(*)(pXSR))fnNext128ss;
			xsr->fnPP = (uint64_t(*)(pXSR))fnNext128pp;
			xsr->fnP = (uint64_t(*)(pXSR))fnNext128p;
			#if (defined(_XSR_JUMP) && (_XSR_JUMP == 1))
				xsr->fnLJ = fnLJump128;
				xsr->fnSJ = fnSJump128;
			#endif
		#else
			free(xsr);
			return 0;
		#endif
		}

		#if (defined(_XSR_JUMP) && (_XSR_JUMP == 1))
			for (int i = 0; i < (uint8_t)(ui32XSR >> 19); i++)
				fnLJumpT(xsr->pS);
			for (int i = 0; i < (uint8_t)(ui32XSR >> 11); i++)
				fnSJumpT(xsr->pS);
		#endif
		for (int i = 0; i < (uint16_t)(ui32XSR & 0x7ff); i++)
			fnNextT(xsr->pS);

		return xsr;
	}
	/*	ui32XSR: XX-000-00000000-00000000-00000000000
		Bit: 29-27 (3Bit):  Bitwise - Random Initializers: 1XX = LJ; X1X = SJ; XX1 = NS;
			 26-19 (8Bit):  Binary  - Count of LongJumps:  0-255;
			 18-11 (8Bit):  Binary  - Count of ShortJumps: 0-255;
			 10-0  (11Bit): Binary  - Count of NextState:  0-2047;	*/
	void fnRelocXSR(pXSRT xsr, uint64_t ui64Seed, uint32_t ui32XSR, uint8_t ui8SM) {
		if (!xsr)
			return;

		/* SM64 Init */
		if (ui8SM >> 7)
			ui8SM |= (uint8_t)fnNextSM64(&ui64Seed) >> 1;
		for (int i = 0; i < (ui8SM & 0x7f); i++)
			fnNextSM64(&ui64Seed);

		/* XSR Init */
		#if (defined(_XSR_JUMP) && (_XSR_JUMP == 1))
			if ((ui32XSR >> 29) & 0x1)
				ui32XSR |= (uint8_t)fnNextSM64(&ui64Seed) << 19;
			if ((ui32XSR >> 28) & 0x1)
				ui32XSR |= (uint8_t)fnNextSM64(&ui64Seed) << 11;
		#endif
		if ((ui32XSR >> 27) & 0x1)
			ui32XSR |= (uint16_t)fnNextSM64(&ui64Seed) & 0x7ff;


		#if (defined(_XSR_512) && (_XSR_512 == 1))
			if (xsr->fnSS == fnNext512ss)
				for (int i = 0; i < 8; i++)
					((uint64_t*)xsr->pS)[i] = fnNextSM64(&ui64Seed);
			else
		#endif
		#if (defined(_XSR_256) && (_XSR_256 == 1))
			if (xsr->fnSS == fnNext256ss)
				for (int i = 0; i < 4; i++)
					((uint64_t*)xsr->pS)[i] = fnNextSM64(&ui64Seed);
			else
		#endif
		#if (defined(_XSR_128) && (_XSR_128 == 1))
			if (xsr->fnSS == fnNext128ss)
				for (int i = 0; i < 4; i++)
					((uint32_t*)xsr->pS)[i] = (uint32_t)(fnNextSM64(&ui64Seed) >> 32);
		#endif

		#if (defined(_XSR_JUMP) && (_XSR_JUMP == 1))
			for (int i = 0; i < (uint8_t)(ui32XSR >> 19); i++)
				xsr->fnLJ(xsr->pS);
			for (int i = 0; i < (uint8_t)(ui32XSR >> 11); i++)
				xsr->fnSJ(xsr->pS);
		#endif
		for (int i = 0; i < (uint16_t)(ui32XSR & 0x7ff); i++)
			xsr->fnP(xsr->pS);
	}
	pXSRT fnCopyXSR(pXSRT xsr) {
		if (!xsr)
			return 0;

		pXSRT xsrC = malloc(sizeof(sXSRT));
		#if (defined(_XSR_512) && (_XSR_512 == 1))
			if (xsr->fnSS == fnNext512ss) {
				xsrC->pS = malloc(sizeof(uint64_t) * 8);
				memcpy(xsrC->pS, xsr->pS, sizeof(uint64_t) * 8);
			} else
		#endif
		#if (defined(_XSR_256) && (_XSR_256 == 1))
			if (xsr->fnSS == fnNext256ss) {
				xsrC->pS = malloc(sizeof(uint64_t) * 4);
				memcpy(xsrC->pS, xsr->pS, sizeof(uint64_t) * 4);
			} else
		#endif
		#if (defined(_XSR_128) && (_XSR_128 == 1))
			if (xsr->fnSS == fnNext128ss) {
				xsrC->pS = malloc(sizeof(uint32_t) * 4);
				memcpy(xsrC->pS, xsr->pS, sizeof(uint32_t) * 4);
			}
		#endif

		xsrC->fnSS = xsr->fnSS;
		xsrC->fnPP = xsr->fnPP;
		xsrC->fnP = xsr->fnP;
		#if (defined(_XSR_JUMP) && (_XSR_JUMP == 1))
			xsrC->fnLJ = xsr->fnLJ;
			xsrC->fnSJ = xsr->fnSJ;
		#endif

		return xsrC;
	}
	void fnDelocXSR(pXSRT xsr) {
		if (!xsr)
			return;
		free(xsr->pS);
		free(xsr);
		xsr = 0;
	}
#endif