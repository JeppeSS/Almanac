TARGET = testRandom.o testStatic.o 


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
	$(CC) $(RANDFILES) $(CFLAG)$ $(LIBS) $< -o $@

check:
	./testRandom.o

static:
	./testStatic.o

clean:
	-rm -f *.o






