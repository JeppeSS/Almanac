#ifndef PLAINTEXT_H
#define PLAINTEXT_H

typedef struct{

    char *msg;

    int error;

    int *bin;
    unsigned int size;

}Plaintext;

// Initializer
int plainT_init(Plaintext *plain, char *msg);

Plaintext text(char *msg);

// Operations
void toBinary(Plaintext *plain);
void fromBinary(Plaintext *plain);

// Cleanup
int plaintext_clean(Plaintext *plain);

#endif

