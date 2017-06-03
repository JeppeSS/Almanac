#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

#include "../crypto/secretkey.h"
#include "../crypto/fm/filemanager.h"


int main(void){

    printf("Testing Public key file writing key\n");

    int numTest = 1;
    int correct = 0;
    SK sk;
    PK pk;

    sk = genSK(8);
    pk = genPK(&sk);

    if(sk.error){
        fprintf(stderr, "[ERROR] Secret key generation failed\n");
    }

    int retVal;
    retVal = writePK(&pk, "publickey.txt");
    
    if(retVal){
        fprintf(stderr, "[ERROR] Writing key to file failed\n");
    }


    PK pk2 = readPK("publickey.txt");

    int flag = 0;
    for(unsigned int i = 0; i < pk2.tau; i++){
        if(mpz_cmp(pk.pubK[i], pk2.pubK[i]) != 0){
            flag = 1;
        }
    }

    if(flag){
        fprintf(stdout, "Test 1: Failed\n"); 
    } else {
        correct++;
    }


    skClean(&sk);
    pkClean(&pk);


    printf("Test result: %d/%d correct\n", correct, numTest);


    return 0;
}

