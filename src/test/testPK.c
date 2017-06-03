#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

#include "../crypto/secretkey.h"
#include "../crypto/publickey.h"


int main(void){

    printf("Testing Public key generation\n");

    int numTest = 2;
    int correct = 0;
    SK sk;
    PK pk;

    sk = genSK(6);

    if(sk.error){
        fprintf(stderr, "[ERROR] Secret key generation failed\n");
        return EXIT_FAILURE;
    }

    pk = genPK(&sk);
    
    if(pk.error){
        fprintf(stderr, "[ERROR] Public key generation failed\n");
        return EXIT_FAILURE;
    }

    mpz_t x0;
    mpz_init(x0);

    mpz_set(x0, pk.pubK[0]);

    int flag = 0;
    for(unsigned int i = 1; i < pk.tau; i++){
        if(mpz_cmp(x0, pk.pubK[i]) < 0){
            flag = 1;
        }
    }

    if(flag){
        fprintf(stdout, "Test 1: Failed\n");
    } else{
        correct++;
    }

    SK sk2;
    PK pk2;

    sk2 = genSK(6);

    if(sk2.error){
        fprintf(stderr, "[ERROR] Secret key generation failed\n");
        return EXIT_FAILURE;
    }

    pk2 = genPK(&sk2);
    
    if(pk2.error){
        fprintf(stderr, "[ERROR] Public key generation failed\n");
        return EXIT_FAILURE;
    }

    if(mpz_even_p(pk2.pubK[0])){
        fprintf(stdout, "Test 2: Failed\n");
    } else {
        correct++;
    }

    printf("Test result: %d/%d correct\n", correct, numTest);

    skClean(&sk);
    pkClean(&pk);
    skClean(&sk2);
    pkClean(&pk2);

    mpz_clear(x0);


    return 0;
}

