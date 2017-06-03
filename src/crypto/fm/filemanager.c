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
