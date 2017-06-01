#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "plaintext.h"


/* 
 * === Function ===============================================================
 *         Name: plainT_init
 *
 *  Description: Initialize the plaintext, allocated memory for it.
 * ============================================================================
 */
int plainT_init(Plaintext *plain, const char *msg){

    // Allocate memory for the message.
    plain->msg = malloc(strlen(msg));

    // If allocation failed.
    if(plain->msg == NULL){
        fprintf(stderr, "[ERROR] Memory allocation for plaintext failed\n");
        return EXIT_FAILURE;
    }

    // Copy the message into the plaintext structure.
    strcpy(plain->msg, msg);
    
    // Allocate memory for the binary representation.
    plain->bin = malloc(strlen(msg) * (8 * sizeof(int)));

    // If allocation failed.
    if(plain->bin == NULL){
        fprintf(stderr, "[ERROR] Memory allocation for binary repr failed\n");
    }

    plain->size = 0;
    plain->error = 0;

    // Create a binary representation of the message.
    toBinary(plain);

    return EXIT_SUCCESS;
}

/* 
 * === Function ===============================================================
 *         Name: text
 *
 *  Description: Constructs a plaintext structure. 
 * ============================================================================
 */
Plaintext text(const char *msg){
    Plaintext plain;

    // Initialize the structure
    int error = plainT_init(&plain, msg);
    
    // If initialization failed.
    if(error){
        plain.error = 1;
        return plain;
    }

    return plain;
}

/* 
 * === Function ===============================================================
 *         Name: toBinary
 *
 *  Description: Make a binary representation of the plaintext message. 
 * ============================================================================
 */
void toBinary(Plaintext *plain){

    int index = 0;

    // Convert each letter (ASCII repr), to binary.
    for(int i = 0; plain->msg[i] != '\0'; ++i){
        for(int j = 0; j < 8; ++j){
            plain->bin[index] = ((plain->msg[i] >> j) & 1);
            index++;
            plain->size++;
        }
    }
}

/* 
 * === Function ===============================================================
 *         Name: fromBinary
 *
 *  Description: Convert the binary representation to text. 
 * ============================================================================
 */
void fromBinary(Plaintext *plain){

    int count = 0;
    int val = 0;
    int index = 0;
    int r = 1;


    // A char, contains 8 bits. 
    // Extract the 8 bits, and convert to ASCII (char).
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

