CXXFLAGS ?= -std=c++11 -Wall -pedantic -g
LIB       = libstinkee.a
LIBSRC    = \
	stinkee_diffuser.o \
	stinkee_signal.o \
	stinkee_squarewave.o

stinkeedemo: $(LIB) stinkeedemo.o
	$(CXX) $(CXXFLAGS) -o stinkeedemo -L. stinkeedemo.o -lstinkee -lportaudio

$(LIB): $(LIBSRC)
	$(AR) -rcs $(LIB) $?

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) -I. $<

.PHONY: clean
clean:
	$(RM) $(LIBSRC) stinkeedemo.o
	$(RM) $(LIB)
	$(RM) stinkeedemo
