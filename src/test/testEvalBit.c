#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

#include "../crypto/secretkey.h"
#include "../crypto/publickey.h"
#include "../crypto/chipertext.h"
#include "../crypto/dghv.h"


int main(void){
    printf("Testing Bit evaluation\n");
    
    int numTest = 5;
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

    pk = genPK(&sk);
    
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
    

    mpz_t eval;
    mpz_init(eval);

    evaluateBit(eval, chiper1, chiper2);

    int bit;

    bit = decryptBit(&sk, eval);

    if(bit == 0){
        fprintf(stdout, "Test 1: Failed\n");
    } else{
        correct++;
    }

    mpz_clear(eval);
    
    ret = encryptBit(chiper3, &pk, 1);

    if(ret){
        fprintf(stderr, "[ERROR] Bit encryption failed\n");
        return EXIT_FAILURE;
    }
    
    mpz_init(eval);

    evaluateBit(eval, chiper1, chiper3);

    bit = decryptBit(&sk, eval);

    if(bit){
        fprintf(stdout, "Test 2: Failed\n");
    } else{
        correct++;
    }

    mpz_clear(eval);
    
    ret = encryptBit(chiper4, &pk, 1);
    
    if(ret){
        fprintf(stderr, "[ERROR] Bit encryption failed\n");
        return EXIT_FAILURE;
    }
    
    mpz_init(eval);

    evaluateBit(eval, chiper1, chiper4);

    bit = decryptBit(&sk, eval);

    if(bit){
        fprintf(stdout, "Test 3: Failed\n");
    } else{
        correct++;
    }

    mpz_clear(eval);

    ret = encryptBit(chiper5, &pk, 0);
    
    if(ret){
        fprintf(stderr, "[ERROR] Bit encryption failed\n");
        return EXIT_FAILURE;
    }
    
    mpz_init(eval);

    evaluateBit(eval, chiper1, chiper5);

    bit = decryptBit(&sk, eval);

    if(bit == 0){
        fprintf(stdout, "Test 4: Failed\n");
    } else{
        correct++;
    }

    mpz_clear(eval);
    
    ret = encryptBit(chiper6, &pk, 1);

    if(ret){
        fprintf(stderr, "[ERROR] Bit encryption failed\n");
        return EXIT_FAILURE;
    }

    mpz_init(eval);

    evaluateBit(eval, chiper1, chiper6);

    bit = decryptBit(&sk, eval);

    if(bit){
        fprintf(stdout, "Test 5: Failed\n");
    } else{
        correct++;
    }

    mpz_clear(eval);
    
    skClean(&sk);
    pkClean(&pk);


    mpz_clears(chiper1, chiper2, chiper3, chiper4, chiper5, chiper6, NULL);

    printf("Test result: %d/%d correct\n", correct, numTest);
    
    return EXIT_SUCCESS;
}
