#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>

#include "../crypto/secretkey.h"
#include "../crypto/publickey.h"
#include "../crypto/chipertext.h"
#include "../crypto/plaintext.h"
#include "../crypto/dghv.h"

int main(void){
    
    printf("Testing String Evaluation\n");
    
    int numTest = 3;
    int correct = 0;
    SK sk;
    PK pk;

    Plaintext msg = text("Tekst streng test");

    Plaintext msg2 = text("2ekst streng test");
    Plaintext msg3 = text("Tekst sdreng test");
    Plaintext msg4 = text("Tekst streng test");
    
    

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

    int flag;

    Chipertext chiper = encrypt(&pk, &msg);
    Chipertext chiper2 = encrypt(&pk, &msg2);
    
    Chipertext eval = evaluate(&chiper, &chiper2);

    Plaintext res = decrypt(&sk, &eval);
    
    flag = 0;
    for(unsigned int i = 0; i < res.size; i++){
        if(res.bin[i]){
            flag = 1;
        }
    }


    if(flag == 0){ 
        fprintf(stdout, "Test 1: Failed\n");
    } else {
        correct++;
    }
    
    Chipertext chiper3 = encrypt(&pk, &msg3);
    
    Chipertext eval2 = evaluate(&chiper, &chiper3);

    Plaintext res2 = decrypt(&sk, &eval2);
    
    flag = 0;
    for(unsigned int i = 0; i < res2.size; i++){
        if(res2.bin[i]){
            flag = 1;
        }
    }


    if(flag == 0){ 
        fprintf(stdout, "Test 2: Failed\n");
    } else {
        correct++;
    }

    Chipertext chiper4 = encrypt(&pk, &msg4);
    
    Chipertext eval3 = evaluate(&chiper, &chiper4);

    Plaintext res3 = decrypt(&sk, &eval3);
    
    flag = 0;
    for(unsigned int i = 0; i < res3.size; i++){
        if(res3.bin[i]){
            flag = 1;
        }
    }


    if(flag){ 
        fprintf(stdout, "Test 3: Failed\n");
    } else {
        correct++;
    }


    skClean(&sk);
    pkClean(&pk);
    
    printf("Test result: %d/%d correct\n", correct, numTest);


    return EXIT_SUCCESS;
}
