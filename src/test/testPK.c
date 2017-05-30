#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

#include "../crypto/secretkey.h"
#include "../crypto/publickey.h"


int main(void){

    printf("Testing Public key generation\n");

    int numTest = 0;
    int correct = 0;
    SK sk;
    PK pk;

    sk = genSK(2);

    if(sk.error){
        fprintf(stderr, "[ERROR] Secret key generation failed\n");
    }

    pk = genPK(&sk, 2);


    for(unsigned int i = 0; i < pk.tau; i++){
        gmp_printf("%Zd\n", pk.pubK[i]);
    }


    printf("Test result: %d/%d correct\n", correct, numTest);

    pkClean(&pk);


    return 0;
}

