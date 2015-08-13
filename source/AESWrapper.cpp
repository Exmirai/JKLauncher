#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <openssl/aes.h>
#include <openssl/rand.h>

#include "AESWrapper.h"

namespace AESWrap
{
    int encrypt(const unsigned char *plainText, size_t plainTextLen,
        unsigned char *cipherText, size_t cipherTextSize,
        const unsigned char *key, size_t keyLen,
        unsigned char *IV, size_t IVLen)
    {
        int lenNeed = (plainTextLen % AES_BLOCK_SIZE) == 0 ? plainTextLen : (plainTextLen / AES_BLOCK_SIZE + 1) * AES_BLOCK_SIZE;
        if (lenNeed >= cipherTextSize)
        {
            return -1;
        }

        AES_KEY aesKey;
        AES_set_encrypt_key(key, keyLen * 8, &aesKey);
        AES_cbc_encrypt(plainText, cipherText, lenNeed, &aesKey, IV, AES_ENCRYPT);

        return lenNeed;
    }

    int decrypt(const unsigned char *cipherText, size_t cipherTextLen,
        unsigned char *plainText, size_t plainTextSize, size_t plainLen,
        const unsigned char *key, size_t keyLen,
        unsigned char *IV, size_t IVLen)
    {
        if (plainLen >= plainTextSize)
        {
            return -1;
        }

        AES_KEY aesKey;
        AES_set_decrypt_key(key, keyLen * 8, &aesKey);
        AES_cbc_encrypt(cipherText, plainText, cipherTextLen, &aesKey, IV, AES_DECRYPT);
        plainText[plainLen] = '\0';

        return plainLen;
    }

    int generateIV(unsigned char *iv, size_t len)
    {
        return RAND_bytes(iv, len);
    }

    int generateKey(unsigned char *key, size_t len)
    {
        return RAND_bytes(key, len);
    }

    void performanceTest()
    {
        return;

        unsigned char c[32768] = { 0 };

        unsigned char p[1024] = { 0 };
        RAND_bytes(p, 1024);

        unsigned char key[32] = { 0 };
        generateKey(key, 32);
        unsigned char IV[AES_BLOCK_SIZE] = { 0 };
        generateIV(IV, AES_BLOCK_SIZE);

        printf("Started performance test.\n");
        time_t startTime = time(0);
        for (int i = 0; i < 1000000; i++)
        {
            encrypt(p, 1024, c, 32768, key, 32, IV, AES_BLOCK_SIZE);
        }
        time_t stopTime = time(0);
        time_t workTime = stopTime - startTime;
        double opps = (double)1000000 / (double)workTime;
        printf("Stopped performance test, test took %u seconds.\n", workTime);
    }
}