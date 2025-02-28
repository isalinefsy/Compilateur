CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -g

SRC = main.cpp automate.cpp etat.cpp lexer.cpp symbole.cpp
OBJ_DIR = obj
BIN_DIR = bin
OBJ = $(SRC:%.cpp=$(OBJ_DIR)/%.o)
EXEC = $(BIN_DIR)/compilateur

# Créer le dossier 'bin' et 'obj' s'ils n'existent pas
$(shell mkdir -p $(OBJ_DIR) $(BIN_DIR))

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)

.PHONY: all clean
