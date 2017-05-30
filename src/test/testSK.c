#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

#include "../crypto/secretkey.h"


int main(void){

    printf("Testing Secret key generation\n");

    SK sk = genSK(8);

    return 0;
}

