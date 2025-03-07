CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -g

# Fichiers sources
SRC = automate.cpp etat.cpp lexer.cpp symbole.cpp
OBJ_DIR = obj
BIN_DIR = bin
OBJ = $(SRC:%.cpp=$(OBJ_DIR)/%.o)

# Exécutable principal
EXEC = $(BIN_DIR)/compilateur
MAIN_OBJ = $(OBJ_DIR)/main.o

# Fichiers pour les tests
TEST_SRC = tests.cpp
TEST_OBJ = $(OBJ_DIR)/tests.o
TEST_EXEC = $(BIN_DIR)/tests

# Création des dossiers si inexistants
$(shell mkdir -p $(OBJ_DIR) $(BIN_DIR))

# Compilation principale
all: $(EXEC)

$(EXEC): $(OBJ) $(MAIN_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compilation et exécution des tests (NE PREND PAS `main.o`)
tests: $(TEST_EXEC)

$(TEST_EXEC): $(TEST_OBJ) $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(TEST_OBJ): $(TEST_SRC)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Nettoyage
clean:
	rm -f $(OBJ) $(MAIN_OBJ) $(EXEC) $(TEST_OBJ) $(TEST_EXEC)

.PHONY: all clean tests
