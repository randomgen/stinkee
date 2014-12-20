CC=g++
CCFLAGS=-std=c++11 -Wall -g
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
	rm -f $(LIBSRC) stinkeedemo.o
	rm -f $(LIB)
	rm -f stinkeedemo
