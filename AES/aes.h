#ifndef __AES_H__
#define __AES_H__

#include <stdint.h>
#include <string.h>

//#define ENABLE_SBOX_TABLE_ENCRYPT
#define ENABLE_SBOX_TABLE_DECRYPT



#define AES_BLOCK_SIZE              16u
#define AES_COLUMN_SIZE             4u
#define AES_NUM_COLUMNS             4u

#define AES_KEY_SCHEDULE_WORD_SIZE  4u

#define AES128_NUM_ROUNDS           10u
#define AES128_KEY_SIZE             16u
#define AES128_KEY_SCHEDULE_SIZE    (AES_BLOCK_SIZE * (AES128_NUM_ROUNDS + 1u))


static inline void aes_block_xor(uint8_t p_block[AES_BLOCK_SIZE], const uint8_t p_data[AES_BLOCK_SIZE]);

void aes128_otfks_encrypt(uint8_t p_block[AES_BLOCK_SIZE], uint8_t p_key[AES128_KEY_SIZE]);
void aes128_otfks_decrypt(uint8_t p_block[AES_BLOCK_SIZE], uint8_t p_decrypt_start_key[AES128_KEY_SIZE]);

#endif //__AES_H__