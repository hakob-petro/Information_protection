#ifndef TEA_H
#define TEA_H

#include <stdint.h>


extern const uint8_t delta;

void encrypt(uint8_t* values, const uint8_t* key);

void decrypt(uint8_t* values, const uint8_t* key);

#endif // TEA_H