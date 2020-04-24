#include "xoshiro.h"

/* XoShiRo Rotate Tool's */////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef _XSR_
	#if ((_XSR_512 == 1) || (_XSR_256 == 1))
		static inline uint64_t fnRotl64(uint64_t ui64X, uint8_t ui8K) {
			return (ui64X << ui8K) | (ui64X >> (64 - ui8K));
		}
	#endif
	#if (_XSR_128 == 1)
		static inline uint32_t fnRotl32(uint32_t ui32X, uint8_t ui8K) {
			return (ui32X << ui8K) | (ui32X >> (32 - ui8K));
		}
	#endif
#endif

/* XoShiRo512-64Bit Algorithm *////////////////////////////////////////////////////////////////////////////////////////////////
#if (_XSR_512 == 1)
	static inline void fnNext512(void* pS) {
		const uint64_t ui64T = ((uint64_t*)pS)[1] << 11;
		((uint64_t*)pS)[2] ^= ((uint64_t*)pS)[0];
		((uint64_t*)pS)[5] ^= ((uint64_t*)pS)[1];
		((uint64_t*)pS)[1] ^= ((uint64_t*)pS)[2];
		((uint64_t*)pS)[7] ^= ((uint64_t*)pS)[3];
		((uint64_t*)pS)[3] ^= ((uint64_t*)pS)[4];
		((uint64_t*)pS)[4] ^= ((uint64_t*)pS)[5];
		((uint64_t*)pS)[0] ^= ((uint64_t*)pS)[6];
		((uint64_t*)pS)[6] ^= ((uint64_t*)pS)[7];
		((uint64_t*)pS)[6] ^= ui64T;
		((uint64_t*)pS)[7] = fnRotl64(((uint64_t*)pS)[7], 21);
	}

	static uint64_t fnNext512ss(void* pS) {
		const uint64_t ui64R = fnRotl64(((uint64_t*)pS)[1] * 5, 7) * 9;
		fnNext512(pS);
		return ui64R;
	}
	static uint64_t fnNext512pp(void* pS) {
		const uint64_t ui64R = fnRotl64(((uint64_t*)pS)[0] +
			((uint64_t*)pS)[2], 17) + ((uint64_t*)pS)[2];
		fnNext512(pS);
		return ui64R;
	}
	static uint64_t fnNext512p(void* pS) {
		const uint64_t ui64R = ((uint64_t*)pS)[0] + ((uint64_t*)pS)[2];
		fnNext512(pS);
		return ui64R;
	}

	#if (_XSR_JUMP == 1)
		static inline void fnJump512(const uint64_t ui64_8[], void* pS) {
			uint64_t ui64T[8];
			memset(ui64T, 0, sizeof(ui64T));
			for (int i = 0; i < 8; i++)
				for (int j = 0; j < 64; j++) {
					if (ui64_8[i] & (1ULL << j))
						for (int n = 0; n < 8; n++)
							ui64T[n] ^= ((uint64_t*)pS)[n];
					fnNext512(pS);
				}
			memcpy(pS, ui64T, sizeof(pS));
		}

		static void fnLJump512(void* pS) {
			static const uint64_t ui64Jump[] = {
				0x11467fef8f921d28, 0xa2a819f2e79c8ea8, 0xa8299fc284b3959a, 0xb4d347340ca63ee1,
				0x1cb0940bedbff6ce, 0xd956c5c4fa1f8e17, 0x915e38fd4eda93bc, 0x5b3ccdfa5d7daca5
			};
			fnJump512(ui64Jump, pS);
		}
		static void fnSJump512(void* pS) {
			static const uint64_t ui64Jump[] = {
				0x33ed89b6e7a353f9, 0x760083d7955323be, 0x2837f2fbb5f22fae, 0x4b8c5674d309511c,
				0xb11ac47a7ba28c25, 0xf1be7667092bcc1c, 0x53851efdb6df0aaf, 0x1ebbc8b23eaf25db
			};
			fnJump512(ui64Jump, pS);
		}
	#endif
#endif

/* XoShiRo256-64Bit Algorithm *////////////////////////////////////////////////////////////////////////////////////////////////
#if (_XSR_256 == 1)
	static inline void fnNext256(void* pS) {
		const uint64_t ui64T = ((uint64_t*)pS)[1] << 17;
		((uint64_t*)pS)[2] ^= ((uint64_t*)pS)[0];
		((uint64_t*)pS)[3] ^= ((uint64_t*)pS)[1];
		((uint64_t*)pS)[1] ^= ((uint64_t*)pS)[2];
		((uint64_t*)pS)[0] ^= ((uint64_t*)pS)[3];
		((uint64_t*)pS)[2] ^= ui64T;
		((uint64_t*)pS)[3] = fnRotl64(((uint64_t*)pS)[3], 45);
	}

	static uint64_t fnNext256ss(void* pS) {
		const uint64_t ui64R = fnRotl64(((uint64_t*)pS)[1] * 5, 7) * 9;
		fnNext256(pS);
		return ui64R;
	}
	static uint64_t fnNext256pp(void* pS) {
		const uint64_t ui64R = fnRotl64(((uint64_t*)pS)[0] +
			((uint64_t*)pS)[3], 23) + ((uint64_t*)pS)[0];
		fnNext256(pS);
		return ui64R;
	}
	static uint64_t fnNext256p(void* pS) {
		const uint64_t ui64R = ((uint64_t*)pS)[0] + ((uint64_t*)pS)[3];
		fnNext256(pS);
		return ui64R;
	}

	#if (_XSR_JUMP == 1)
		static inline void fnJump256(const uint64_t ui64_4[], void* pS) {
			uint64_t s0 = 0,
					 s1 = 0,
					 s2 = 0,
					 s3 = 0;
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 64; j++) {
					if (ui64_4[i] & (1ULL << j)) {
						s0 ^= ((uint64_t*)pS)[0];
						s1 ^= ((uint64_t*)pS)[1];
						s2 ^= ((uint64_t*)pS)[2];
						s3 ^= ((uint64_t*)pS)[3];
					}
					fnNext256(pS);
				}

			((uint64_t*)pS)[0] = s0;
			((uint64_t*)pS)[1] = s1;
			((uint64_t*)pS)[2] = s2;
			((uint64_t*)pS)[3] = s3;
		}

		static void fnLJump256(void* pS) {
			static const uint64_t ui64_4Jump[] = {
				0x76e15d3efefdcbbf, 0xc5004e441c522fb3, 0x77710069854ee241, 0x39109bb02acbe635
			};
			fnJump256(ui64_4Jump, pS);
		}
		static void fnSJump256(void* pS) {
			static const uint64_t ui64_4Jump[] = {
				0x180ec6d33cfd0aba, 0xd5a61266f0c9392c, 0xa9582618e03fc9aa, 0x39abdc4529b1661c
			};
			fnJump256(ui64_4Jump, pS);
		}
	#endif
#endif

/* XoShiRo128-32Bit Algorithm *////////////////////////////////////////////////////////////////////////////////////////////////
#if (_XSR_128 == 1)
	static inline void fnNext128(void* pS) {
		const uint32_t ui32T = ((uint32_t*)pS)[1] << 9;
		((uint32_t*)pS)[2] ^= ((uint32_t*)pS)[0];
		((uint32_t*)pS)[3] ^= ((uint32_t*)pS)[1];
		((uint32_t*)pS)[1] ^= ((uint32_t*)pS)[2];
		((uint32_t*)pS)[0] ^= ((uint32_t*)pS)[3];
		((uint32_t*)pS)[2] ^= ui32T;
		((uint32_t*)pS)[3] = fnRotl32(((uint32_t*)pS)[3], 11);
	}

	static uint32_t fnNext128ss(void* pS) {
		const uint32_t ui32R = fnRotl32(((uint32_t*)pS)[1] * 5, 7) * 9;
		fnNext128(pS);
		return ui32R;
	}
	static uint32_t fnNext128pp(void* pS) {
		const uint32_t ui32R = fnRotl32(((uint32_t*)pS)[0] +
			((uint32_t*)pS)[3], 7) + ((uint32_t*)pS)[0];
		fnNext128(pS);
		return ui32R;
	}
	static uint32_t fnNext128p(void* pS) {
		const uint32_t ui32R = ((uint32_t*)pS)[0] + ((uint32_t*)pS)[3];
		fnNext128(pS);
		return ui32R;
	}

	#if (_XSR_JUMP == 1)
		static inline void fnJump128(const uint32_t ui32_4[], void* pS) {
			uint32_t s0 = 0,
					 s1 = 0,
					 s2 = 0,
					 s3 = 0;
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 32; j++) {
					if (ui32_4[i] & (0x1U << j)) {
						s0 ^= ((uint32_t*)pS)[0];
						s1 ^= ((uint32_t*)pS)[1];
						s2 ^= ((uint32_t*)pS)[2];
						s3 ^= ((uint32_t*)pS)[3];
					}
					fnNext128(pS);
				}

			((uint32_t*)pS)[0] = s0;
			((uint32_t*)pS)[1] = s1;
			((uint32_t*)pS)[2] = s2;
			((uint32_t*)pS)[3] = s3;
		}

		static void fnLJump128(void* pS) {
			const uint32_t ui32_4Jump[] = {
				0xb523952e, 0x0b6f099f, 0xccf5a0ef, 0x1c580662
			};
			fnJump128(ui32_4Jump, pS);
		}
		static void fnSJump128(void* pS) {
			const uint32_t ui32_4Jump[] = {
				0x8764000b, 0xf542d2d3, 0x6fa035c3, 0x77f2db5b
			};
			fnJump128(ui32_4Jump, pS);
		}
	#endif
#endif

/* Uniform Distribution Algorithms *///////////////////////////////////////////////////////////////////////////////////////////
#if (_XSR_UINT == 1)
	#if ((_XSR_512 == 1) || (_XSR_256 == 1))
		uint64_t fnURID64(uint64_t ui64Max, uint64_t ui64Min, uint64_t (*fn)(void*), void* pS) {
			uint64_t ui64Ret;
			const uint64_t ui64Range = (ui64Max - ui64Min) + 1;
			const uint64_t ui64Scale = (uint64_t)-1 / ui64Range;
			const uint64_t ui64Limit = ui64Range * ui64Scale;

			do {
				ui64Ret = fn(pS);
			} while (ui64Ret >= ui64Limit);
			ui64Ret /= ui64Scale;

			return ui64Ret + ui64Min;
		}
	#endif
	#if (_XSR_128 == 1)
		uint32_t fnURID32(uint32_t ui32Max, uint32_t ui32Min, uint32_t (*fn)(void*), void* pS) {
			uint32_t ui32Ret;
			const uint32_t ui32Range = (ui32Max - ui32Min) + 1;
			const uint32_t ui32Scale = (uint32_t)-1 / ui32Range;
			const uint32_t ui32Limit = ui32Range * ui32Scale;

			do {
				ui32Ret = fn(pS);
			} while (ui32Ret >= ui32Limit);
			ui32Ret /= ui32Scale;

			return ui32Ret + ui32Min;
		}
	#endif
#endif
#if (_XSR_REAL == 1)
	#if ((_XSR_512 == 1) || (_XSR_256 == 1))
		double fnURRD53(pXSR xsr) {
			// 53 bits resolution:
			return (xsr->fnP(xsr->pS) >> 11) * (1 / 0x20000000000000p0); // (r >> 11) * 2^(-53)
			// 52 bits resolution:
			// return (xsr->fnP(xsr->pS) >> 12) * (1 / 0x10000000000000p0); // (r >> 12) * 2^(-52)
		}
	#endif
	#if (_XSR_128 == 1)
		float fnURRD24(pXSR xsr) {
			// 24 bits resolution:
			return (xsr->fnP(xsr->pS) >> 8) * (1.f / 0x1000000p0f); // (r >> 8) * 2^(-24)
			// 23 bits resolution:
			// return (xsr->fnP(xsr->pS) >> 9) * (1.f / 0x800000p0f); // (r >> 9) * 2^(-23)
		}
	#endif
#endif

/* XoShiRo Sub Tool's *////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef _XSR_
	static uint64_t fnNextSM64(uint64_t* ui64SM) {
		uint64_t ui64Z = (*ui64SM += 0x9e3779b97f4a7c15);
		ui64Z = (ui64Z ^ (ui64Z >> 30)) * 0xbf58476d1ce4e5b9;
		ui64Z = (ui64Z ^ (ui64Z >> 27)) * 0x94d049bb133111eb;
		return ui64Z ^ (ui64Z >> 31);
	}
	static inline void fnSMPInit(uint64_t* ui64Seed, pXSRPA pParamA, pXSRPB pParamB) {
		/* SM64 Init */
		if (pParamB->ran)
			pParamB->ns |= fnNextSM64(ui64Seed) >> 57;
		for (int i = 0; i < pParamB->ns; i++)
			fnNextSM64(ui64Seed);

		/* XSR Init */
		#if (_XSR_JUMP == 1)
			if (pParamA->ran & 0b100)
				pParamA->lj |= fnNextSM64(ui64Seed) >> 56;
			if (pParamA->ran & 0b10)
				pParamA->sj |= fnNextSM64(ui64Seed) >> 56;
		#endif
		if (pParamA->ran & 0b1)
			pParamA->ns |= fnNextSM64(ui64Seed) >> 53;
	}
	static inline void fnSInit(pXSR xsr, uint64_t* ui64Seed, uint8_t ui8XSR) {
		switch (ui8XSR) {
		case 0b11:
		#if (_XSR_512 == 1)
			xsr->pS = malloc(sizeof(uint64_t) * 8);
			if (xsr->pS) {
				for (int i = 0; i < 8; i++)
					((uint64_t*)xsr->pS)[i] = fnNextSM64(ui64Seed);
				xsr->fnSS = fnNext512ss;
				xsr->fnPP = fnNext512pp;
				xsr->fnP = fnNext512p;
				#if (_XSR_JUMP == 1)
					xsr->fnLJ = fnLJump512;
					xsr->fnSJ = fnSJump512;
				#endif
			} break;
		#else
			xsr->pS = 0;
			return;
		#endif
		case 0b10:
		#if (_XSR_256 == 1)
			xsr->pS = malloc(sizeof(uint64_t) * 4);
			if (xsr->pS) {
				for (int i = 0; i < 4; i++)
					((uint64_t*)xsr->pS)[i] = fnNextSM64(ui64Seed);
				xsr->fnSS = fnNext256ss;
				xsr->fnPP = fnNext256pp;
				xsr->fnP = fnNext256p;
				#if (_XSR_JUMP == 1)
					xsr->fnLJ = fnLJump256;
					xsr->fnSJ = fnSJump256;
				#endif
			} break;
		#else
			xsr->pS = 0;
			return;
		#endif
		case 0b01:
		#if (_XSR_128 == 1)
			xsr->pS = malloc(sizeof(uint32_t) * 4);
			if (xsr->pS) {
				for (int i = 0; i < 4; i++)
					((uint32_t*)xsr->pS)[i] = fnNextSM64(ui64Seed) >> 32;
				xsr->fnSS = (uint64_t (*)(void*))fnNext128ss;
				xsr->fnPP = (uint64_t (*)(void*))fnNext128pp;
				xsr->fnP = (uint64_t (*)(void*))fnNext128p;
				#if (_XSR_JUMP == 1)
					xsr->fnLJ = fnLJump128;
					xsr->fnSJ = fnSJump128;
				#endif
			}
		#else
			xsr->pS = 0;
			return;
		#endif
		}
	}
	static inline void fnXSRInit(pXSR xsr, sXSRPA sParamA) {
		#if (_XSR_JUMP == 1)
			for (uint8_t i = 0; i < sParamA.lj; i++)
				xsr->fnLJ(xsr->pS);
			for (uint8_t i = 0; i < sParamA.sj; i++)
				xsr->fnSJ(xsr->pS);
		#endif
		for (uint16_t i = 0; i < sParamA.ns; i++)
			xsr->fnP(xsr->pS);
	}
#endif

/* XoShiRo Algorithm Interface Tool's *////////////////////////////////////////////////////////////////////////////////////////
#ifdef _XSR_
	pXSR fnAllocXSR(uint64_t ui64Seed, sXSRPA sParamA, sXSRPB sParamB) {
		if (!sParamA.mod)
			return 0;
		fnSMPInit(&ui64Seed, &sParamA, &sParamB);

		pXSR xsr = malloc(sizeof(sXSR));
		if (xsr) {
			fnSInit(xsr, &ui64Seed, (uint8_t)(sParamA.mod));
			if (xsr->pS)
				fnXSRInit(xsr, sParamA);
			else {
				free(xsr);
				return 0;
			}
		} else
			return 0;

		return xsr;
	}
	#if (_XSR_SCON == 1)
		pXSR fnRelocXSR(pXSR xsr, uint64_t ui64Seed, sXSRPA sParamA, sXSRPB sParamB) {
			if (!xsr)
				return 0;
			if (!sParamA.mod) {
				fnDelocXSR(xsr);
				return 0;
			}
			fnSMPInit(&ui64Seed, &sParamA, &sParamB);

			uint8_t ui8Cmp = 0;
			#if (_XSR_512 == 1)
				if (xsr->fnSS == fnNext512ss)
					ui8Cmp = 3;
				else
			#endif
			#if (_XSR_256 == 1)
				if (xsr->fnSS == fnNext256ss)
					ui8Cmp = 2;
				else
			#endif
			#if (_XSR_128 == 1)
				if (xsr->fnSS == (uint64_t (*)(void*))fnNext128ss)
					ui8Cmp = 1;
			#else
					;
			#endif

			if (sParamA.mod == ui8Cmp) {
				#if (_XSR_512 == 1)
					if (xsr->fnSS == fnNext512ss)
						for (int i = 0; i < 8; i++)
							((uint64_t*)xsr->pS)[i] = fnNextSM64(&ui64Seed);
					else
				#endif
				#if (_XSR_256 == 1)
					if (xsr->fnSS == fnNext256ss)
						for (int i = 0; i < 4; i++)
							((uint64_t*)xsr->pS)[i] = fnNextSM64(&ui64Seed);
					else
				#endif
				#if (_XSR_128 == 1)
					if (xsr->fnSS == (uint64_t (*)(void*))fnNext128ss)
						for (int i = 0; i < 4; i++)
							((uint32_t*)xsr->pS)[i] = fnNextSM64(&ui64Seed) >> 32;
				#else
						;
				#endif
			} else {
				free(xsr->pS);
				fnSInit(xsr, &ui64Seed, (uint8_t)sParamA.mod);
				if (!xsr->pS) {
					free(xsr);
					return 0;
				}
			}

			fnXSRInit(xsr, sParamA);
			return xsr;
		}
		pXSR fnCopyXSR(pXSR xsr) {
			if (!xsr)
				return 0;

			pXSR xsrC = malloc(sizeof(sXSR));
			if (!xsrC)
				return 0;

			#if (_XSR_512 == 1)
				if (xsr->fnSS == fnNext512ss) {
					xsrC->pS = malloc(sizeof(uint64_t) * 8);
					memcpy(xsrC->pS, xsr->pS, sizeof(uint64_t) * 8);
				} else
			#endif
			#if (_XSR_256 == 1)
				if (xsr->fnSS == fnNext256ss) {
					xsrC->pS = malloc(sizeof(uint64_t) * 4);
					memcpy(xsrC->pS, xsr->pS, sizeof(uint64_t) * 4);
				} else
			#endif
			#if (_XSR_128 == 1)
				if (xsr->fnSS == (uint64_t (*)(void*))fnNext128ss) {
					xsrC->pS = malloc(sizeof(uint32_t) * 4);
					memcpy(xsrC->pS, xsr->pS, sizeof(uint32_t) * 4);
				}
			#else
					;
			#endif

			xsrC->fnSS = xsr->fnSS;
			xsrC->fnPP = xsr->fnPP;
			xsrC->fnP = xsr->fnP;
			#if (_XSR_JUMP == 1)
				xsrC->fnLJ = xsr->fnLJ;
				xsrC->fnSJ = xsr->fnSJ;
			#endif

			return xsrC;
		}
	#endif
	void fnDelocXSR(pXSR xsr) {
		if (!xsr)
			return;

		if (xsr->pS)
			free(xsr->pS);
		free(xsr);
		xsr = 0;
	}
#endif