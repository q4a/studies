CXXFLAGS += -I. -O3 -g0 -Wall -std=c++11 -DNDEBUG -D_UNICODE
CPPFILES = $(basename $(wildcard *.cpp))
TARGETS = $(addprefix bin/, $(addsuffix .exe, $(CPPFILES)))

all: pre-build $(TARGETS)

pre-build:
	@if [ ! -d bin ]; then mkdir bin && echo 'mkdir bin'; fi

bin/%.exe: %.cpp
	g++ $(CXXFLAGS) -o $@ $<

clean:
	rm -rf $(TARGETS)
