#ifndef __RSA_WRAPPER_H__
#define __RSA_WRAPPER_H__

#define DEFAULT_RSA_PADDING RSA_PKCS1_OAEP_PADDING
#define DEFAULT_RSA_EXP 65537
#define DEFAULT_RSA_KEYLEN 4096

namespace RSAWrap
{
    RSA *createRSAKeypair(char *pubKey, char *privKey);
    RSA *createRSAPublic(char *pubKey);
    RSA *createRSAPrivate(char *privKey);

    int generateRSA(int exp, int bits, char *privKey, int privKeyLen, char *pubKey, int pubKeyLen);

    // reads RSA key in PEM format from a file.
    int readKey(const char *filename, char *key, int keyLen, bool isPublic);

    int encrypt(const unsigned char *plainText, size_t plainTextLen,
                unsigned char *cipherText, size_t cipherTextSize,
                char *pubKey, int padding);

    int encrypt(const unsigned char *plainText, size_t plainTextLen,
                unsigned char *cipherText, size_t cipherTextSize,
                RSA *pubKey, int padding);

    int decrypt(const unsigned char *cipherText, size_t cipherTextLen,
                unsigned char *plainText, size_t plainTextSize,
                char *privKey, int padding);

    int decrypt(const unsigned char *cipherText, size_t cipherTextLen,
                unsigned char *plainText, size_t plainTextSize,
                RSA *privKey);
}
#endif