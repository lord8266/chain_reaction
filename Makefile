P=$(m)
pks= sdl2 SDL2_image SDL2_ttf
CFLAGS=-Wall -Wno-unused-variable -Wno-unused-value  -std=gnu++17 -g `pkg-config --cflags $(pks)`

OBJECTS=
LDLIBS= `pkg-config --libs $(pks)`
dir = sources

all: $(dir)/header.h
	g++ $(CFLAGS) $(dir)/chainreaction.cc  -o $(P) $(LDLIBS)
