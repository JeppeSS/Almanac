#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

#include "../crypto/secretkey.h"


int main(void){

    printf("Testing Secret key generation\n");

    int numTest = 2;
    int correct = 0;
    SK sk;

    int flag = 0;
    for(int i = 0; i < 2000; i++){
        sk = genSK(8);

        if(sk.error){
            fprintf(stderr, "[ERROR] Secret key generation failed\n");
        }

        if(mpz_even_p(sk.secK)){
            flag = 1;
        }
        skClean(&sk);
    }


    if(flag){
        fprintf(stdout, "Test 1: Failed\n");
    } else {
        correct++;
    }
    
    flag = 0;
    size_t bitSize;
    for(int i = 0; i < 2000; i++){
        sk = genSK(12);

        if(sk.error){
            fprintf(stderr, "[ERROR] Secret key generation failed\n");
        }

        bitSize = mpz_sizeinbase(sk.secK, 2);

        if(bitSize != sk.eta){
            flag = 1;
        }
        skClean(&sk);
    }


    if(flag){
        fprintf(stdout, "Test 2: Failed\n");
    } else {
        correct++;
    }

    printf("Test result: %d/%d correct\n", correct, numTest);


    return 0;
}

