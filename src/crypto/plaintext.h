#ifndef PLAINTEXT_H
#define PLAINTEXT_H

/*
 * === Structure ==============================================================
 *         Name:  Plaintext
 *
 *  Description: The plaintext structure, contains a msg pointer containing
 *  text of the plaintext. An error flag, used to determine if the plaintext
 *  initialization went well, and the binary representation.
 * ============================================================================
 */
typedef struct{

    // The text representation
    char *msg;

    // Error flag
    int error;

    // Binary representation
    int *bin;

    // Bit size of the plaintext.
    unsigned int size;

}Plaintext;

// Initializer
int plainT_init(Plaintext *plain, const char *msg);

Plaintext text(const char *msg);

// Operations
void toBinary(Plaintext *plain);
void fromBinary(Plaintext *plain);

#endif

