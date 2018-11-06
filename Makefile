P=chain
#im no makefile expert
all:
	cd sources && make
	mv sources/$(P) ./

rebuild: clean all

clean:
	rm sources/*.o
