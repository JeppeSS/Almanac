#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

#include "../crypto/rand/random.h"


int main(void){

    mpz_t randT1, rangT1;
    
    int dim = 512;

    unsigned long int bit = 1;

    mpz_init(rangT1);
    mpz_set_ui(rangT1, bit);

    

    FILE *fp = fopen("Data/bitmap.txt", "w");

    if(!fp){
        fprintf(stderr, "[ERROR] Could no open file");
        return EXIT_FAILURE;
    }

    fprintf(stdout, "Writing data to bitmap.txt\n");
    fprintf(fp, "%d\n", dim);

    int ret = 0;

    for(int i = 0; i < dim; i++){
        for(int j = 0; j < dim; j++){
            
            mpz_init(randT1);

            ret = randomUniform(randT1, rangT1);

            if(ret < 0){
                fprintf(stderr, "[ERROR] Testing statistic failed\n");
                return EXIT_FAILURE;
            }

            mpz_out_str(fp, 10, randT1); 
            
            if(j != dim - 1){
                fprintf(fp, ",");
            }

            mpz_clear(randT1);
            mpz_init(randT1);

            mpz_clear(randT1);

        }
            fprintf(fp, "\n");
    }
    
    fclose(fp);
    
    return 0;
}

