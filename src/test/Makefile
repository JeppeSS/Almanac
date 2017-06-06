TARGET = testRandom.o testSK.o testBitmap.o testFreq.o testPK.o testEncBit.o testEncryp.o testFunctionL.o testEncBitSize.o testCorrectness.o testEvalBit.o testEval.o testWriteSK.o testWritePK.o


CRYPTODIR = ../crypto
CRYPTOFILES = $(CRYPTODIR)/secretkey.c $(CRYPTODIR)/publickey.c $(CRYPTODIR)/chipertext.c $(CRYPTODIR)/dghv.c $(CRYPTODIR)/plaintext.c

CRYPTOFMDIR = ../crypto/fm
CRYPTOFMFIL = $(CRYPTOFMDIR)/filemanager.c

RANDDIR = ../crypto/rand
RANDFILES = $(RANDDIR)/random.c

CC = gcc
CFLAG= -std=c11 -Wall -Wextra -pedantic -Wshadow -Wpointer-arith -Wcast-align \
            -Wwrite-strings -Wmissing-prototypes -Wmissing-declarations \
            -Wredundant-decls -Wnested-externs -Winline -Wno-long-long \
            -Wuninitialized -Wconversion -Wstrict-prototypes 
LIBS = -lm -lgmp -fopenmp
.PHONY: default all clean

default: $(TARGET)
all: $(TARGET)


.PRECIOUS: $(TARGET) $(OBJECTS)



$(TARGET): %.o: %.c
	$(CC) $(RANDFILES) $(CRYPTOFILES) $(CRYPTOFMFIL) $(CFLAG)$ $(LIBS) $< -o $@

crypTest:
	./testRandom.o
	./testSK.o
	./testPK.o
	./testEncBit.o
	./testEvalBit.o
	./testEval.o
	./testWriteSK.o
	./testWritePK.o

static:
	./testBitmap.o
	python3.6 bitmap.py
	./testFreq.o 
	python3.6 freq.py


clean:
	-rm -f *.o






