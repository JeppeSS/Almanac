#ifndef SECRETKEY_H
#define SECRETKEY_H

#include <gmp.h>



/*
 * === Structure ==============================================================
 *         Name:  Secret key (SK)
 *
 *  Description: The secret key is an odd eta-bit integer:
 *
 *      SK <-- (2Z + 1) ∩ [2^{eta - 1}, 2^{eta})
 * ============================================================================
 */
typedef struct{

    // Security Parameter.
    unsigned int lambda;

    // Bit-length of the secret key.
    unsigned int eta;

    // 0 = success, 1 = failed.
    unsigned char error;

    // Secret key.
    mpz_t secK;
} SK;

// Initializer
void sk_init(SK *sk, unsigned int lambda);

// Generator
SK genSK(unsigned int lambda);

// Cleanup
void skClean(SK *sk);

#endif
