P=chain
pks= sdl2 SDL2_image SDL2_ttf
CFLAGS=-Wall -Wno-unused-variable -g -Wno-unused-value  -std=gnu++17 `pkg-config --cflags $(pks)`

OBJECTS= game_base.o  box.o  event_manager.o  display_manager.o  animation.o
LDLIBS= `pkg-config --libs $(pks)`

all: main.h main.cc $(OBJECTS)
	g++ $(CFLAGS) main.cc $(OBJECTS) -o $(P) $(LDLIBS)

game_base.o: game_base.h game_base.cc
	g++ $(CFLAGS) -c game_base.cc -o game_base.o $(LDLIBS)


box.o: box.h box.cc
	g++ $(CFLAGS) -c box.cc -o box.o $(LDLIBS)

display_manager.o: display_manager.h display_manager.cc
	g++ $(CFLAGS) -c display_manager.cc -o display_manager.o $(LDLIBS)

event_manager.o: event_manager.h event_manager.cc
	g++ $(CFLAGS) -c event_manager.cc -o event_manager.o $(LDLIBS)

animation.o: animation.h animation.cc
	g++ $(CFLAGS) -c animation.cc -o animation.o $(LDLIBS)
