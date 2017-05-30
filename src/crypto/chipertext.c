#include <stdio.h>
#include <stdlib.h>

#include "chipertext.h"

/* 
 * === Function ===============================================================
 *         Name: chiper_init
 *
 *  Description: Initialize the chipertext allocating memory for it.
 * ============================================================================
 */
int chiper_init(Chipertext *chiper, unsigned int size){
    
    // Allocate memory for the chipertext.
    chiper->chiper = malloc(size * sizeof(mpz_t));

    // If allocation failed.
    if(chiper->chiper == NULL){
        return EXIT_FAILURE;
    }

    // Initialize all chipertext.
    for(unsigned int i = 0; i < size; i++){
        mpz_init(chiper->chiper[i]);
    }

    // Initialize chiper size.
    chiper->size = size;

    return EXIT_SUCCESS;
}

/* 
 * === Function ===============================================================
 *         Name: chiper_clean
 *
 *  Description: Free the used memory for the chipertext.
 * ============================================================================
 */
int chiper_clean(Chipertext *chiper){

    // Clear chiper memory
    for(unsigned int i = 0; i < chiper->size; i++){
        mpz_clear(chiper->chiper[i]);
    }

    // Free allocated memory for chipertext.
    free(chiper->chiper);

    chiper->size = 0;

    return EXIT_SUCCESS;
}
