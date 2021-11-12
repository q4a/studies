CXXFLAGS += -I. -O0 -g3 -Wall -std=c++11 -D__DEBUG__ -D_DEBUG -D_UNICODE
CPPFILES = $(basename $(wildcard *.cpp))
TARGETS = $(addprefix bin/, $(addsuffix .exe, $(CPPFILES)))

all: pre-build $(TARGETS)

pre-build:
	@if [ ! -d bin ]; then mkdir bin && echo 'mkdir bin'; fi

bin/%.exe: %.cpp
	g++ $(CXXFLAGS) -o $@ $<

clean:
	rm -rf $(TARGETS)
