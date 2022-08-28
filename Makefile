CXX = g++

SRC = $(wildcard src/*.cpp)
INC = -Iinclude

OBJ = $(SRC:%.cpp=%.o)

all: scan

scan: $(OBJ)
	$(CXX) -o $@ $^

%.o: %.cpp
	$(CXX) -o $@ $< $(INC)
