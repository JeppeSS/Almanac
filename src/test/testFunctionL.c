#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../crypto/secretkey.h"
#include "../crypto/publickey.h"


int main(void){


    FILE *fp = fopen("Data/timeComplex.txt", "w");

    if(!fp){
        fprintf(stderr, "[ERROR] Could no open file");
        return EXIT_FAILURE;
    }
    fprintf(stdout, "Writing data to timeComplex.txt\n");


    unsigned int startLamb = 4;
    unsigned int endLamb   = 6;
    unsigned int lambRuns  = 5;

    SK sk;
    PK pk;

    clock_t start;
    clock_t end;

    float sec;


    for(unsigned int i = startLamb; i <= endLamb; i++){
        for(unsigned int j = 0; j < lambRuns; j++){
            sk = genSK(i);
            
            start = clock();

            pk = genPK(&sk);

            end = clock();

            sec = (float) (end - start) / CLOCKS_PER_SEC;

            fprintf(fp, "%d ", i);
            fprintf(fp, "%E\n", sec);

            start = 0;
            end   = 0;
            skClean(&sk);
            pkClean(&pk);
        }
        fprintf(stdout, "Done calculating lambda: %d\n", i);
    }

    fprintf(stdout, "Done calculating range: %d - %d\n", startLamb, endLamb);
    
    startLamb = 7;
    endLamb   = 10;
    lambRuns  = 2;
    
    for(unsigned int i = startLamb; i <= endLamb; i++){
        for(unsigned int j = 0; j < lambRuns; j++){
            sk = genSK(i);
            
            start = clock();

            pk = genPK(&sk);

            end = clock();

            sec = (float) (end - start) / CLOCKS_PER_SEC;

            fprintf(fp, "%d ", i);
            fprintf(fp, "%E\n", sec);

            start = 0;
            end   = 0;
            skClean(&sk);
            pkClean(&pk);
        }
        fprintf(stdout, "Done calculating lambda: %d\n", i);
    }

    fclose(fp);

    fprintf(stdout, "Done calculating range: %d - %d\n", startLamb, endLamb);
    return EXIT_SUCCESS;
}
