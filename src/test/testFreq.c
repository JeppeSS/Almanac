#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

#include "../crypto/rand/random.h"


int main(void){

    mpz_t randT1, rangT1;
    

    int samples = 100000;
    unsigned long int maxNum = 25;

    mpz_init(rangT1);
    mpz_set_ui(rangT1, maxNum);

    

    FILE *fp = fopen("Data/freq.txt", "w");

    if(!fp){
        fprintf(stderr, "[ERROR] Could no open file");
        return EXIT_FAILURE;
    }

    fprintf(stdout, "Writing data to freq.txt\n");

    int ret = 0;

    for(int i = 0; i < samples; i++){
        mpz_init(randT1);

        ret = randomUniform(randT1, rangT1);

        if(ret < 0){
            fprintf(stderr, "[ERROR] Testing statistic failed\n");
            return EXIT_FAILURE;
        }

        mpz_out_str(fp, 10, randT1); 
        
        fprintf(fp, "\n");

        mpz_clear(randT1);
        mpz_init(randT1);

        mpz_clear(randT1);

    }
    
    fclose(fp);
    
    return 0;
}

