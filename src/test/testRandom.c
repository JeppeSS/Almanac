#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

#include "../crypto/rand/random.h"


int main(void){

    printf("Testing random functions\n");

    int numTest = 7;
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
        fprintf(stdout, "Test 4: Failed\n");
    } else {
        correct++;
    }


    mpz_t val1, min1, max1;
    mpz_inits(min1, max1, NULL);

    mpz_set_ui(min1, 50);
    mpz_set_ui(max1, 100);

    int ret5; 
    flag = 0;
    
    for(int i = 0; i < 2000; i++){
        
        mpz_init(val1);
        
        ret5 = randomRange(val1, min1, max1);
        
        if(ret5){
            fprintf(stderr, "[ERROR] Testing random failed\n");
            return EXIT_FAILURE;
        }
        
        if(mpz_cmp(val1, min1) < 0 || mpz_cmp(val1, max1) > 0){
            flag = 1;
        }


        mpz_clear(val1);

    }

    if(flag){
        fprintf(stdout, "Test 5: Failed\n");
    } else {
        correct++;
    }
    
    mpz_t val2, min2, max2;
    mpz_inits(min2, max2, NULL);

    mpz_set_str(min2, "10000000000", 10);
    mpz_set_str(max2, "150000000000000000000000000000000", 10);

    int ret6; 
    flag = 0;
    
    for(int i = 0; i < 200; i++){
        
        mpz_init(val2);
        
        ret6 = randomRange(val2, min2, max2);
        
        if(ret6){
            fprintf(stderr, "[ERROR] Testing random failed\n");
            return EXIT_FAILURE;
        }
        
        if(mpz_cmp(val2, min2) < 0 || mpz_cmp(val2, max2) > 0){
            flag = 1;
        }


        mpz_clear(val2);

    }

    if(flag){
        fprintf(stdout, "Test 6: Failed\n");
    } else {
        correct++;
    }
    
    mpz_t val3, min3, max3;
    mpz_inits(val3, min3, max3, NULL);

    mpz_set_ui(min3, 10);
    mpz_set_ui(max3, 5);

    int ret7 = randomRange(val3, min3, max3);

    if(ret7){
        correct++;
    }else{
        fprintf(stdout, "Test 7: Failed\n");
    }


    mpz_clears(randT1, rangT1, NULL);
    mpz_clears(randT2, rangT2, NULL);
    mpz_clears(randT3, rangT3, NULL);
    mpz_clear(rangT4);
    mpz_clears(min1, max1, NULL);
    mpz_clears(min2, max2, NULL);
    mpz_clears(min3, max3, NULL);
    mpz_clear(val3);
    
    printf("Test result: %d/%d correct\n", numTest, correct);
    return 0;
}

