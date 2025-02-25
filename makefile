# Variáveis
CXX = g++
CXXFLAGS = -g -Wall -Wextra
SRC_DIR = src
BUILD_DIR = build
TARGET = $(BUILD_DIR)/main

# Lista de arquivos fonte
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)

# Arquivos objeto
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Arquivos de dependência
DEPS = $(OBJ_FILES:.o=.d)

# Regras
all: $(TARGET)

# Regra para criar o executável
$(TARGET): $(OBJ_FILES)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Regra para compilar os arquivos objeto e gerar dependências
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -MMD -c $< -o $@

# Incluir os arquivos de dependência gerados
-include $(DEPS)

# Regra para rodar o programa
run: all
	./$(TARGET)

# Limpar arquivos compilados
clean:
	rm -rf $(BUILD_DIR)

# Phony targets (não correspondem a arquivos reais)
.PHONY: all run clean
