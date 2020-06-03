TARGET=sudokutectonic

CPPFLAGS=-Wall -Werror -pedantic -ggdb -O0 -std=c++11 -Isrc -I include -I include/interfaces -g 

SOURCES=$(wildcard src/*.cpp)
HEADERS=$(wildcard include/*.hpp)

LDFLAGS=-lgtest -lgmock -lgmock_main -lpthread

CXX=g++

.phony: all clean test

all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	$(CXX) $(CPPFLAGS) -o $@ $(SOURCES)

clean:
	@rm -rf $(TARGET) $(TEST)


