#include "xoshiro.h"

#ifdef XSR
static uint64_t ui64S;
uint64_t fnNextSM() {
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