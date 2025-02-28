CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -g

SRC = main.cpp automate.cpp etat.cpp lexer.cpp symbole.cpp
OBJ = $(SRC:.cpp=.o)
EXEC = compilateur

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)

.PHONY: all clean
