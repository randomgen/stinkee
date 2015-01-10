CXX      ?= g++
CXXFLAGS ?= -std=c++11 -Wall -pedantic -g
LIB       = libstinkee.a
LIBSRC    = \
	stinkee_diffuser.o \
	stinkee_signal.o \
	stinkee_squarewave.o

stinkeedemo: $(LIB) stinkeedemo.o
	$(CXX) $(CXXFLAGS) -o stinkeedemo -L. stinkeedemo.o -lstinkee -lportaudio

$(LIB): $(LIBSRC)
	ar -rcs $(LIB) $?

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) -I. $<

.PHONY: clean
clean:
	rm -f $(LIBSRC) stinkeedemo.o
	rm -f $(LIB)
	rm -f stinkeedemo
