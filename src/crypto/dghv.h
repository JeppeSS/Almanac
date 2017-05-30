#ifndef DGHV_H
#define DGHV_H

#include <gmp.h>

#include "publickey.h"
#include "secretkey.h"

int encryptBit(mpz_t chiper, PK *pk, int bit);
int decryptBit(SK *sk, mpz_t chiper);

#endif
