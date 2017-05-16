TARGET=selverob
SOURCES=src
INCLUDE=src/include

INFILES=$(shell find src -name "*.cpp")
OFILES=$(INFILES:.cpp=.o)

CXX=g++
CXXFLAGS=-Wall -pedantic -Wno-long-long -O0 -ggdb -Isrc -std=c++11
LDFLAGS=-lsqlite3 -lpthread

all: compile

compile: .deps $(OFILES)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(TARGET) $(OFILES)

run: compile
	./$(TARGET)

clean:
	find src -name "*.o" | xargs rm
	rm -f ./.deps
	rm -f ./$(TARGET)

doc: $(INFILES)
	doxygen

dependencies: .deps

.deps: $(INFILES)
	rm -f .deps
	$(CXX) $(CXXFLAGS) -MM $^>>.deps

build/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $(ARTIFACTS)/$@

.PHONY: all compile run clean doc dependencies 

include .deps