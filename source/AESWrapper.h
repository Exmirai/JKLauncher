#ifndef __AES_WRAPPER_H__
#define __AES_WRAPPER_H__

#define DEFAULT_AES_KEYBITS 256
#define DEFAULT_AES_KEYLEN 32

namespace AESWrap
{
    int generateIV(unsigned char *iv, size_t len);
    int generateKey(unsigned char *key, size_t len);

    int encrypt(const unsigned char *plainText, size_t plainTextLen,
        unsigned char *cipherText, size_t cipherTextSize,
        const unsigned char *key, size_t keyLen,
        unsigned char *IV, size_t IVLen);

    int decrypt(const unsigned char *cipherText, size_t cipherTextLen,
        unsigned char *plainText, size_t plainTextSize, size_t plainLen,
        const unsigned char *key, size_t keyLen,
        unsigned char *IV, size_t IVLen);

    void performanceTest();
}
#endif // __AES_WRAPPER_H__