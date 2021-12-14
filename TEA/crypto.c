// #include "dev_cc1101.h"
// #include "crypto.h"

#include "tea.h"

static uint8_t crypto_enable = 1;

#define CC1101_FIFO_LEN 64
#define KEY_LEN 4
#define ROUNDS 32


uint8_t cc1101_fifo[CC1101_FIFO_LEN];
uint8_t key[KEY_LEN];


void Crypto_SetMode(uint8_t const * key, int keysize) {
	crypto_enable = (keysize >= 0);
	
	// use key
}

void Crypto_Cipher(void)
{
	if (!crypto_enable)
		return;

	for (uint8_t i = 0; i < ROUNDS; i++)
	{
		encrypt(cc1101_fifo + 2u * i, key);
	}

}

void Crypto_Decipher(void)
{
	if (!crypto_enable)
		return;

	for (uint8_t i = 0; i < ROUNDS; i++)
	{
		decrypt(cc1101_fifo + 2u * i, key);
	}
}

////////////////	TEST	//////////////////
#include <stdio.h>

int main() {
	for (uint8_t i = 0; i < KEY_LEN; ++i) {
		key[i] = i;
	}

	for (uint8_t i = 0; i < CC1101_FIFO_LEN; ++i) {
		cc1101_fifo[i] = 62u + i;
	}
	printf("Message: %s\n", cc1101_fifo);

	Crypto_Cipher();
	printf("Encrypted: %s\n", cc1101_fifo);
	
	Crypto_Decipher();
	printf("Decrypted: %s\n", cc1101_fifo);

}