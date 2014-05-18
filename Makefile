CC=clang++
CCFLAGS=-std=c++11 -Wall
LIBSRC=\
	stinkee_device.cpp \
	stinkee_signal.cpp \
	stinkee_squarewaveutil.cpp

stinkeedemo: libstinkee stinkeedemo.cpp
	$(CC) -I. -L. -lstinkee -lportaudio stinkeedemo.cpp -o stinkeedemo

libstinkee: $(LIBSRC)
	$(CC) -c $(CCFLAGS) -I. $(LIBSRC)
	ar -rcs libstinkee.a *.o

.PHONY: clean
clean:
	rm -f *.o
	rm -f libstinkee.a
	rm -f stinkeedemo
