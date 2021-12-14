#include "tea.h"


const uint8_t delta = 0x9e;


void encrypt(uint8_t* values, const uint8_t* key) {
    uint8_t sum = 0;

	for (uint8_t i = 0; i < 32; i++) {
        sum += delta;
        values[0] += ((values[1] << 4) + key[0]) ^ (values[1] + sum) ^ ((values[1] >> 5) + key[1]);
        values[1] += ((values[0] << 4) + key[2]) ^ (values[0] + sum) ^ ((values[0] >> 5) + key[3]);
	}
}


void decrypt(uint8_t* values, const uint8_t* key) {
    uint8_t sum = delta << 5u;

	for (uint8_t i = 0; i < 32; i++) {
        values[1] -= ((values[0] << 4) + key[2]) ^ (values[0] + sum) ^ ((values[0] >> 5) + key[3]);
        values[0] -= ((values[1] << 4) + key[0]) ^ (values[1] + sum) ^ ((values[1] >> 5) + key[1]);
        sum -= delta;
    }
}