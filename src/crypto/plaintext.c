#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "plaintext.h"


int plainT_init(Plaintext *plain, char *msg){

    plain->msg = malloc(strlen(msg));

    if(plain->msg == NULL){
        fprintf(stderr, "[ERROR] Memory allocation for plaintext failed\n");
        return EXIT_FAILURE;
    }

    strcpy(plain->msg, msg);
    
    plain->bin = malloc(strlen(msg) * (8 * sizeof(int)));

    if(plain->bin == NULL){
        fprintf(stderr, "[ERROR] Memory allocation for binary repr failed\n");
    }

    plain->size = 0;
    plain->error = 0;

    toBinary(plain);

    return EXIT_SUCCESS;
}

Plaintext text(char *msg){
    Plaintext plain;

    int error = plainT_init(&plain, msg);
    
    if(error){
        plain.error = 1;
        return plain;
    }

    return plain;
}

void toBinary(Plaintext *plain){

    int index = 0;

    for(int i = 0; plain->msg[i] != '\0'; ++i){
        for(int j = 0; j < 8; ++j){
            plain->bin[index] = ((plain->msg[i] >> j) & 1);
            index++;
            plain->size++;
        }
    }
}

void fromBinary(Plaintext *plain){

    int count = 0;
    int val = 0;
    int index = 0;
    int r = 1;


    for(unsigned int i = 0; i <= plain->size; ++i){
        if(count == 8){
            count = 0;
            plain->msg[index] = (char)val;
            index++;
            val = 0;
            r = 1;
        }


        val += plain->bin[i] * r;
        r *= 2;
        count++;
    }
}

