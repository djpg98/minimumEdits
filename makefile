COMPILAR = gcc -c

LINKEAR = gcc

MAIN = main

OBJETOS = main.o minimumEdits.o

.PHONY = all clean

all: $(MAIN)

clean:
	rm $(OBJETOS)
	rm $(MAIN)

minimumEdits.o: minimumEdits.c minimumEdits.h
	$(COMPILAR) minimumEdits.c -o minimumEdits.o

$(MAIN): main.c $(OBJETOS)
	$(COMPILAR) main.c -o main.o
	$(LINKEAR) $(OBJETOS) -o $(MAIN)