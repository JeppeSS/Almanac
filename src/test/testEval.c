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
    
    printf("Testing String Encryption\n");
    
    int numTest = 1;
    int correct = 0;
    SK sk;
    PK pk;

    Plaintext msg = text("Tekst streng test");

    Plaintext msg2 = text("2ekst streng test");
    Plaintext msg3 = text("Tekst sdreng test");
    Plaintext msg3 = text("Tekst stfdsreng test");
    Plaintext msg5 = text("Tekst stregg test");
    
    Plaintext msg6 = text("Tekst streng test");
    
    
    Plaintext msg7 = text("Tekst streng test");

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


    Chipertext chiper = encrypt(&pk, &msg);
    
    Plaintext decr = decrypt(&sk, &chiper);

    
    int comp1 = strcmp(msg.msg, decr.msg);


    if(comp1 != 0){
        fprintf(stdout, "Test 1: Failed\n"); 
    } else {
        correct++;
    }
    


    skClean(&sk);
    pkClean(&pk);
    
    printf("Test result: %d/%d correct\n", numTest, correct);


    return EXIT_SUCCESS;
}
