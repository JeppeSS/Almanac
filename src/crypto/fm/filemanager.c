#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>


#include "filemanager.h"
#include "../secretkey.h"
#include "../publickey.h"


/* 
 * === Function ===============================================================
 *         Name: writeSK
 *
 *  Description: Writes the secret key out to the pointed file.
 * ============================================================================
 */
int writeSK(SK *sk, const char *filename){

    // Open the file for writing
    FILE *fp = fopen(filename, "wb");

    // Opening file failed
    if(!fp){
        fprintf(stderr, "[ERROR] Could not write secret key to file\n");
        return EXIT_FAILURE;
    }
    
    // Contains the parameters for the secret key only lambda
    // because the others parameters can be derived from lambda.
    const char *BEGINPAR = "-----BEGIN SHE PARAMATERS-----";
    const char *ENDPAR   = "-----END SHE PARAMATERS-----";

    fprintf(fp, "%s\n", BEGINPAR);

    fprintf(fp, "%X\n", sk->lambda);

    fprintf(fp, "%s\n", ENDPAR);

    // Write the secret key to the file in base 16.
    const char *BEGINK = "-----BEGIN SHE SECRET KEY-----";
    const char *ENDK   = "-----END SHE SECRET KEY-----";

    fprintf(fp, "%s\n", BEGINK);

    size_t data = mpz_out_str(fp, 16, sk->secK);

    // Writing key failed
    if(!data){
        fprintf(stderr, "[ERROR] Could not write secret key\n");
        return EXIT_FAILURE;
    }

    fprintf(fp, "\n%s\n", ENDK);


    // Close file
    fclose(fp);


    return EXIT_SUCCESS;
}


/* 
 * === Function ===============================================================
 *         Name: readSK
 *
 *  Description: Reads the secret key into a SK structure.
 * ============================================================================
 */
SK readSK(const char *filename){
    
    SK secK;

    // The filename of the secret key.
    FILE *fp = fopen(filename, "rb");
    
    // Copy the whole file into source.
    char *source;

    // If file could not be opend.
    if(!fp){
        fprintf(stderr, "[ERROR] Could not write public key to file\n");
    }

    long bufsize;

    /*Go to the end of the file */
    if(fseek(fp, 0L, SEEK_END) == 0){

        bufsize = ftell(fp);

        if(bufsize == -1){
            fprintf(stderr, "[ERROR] Could not read file\n");
        }

        /* Allocate our buffer to that size.  */
        source = malloc(sizeof(char) * ((unsigned int)bufsize + 1));

        /*  Go back to the start of the file. */
        if(fseek(fp, 0L, SEEK_SET) != 0){
            fprintf(stderr, "[ERROR] Could not read file\n");
        }

        /* Read the entire file into memory. */
        size_t newLen = fread(source, sizeof(char), (unsigned int)bufsize, fp);

        if(ferror(fp) != 0){
            fprintf(stderr, "[ERROR] Could not read file\n");
        } else {
            /* Just to be sure that the file has an ending. */
            source[newLen++] = '\0';
        }

        fclose(fp);
    }

    // Allocate memory for lambda, assume lambda will not be larger than
    // 100 blocks of size char.
    char *lamb = calloc(100, sizeof(char));

    // Where the lambda parameter begins.
    int startParam = 31;
    int index      = 0;
    for(int i = startParam; source[i] != '\n'; i++){
        lamb[index] = source[i];
        startParam++;
        index++;
    }

    // Convert the lambda to an unsigned int.
    unsigned int lambda = (unsigned int)atoi(lamb);

    // Where secret key value begins.
    startParam += 61;

    // Initialize the secret key with lambda.
    sk_init(&secK, lambda);

    // Allocate space for the secret key. 
    char *secretK = calloc(secK.eta, sizeof(char));
    
    // Copy the secret key from source into the allocated
    // memory
    index = 0;
    for(int i = startParam; source[i] != '\n'; i++){
        secretK[index] = source[i];
        index++;
    }

    // Convert the key to mpz_t value
    int convert = mpz_set_str(secK.secK, secretK, 16);

    // If conversion failed.
    if(convert < 0){
        fprintf(stderr, "[ERROR] Could not import secret key\n");
    }


    // Free memory.
    free(secretK);
    free(source);


    return secK;

}
