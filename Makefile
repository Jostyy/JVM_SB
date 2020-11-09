# all:
# 	g++ -std=c++11 -Wextra -Wall ./include/constantPool.h ./include/frame.h ./include/heap.h ./include/classeLeitor.h ./include/classFlags.h ./include/pilhaOperandos.h ./include/operacoes.h ./include/methods.h ./include/methodArea.h ./include/localVariables.h ./include/interfaces.h ./include/fields.h ./include/attributes.h ./include/baseTypes.h ./include/classe.h ./src/constantPool.cpp ./src/frame.cpp ./src/heap.cpp ./src/classeLeitor.cpp ./src/classFlags.cpp ./src/pilhaOperandos.cpp ./src/operacoes.cpp ./src/methods.cpp ./src/methodArea.cpp ./src/localVariables.cpp ./src/interfaces.cpp ./src/fields.cpp ./src/attributes.cpp ./src/baseTypes.cpp ./src/classe.cpp ./src/main.cpp -lm -o jvm

SRC_DIR = src
INC_DIR = ./include
OBJ_DIR = obj
DOC_DIR = doc

CXX_SOURCES  = $(wildcard $(SRC_DIR)/*.cpp)
INCLUDES = $(wildcard $(INC_DIR)/*.h)
OBJECTS  = $(CXX_SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

CFLAGS = -std=c++11 -I$(INC_DIR) -Wall -Wextra

ifeq ($(OS),Windows_NT)
	EXE = bin\jvm.exe
	CC = g++
	RM = del /Q

	CLEAN_DOC_COMMAND = $(RM) $(DOC_DIR)
	CLEAN_OBJ_COMMAND = $(RM) $(OBJ_DIR)
	CLEAN_BIN_COMMAND = $(RM) $(EXE)
else
	EXE = bin/jvm
	CC = g++
	RM = rm -rf

	CLEAN_DOC_COMMAND = $(RM) $(DOC_DIR)/*
	CLEAN_OBJ_COMMAND = $(RM) $(OBJ_DIR)/*
	CLEAN_BIN_COMMAND = $(RM) $(EXE)
endif


all: $(EXE)


debug: CFLAGS += -g
debug: $(EXE)


$(EXE): $(OBJECTS)
	@echo "Linking and generating executable ("$@")"
	@$(CC) $(CFLAGS) $(OBJECTS) -o $@


$(OBJECTS): $(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	@echo "Compiling "$<" to "$@""
	@$(CC) $(CFLAGS) -c $< -o $@




.PHONY: clean
clean: clean_obj clean_bin

.PHONY: clean_doc
clean_doc:
	$(CLEAN_DOC_COMMAND)

.PHONY: clean_obj
clean_obj:
	$(CLEAN_OBJ_COMMAND)

.PHONY: clean_bin
clean_bin:
	$(CLEAN_BIN_COMMAND)