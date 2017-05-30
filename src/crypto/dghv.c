#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

#include "publickey.h"
#include "secretkey.h"
#include "dghv.h"
#include "rand/random.h"



int encryptBit(mpz_t chiper, PK *pk, int bit){

    mpz_t subStart, subEnd, tau, r, sum;
    mpz_inits(tau, r, sum, NULL);

    mpz_set_ui(tau, pk->tau);

    unsigned long int start = 0;
    unsigned long int end   = 0;
    
    int errorStart;
    int errorEnd;
    while(start == 0 || end == 0){
        
        mpz_init(subStart);
        mpz_init(subEnd);
        
        errorStart = randomUniform(subStart, tau);
        
        if(errorStart){
            return EXIT_FAILURE;
        }

        errorEnd = randomUniform(subEnd, tau);
        
        if(errorEnd){
            return EXIT_FAILURE;
        }

        start = mpz_get_ui(subStart);
        end   = mpz_get_ui(subEnd);

        // Swap if start is larger than end.
        if(start > end){
            start = mpz_get_ui(subEnd);
            end   = mpz_get_ui(subStart);
        }

        mpz_set_ui(subStart, 0);
        mpz_set_ui(subEnd, 0);
        mpz_clears(subStart, subEnd, NULL);
    }

    mpz_ui_pow_ui(r, 2, pk->rhoM);

    int errorR = randomUniform(r, r);
    
    if(errorR){
        return EXIT_FAILURE;
    }

    for(unsigned long int i = start; i < end; i++){
        mpz_add(sum, sum, pk->pubK[i]);
    }


    mpz_mul_si(r, r, 2);

    long unsigned int bits = (long unsigned int) bit;

    mpz_add_ui(sum, sum, bits);
    mpz_add(r, r, sum);

    mpz_mod(chiper, r, pk->pubK[0]);

    mpz_set_ui(tau, 0);
    mpz_set_ui(r, 0);
    mpz_set_ui(sum, 0);

    mpz_clear(tau);
    mpz_clear(r);
    mpz_clear(sum);

    return EXIT_SUCCESS;
}

int decryptBit(SK *sk, mpz_t chiper){

    // Set plain = 0
    mpz_t plain;
    mpz_init(plain);


    mpz_mod(plain, chiper, sk->secK);
    mpz_mod_ui(plain, plain, 2);

    long unsigned int val = mpz_get_ui(plain);
    
    int bit = (int) val;
    

    return bit;
}
