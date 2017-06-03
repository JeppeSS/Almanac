#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

#include "publickey.h"
#include "secretkey.h"
#include "dghv.h"
#include "plaintext.h"
#include "chipertext.h"
#include "rand/random.h"


/* 
 * === Function ===============================================================
 *         Name: Encrypts a single bit.
 *
 *  Description: Encrypts a single bit, takes a placeholder for the chier,
 *  a public key, and a bit.
 * ============================================================================
 */
int encryptBit(mpz_t chiper, PK *pk, int bit){

    // Set tau, r, sum = 0
    mpz_t subStart, subEnd, tau, r, sum;
    mpz_inits(tau, r, sum, NULL);

    // Set tau to the number of vales in the public key.
    mpz_set_ui(tau, pk->tau);

    // Find a random subset from the public key vector.
    unsigned long int start = 0;
    unsigned long int end   = 0;
    
    // Keeps running if start or end is = 0.
    int errorStart;
    int errorEnd;
    while(start == 0 || end == 0){
        
        mpz_init(subStart);
        mpz_init(subEnd);
        
        errorStart = randomUniform(subStart, tau);
        
        // Random failed.
        if(errorStart){
            return EXIT_FAILURE;
        }

        errorEnd = randomUniform(subEnd, tau);
        
        // Random failed.
        if(errorEnd){
            return EXIT_FAILURE;
        }

        start = mpz_get_ui(subStart);
        end   = mpz_get_ui(subEnd);

        // Swap if start is larger than end,
        // to reduce loop runs.
        if(start > end){
            start = mpz_get_ui(subEnd);
            end   = mpz_get_ui(subStart);
        }

        // Eliminate subset range and free memory.
        mpz_set_ui(subStart, 0);
        mpz_set_ui(subEnd, 0);
        mpz_clears(subStart, subEnd, NULL);
    }

    // Define range 2^{rhoM} as encryption noise
    mpz_ui_pow_ui(r, 2, pk->rhoM);

    
    int errorR = randomUniform(r, r);

    // If random fails
    if(errorR){
        return EXIT_FAILURE;
    }

    // Sum the subset generated.
    for(unsigned long int i = start; i < end; i++){
        mpz_add(sum, sum, pk->pubK[i]);
    }


    // set r = 2*r
    mpz_mul_si(r, r, 2);

    long unsigned int bits = (long unsigned int) bit;


    // set chiper = bit + 2r + Sum(subset)
    mpz_add_ui(sum, sum, bits);
    mpz_add(r, r, sum);
    mpz_mod(chiper, r, pk->pubK[0]);
    
    
    // Set values to 0 and free memory.
    mpz_set_ui(tau, 0);
    mpz_set_ui(r, 0);
    mpz_set_ui(sum, 0);


    mpz_clear(tau);
    mpz_clear(r);
    mpz_clear(sum);

    return EXIT_SUCCESS;
}


/* 
 * === Function ===============================================================
 *         Name: decrypts a single bit.
 *
 *  Description: Decrypts a single bit, takes the secret key and the
 *  chipertext. Returns the bit.
 * ============================================================================
 */
int decryptBit(SK *sk, mpz_t chiper){

    // Set plain = 0
    mpz_t plain;
    mpz_init(plain);


    // (chiper % secK) % 2
    mpz_mod(plain, chiper, sk->secK);
    mpz_mod_ui(plain, plain, 2);

    long unsigned int val = mpz_get_ui(plain);
    
    int bit = (int) val;
    

    return bit;
}


/* 
 * === Function ===============================================================
 *         Name: Encrypts a text string
 *
 *  Description: Encrypts a whole text sring, return a chipertext structure
 * ============================================================================
 */
Chipertext encrypt(PK *pk, Plaintext *plain){

    Chipertext chiper;

    chiper_init(&chiper, plain->size);

    // Encrypt each bit seapretly and store in a vector of encrypted
    // bits
    for(unsigned int i = 0; i < plain->size; i++){
        encryptBit(chiper.chiper[i], pk, plain->bin[i]);
    }

    return chiper;
}

/* 
 * === Function ===============================================================
 *         Name: decrypts a text string
 *
 *  Description: decrypts a whole text sring, return a plaintext structure
 * ============================================================================
 */
Plaintext decrypt(SK *sk, Chipertext *chiper){
    Plaintext plain;

    plain.msg  = calloc(chiper->size, sizeof(int));
    plain.bin  = calloc(chiper->size * 8, sizeof(int));
    plain.size = chiper->size;

    // Decrypt each bit seapretly and store in a vector of bits.
    for(unsigned int i = 0; i < plain.size; i++){
        plain.bin[i] = decryptBit(sk, chiper->chiper[i]);
    }

    // Convert the binary representation to string.
    fromBinary(&plain);

    return plain;

}

/* 
 * === Function ===============================================================
 *         Name: evaluateBit
 *
 *  Description: Evaluates two single bits, when decrypted 0 if equal 1
 *  otherwise
 * ============================================================================
 */
void evaluateBit(mpz_t chiper, mpz_t chiper1, mpz_t chiper2){
    mpz_add(chiper, chiper1, chiper2);
}

