CXX = g++
CXXFLAGS = -Wall -std=c++11

all: mymk

mymk: mymk.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

install: mymk
	cp mymk /usr/local/bin/

clean:
	rm -f mymk