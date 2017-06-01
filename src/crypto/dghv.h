#ifndef DGHV_H
#define DGHV_H

#include <gmp.h>

#include "publickey.h"
#include "secretkey.h"
#include "plaintext.h"
#include "chipertext.h"

// Bit operation functions functions
int encryptBit(mpz_t chiper, PK *pk, int bit);
int decryptBit(SK *sk, mpz_t chiper);

// Text encryption / decryption
Chipertext encrypt(PK *pk, Plaintext *plain);
Plaintext decrypt(SK *sk, Chipertext *chiper);

// Evaluate two bits (Compare).
void evaluateBit(mpz_t chiper, mpz_t chiper1, mpz_t chiper2);
// Evaluate two strings (Compare).
void evaluate(Chipertext *res, Chipertext *chiper1, Chipertext *chiper2);

#endif
