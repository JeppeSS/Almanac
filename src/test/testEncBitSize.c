#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

#include "../crypto/secretkey.h"
#include "../crypto/publickey.h"
#include "../crypto/chipertext.h"
#include "../crypto/dghv.h"


int main(void){
    
    FILE *fp = fopen("Data/encSize.txt", "w");

    if(!fp){
        fprintf(stderr, "[ERROR] Could no open file");
        return EXIT_FAILURE;
    }
    fprintf(stdout, "Writing data to encSize.txt\n");
    
    SK sk;
    PK pk;

    mpz_t chiper;


    unsigned int startLamb = 1;
    unsigned int endLamb   = 3;
    unsigned int lambRuns  = 10;
    
    int ret;
    size_t bitSize;
    for(unsigned int i = startLamb; i <= endLamb; i++){
        for(unsigned int j = 0; j < lambRuns; j++){
            mpz_inits(chiper, NULL);
            sk = genSK(i);
            pk = genPK(&sk);

            ret = encryptBit(chiper, &pk, 1);
            if(ret){
                return EXIT_FAILURE;
            }

            bitSize = mpz_sizeinbase(chiper, 2);
            
            fprintf(fp, "%d ", i);
            fprintf(fp, "%lu\n", bitSize);

            skClean(&sk);
            pkClean(&pk);
            mpz_clears(chiper, NULL);
        }
        fprintf(stdout, "Done calculating lambda: %d\n", i);
    }
    
    startLamb = 1;
    endLamb   = 3;
    lambRuns  = 2;
    
    for(unsigned int i = startLamb; i <= endLamb; i++){
        for(unsigned int j = 0; j < lambRuns; j++){
            mpz_inits(chiper, NULL);
            sk = genSK(i);
            pk = genPK(&sk);

            ret = encryptBit(chiper, &pk, 1);
            if(ret){
                return EXIT_FAILURE;
            }

            bitSize = mpz_sizeinbase(chiper, 2);
            
            fprintf(fp, "%d ", i);
            fprintf(fp, "%lu\n", bitSize);

            skClean(&sk);
            pkClean(&pk);
            mpz_clears(chiper, NULL);
        }
        fprintf(stdout, "Done calculating lambda: %d\n", i);
    }
    


    fclose(fp);

    
    return EXIT_SUCCESS;
}
