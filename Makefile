
CC = g++
CFLAGS = -Wall -Wextra -std=c++17 -O2 -g # Adicionado -g para debug
# -Wno-overloaded-virtual para suprimir os avisos sobre ocultação de virtual, se desejado após revisão.
INCLUDES = -I.
SRC_DIR = .
OBJ_DIR = obj

SOURCES = main.cpp Registro.cpp SistemaRegistro.cpp No.cpp ArvoreBinariaBusca.cpp ABBIndice.cpp
OBJECTS = $(addprefix $(OBJ_DIR)/,$(SOURCES:.cpp=.o))
EXECUTABLE = sistema_registros

all: $(EXECUTABLE)

$(OBJ_DIR):
	mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@ $(LDFLAGS)

# Dependências explícitas:
# O arquivo .o depende do seu .cpp e de quaisquer .h que ele inclua diretamente ou indiretamente
# e que sejam parte do projeto (mudanças neles devem triggar recompilação).

$(OBJ_DIR)/main.o: main.cpp SistemaRegistro.h Registro.h ABBIndice.h ArvoreBinariaBusca.h No.h
$(OBJ_DIR)/Registro.o: Registro.cpp Registro.h
$(OBJ_DIR)/SistemaRegistro.o: SistemaRegistro.cpp SistemaRegistro.h ABBIndice.h Registro.h
# Para No.cpp, ArvoreBinariaBusca.cpp, ABBIndice.cpp:
# Se estes .cpp files estão praticamente vazios (só incluem o .h correspondente),
# eles ainda geram um .o. A dependência principal é o .h.
$(OBJ_DIR)/No.o: No.cpp No.h
$(OBJ_DIR)/ArvoreBinariaBusca.o: ArvoreBinariaBusca.cpp ArvoreBinariaBusca.h No.h
# ParChaveIndice.h não existe como arquivo separado; está dentro de ABBIndice.h.
# Portanto, a dependência de ABBIndice.h já cobre isso.
$(OBJ_DIR)/ABBIndice.o: ABBIndice.cpp ABBIndice.h ArvoreBinariaBusca.h No.h

clean:
	rm -rf $(OBJ_DIR) $(EXECUTABLE)

.PHONY: all clean