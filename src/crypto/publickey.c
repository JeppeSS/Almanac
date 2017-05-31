#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gmp.h>
#include <omp.h>

#include "rand/random.h"
#include "secretkey.h"
#include "publickey.h"

// Helper function
static int pkSample(mpz_t sample, SK *sk, PK *pk);
static void sort(PK *pk);


/* 
 * === Function ===============================================================
 *         Name: pk_init
 *
 *  Description: Initialize the public key
 * ============================================================================
 */
int pk_init(PK *pk, unsigned int lambda){
    
    // Set all parameters according to lambda.
    pk->rho    = lambda;
    pk->rhoM   = 2*lambda;
    pk->gamma  = (unsigned int) pow(lambda, 5);
    pk->tau    = pk->gamma + lambda + 1;
    pk->error  = 0;
    
    // Allocate (tau * byte size of mpz_t struct) size.
    // The PK array contains a array of pointers to mpz_t values.
    pk->pubK = malloc(pk->tau * sizeof(mpz_t));

    // Memory allocation failed.
    if(!pk->pubK){
        fprintf(stderr, "[Error] Public key memory allocation failed\n");
        return EXIT_FAILURE;
    }

    // Set all values in PK to 0
    for(unsigned int i = 0; i < pk->tau; i++){
        mpz_init(pk->pubK[i]);
    }

    return EXIT_SUCCESS;
}

/*
 * === Function ===============================================================
 *         Name: pkSample
 *
 *  Description: For a specific (eta-bit) odd positive integer SK, the
 *  following distribution over gamma-bit integers, generates a sample.
 * ============================================================================
 */
static int pkSample(mpz_t sample, SK *sk, PK *pk){
    
    // q <-- [0, 2^{gamma} / secK).
    // r <-- [0, 2^{rho}]. 
    mpz_t q, r;

    // Holds the random number in q and r's range.
    mpz_t randq;
    mpz_t randr;

    // Set values = 0
    mpz_inits(q, r, randq, randr, NULL);

    // q <-- 2^{gamma} / secK
    mpz_ui_pow_ui(q, 2, pk->gamma);
    mpz_tdiv_q(q, q, sk->secK);

    // r <-- 2^{rho}
    mpz_ui_pow_ui(r, 2, pk->rho);

    int ret = randomUniform(randq, q);

    if(ret){
        return EXIT_FAILURE;
    }

    ret = randomUniform(randr, r);
    
    if(ret){
        return EXIT_FAILURE;
    }

    // sample <-- secK * q + 2r
    mpz_mul(sample, sk->secK, randq);
    mpz_mul_si(randr, randr, 2);
    mpz_add(sample, sample, randr);


    // Set values = 0
    mpz_set_ui(q, 0);
    mpz_set_ui(r, 0);
    mpz_set_ui(randq, 0);
    mpz_set_ui(randr, 0);

    // Free memory
    mpz_clears(q, r, randq, randr, NULL);

    return EXIT_SUCCESS;
}


/*
 * === Function ===============================================================
 *         Name: sort
 *
 *  Description: Find the largest value in the public key vector and swaps it
 *  with x_{0}.
 * ============================================================================
 */
static void sort(PK *pk){
    
    // Find the largest element and set it to x_{0}
    mpz_t tmp;
    mpz_init(tmp);

    // Only swap if needed
    unsigned int swap = 0;
    unsigned int index;

    mpz_set(tmp, pk->pubK[0]);

    for(unsigned int i = 0; i < pk->tau; i++){
        if(mpz_cmp(tmp, pk->pubK[i]) < 0){
            mpz_set(tmp, pk->pubK[i]);
            index = i;

            swap = 1;
        }
    }

    if(swap){
        // Swap the elements
        mpz_set(pk->pubK[index], pk->pubK[0]);
        mpz_set(pk->pubK[0], tmp);
    }

    // Clear the tmp variable
    mpz_set_ui(tmp, 0);
    mpz_clear(tmp);
}

/*
 * === Function ===============================================================
 *         Name: genPK
 *
 *  Description: Generates a public key vector
 *  pk = (x_{0}, x_{1}, ..., x_{tau})
 * ============================================================================
 */
PK genPK(SK *sk){

    // Initialize the public key
    PK pk;
    int allocate = pk_init(&pk, sk->lambda);

    // Memory allocation failed.
    if(allocate){
        pk.error = 1;
        return pk;
    }

    mpz_t res;
    mpz_init(res);

    // Generate public key vector. Relabel so that x_{0} is the largest.
    // Restart unless x_{0} is odd and rp(x_{0}) is even.
    int error;
    while(mpz_odd_p(res) || mpz_even_p(pk.pubK[0])){
        
        // Generates samples for all values in the public key vector.
        #pragma omp parallel for
        for(unsigned int i = 0; i < pk.tau; i++){
            error = pkSample(pk.pubK[i], sk, &pk);
            
            // Sample failed.
            if(error){
                pk.error  = 1;
            }
        }

        // Sort the public key vector so x_{0} is the largest.
        // !! ONLY swap the largest and x_{0} !!
        sort(&pk);

        // Find the reminder.
        mpz_tdiv_q(res, pk.pubK[0], sk->secK);
        mpz_mod(res, pk.pubK[0], sk->secK);
    }

    // Set res = 0
    mpz_set_ui(res, 0);

    // Free memory
    mpz_clear(res);

    return pk;
}

/*
 * === Function ===============================================================
 *         Name: pkClean
 *
 *  Description: Free pk memory
 * ============================================================================
 */
void pkClean(PK *pk){

    for(unsigned int i = 0; i < pk->tau; i++){
        mpz_set_ui(pk->pubK[i], 0);
        mpz_clear(pk->pubK[i]);
    }

    pk->rho    = 0;
    pk->rhoM   = 0;
    pk->gamma  = 0;
    pk->tau    = 0;
}
