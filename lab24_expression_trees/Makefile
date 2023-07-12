CC=gcc
RM=rm -f
CFLAGS=-Wall -pedantic -std=c18
SOURCES=main.c tree.c 
OBJECTS=main.o tree.o 
TARGET=main.out

all: ${SOURCES} $(TARGET)

${TARGET}: ${OBJECTS}
	${CC} ${CFLAGS} ${OBJECTS} -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	${RM} *.o ${TARGET}
