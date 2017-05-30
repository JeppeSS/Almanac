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


SK genSK(unsigned int lambda){

    fprintf(stdout, "[OK] Generating Secret key\n");
    
    // Initialize a new secret key.
    SK sk;
    sk_init(&sk, lambda);
    
    fprintf(stdout, "[OK] Size: %d bit\n", sk.eta);
    fprintf(stdout, "[OK] Please wait..\n");

    mpz_t min, max;
    mpz_inits(min, max, NULL);

    mpz_set_ui(min, 2);
    mpz_set_ui(max, 2);

    mpz_pow_ui(min, min, sk.eta - 1);
    mpz_pow_ui(max, max, sk.eta);
    
    mpz_t randNum;
    mpz_init(randNum);

    int err;
    err = randomRange(randNum, min, max);

    if(err){
        sk.error = 1;
    }

    if(mpz_even_p(randNum)){
        mpz_sub_ui(randNum, randNum, 1);
    }

    mpz_clears(randNum, min, max, NULL);

    return sk;

    
}
