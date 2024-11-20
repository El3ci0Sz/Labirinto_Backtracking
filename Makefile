SRC_DIR = src
INCLUDE_DIR = include

# Compilador e flags
CC = gcc
CFLAGS = -I$(INCLUDE_DIR) -Wall

# Arquivos fonte e objetos
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.c=$(SRC_DIR)/%.o)

# Nome do executável
EXEC = Labirinto_Backtracking

# Regra para compilar o programa
$(EXEC): $(OBJ_FILES)
	$(CC) -o $(EXEC) $(OBJ_FILES)

# Regra para compilar arquivos .c em arquivos .o
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $(CFLAGS) $< -o $@