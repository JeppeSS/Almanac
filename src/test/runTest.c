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
    
    fprintf(stdout, "HOMOMORPHIC ENCRYPTION\n");
    fprintf(stdout, "This test file will run some test on ID comparison.\n");
    fprintf(stdout, "It should be noted that due to the low lambda there is a probability that the test will fail.\n\n");
    
    SK sk;
    PK pk;

    fprintf(stdout, "[OK] Security Parameter set to 8\n");
    fprintf(stdout, "[OK] Generating Secret key\n");

    sk = genSK(8);
    fprintf(stdout, "[OK] Secret key of %d-bit generated\n", sk.eta);
    
    if(sk.error){
        fprintf(stderr, "[ERROR] Secret key generation failed\n");
        return EXIT_FAILURE;
    }

    fprintf(stdout, "[OK] Generating Public key\n");
    fprintf(stdout, "[OK] This could take some time, please wait...\n");

    pk = genPK(&sk);

    fprintf(stdout, "[OK] Public key with a vector of %d values each of %d-bits generated\n\n", pk.tau, pk.gamma);
    
    if(pk.error){
        fprintf(stderr, "[ERROR] Public key generation failed\n");
        return EXIT_FAILURE;
    }

    const char *ID1 = "SH-179EC"; 
    Plaintext ID1Pl = text(ID1);

    fprintf(stdout, "[OK] Encrypting the ID: %s\n", ID1);

    Chipertext ID1Ch = encrypt(&pk, &ID1Pl);


    size_t bitSize;
    size_t sum = 0;
    for(unsigned int i = 0; i < ID1Ch.size; i++){
        bitSize = mpz_sizeinbase(ID1Ch.chiper[i], 2);
        sum += bitSize;

    }
    
    fprintf(stdout, "[OK] Encryption done, chipertext size: %ld-bit\n", sum);

    fprintf(stdout, "[OK] Decrypting the ID, to test if Public key is correct\n");

    Plaintext ID1De = decrypt(&sk, &ID1Ch);

    fprintf(stdout, "[OK] Decrypting done, the decrypted value: %s\n", ID1De.msg);
    
    fprintf(stdout, "[OK] Comparing the decrypted value to the original ID\n");

    if(strcmp(ID1, ID1De.msg) != 0){
        fprintf(stderr, "[ERROR] Did not decrypt to original ID bad Public key, increase Lambda or try again\n");
        return EXIT_FAILURE;
    }

    fprintf(stdout, "[OK] Correct decryption\n\n");
    fprintf(stdout, "[OK] Will now try to compare two encrypted IDs\n");
    
    const char *ID2 = "SH-280EC"; 
    Plaintext ID2Pl = text(ID2);
    
    fprintf(stdout, "[OK] Encrypting the new ID: %s\n", ID2);


    Chipertext ID2Ch = encrypt(&pk, &ID2Pl);

    sum = 0;
    for(unsigned int i = 0; i < ID2Ch.size; i++){
        bitSize = mpz_sizeinbase(ID2Ch.chiper[i], 2);
        sum += bitSize;

    }

    fprintf(stdout, "[OK] Encryption done, chipertext size: %ld-bit\n", sum);
    fprintf(stdout, "[OK] Comparing the encrypted value of ID1: %s and ID2: %s\n", ID1, ID2);

    Chipertext eID1_ID2 = evaluate(&ID1Ch, &ID2Ch);

    fprintf(stdout, "[OK] Evaluation done, decrypting to see if equal\n");
    
    Plaintext eDe1 = decrypt(&sk, &eID1_ID2);

    int flag = 0;
    for(unsigned int i = 0; i < eDe1.size; i++){
        if(eDe1.bin[i]){
            flag = 1;
        }
    }

    if(!flag){
        fprintf(stderr, "[ERROR] IDs are equal, try increasing Lambda or try again\n");
        return EXIT_FAILURE;
    }
    
    fprintf(stdout, "[OK] IDs are not equal\n\n");

    fprintf(stdout, "[OK] Will now try to compare two identical IDs\n");

    const char *ID3 = "SH-179EC"; 
    Plaintext ID3Pl = text(ID3);

    fprintf(stdout, "[OK] Encrypting another ID: %s\n", ID3);

    Chipertext ID3Ch = encrypt(&pk, &ID3Pl);
    
    sum = 0;
    for(unsigned int i = 0; i < ID3Ch.size; i++){
        bitSize = mpz_sizeinbase(ID3Ch.chiper[i], 2);
        sum += bitSize;

    }
    
    fprintf(stdout, "[OK] Encryption done, chipertext size: %ld-bit\n", sum);
    fprintf(stdout, "[OK] Comparing the encrypted value of ID1: %s and ID3: %s\n", ID1, ID3);
    
    Chipertext eID1_ID3 = evaluate(&ID1Ch, &ID3Ch);

    fprintf(stdout, "[OK] Evaluation done, decrypting to see if equal\n");
    
    Plaintext eDe2 = decrypt(&sk, &eID1_ID3);

    flag = 0;
    for(unsigned int i = 0; i < eDe2.size; i++){
        if(eDe2.bin[i]){
            flag = 1;
        }
    }

    if(flag){
        fprintf(stderr, "[ERROR] IDs are not equal, try increasing Lambda or try again\n");
        return EXIT_FAILURE;
    }
    
    fprintf(stdout, "[OK] IDs are equal\n\n");
    
    SK sk2;
    PK pk2;

    fprintf(stdout, "[OK] Will now compare same ID encrypted with different key\n");
    fprintf(stdout, "[OK] Security Parameter set to 8\n");
    fprintf(stdout, "[OK] Generating another Secret key\n");

    sk2 = genSK(8);
    fprintf(stdout, "[OK] Secret key of %d-bit generated\n", sk.eta);
    
    if(sk.error){
        fprintf(stderr, "[ERROR] Secret key generation failed\n");
        return EXIT_FAILURE;
    }

    fprintf(stdout, "[OK] Generating another Public key\n");
    fprintf(stdout, "[OK] This could take some time, please wait...\n");

    pk2 = genPK(&sk2);
    
    const char *ID4 = "SH-179EC"; 
    Plaintext ID4Pl = text(ID4);

    fprintf(stdout, "[OK] Encrypting the ID with a new key: %s\n", ID4);

    Chipertext ID4Ch = encrypt(&pk, &ID4Pl);
    
    sum = 0;
    for(unsigned int i = 0; i < ID4Ch.size; i++){
        bitSize = mpz_sizeinbase(ID4Ch.chiper[i], 2);
        sum += bitSize;

    }
    
    fprintf(stdout, "[OK] Encryption done, chipertext size: %ld-bit\n", sum);
    fprintf(stdout, "[OK] Comparing the encrypted value of ID1: %s and ID4 (with a new key): %s\n", ID1, ID4);
    
    Chipertext eID1_ID4 = evaluate(&ID1Ch, &ID4Ch);

    fprintf(stdout, "[OK] Evaluation done, decrypting to see if equal\n");
    
    Plaintext eDe3 = decrypt(&sk2, &eID1_ID4);

    flag = 0;
    for(unsigned int i = 0; i < eDe3.size; i++){
        if(eDe3.bin[i]){
            flag = 1;
        }
    }

    if(!flag){
        fprintf(stderr, "[ERROR] IDs are equal, try increasing Lambda or try again\n");
        return EXIT_FAILURE;
    }
    
    fprintf(stdout, "[OK] IDs are not equal\n\n");



    fprintf(stdout, "[OK] Test completed, will now perform cleanup\n");

    skClean(&sk);
    pkClean(&pk);
    
    skClean(&sk2);
    pkClean(&pk2);
    
    chiper_clean(&ID1Ch);
    chiper_clean(&ID2Ch);
    chiper_clean(&ID3Ch);
    chiper_clean(&ID4Ch);
    
    return EXIT_SUCCESS;
}
