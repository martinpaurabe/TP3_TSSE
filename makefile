SRC_DIR = ./src
INC_DIR = ./inc
OUT_DIR = ./build
OBJ_DIR = $(OUT_DIR)/obj

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

.DEFAULT_GOAL := all

-include $(patsubst %.o,%.d,$(OBJ_FILES))   #Si vas a buscar un .o busca un .d que te dirá
											#si hay que recompilar el .o porque algún .h cambió

all: $(OBJ_FILES)
	@echo Enlazando $@
	@gcc $(OBJ_FILES) -o $(OUT_DIR)/app.elf

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo Compilando $@
	@mkdir -p $(OBJ_DIR)
	@gcc -o $@ -c $< -I $(INC_DIR) -MMD -D USE_DYNAMIC_MEM #definimos USE_DYNAMIC_MEM para uso de memoria dinámica

clean:
	@rm -r $(OUT_DIR)

# parametro para generar la documentación de doxygen
doc:
	@mkdir -p $(OUT_DIR)   
	@doxygen doxyfile  #ejecutar "doxywizard# para generar el doxyfile, con "open build/doc/html/index.html" se abre el resultado
