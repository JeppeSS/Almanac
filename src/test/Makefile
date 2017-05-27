TARGET = 



CC = gcc
CFLAG= -std=c11 -Wall -Wextra -pedantic -Wshadow -Wpointer-arith -Wcast-align \
            -Wwrite-strings -Wmissing-prototypes -Wmissing-declarations \
            -Wredundant-decls -Wnested-externs -Winline -Wno-long-long \
            -Wuninitialized -Wconversion -Wstrict-prototypes 
LIBS = -lm -lgmp -fopenmp $(mysql_config --cflags --libs)
.PHONY: default all clean

default: $(TARGET)
all: $(TARGET)

HEADERS = $(wildcard *.h)

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): %.o: %.c
	$(CC) $< $(SRC) $(CFLAG)$ $(LIBS)-o $@

clean:
	-rm -f *.o






