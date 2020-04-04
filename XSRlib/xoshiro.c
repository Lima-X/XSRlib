#include "xoshiro.h"

/* XoShiRo Rotate Sub Tool's */
#ifdef XSR
static inline uint64_t rotl64(const uint64_t ui64X, uint8_t ui8K) {
	return (ui64X << ui8K) | (ui64X >> (64 - ui8K));
}
static inline uint32_t rotl32(const uint32_t ui32X, uint8_t ui8K) {
	return (ui32X << ui8K) | (ui32X >> (32 - ui8K));
}
#endif

/* XoShiRo512-64Bit Algorithm */
#if (defined(_XSR512) && (_XSR512 == 1))
static uint64_t ui64_8S[8];
static inline void fnNext512(void) {
	const uint64_t ui64T = ui64_8S[1] << 11;
	ui64_8S[2] ^= ui64_8S[0];
	ui64_8S[5] ^= ui64_8S[1];
	ui64_8S[1] ^= ui64_8S[2];
	ui64_8S[7] ^= ui64_8S[3];
	ui64_8S[3] ^= ui64_8S[4];
	ui64_8S[4] ^= ui64_8S[5];
	ui64_8S[0] ^= ui64_8S[6];
	ui64_8S[6] ^= ui64_8S[7];
	ui64_8S[6] ^= ui64T;
	ui64_8S[7] = rotl64(ui64_8S[7], 21);
}

uint64_t fnNext512ss(void) {
	const uint64_t ui64R = rotl64(ui64_8S[1] * 5, 7) * 9;
	fnNext512();
	return ui64R;
}
uint64_t fnNext512pp(void) {
	const uint64_t ui64R = rotl64(ui64_8S[0] + ui64_8S[2], 17) + ui64_8S[2];
	fnNext512();
	return ui64R;
}
uint64_t fnNext512p(void) {
	const uint64_t ui64R = ui64_8S[0] + ui64_8S[2];
	fnNext512();
	return ui64R;
}

static inline void fnJump512(const uint64_t ui64_8[]) {
	uint64_t ui64T[sizeof(ui64_8S) / sizeof(*ui64_8S)];
	memset(ui64T, 0, sizeof ui64T);
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 64; j++) {
			if (ui64_8[i] & (1Ui64 << j))
				for (int n = 0; n < (sizeof(ui64_8S) / sizeof(*ui64_8S)); n++)
					ui64T[n] ^= ui64_8S[n];
			fnNext512();
		}
	memcpy(ui64_8S, ui64T, sizeof ui64_8S);
}

/* This is the jump function for the generator. It is equivalent
   to 2^256 calls to next(); it can be used to generate 2^256
   non-overlapping subsequences for parallel computations. */
void fnSJump512(void) {
	static const uint64_t ui64Jump[] = {
		0x33ed89b6e7a353f9, 0x760083d7955323be, 0x2837f2fbb5f22fae, 0x4b8c5674d309511c,
		0xb11ac47a7ba28c25, 0xf1be7667092bcc1c, 0x53851efdb6df0aaf, 0x1ebbc8b23eaf25db
	};
	fnJump512(ui64Jump);
}

/* This is the long-jump function for the generator. It is equivalent to
   2^384 calls to next(); it can be used to generate 2^128 starting points,
   from each of which jump() will generate 2^128 non-overlapping
   subsequences for parallel distributed computations. */
void fnLJump512(void) {
	static const uint64_t ui64Jump[] = {
		0x11467fef8f921d28, 0xa2a819f2e79c8ea8, 0xa8299fc284b3959a, 0xb4d347340ca63ee1,
		0x1cb0940bedbff6ce, 0xd956c5c4fa1f8e17, 0x915e38fd4eda93bc, 0x5b3ccdfa5d7daca5
	};
	fnJump512(ui64Jump);
}
#endif

/* XoShiRo256-64Bit Algorithm */
#if (defined(_XSR256) && (_XSR256 == 1))
static uint64_t ui64_4S[4];
static inline void fnNext256(void) {
	const uint64_t ui64T = ui64_4S[1] << 17;
	ui64_4S[2] ^= ui64_4S[0];
	ui64_4S[3] ^= ui64_4S[1];
	ui64_4S[1] ^= ui64_4S[2];
	ui64_4S[0] ^= ui64_4S[3];
	ui64_4S[2] ^= ui64T;
	ui64_4S[3] = rotl64(ui64_4S[3], 45);
}

uint64_t fnNext256ss(void) {
	const uint64_t ui64R = rotl64(ui64_4S[1] * 5, 7) * 9;
	fnNext256();
	return ui64R;
}
uint64_t fnNext256pp(void) {
	const uint64_t ui64R = rotl64(ui64_4S[0] + ui64_4S[3], 23) + ui64_4S[0];
	fnNext256();
	return ui64R;
}
uint64_t fnNext256p(void) {
	const uint64_t ui64R = ui64_4S[0] + ui64_4S[3];
	fnNext256();
	return ui64R;
}

static inline void fnJump256(const uint64_t ui64_4[]) {
	uint64_t s0 = 0, s1 = 0, s2 = 0, s3 = 0;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 64; j++) {
			if (ui64_4[i] & (1Ui64 << j)) {
				s0 ^= ui64_4S[0];
				s1 ^= ui64_4S[1];
				s2 ^= ui64_4S[2];
				s3 ^= ui64_4S[3];
			}
			fnNext256();
		}

	ui64_4S[0] = s0; ui64_4S[1] = s1; ui64_4S[2] = s2; ui64_4S[3] = s3;
}

/* This is the jump function for the generator. It is equivalent
   to 2^128 calls to next(); it can be used to generate 2^128
   non-overlapping subsequences for parallel computations. */
void fnSJump256(void) {
	static const uint64_t ui64_4Jump[] = {
		0x180ec6d33cfd0aba, 0xd5a61266f0c9392c, 0xa9582618e03fc9aa, 0x39abdc4529b1661c
	};
	fnJump256(ui64_4Jump);
}

/* This is the long-jump function for the generator. It is equivalent to
   2^192 calls to next(); it can be used to generate 2^64 starting points,
   from each of which jump() will generate 2^64 non-overlapping
   subsequences for parallel distributed computations. */
void fnLJump256(void) {
	static const uint64_t ui64_4Jump[] = {
		0x76e15d3efefdcbbf, 0xc5004e441c522fb3, 0x77710069854ee241, 0x39109bb02acbe635
	};
	fnJump256(ui64_4Jump);
}
#endif

/* XoShiRo128-32Bit Algorithm */
#if (defined(_XSR128) && (_XSR128 == 1))
static uint32_t ui32_4S[4];
static inline void fnNext128(void) {
	const uint32_t ui32T = ui32_4S[1] << 9;
	ui32_4S[2] ^= ui32_4S[0];
	ui32_4S[3] ^= ui32_4S[1];
	ui32_4S[1] ^= ui32_4S[2];
	ui32_4S[0] ^= ui32_4S[3];
	ui32_4S[2] ^= ui32T;
	ui32_4S[3] = rotl32(ui32_4S[3], 11);
}

uint32_t fnNext128ss(void) {
	const uint32_t ui32R = rotl32(ui32_4S[1] * 5, 7) * 9;
	fnNext128();
	return ui32R;
}
uint32_t fnNext128pp(void) {
	const uint32_t ui32R = rotl32(ui32_4S[0] + ui32_4S[3], 7) + ui32_4S[0];
	fnNext128();
	return ui32R;
}
uint32_t fnNext128p(void) {
	const uint32_t ui32R = ui32_4S[0] + ui32_4S[3];
	fnNext128();
	return ui32R;
}

static inline void fnJump128(const uint32_t ui32_4[]) {
	uint32_t s0 = 0, s1 = 0, s2 = 0, s3 = 0;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 32; j++) {
			if (ui32_4[i] & (0x1U << j)) {
				s0 ^= ui32_4S[0];
				s1 ^= ui32_4S[1];
				s2 ^= ui32_4S[2];
				s3 ^= ui32_4S[3];
			}
			fnNext128();
		}

	ui32_4S[0] = s0; ui32_4S[1] = s1; ui32_4S[2] = s2; ui32_4S[3] = s3;
}

/* This is the jump function for the generator. It is equivalent
   to 2^64 calls to next(); it can be used to generate 2^64
   non-overlapping subsequences for parallel computations. */
void fnSJump128(void) {
	const uint32_t ui32_4Jump[] = {
		0x8764000b, 0xf542d2d3, 0x6fa035c3, 0x77f2db5b
	};
	fnJump128(ui32_4Jump);
}

/* This is the long-jump function for the generator. It is equivalent to
   2^96 calls to next(); it can be used to generate 2^32 starting points,
   from each of which jump() will generate 2^32 non-overlapping
   subsequences for parallel distributed computations. */
void fnLJump128(void) {
	const uint32_t ui32_4Jump[] = {
		0xb523952e, 0x0b6f099f, 0xccf5a0ef, 0x1c580662
	};
	fnJump128(ui32_4Jump);
}
#endif

/* SplitMix64Bit Algorithm */
#ifdef XSR
static uint64_t ui64S;
static uint64_t fnNextSM() {
	uint64_t ui64Z = (ui64S += 0x9e3779b97f4a7c15);
	ui64Z = (ui64Z ^ (ui64Z >> 30)) * 0xbf58476d1ce4e5b9;
	ui64Z = (ui64Z ^ (ui64Z >> 27)) * 0x94d049bb133111eb;
	return ui64Z ^ (ui64Z >> 31);
}

void fnInitSM64(uint64_t ui64Seed, uint16_t ui16Init) {
	ui64S = ui64Seed;
	for (int i = 0; i < ui16Init; i++) {
		fnNextSM();
	}
}
#endif

/* XoShiRo Algorithm Interface Tool's */

pXSR fnAllocXSR(enum XSRT xsrType, uint16_t ui16Init) {
	if (ui16Init == (uint16_t)-1) {
		ui16Init = (uint16_t)(fnNextSM() >> 48);
	}

	pXSR pHeap;
	switch (xsrType) {
	case XSR512:
		pHeap = malloc(sizeof(uint64_t) * 8);

		for (int i = 0; i < 8; i++)
			((uint64_t*)pHeap)[i] = fnNextSM();
		for (int i = 0; i < ui16Init; i++)
			fnNext512();

		break;
	case XSR256:
		pHeap = malloc(sizeof(uint64_t) * 4);

		for (int i = 0; i < 4; i++)
			((uint64_t*)pHeap)[i] = fnNextSM();
		for (int i = 0; i < ui16Init; i++)
			fnNext256();

		break;
	case XSR128:
		pHeap = malloc(sizeof(uint32_t) * 4);

		for (int i = 0; i < 4; i++)
			((uint32_t*)pHeap)[i] = (uint32_t)(fnNextSM() >> 32);
		for (int i = 0; i < ui16Init; i++)
			fnNext128();

		break;
	default:
		return 0x00;
	}

	return pHeap;
}