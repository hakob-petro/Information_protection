//#include "dev_cc1101.h"
//#include "crypto.h"


//////////////////////////////////////
static int crypto_enable = 1;

#include "aes.h"

#define CC1101_FIFO_LEN 64
#define KEY_LEN 16

uint8_t cc1101_fifo[CC1101_FIFO_LEN];
uint8_t key[KEY_LEN];
//////////////////////////////////////

void Crypto_SetMode(uint8_t const * key, int keysize) {
	crypto_enable = (keysize >= 0);
	
	// use key
}

void Crypto_Cipher(void)
{
	if (!crypto_enable)
		return;
	

	for(uint8_t i = 0; i < 4; i++)
		aes128_otfks_encrypt(cc1101_fifo + i * 16u, key);
	
}

void Crypto_Decipher(void)
{
	if (!crypto_enable)
		return;
	
	for(uint8_t i = 3; i != 255; i--) 
		aes128_otfks_decrypt(cc1101_fifo + i * 16u, key);
}


////////////////	TEST	//////////////////
#include <stdlib.h>
#include <stdio.h>

int main() {
	for(uint8_t i = 0; i < KEY_LEN; ++i) {
		key[i] = i;
	}
	for(uint8_t i = 0; i < CC1101_FIFO_LEN; ++i) {
		cc1101_fifo[i] = 62u+i;
	}
	printf("%s\n", cc1101_fifo);

	Crypto_Cipher();
	printf("%s\n", cc1101_fifo);
	Crypto_Decipher();
	printf("%s\n", cc1101_fifo);

}