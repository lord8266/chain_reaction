P=$(m)
pks=
CFLAGS=-Wall -Werror -Wno-unused-variable  -std=gnu++17 -g

OBJECTS=
LDLIBS=

all:
	g++ $(CFLAGS) $(P).cc $(OBJECTS) -o $(P) $(LDLIBS)
