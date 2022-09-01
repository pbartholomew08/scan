CXX = g++

CXXFLAGS = -O2 -std=c++17

SRC = $(wildcard src/*.cpp)
INC = -Iinclude
LTBB = -ltbb

OBJ = $(SRC:%.cpp=%.o)

all: scan

scan: $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(INC) $(LTBB)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(INC)

clean:
	rm -f scan $(OBJ)
