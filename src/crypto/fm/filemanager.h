#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "../secretkey.h"
#include "../publickey.h"

// Key writers
int writeSK(SK *sk, const char *filename);
int writePK(PK *pk, const char *filename);

// Key reader
SK readSK(const char *filename);
PK readPK(const char *filename);
#endif
