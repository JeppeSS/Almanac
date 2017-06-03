#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>


#include "filemanager.h"
#include "../secretkey.h"
#include "../publickey.h"


int writeSK(SK *sk, const char *filename){

    FILE *fp = fopen(filename, "wb");

    if(!fp){
        fprintf(stderr, "[ERROR] Could not write secret key to file\n");
        return EXIT_FAILURE;
    }
    
    const char *BEGINPAR = "-----BEGIN SHE PARAMATERS-----";
    const char *ENDPAR   = "-----END SHE PARAMATERS-----";

    fprintf(fp, "%s\n", BEGINPAR);

    fprintf(fp, "%X\n", sk->lambda);

    fprintf(fp, "%s\n", ENDPAR);

    const char *BEGINK = "-----BEGIN SHE SECRET KEY-----";
    const char *ENDK   = "-----END SHE SECRET KEY-----";

    fprintf(fp, "%s\n", BEGINK);

    size_t data = mpz_out_str(fp, 16, sk->secK);

    if(!data){
        fprintf(stderr, "[ERROR] Could not write secret key\n");
        return EXIT_FAILURE;
    }

    fprintf(fp, "\n%s\n", ENDK);


    fclose(fp);


    return EXIT_SUCCESS;
}
