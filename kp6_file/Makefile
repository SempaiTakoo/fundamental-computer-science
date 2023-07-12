CC=gcc
RM=rm -f
CFLAGS=-Wall -pedantic -std=c18
SOURCES=main.c student.c
OBJECTS=main.o student.o
TARGET=main.exe

all: ${SOURCES} $(TARGET)

${TARGET}: ${OBJECTS}
	${CC} ${CFLAGS} ${OBJECTS} -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	${RM} *.o ${TARGET}