#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <math.h>

#include "secretkey.h"
#include "rand/random.h"

/* 
 * === Function ===============================================================
 *         Name: sk_init
 *
 *  Description: Initialize the secret key
 * ============================================================================
 */
void sk_init(SK *sk, unsigned int lambda){
    
    // Set security parameter.
    sk->lambda = lambda;

    // Initialize eta-bit size for key according
    // to lambda.
    sk->eta    = (unsigned int) pow(lambda, 2);

    // Initialize secK = 0.
    mpz_init(sk->secK);

    // Initialize to no error encountered.
    sk->error = 0;
}

/* 
 * === Function ===============================================================
 *         Name: genSK
 *
 *  Description: Generates a secret key, according to lambda.
 *  returns a SK structure.
 * ============================================================================
 */
SK genSK(unsigned int lambda){

    // Initialize a new secret key.
    SK sk;
    sk_init(&sk, lambda);
    
    // Set min, max = 0
    mpz_t min, max;
    mpz_inits(min, max, NULL);

    // min = 2^{eta-1}
    // max = 2^{eta}
    mpz_set_ui(min, 2);
    mpz_set_ui(max, 2);

    mpz_pow_ui(min, min, sk.eta - 1);
    mpz_pow_ui(max, max, sk.eta);
    
    // randNum = 0
    mpz_t randNum;
    mpz_init(randNum);

    int err;
    err = randomRange(randNum, min, max);

    // Error in randomRange happend.
    // Set secret key to 0 and exit.
    if(err){
        mpz_set_ui(sk.secK, 0);
        sk.error = 1;
        return sk;
    }

    // The secret key should be an odd integer.
    // If the key is even, subtract 1.
    if(mpz_even_p(randNum)){
        mpz_sub_ui(randNum, randNum, 1);
        
        // Check the bit length
        size_t bitSize =  mpz_sizeinbase(randNum, 2);
        
        // If the bitsize decreases, add 2.
        if(bitSize != sk.eta){
            mpz_add_ui(randNum, randNum, 2);
        }
    }

    // Set the secret key to randNum
    mpz_set(sk.secK, randNum);

    // To prevent attacker to find the secret key in memory.
    // Override before freeing.
    mpz_set_ui(randNum, 0);
    mpz_set_ui(min, 0);
    mpz_set_ui(max, 0);

    // Free memory
    mpz_clears(randNum, min, max, NULL);

    return sk;
}


/* 
 * === Function ===============================================================
 *         Name: skClean
 *
 *  Description: Set all values to 0 and free memory
 * ============================================================================
 */
void skClean(SK *sk){
    sk->lambda = 0;
    sk->eta    = 0;

    mpz_set_ui(sk->secK, 0);
    mpz_clear(sk->secK);
}
