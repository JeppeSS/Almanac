#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

#include "../crypto/rand/random.h"


int main(void){

    printf("Testing random functions\n");

    int numTest = 4;
    int correct = 0;

    mpz_t randT1, rangT1;
    mpz_t randT2, rangT2;
    mpz_t randT3, rangT3;
    mpz_t randT4, rangT4;

    mpz_inits(randT1, rangT1, NULL);
    mpz_inits(randT2, rangT2, NULL);
    mpz_inits(randT3, rangT3, NULL);
    mpz_init(rangT4);

    mpz_set_ui(rangT1, 10);
    mpz_set_ui(rangT2, 1500000000);
    
    int base;
    base = mpz_set_str(rangT3, "150000000000000000000000000000000", 10);
    
    mpz_set_ui(rangT4, 1000);

    if(base < 0){
        fprintf(stderr, "[ERROR] Testing random failed\n");
        return EXIT_FAILURE;
    }

    int ret = randomUniform(randT1, rangT1);

    if(ret){
        fprintf(stderr, "[ERROR] Testing random failed\n");
        return EXIT_FAILURE;
    }

    if(mpz_cmp_ui(randT1, 0) < 0 || mpz_cmp_ui(randT1, 11) > 0){
        fprintf(stdout, "Test 1: Failed\n");
    } else{
        correct++;
    }
    
    int ret2 = randomUniform(randT2, rangT2);

    if(ret2){
        fprintf(stderr, "[ERROR] Testing random failed\n");
        return EXIT_FAILURE;
    }
    
    if(mpz_cmp_ui(randT2, 0) < 0 || mpz_cmp_ui(randT2, 15000000001) > 0){
        fprintf(stdout, "Test 2: Failed\n");
    } else{
        correct++;
    }
    
    int ret3 = randomUniform(randT3, rangT3);

    if(ret3){
        fprintf(stderr, "[ERROR] Testing random failed\n");
        return EXIT_FAILURE;
    }

    
    if(mpz_cmp_ui(randT3, 0) < 0 ||
       mpz_cmp(randT3, rangT3) > 0){
        fprintf(stdout, "Test 3: Failed\n");
    } else{
        correct++;
    }

    
    int ret4;
    int flag = 0;
    for(int i = 0; i < 2000; i++){
        
        mpz_init(randT4);

        
        ret4 = randomUniform(randT4, rangT4);
        
        if(ret4){
            fprintf(stderr, "[ERROR] Testing random failed\n");
            return EXIT_FAILURE;
        }
        
        if(mpz_cmp_ui(randT4, 0) < 0 || mpz_cmp_ui(randT4, 1000) > 0){
            flag = 1;
        }

        mpz_clear(randT4);

    }

    if(flag){
        fprintf(stdout, "Test 3: Failed\n");
    } else {
        correct++;
    }



    mpz_clears(randT1, rangT1, NULL);
    mpz_clears(randT2, rangT2, NULL);
    mpz_clears(randT3, rangT3, NULL);
    mpz_clear(rangT4);
    
    printf("Test result: %d/%d correct\n", correct, numTest);
    return 0;
}

