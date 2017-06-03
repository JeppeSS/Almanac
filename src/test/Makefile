TARGET = testRandom.o testSK.o testBitmap.o testFreq.o testPK.o testEncBit.o testEncryp.o testFunctionL.o testEncBitSize.o testCorrectness.o testEvalBit.o testEval.o


CRYPTODIR = ../crypto
CRYPTOFILES = $(CRYPTODIR)/secretkey.c $(CRYPTODIR)/publickey.c $(CRYPTODIR)/chipertext.c $(CRYPTODIR)/dghv.c $(CRYPTODIR)/plaintext.c

RANDDIR = ../crypto/rand
RANDFILES = $(RANDDIR)/random.c

CC = gcc
CFLAG= -std=c11 -Wall -Wextra -pedantic -Wshadow -Wpointer-arith -Wcast-align \
            -Wwrite-strings -Wmissing-prototypes -Wmissing-declarations \
            -Wredundant-decls -Wnested-externs -Winline -Wno-long-long \
            -Wuninitialized -Wconversion -Wstrict-prototypes 
LIBS = -lm -lgmp -fopenmp $(mysql_config --cflags --libs)
.PHONY: default all clean

default: $(TARGET)
all: $(TARGET)


.PRECIOUS: $(TARGET) $(OBJECTS)



$(TARGET): %.o: %.c
	$(CC) $(RANDFILES) $(CRYPTOFILES) $(CFLAG)$ $(LIBS) $< -o $@

check:
	./testRandom.o
	./testSK.o
	./testPK.o
	./testEncBit.o
	./testEvalBit.o
	./testEval.o

static:
	./testBitmap.o
	python3.6 bitmap.py
	./testFreq.o 
	python3.6 freq.py


clean:
	-rm -f *.o






