#ifndef RANDOM_H
#define RANDOM_H

#include <gmp.h>

// Random function
int randomUniform(mpz_t rand, mpz_t n);
int randomRange(mpz_t rand, mpz_t min, mpz_t max);
#endif
