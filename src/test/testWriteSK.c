#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

#include "../crypto/secretkey.h"
#include "../crypto/fm/filemanager.h"


int main(void){

    printf("Testing Secret file writing key\n");

    int numTest = 1;
    int correct = 0;
    SK sk;

    sk = genSK(8);

    if(sk.error){
        fprintf(stderr, "[ERROR] Secret key generation failed\n");
    }

    int retVal;
    retVal = writeSK(&sk, "secretKey.txt");
    
    if(retVal){
        fprintf(stderr, "[ERROR] Writing key to file failed\n");
    }

    SK sk2;

    sk2 = readSK("secretKey.txt"); 

    if(mpz_cmp(sk.secK, sk2.secK) == 0){
        correct++;
    } else {
        fprintf(stdout, "Test 1: Failed\n"); 
    }


    skClean(&sk);
    skClean(&sk2);


    printf("Test result: %d/%d correct\n", correct, numTest);


    return 0;
}

