
CC = g++
CFLAGS = -Wall -Wextra -std=c++17 -O2
INCLUDES = -I.
SRC_DIR = .
OBJ_DIR = obj

SOURCES = ABBIndice.cpp ArvoreBinariaBusca.cpp No.cpp Registro.cpp SistemaRegistro.cpp
OBJECTS = $(addprefix $(OBJ_DIR)/,$(SOURCES:.cpp=.o))
EXECUTABLE = sistema_registros

all: $(EXECUTABLE)

$(OBJ_DIR) $(BIN_DIR):
	mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(EXECUTABLE): $(OBJECTS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJ_DIR)/ABBIndice.o: ABBIndice.cpp 
$(OBJ_DIR)/ArvoreBinariaBusca.o: ArvoreBinariaBusca.cpp
$(OBJ_DIR)/No.o: No.cpp 
$(OBJ_DIR)/Registro.o: Registro.cpp 
$(OBJ_DIR)/SistemaRegistro.o: SistemaRegistro.cpp 

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean