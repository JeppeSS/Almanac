#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

#include "../crypto/secretkey.h"
#include "../crypto/publickey.h"
#include "../crypto/chipertext.h"
#include "../crypto/dghv.h"


int main(void){
    printf("Testing Bit encryption\n");
    
    int numTest = 0;
    int correct = 0;
    SK sk;
    PK pk;

    mpz_t chiper1;
    mpz_t chiper2;
    mpz_t chiper3;
    mpz_t chiper4;
    mpz_t chiper5;
    mpz_t chiper6;

    mpz_inits(chiper1, chiper2, chiper3, chiper4, chiper5, chiper6, NULL);

    sk = genSK(8);
    
    if(sk.error){
        fprintf(stderr, "[ERROR] Secret key generation failed\n");
        return EXIT_FAILURE;
    }

    pk = genPK(&sk, 8);
    
    if(pk.error){
        fprintf(stderr, "[ERROR] Public key generation failed\n");
        return EXIT_FAILURE;
    }


    int ret;
    ret = encryptBit(chiper1, &pk, 1);

    if(ret){
        fprintf(stderr, "[ERROR] Bit encryption failed\n");
        return EXIT_FAILURE;
    }

    ret = encryptBit(chiper2, &pk, 0);
    
    if(ret){
        fprintf(stderr, "[ERROR] Bit encryption failed\n");
        return EXIT_FAILURE;
    }

    ret = encryptBit(chiper3, &pk, 1);

    if(ret){
        fprintf(stderr, "[ERROR] Bit encryption failed\n");
        return EXIT_FAILURE;
    }
    
    ret = encryptBit(chiper4, &pk, 1);
    
    if(ret){
        fprintf(stderr, "[ERROR] Bit encryption failed\n");
        return EXIT_FAILURE;
    }

    ret = encryptBit(chiper5, &pk, 0);
    
    if(ret){
        fprintf(stderr, "[ERROR] Bit encryption failed\n");
        return EXIT_FAILURE;
    }
    
    ret = encryptBit(chiper6, &pk, 1);

    if(ret){
        fprintf(stderr, "[ERROR] Bit encryption failed\n");
        return EXIT_FAILURE;
    }

    int bit;

    bit = decryptBit(&sk, chiper1);
    printf("%d\n", bit);
    
    bit = decryptBit(&sk, chiper2);
    printf("%d\n", bit);
    
    bit = decryptBit(&sk, chiper3);
    printf("%d\n", bit);
    
    bit = decryptBit(&sk, chiper4);
    printf("%d\n", bit);
    
    bit = decryptBit(&sk, chiper5);
    printf("%d\n", bit);
    
    bit = decryptBit(&sk, chiper6);
    printf("%d\n", bit);
    
    skClean(&sk);
    pkClean(&pk);


    mpz_clears(chiper1, chiper2, chiper3, chiper4, chiper5, chiper6, NULL);

    printf("Test result: %d/%d correct\n", numTest, correct);
    
    return EXIT_SUCCESS;
}
