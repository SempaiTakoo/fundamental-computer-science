CC=gcc
RM=rm -f
CFLAGS=-Wall -pedantic -std=c18
SOURCES=main.c list.c
OBJECTS=main.o list.o
TARGET=main.exe

all: ${SOURCES} $(TARGET)

${TARGET}: ${OBJECTS}
	${CC} ${CFLAGS} ${OBJECTS} -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	${RM} *.o ${TARGET}