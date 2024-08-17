# Compilador e flags
CC = g++
CFLAGS = -O3 -Wall

# Diretórios
SRC_DIR = src
BUILD_DIR = build
INSTANCES_DIR = instances

# Arquivos fonte e executável
SRC = $(wildcard $(SRC_DIR)/*.cpp)
TARGET = $(BUILD_DIR)/avob_scheduler

# Regra padrão: compilar o projeto
all: $(TARGET)

# Regra para criar o executável
$(TARGET): $(SRC)
	@echo "Compilando o programa..."
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)
	@if [ $$? -eq 0 ]; then \
		echo "Compilação bem-sucedida."; \
	else \
		echo "Erro durante a compilação."; \
	fi

# Regra para limpar arquivos gerados
clean:
	rm -f $(TARGET)

# Rodar o executável com uma instância
run: all
	./$(TARGET) $(INSTANCES_DIR)/instance1.txt