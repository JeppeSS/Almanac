#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

#include "../crypto/secretkey.h"
#include "../crypto/publickey.h"
#include "../crypto/chipertext.h"
#include "../crypto/dghv.h"


int main(void){
    
    FILE *fp = fopen("Data/correctness.txt", "w");

    if(!fp){
        fprintf(stderr, "[ERROR] Could no open file");
        return EXIT_FAILURE;
    }
    fprintf(stdout, "Writing data to encSize.txt\n");
    
    SK sk;
    PK pk;

    mpz_t chiper1;
    mpz_t chiper2;
    mpz_t chiper3;
    mpz_t chiper4;
    mpz_t chiper5;
    mpz_t chiper6;
    
    unsigned int startLamb = 1;
    unsigned int endLamb   = 3;
    unsigned int lambRuns  = 250;
    
    int ret;
    int flag = 0;
    int bit;
    int correct;
    float res;
    for(unsigned int i = startLamb; i <= endLamb; i++){
        for(unsigned int j = 0; j < lambRuns; j++){
            mpz_inits(chiper1, chiper2, chiper3, chiper4, chiper5, chiper6, NULL);
            sk = genSK(i);
            pk = genPK(&sk);

            ret = encryptBit(chiper1, &pk, 1);
            if(ret){
                return EXIT_FAILURE;
            }
            
            ret = encryptBit(chiper2, &pk, 0);
            if(ret){
                return EXIT_FAILURE;
            }
            
            ret = encryptBit(chiper3, &pk, 1);
            if(ret){
                return EXIT_FAILURE;
            }
            
            ret = encryptBit(chiper4, &pk, 1);
            if(ret){
                return EXIT_FAILURE;
            }
            
            ret = encryptBit(chiper5, &pk, 0);
            if(ret){
                return EXIT_FAILURE;
            }
            
            ret = encryptBit(chiper6, &pk, 1);
            if(ret){
                return EXIT_FAILURE;
            }

            bit = decryptBit(&sk, chiper1);

            if(bit != 1){
                flag = 1;
            }

            bit = decryptBit(&sk, chiper2);

            if(bit != 0){
                flag = 1;
            }
            bit = decryptBit(&sk, chiper3);

            if(bit != 1){
                flag = 1;
            }

            bit = decryptBit(&sk, chiper4);

            if(bit != 1){
                flag = 1;
            }

            bit = decryptBit(&sk, chiper5);

            if(bit != 0){
                flag = 1;
            }

            bit = decryptBit(&sk, chiper6);

            if(bit != 1){
                flag = 1;
            }

            if(flag == 0){
                correct++;
            } else {
                flag = 0;
            }

            skClean(&sk);
            pkClean(&pk);
            mpz_clears(chiper1, chiper2, chiper3, chiper4, chiper5, chiper6, NULL);
        }
        fprintf(stdout, "Done calculating lambda: %d\n", i);
        res = (float) correct / (float)lambRuns;
        fprintf(fp, "%d ", i);
        fprintf(fp, "%f\n", res);
        res = 0.0;
        correct = 0;
        
    }


    for(unsigned int i = startLamb; i <= endLamb; i++){
        for(unsigned int j = 0; j < lambRuns; j++){
            mpz_inits(chiper1, chiper2, chiper3, chiper4, chiper5, chiper6, NULL);
            sk = genSK(i);
            pk = genPK(&sk);

            ret = encryptBit(chiper1, &pk, 1);
            if(ret){
                return EXIT_FAILURE;
            }
            
            ret = encryptBit(chiper2, &pk, 0);
            if(ret){
                return EXIT_FAILURE;
            }
            
            ret = encryptBit(chiper3, &pk, 1);
            if(ret){
                return EXIT_FAILURE;
            }
            
            ret = encryptBit(chiper4, &pk, 1);
            if(ret){
                return EXIT_FAILURE;
            }
            
            ret = encryptBit(chiper5, &pk, 0);
            if(ret){
                return EXIT_FAILURE;
            }
            
            ret = encryptBit(chiper6, &pk, 1);
            if(ret){
                return EXIT_FAILURE;
            }

            bit = decryptBit(&sk, chiper1);

            if(bit != 1){
                flag = 1;
            }

            bit = decryptBit(&sk, chiper2);

            if(bit != 0){
                flag = 1;
            }
            bit = decryptBit(&sk, chiper3);

            if(bit != 1){
                flag = 1;
            }

            bit = decryptBit(&sk, chiper4);

            if(bit != 1){
                flag = 1;
            }

            bit = decryptBit(&sk, chiper5);

            if(bit != 0){
                flag = 1;
            }

            bit = decryptBit(&sk, chiper6);

            if(bit != 1){
                flag = 1;
            }

            if(flag == 0){
                correct++;
            } else {
                flag = 0;
            }

            skClean(&sk);
            pkClean(&pk);
            mpz_clears(chiper1, chiper2, chiper3, chiper4, chiper5, chiper6, NULL);
        }
        fprintf(stdout, "Done calculating lambda: %d\n", i);
        res = (float) correct / (float)lambRuns;
        fprintf(fp, "%d ", i);
        fprintf(fp, "%f\n", res);
        res = 0.0;
        correct = 0;
        
    }


    for(unsigned int i = startLamb; i <= endLamb; i++){
        for(unsigned int j = 0; j < lambRuns; j++){
            mpz_inits(chiper1, chiper2, chiper3, chiper4, chiper5, chiper6, NULL);
            sk = genSK(i);
            pk = genPK(&sk);

            ret = encryptBit(chiper1, &pk, 1);
            if(ret){
                return EXIT_FAILURE;
            }
            
            ret = encryptBit(chiper2, &pk, 0);
            if(ret){
                return EXIT_FAILURE;
            }
            
            ret = encryptBit(chiper3, &pk, 1);
            if(ret){
                return EXIT_FAILURE;
            }
            
            ret = encryptBit(chiper4, &pk, 1);
            if(ret){
                return EXIT_FAILURE;
            }
            
            ret = encryptBit(chiper5, &pk, 0);
            if(ret){
                return EXIT_FAILURE;
            }
            
            ret = encryptBit(chiper6, &pk, 1);
            if(ret){
                return EXIT_FAILURE;
            }

            bit = decryptBit(&sk, chiper1);

            if(bit != 1){
                flag = 1;
            }

            bit = decryptBit(&sk, chiper2);

            if(bit != 0){
                flag = 1;
            }
            bit = decryptBit(&sk, chiper3);

            if(bit != 1){
                flag = 1;
            }

            bit = decryptBit(&sk, chiper4);

            if(bit != 1){
                flag = 1;
            }

            bit = decryptBit(&sk, chiper5);

            if(bit != 0){
                flag = 1;
            }

            bit = decryptBit(&sk, chiper6);

            if(bit != 1){
                flag = 1;
            }

            if(flag == 0){
                correct++;
            } else {
                flag = 0;
            }

            skClean(&sk);
            pkClean(&pk);
            mpz_clears(chiper1, chiper2, chiper3, chiper4, chiper5, chiper6, NULL);
        }
        fprintf(stdout, "Done calculating lambda: %d\n", i);
        res = (float) correct / (float)lambRuns;
        fprintf(fp, "%d ", i);
        fprintf(fp, "%f\n", res);
        res = 0.0;
        correct = 0; 
    }
    
    startLamb = 4;
    endLamb   = 6;
    lambRuns  = 50;
    
    for(unsigned int i = startLamb; i <= endLamb; i++){
        for(unsigned int j = 0; j < lambRuns; j++){
            mpz_inits(chiper1, chiper2, chiper3, chiper4, chiper5, chiper6, NULL);
            sk = genSK(i);
            pk = genPK(&sk);

            ret = encryptBit(chiper1, &pk, 1);
            if(ret){
                return EXIT_FAILURE;
            }
            
            ret = encryptBit(chiper2, &pk, 0);
            if(ret){
                return EXIT_FAILURE;
            }
            
            ret = encryptBit(chiper3, &pk, 1);
            if(ret){
                return EXIT_FAILURE;
            }
            
            ret = encryptBit(chiper4, &pk, 1);
            if(ret){
                return EXIT_FAILURE;
            }
            
            ret = encryptBit(chiper5, &pk, 0);
            if(ret){
                return EXIT_FAILURE;
            }
            
            ret = encryptBit(chiper6, &pk, 1);
            if(ret){
                return EXIT_FAILURE;
            }

            bit = decryptBit(&sk, chiper1);

            if(bit != 1){
                flag = 1;
            }

            bit = decryptBit(&sk, chiper2);

            if(bit != 0){
                flag = 1;
            }
            bit = decryptBit(&sk, chiper3);

            if(bit != 1){
                flag = 1;
            }

            bit = decryptBit(&sk, chiper4);

            if(bit != 1){
                flag = 1;
            }

            bit = decryptBit(&sk, chiper5);

            if(bit != 0){
                flag = 1;
            }

            bit = decryptBit(&sk, chiper6);

            if(bit != 1){
                flag = 1;
            }

            if(flag == 0){
                correct++;
            } else {
                flag = 0;
            }

            skClean(&sk);
            pkClean(&pk);
            mpz_clears(chiper1, chiper2, chiper3, chiper4, chiper5, chiper6, NULL);
        }
        fprintf(stdout, "Done calculating lambda: %d\n", i);
        res = (float) correct / (float)lambRuns;
        fprintf(fp, "%d ", i);
        fprintf(fp, "%f\n", res);
        res = 0.0;
        correct = 0; 
    }
    
    for(unsigned int i = startLamb; i <= endLamb; i++){
        for(unsigned int j = 0; j < lambRuns; j++){
            mpz_inits(chiper1, chiper2, chiper3, chiper4, chiper5, chiper6, NULL);
            sk = genSK(i);
            pk = genPK(&sk);

            ret = encryptBit(chiper1, &pk, 1);
            if(ret){
                return EXIT_FAILURE;
            }
            
            ret = encryptBit(chiper2, &pk, 0);
            if(ret){
                return EXIT_FAILURE;
            }
            
            ret = encryptBit(chiper3, &pk, 1);
            if(ret){
                return EXIT_FAILURE;
            }
            
            ret = encryptBit(chiper4, &pk, 1);
            if(ret){
                return EXIT_FAILURE;
            }
            
            ret = encryptBit(chiper5, &pk, 0);
            if(ret){
                return EXIT_FAILURE;
            }
            
            ret = encryptBit(chiper6, &pk, 1);
            if(ret){
                return EXIT_FAILURE;
            }

            bit = decryptBit(&sk, chiper1);

            if(bit != 1){
                flag = 1;
            }

            bit = decryptBit(&sk, chiper2);

            if(bit != 0){
                flag = 1;
            }
            bit = decryptBit(&sk, chiper3);

            if(bit != 1){
                flag = 1;
            }

            bit = decryptBit(&sk, chiper4);

            if(bit != 1){
                flag = 1;
            }

            bit = decryptBit(&sk, chiper5);

            if(bit != 0){
                flag = 1;
            }

            bit = decryptBit(&sk, chiper6);

            if(bit != 1){
                flag = 1;
            }

            if(flag == 0){
                correct++;
            } else {
                flag = 0;
            }

            skClean(&sk);
            pkClean(&pk);
            mpz_clears(chiper1, chiper2, chiper3, chiper4, chiper5, chiper6, NULL);
        }
        fprintf(stdout, "Done calculating lambda: %d\n", i);
        res = (float) correct / (float)lambRuns;
        fprintf(fp, "%d ", i);
        fprintf(fp, "%f\n", res);
        res = 0.0;
        correct = 0; 
    }
    
    for(unsigned int i = startLamb; i <= endLamb; i++){
        for(unsigned int j = 0; j < lambRuns; j++){
            mpz_inits(chiper1, chiper2, chiper3, chiper4, chiper5, chiper6, NULL);
            sk = genSK(i);
            pk = genPK(&sk);

            ret = encryptBit(chiper1, &pk, 1);
            if(ret){
                return EXIT_FAILURE;
            }
            
            ret = encryptBit(chiper2, &pk, 0);
            if(ret){
                return EXIT_FAILURE;
            }
            
            ret = encryptBit(chiper3, &pk, 1);
            if(ret){
                return EXIT_FAILURE;
            }
            
            ret = encryptBit(chiper4, &pk, 1);
            if(ret){
                return EXIT_FAILURE;
            }
            
            ret = encryptBit(chiper5, &pk, 0);
            if(ret){
                return EXIT_FAILURE;
            }
            
            ret = encryptBit(chiper6, &pk, 1);
            if(ret){
                return EXIT_FAILURE;
            }

            bit = decryptBit(&sk, chiper1);

            if(bit != 1){
                flag = 1;
            }

            bit = decryptBit(&sk, chiper2);

            if(bit != 0){
                flag = 1;
            }
            bit = decryptBit(&sk, chiper3);

            if(bit != 1){
                flag = 1;
            }

            bit = decryptBit(&sk, chiper4);

            if(bit != 1){
                flag = 1;
            }

            bit = decryptBit(&sk, chiper5);

            if(bit != 0){
                flag = 1;
            }

            bit = decryptBit(&sk, chiper6);

            if(bit != 1){
                flag = 1;
            }

            if(flag == 0){
                correct++;
            } else {
                flag = 0;
            }

            skClean(&sk);
            pkClean(&pk);
            mpz_clears(chiper1, chiper2, chiper3, chiper4, chiper5, chiper6, NULL);
        }
        fprintf(stdout, "Done calculating lambda: %d\n", i);
        res = (float) correct / (float)lambRuns;
        fprintf(fp, "%d ", i);
        fprintf(fp, "%f\n", res);
        res = 0.0;
        correct = 0; 
    }
    
    startLamb = 7;
    endLamb   = 10;
    lambRuns  = 5;
    
    for(unsigned int i = startLamb; i <= endLamb; i++){
        for(unsigned int j = 0; j < lambRuns; j++){
            mpz_inits(chiper1, chiper2, chiper3, chiper4, chiper5, chiper6, NULL);
            sk = genSK(i);
            pk = genPK(&sk);

            ret = encryptBit(chiper1, &pk, 1);
            if(ret){
                return EXIT_FAILURE;
            }
            
            ret = encryptBit(chiper2, &pk, 0);
            if(ret){
                return EXIT_FAILURE;
            }
            
            ret = encryptBit(chiper3, &pk, 1);
            if(ret){
                return EXIT_FAILURE;
            }
            
            ret = encryptBit(chiper4, &pk, 1);
            if(ret){
                return EXIT_FAILURE;
            }
            
            ret = encryptBit(chiper5, &pk, 0);
            if(ret){
                return EXIT_FAILURE;
            }
            
            ret = encryptBit(chiper6, &pk, 1);
            if(ret){
                return EXIT_FAILURE;
            }

            bit = decryptBit(&sk, chiper1);

            if(bit != 1){
                flag = 1;
            }

            bit = decryptBit(&sk, chiper2);

            if(bit != 0){
                flag = 1;
            }
            bit = decryptBit(&sk, chiper3);

            if(bit != 1){
                flag = 1;
            }

            bit = decryptBit(&sk, chiper4);

            if(bit != 1){
                flag = 1;
            }

            bit = decryptBit(&sk, chiper5);

            if(bit != 0){
                flag = 1;
            }

            bit = decryptBit(&sk, chiper6);

            if(bit != 1){
                flag = 1;
            }

            if(flag == 0){
                correct++;
            } else {
                flag = 0;
            }

            skClean(&sk);
            pkClean(&pk);
            mpz_clears(chiper1, chiper2, chiper3, chiper4, chiper5, chiper6, NULL);
        }
        fprintf(stdout, "Done calculating lambda: %d\n", i);
        res = (float) correct / (float)lambRuns;
        fprintf(fp, "%d ", i);
        fprintf(fp, "%f\n", res);
        res = 0.0;
        correct = 0; 
    }
    
    
    for(unsigned int i = startLamb; i <= endLamb; i++){
        for(unsigned int j = 0; j < lambRuns; j++){
            mpz_inits(chiper1, chiper2, chiper3, chiper4, chiper5, chiper6, NULL);
            sk = genSK(i);
            pk = genPK(&sk);

            ret = encryptBit(chiper1, &pk, 1);
            if(ret){
                return EXIT_FAILURE;
            }
            
            ret = encryptBit(chiper2, &pk, 0);
            if(ret){
                return EXIT_FAILURE;
            }
            
            ret = encryptBit(chiper3, &pk, 1);
            if(ret){
                return EXIT_FAILURE;
            }
            
            ret = encryptBit(chiper4, &pk, 1);
            if(ret){
                return EXIT_FAILURE;
            }
            
            ret = encryptBit(chiper5, &pk, 0);
            if(ret){
                return EXIT_FAILURE;
            }
            
            ret = encryptBit(chiper6, &pk, 1);
            if(ret){
                return EXIT_FAILURE;
            }

            bit = decryptBit(&sk, chiper1);

            if(bit != 1){
                flag = 1;
            }

            bit = decryptBit(&sk, chiper2);

            if(bit != 0){
                flag = 1;
            }
            bit = decryptBit(&sk, chiper3);

            if(bit != 1){
                flag = 1;
            }

            bit = decryptBit(&sk, chiper4);

            if(bit != 1){
                flag = 1;
            }

            bit = decryptBit(&sk, chiper5);

            if(bit != 0){
                flag = 1;
            }

            bit = decryptBit(&sk, chiper6);

            if(bit != 1){
                flag = 1;
            }

            if(flag == 0){
                correct++;
            } else {
                flag = 0;
            }

            skClean(&sk);
            pkClean(&pk);
            mpz_clears(chiper1, chiper2, chiper3, chiper4, chiper5, chiper6, NULL);
        }
        fprintf(stdout, "Done calculating lambda: %d\n", i);
        res = (float) correct / (float)lambRuns;
        fprintf(fp, "%d ", i);
        fprintf(fp, "%f\n", res);
        res = 0.0;
        correct = 0; 
    }
    
    for(unsigned int i = startLamb; i <= endLamb; i++){
        for(unsigned int j = 0; j < lambRuns; j++){
            mpz_inits(chiper1, chiper2, chiper3, chiper4, chiper5, chiper6, NULL);
            sk = genSK(i);
            pk = genPK(&sk);

            ret = encryptBit(chiper1, &pk, 1);
            if(ret){
                return EXIT_FAILURE;
            }
            
            ret = encryptBit(chiper2, &pk, 0);
            if(ret){
                return EXIT_FAILURE;
            }
            
            ret = encryptBit(chiper3, &pk, 1);
            if(ret){
                return EXIT_FAILURE;
            }
            
            ret = encryptBit(chiper4, &pk, 1);
            if(ret){
                return EXIT_FAILURE;
            }
            
            ret = encryptBit(chiper5, &pk, 0);
            if(ret){
                return EXIT_FAILURE;
            }
            
            ret = encryptBit(chiper6, &pk, 1);
            if(ret){
                return EXIT_FAILURE;
            }

            bit = decryptBit(&sk, chiper1);

            if(bit != 1){
                flag = 1;
            }

            bit = decryptBit(&sk, chiper2);

            if(bit != 0){
                flag = 1;
            }
            bit = decryptBit(&sk, chiper3);

            if(bit != 1){
                flag = 1;
            }

            bit = decryptBit(&sk, chiper4);

            if(bit != 1){
                flag = 1;
            }

            bit = decryptBit(&sk, chiper5);

            if(bit != 0){
                flag = 1;
            }

            bit = decryptBit(&sk, chiper6);

            if(bit != 1){
                flag = 1;
            }

            if(flag == 0){
                correct++;
            } else {
                flag = 0;
            }

            skClean(&sk);
            pkClean(&pk);
            mpz_clears(chiper1, chiper2, chiper3, chiper4, chiper5, chiper6, NULL);
        }
        fprintf(stdout, "Done calculating lambda: %d\n", i);
        res = (float) correct / (float)lambRuns;
        fprintf(fp, "%d ", i);
        fprintf(fp, "%f\n", res);
        res = 0.0;
        correct = 0; 
    }


    fclose(fp);

    
    return EXIT_SUCCESS;
}
