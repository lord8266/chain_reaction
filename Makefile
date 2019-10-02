P=chain
#im no makefile expert
all:
	cd sources && make -j9
	mv sources/$(P) ./

rebuild: clean all

clean:
	rm sources/*.o
