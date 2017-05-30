#ifndef PUBLICKEY_H
#define PUBLICKEY_H

#include <gmp.h>

#include "secretkey.h"

/*
 * === Structure ==============================================================
 *         Name:  Public key (PK)
 *
 *  Description: The public key contains a vector, and some parameters
 *  depending on lambda.
 *
 *  pubK = (x_{0}, x_{1}, ..., x_{tau})
 *
 *  Where x_{0} is the largest element.
 * ============================================================================
 */
typedef struct{

    // Security Parameter.
    unsigned int lambda;

    // Bit-length of noise
    unsigned int rho;
    unsigned int rhoM;

    // Bit-length of the integers in the public key
    unsigned int gamma;

    // Number of integers in the public key
    unsigned int tau;

    // 0 = success, 1 = failed.
    unsigned char error;

    // Secret key.
    mpz_t *pubK;
} PK;


// Initializer
int pk_init(PK *pk, unsigned int lambda);

// Generators
PK genPK(SK *sk, unsigned int lambda);

// Cleanup
void pkClean(PK *pk);
#endif
