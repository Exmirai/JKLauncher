#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/rsa.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/err.h>
#include <stdio.h>

#include "RSAWrapper.h"

namespace RSAWrap
{
    RSA* createRSAKeypair(char *pubKey, char *privKey)
    {
        RSA *rsa = NULL;
        BIO *keybio;
        keybio = BIO_new_mem_buf(pubKey, -1);
        if (keybio == NULL)
        {
            printf("Failed to create key BIO");
            return 0;
        }
        rsa = PEM_read_bio_RSA_PUBKEY(keybio, &rsa, NULL, NULL);

        BIO_free_all(keybio);

        keybio = BIO_new_mem_buf(privKey, -1);
        if (keybio == NULL)
        {
            printf("Failed to create key BIO");
            return 0;
        }
        rsa = PEM_read_bio_RSAPrivateKey(keybio, &rsa, NULL, NULL);

        if (rsa == NULL)
        {
            printf("Failed to create RSA: %s\n", ERR_error_string(ERR_get_error(), NULL));
        }

        BIO_free_all(keybio);

        return rsa;
    }

    RSA *createRSAPublic(char *pubKey)
    {
        RSA *rsa = NULL;
        BIO *keybio;
        keybio = BIO_new_mem_buf(pubKey, -1);
        if (keybio == NULL)
        {
            printf("Failed to create key BIO");
            return 0;
        }

        rsa = PEM_read_bio_RSA_PUBKEY(keybio, &rsa, NULL, NULL);

        if (rsa == NULL)
        {
            printf("Failed to create RSA: %s\n", ERR_error_string(ERR_get_error(), NULL));
        }

        BIO_free_all(keybio);

        return rsa;
    }

    RSA *createRSAPrivate(char *privKey)
    {
        RSA *rsa = NULL;
        BIO *keybio;
        keybio = BIO_new_mem_buf(privKey, -1);
        if (keybio == NULL)
        {
            printf("Failed to create key BIO");
            return 0;
        }
        rsa = PEM_read_bio_RSAPrivateKey(keybio, &rsa, NULL, NULL);

        if (rsa == NULL)
        {
            printf("Failed to create RSA: %s\n", ERR_error_string(ERR_get_error(), NULL));
        }

        BIO_free_all(keybio);

        return rsa;
    }

    int generateRSA(int exp, int bits, char *privKey, int privKeyLen, char *pubKey, int pubKeyLen)
    {
        int keylen;

        RSA *rsa = RSA_generate_key(bits, exp, 0, 0);

        BIO *bio = BIO_new(BIO_s_mem());

        // public
        PEM_write_bio_RSA_PUBKEY(bio, rsa);
        keylen = BIO_pending(bio);
        if (keylen >= pubKeyLen)
        {
            BIO_free_all(bio);
            RSA_free(rsa);
            return -1;
        }

        BIO_read(bio, pubKey, keylen);

        BIO_free_all(bio);

        bio = BIO_new(BIO_s_mem());
        // private
        PEM_write_bio_RSAPrivateKey(bio, rsa, NULL, NULL, 0, NULL, NULL);

        keylen = BIO_pending(bio);
        if (keylen >= privKeyLen)
        {
            BIO_free_all(bio);
            RSA_free(rsa);
            return -1;
        }

        BIO_read(bio, privKey, keylen);
        BIO_free_all(bio);

        RSA_free(rsa);

        return 0;
    }

    int readKey(const char* filename, char* key, int keyLen, bool isPublic)
    {
        FILE* fp = fopen(filename, "rb");
        if (!fp)
            return -1;

        fseek(fp, 0, SEEK_END);
        int fileSize = ftell(fp);
        rewind(fp);

        if (fileSize >= keyLen)
        {
            fclose(fp);
            return -1;
        }

        size_t ret = fread(key, sizeof(char), fileSize, fp);
        fclose(fp);

        return ret;
    }

    int encrypt(const unsigned char *plainText, size_t plainTextLen,
                unsigned char *cipherText, size_t cipherTextSize,
                char *pubKey, int padding)
    {
        RSA *pubKeyRSA = createRSAPublic(pubKey);
        int encLen = RSA_public_encrypt(plainTextLen, plainText, cipherText, pubKeyRSA, padding);
        RSA_free(pubKeyRSA);

        return encLen;
    }

    int encrypt(const unsigned char *plainText, size_t plainTextLen,
                unsigned char *cipherText, size_t cipherTextSize,
                RSA *pubKey, int padding)
    {
        return RSA_public_encrypt(plainTextLen, plainText, cipherText, pubKey, padding);
    }

    int decrypt(const unsigned char *cipherText, size_t cipherTextLen,
                unsigned char *plainText, size_t plainTextSize,
                char *privKey, int padding)
    {
        RSA *privKeyRSA = createRSAPrivate(privKey);
        int decrLen = RSA_private_decrypt(cipherTextLen, cipherText, plainText, privKeyRSA, padding);
        RSA_free(privKeyRSA);
        return decrLen;
    }

    int decrypt(const unsigned char *cipherText, size_t cipherTextLen,
                unsigned char *plainText, size_t plainTextSize,
                RSA *privKey, int padding)
    {
        return RSA_private_decrypt(cipherTextLen, cipherText, plainText, privKey, padding);
    }


}
