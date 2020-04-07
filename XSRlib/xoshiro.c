#include "xoshiro.h"

/* XoShiRo Rotate Sub Tool's *///////////////////////////////////////////////////////
#ifdef XSR_
static inline uint64_t rotl64(const uint64_t ui64X, uint8_t ui8K) {
	return (ui64X << ui8K) | (ui64X >> (64 - ui8K));
}
static inline uint32_t rotl32(const uint32_t ui32X, uint8_t ui8K) {
	return (ui32X << ui8K) | (ui32X >> (32 - ui8K));
}
#endif

/* XoShiRo512-64Bit Algorithm *//////////////////////////////////////////////////////
#if (defined(XSR_512) && (XSR_512 == 1))
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
	((uint64_t*)xsr)[7] = rotl64(((uint64_t*)xsr)[7], 21);
}

static uint64_t fnNext512ss(pXSR xsr) {
	const uint64_t ui64R = rotl64(((uint64_t*)xsr)[1] * 5, 7) * 9;
	fnNext512(xsr);
	return ui64R;
}
static uint64_t fnNext512pp(pXSR xsr) {
	const uint64_t ui64R = rotl64(((uint64_t*)xsr)[0] +
		((uint64_t*)xsr)[2], 17) + ((uint64_t*)xsr)[2];
	fnNext512(xsr);
	return ui64R;
}
static uint64_t fnNext512p(pXSR xsr) {
	const uint64_t ui64R = ((uint64_t*)xsr)[0] + ((uint64_t*)xsr)[2];
	fnNext512(xsr);
	return ui64R;
}

static inline void fnJump512(const uint64_t ui64_8[], pXSR xsr) {
	uint64_t ui64T[8];
	memset(ui64T, 0, sizeof(ui64T));
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 64; j++) {
			if (ui64_8[i] & (1Ui64 << j))
				for (int n = 0; n < 8; n++)
					ui64T[n] ^= ((uint64_t*)xsr)[n];
			fnNext512(xsr);
		}
	memcpy(xsr, ui64T, sizeof(xsr));
}

/* This is the long-jump function for the generator. It is equivalent to
   2^384 calls to next(); it can be used to generate 2^128 starting points,
   from each of which jump() will generate 2^128 non-overlapping
   subsequences for parallel distributed computations. */
static void fnLJump512(pXSR xsr) {
	static const uint64_t ui64Jump[] = {
		0x11467fef8f921d28, 0xa2a819f2e79c8ea8, 0xa8299fc284b3959a, 0xb4d347340ca63ee1,
		0x1cb0940bedbff6ce, 0xd956c5c4fa1f8e17, 0x915e38fd4eda93bc, 0x5b3ccdfa5d7daca5
	};
	fnJump512(ui64Jump, xsr);
}

/* This is the jump function for the generator. It is equivalent
   to 2^256 calls to next(); it can be used to generate 2^256
   non-overlapping subsequences for parallel computations. */
static void fnSJump512(pXSR xsr) {
	static const uint64_t ui64Jump[] = {
		0x33ed89b6e7a353f9, 0x760083d7955323be, 0x2837f2fbb5f22fae, 0x4b8c5674d309511c,
		0xb11ac47a7ba28c25, 0xf1be7667092bcc1c, 0x53851efdb6df0aaf, 0x1ebbc8b23eaf25db
	};
	fnJump512(ui64Jump, xsr);
}
#endif

/* XoShiRo256-64Bit Algorithm *//////////////////////////////////////////////////////
#if (defined(XSR_256) && (XSR_256 == 1))
static inline void fnNext256(pXSR xsr) {
	const uint64_t ui64T = ((uint64_t*)xsr)[1] << 17;
	((uint64_t*)xsr)[2] ^= ((uint64_t*)xsr)[0];
	((uint64_t*)xsr)[3] ^= ((uint64_t*)xsr)[1];
	((uint64_t*)xsr)[1] ^= ((uint64_t*)xsr)[2];
	((uint64_t*)xsr)[0] ^= ((uint64_t*)xsr)[3];
	((uint64_t*)xsr)[2] ^= ui64T;
	((uint64_t*)xsr)[3] = rotl64(((uint64_t*)xsr)[3], 45);
}

static uint64_t fnNext256ss(pXSR xsr) {
	const uint64_t ui64R = rotl64(((uint64_t*)xsr)[1] * 5, 7) * 9;
	fnNext256(xsr);
	return ui64R;
}
static uint64_t fnNext256pp(pXSR xsr) {
	const uint64_t ui64R = rotl64(((uint64_t*)xsr)[0] +
		((uint64_t*)xsr)[3], 23) + ((uint64_t*)xsr)[0];
	fnNext256(xsr);
	return ui64R;
}
static uint64_t fnNext256p(pXSR xsr) {
	const uint64_t ui64R = ((uint64_t*)xsr)[0] + ((uint64_t*)xsr)[3];
	fnNext256(xsr);
	return ui64R;
}

static inline void fnJump256(const uint64_t ui64_4[], pXSR xsr) {
	uint64_t s0 = 0, s1 = 0, s2 = 0, s3 = 0;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 64; j++) {
			if (ui64_4[i] & (1Ui64 << j)) {
				s0 ^= ((uint64_t*)xsr)[0];
				s1 ^= ((uint64_t*)xsr)[1];
				s2 ^= ((uint64_t*)xsr)[2];
				s3 ^= ((uint64_t*)xsr)[3];
			}
			fnNext256(xsr);
		}

	((uint64_t*)xsr)[0] = s0; ((uint64_t*)xsr)[1] = s1;
	((uint64_t*)xsr)[2] = s2; ((uint64_t*)xsr)[3] = s3;
}

/* This is the long-jump function for the generator. It is equivalent to
   2^192 calls to next(); it can be used to generate 2^64 starting points,
   from each of which jump() will generate 2^64 non-overlapping
   subsequences for parallel distributed computations. */
static void fnLJump256(pXSR xsr) {
	static const uint64_t ui64_4Jump[] = {
		0x76e15d3efefdcbbf, 0xc5004e441c522fb3, 0x77710069854ee241, 0x39109bb02acbe635
	};
	fnJump256(ui64_4Jump, xsr);
}

/* This is the jump function for the generator. It is equivalent
   to 2^128 calls to next(); it can be used to generate 2^128
   non-overlapping subsequences for parallel computations. */
static void fnSJump256(pXSR xsr) {
	static const uint64_t ui64_4Jump[] = {
		0x180ec6d33cfd0aba, 0xd5a61266f0c9392c, 0xa9582618e03fc9aa, 0x39abdc4529b1661c
	};
	fnJump256(ui64_4Jump, xsr);
}
#endif

/* XoShiRo128-32Bit Algorithm *//////////////////////////////////////////////////////
#if (defined(XSR_128) && (XSR_128 == 1))
static inline void fnNext128(pXSR xsr) {
	const uint32_t ui32T = ((uint32_t*)xsr)[1] << 9;
	((uint32_t*)xsr)[2] ^= ((uint32_t*)xsr)[0];
	((uint32_t*)xsr)[3] ^= ((uint32_t*)xsr)[1];
	((uint32_t*)xsr)[1] ^= ((uint32_t*)xsr)[2];
	((uint32_t*)xsr)[0] ^= ((uint32_t*)xsr)[3];
	((uint32_t*)xsr)[2] ^= ui32T;
	((uint32_t*)xsr)[3] = rotl32(((uint32_t*)xsr)[3], 11);
}

static uint32_t fnNext128ss(pXSR xsr) {
	const uint32_t ui32R = rotl32(((uint32_t*)xsr)[1] * 5, 7) * 9;
	fnNext128(xsr);
	return ui32R;
}
static uint32_t fnNext128pp(pXSR xsr) {
	const uint32_t ui32R = rotl32(((uint32_t*)xsr)[0] +
		((uint32_t*)xsr)[3], 7) + ((uint32_t*)xsr)[0];
	fnNext128(xsr);
	return ui32R;
}
static uint32_t fnNext128p(pXSR xsr) {
	const uint32_t ui32R = ((uint32_t*)xsr)[0] + ((uint32_t*)xsr)[3];
	fnNext128(xsr);
	return ui32R;
}

static inline void fnJump128(const uint32_t ui32_4[], pXSR xsr) {
	uint32_t s0 = 0, s1 = 0, s2 = 0, s3 = 0;
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

	((uint32_t*)xsr)[0] = s0; ((uint32_t*)xsr)[1] = s1;
	((uint32_t*)xsr)[2] = s2; ((uint32_t*)xsr)[3] = s3;
}

/* This is the long-jump function for the generator. It is equivalent to
   2^96 calls to next(); it can be used to generate 2^32 starting points,
   from each of which jump() will generate 2^32 non-overlapping
   subsequences for parallel distributed computations. */
static void fnLJump128(pXSR xsr) {
	const uint32_t ui32_4Jump[] = {
		0xb523952e, 0x0b6f099f, 0xccf5a0ef, 0x1c580662
	};
	fnJump128(ui32_4Jump, xsr);
}

/* This is the jump function for the generator. It is equivalent
   to 2^64 calls to next(); it can be used to generate 2^64
   non-overlapping subsequences for parallel computations. */
static void fnSJump128(pXSR xsr) {
	const uint32_t ui32_4Jump[] = {
		0x8764000b, 0xf542d2d3, 0x6fa035c3, 0x77f2db5b
	};
	fnJump128(ui32_4Jump, xsr);
}
#endif

/* SplitMix64Bit Algorithm */////////////////////////////////////////////////////////
#ifdef XSR_
static uint64_t fnNextSM(uint64_t* ui64SM) {
	uint64_t ui64Z = (*ui64SM += 0x9e3779b97f4a7c15);
	ui64Z = (ui64Z ^ (ui64Z >> 30)) * 0xbf58476d1ce4e5b9;
	ui64Z = (ui64Z ^ (ui64Z >> 27)) * 0x94d049bb133111eb;
	return ui64Z ^ (ui64Z >> 31);
}
#endif

/* XoShiRo Algorithm Interface Tool's *//////////////////////////////////////////////

/*	ui32XSR: 00-000-00000000-00000000-00000000000
	Bit: 31-30: Binary  - GeneratorType:       11 = 512b; 10 = 256b; 01 = 128b;
		 29-27: Bitwise - Random Initializers: 100 = LJ; 010 = SJ; 001 = NS;
		 26-19: Binary  - Count of LongJumps:  0-255;
		 18-11: Binary  - Count of ShortJumps: 0-255;
		 10-0:  Binary  - Count of NextState:  0-2047;

	ui8SM: 0-0000000
	Bit: 7:   Bitwise - Random Initializers: 1 = NS;
		 6-0: Binary  - Count of NextState:  0-127; */
pXSRT fnAllocXSR(
	uint64_t ui64Seed,
	uint32_t ui32XSR,
	uint8_t ui8SM
) {
	if (!(ui32XSR >> 30))
		return 0;

	/* SM64 Init */
	if (ui8SM >> 7)
		ui8SM |= (uint8_t)fnNextSM(&ui64Seed) >> 1;
	for (int i = 0; i < (ui8SM & 0x7f); i++)
		fnNextSM(&ui64Seed);

	/* XSR Init */
	if ((ui32XSR >> 29) & 0x1)
		ui32XSR |= (uint8_t)fnNextSM(&ui64Seed) << 19;
	if ((ui32XSR >> 28) & 0x1)
		ui32XSR |= (uint8_t)fnNextSM(&ui64Seed) << 11;
	if ((ui32XSR >> 27) & 0x1)
		ui32XSR |= (uint16_t)fnNextSM(&ui64Seed) & 0x7ff;

	void (*fnLJumpT)(pXSR) = 0;
	void (*fnSJumpT)(pXSR) = 0;
	void (*fnNextT)(pXSR) = 0;
	pXSRT xsr = calloc(1, sizeof(sXSRT));
	switch (ui32XSR >> 30) {
	case 0b11:
		xsr->pS = malloc(sizeof(uint64_t) * 8);
		for (int i = 0; i < 8; i++)
			((uint64_t*)xsr->pS)[i] = fnNextSM(&ui64Seed);
		fnLJumpT = fnLJump512; fnSJumpT = fnSJump512; fnNextT = fnNext512;
		xsr->fnSS = fnNext512ss; xsr->fnPP = fnNext512pp; xsr->fnP = fnNext512p;
		xsr->fnLJ = fnLJump512; xsr->fnSJ = fnSJump512;
		break;
	case 0b10:
		xsr->pS = malloc(sizeof(uint64_t) * 4);
		for (int i = 0; i < 4; i++)
			((uint64_t*)xsr->pS)[i] = fnNextSM(&ui64Seed);
		fnLJumpT = fnLJump256; fnSJumpT = fnSJump256; fnNextT = fnNext256;
		xsr->fnSS = fnNext256ss; xsr->fnPP = fnNext256pp; xsr->fnP = fnNext256p;
		xsr->fnLJ = fnLJump256; xsr->fnSJ = fnSJump256;
		break;
	case 0b01:
		xsr->pS = malloc(sizeof(uint32_t) * 4);
		for (int i = 0; i < 4; i++)
			((uint32_t*)xsr->pS)[i] = (uint32_t)(fnNextSM(&ui64Seed) >> 32);
		fnLJumpT = fnLJump128; fnSJumpT = fnSJump128; fnNextT = fnNext128;
		xsr->fnSS = (uint64_t(*)(pXSR))fnNext128ss;
		xsr->fnPP = (uint64_t(*)(pXSR))fnNext128pp;
		xsr->fnP = (uint64_t(*)(pXSR))fnNext128p;
		xsr->fnLJ = fnLJump128; xsr->fnSJ = fnSJump128;
	}

	for (int i = 0; i < (uint8_t)(ui32XSR >> 19); i++)
		fnLJumpT(xsr->pS);
	for (int i = 0; i < (uint8_t)(ui32XSR >> 11); i++)
		fnSJumpT(xsr->pS);
	for (int i = 0; i < (uint16_t)(ui32XSR & 0x7ff); i++)
		fnNextT(xsr->pS);

	return xsr;
}

void fnDeAllocXSR(pXSRT xsr) {
	free(xsr->pS);
	free(xsr);
}

//#include <stdio.h>
/* Test Stuff (Don't touch that) */
uint64_t ui64URngDist(uint64_t ui64Max, uint64_t ui64Min, pXSRT64 xsrT64);
int main() {
	// Test Speed
	pXSRT test = fnAllocXSR(531678126513478261,
		0b10111000000010000000100000000001, 0b10000001);
	uint64_t a = test->fnSS(test->pS);

	for (uint32_t i = 0; i < (uint32_t)-1; i++)
		a = test->fnSS(test->pS);

	fnDeAllocXSR(test);

	/* Test Uniform Distrubution
	test256 = fnXSRSetup(531678126513478261,
		0b10111000000010000000100000000001, 0b10000001);
	double nA = 0;
	uint64_t nB = 0;
	uint64_t nBC = 0;

	for (uint64_t i = 0; i < (uint64_t)-1; i++) {
		double A = fnDURngDistC(i);
		if (A == nA) {
			nB++;
		} else {
			nA = A;
			if (nB != nBC) {
				printf_s("ERROR\n");
			}
			printf_s("B: %u\n", nB);
			nBC = nB;
			nB = 0;
		}
	}
	free(test256); */

	return 0;
}