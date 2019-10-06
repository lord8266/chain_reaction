P=main
pks= sdl2 SDL2_image SDL2_ttf
CFLAGS=-Wall -Werror -Wno-unused-variable -g -Wno-unused-value  `pkg-config --cflags $(pks)`

OBJECTS=core.o list.o
LDLIBS= `pkg-config --libs $(pks)`

all: main.h main.c $(OBJECTS)
	gcc $(CFLAGS) main.c $(OBJECTS) -o $(P) $(LDLIBS)

core.o: core.c core.h
	gcc $(CFLAGS) -c core.c -o core.o

list.o: list.c list.h
	gcc $(CFLAGS) -c list.c -o list.o
