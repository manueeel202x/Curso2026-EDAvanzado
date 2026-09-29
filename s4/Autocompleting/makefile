# Compilador
CXX = g++
CXXFLAGS = -Wall -g -Iinclude

# Carpetas
SRC_DIR = src
APP_DIR = apps
OBJ_DIR = obj
BIN_DIR = bin

# Archivos
OBJS   = $(OBJ_DIR)/trie.o $(OBJ_DIR)/main.o
TARGET = $(BIN_DIR)/autocomplete

.PHONY: all clean run

# Regla principal
all: $(TARGET)

# Enlazado (garantiza que exista bin/)
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compilacion (garantiza que exista obj/)
$(OBJ_DIR)/trie.o: $(SRC_DIR)/trie.cpp include/trie.h | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/main.o: $(APP_DIR)/main.cpp include/trie.h | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Crear directorios si no existen
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Ejecutar el binario (opcional)
run: all
	./$(TARGET)

# Limpiar
clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET)
