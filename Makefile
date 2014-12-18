CC=g++
CCFLAGS=-std=c++11 -Wall
LIB=libstinkee.a
LIBSRC=\
	stinkee_device.o \
	stinkee_signal.o \
	stinkee_squarewaveutil.o

stinkeedemo: $(LIB) stinkeedemo.o
	$(CC) $(CCFLAGS) -o stinkeedemo -L. stinkeedemo.o -lstinkee -lportaudio

$(LIB): $(LIBSRC)
	ar -rcs $(LIB) $?

%.o: %.cpp
	$(CC) -c $(CCFLAGS) -I. $<

.PHONY: clean
clean:
	rm -f *.o
	rm -f libstinkee.a
	rm -f stinkeedemo
