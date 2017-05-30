#ifndef CHIPERTEXT_H
#define CHIPERTEXT_H

#include <gmp.h>


/*
 * === Structure ==============================================================
 *         Name:  Chipertext
 *
 *  Description: The chipertext structure, contains the chiper and the size
 *  of the chiper.
 * ============================================================================
 */
typedef struct{

    // Chipertext
    mpz_t *chiper;

    // Size of chipertext
    unsigned int size;

}Chipertext;


// Initializer
int chiper_init(Chipertext *chiper, unsigned int size);

// Cleanup
int chiper_clean(Chipertext *chiper);

#endif
