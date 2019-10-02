P=main
pks= sdl2 SDL2_image SDL2_ttf
CFLAGS=-Wall -Werror -Wno-unused-variable -g -Wno-unused-value  -std=gnu++17 `pkg-config --cflags $(pks)`

OBJECTS=core.o
LDLIBS= `pkg-config --libs $(pks)`

all: main.h main.cc $(OBJECTS)
	g++ $(CFLAGS) main.cc $(OBJECTS) -o $(P) $(LDLIBS)

core.o: core.cc core.h
	g++ $(CFLAGS) -c core.cc -o core.o
