OBJ_DIR := ./.obj
SRC_DIR := ./src

OBJ_FILES := julia.o global.o color.o budhabrot.o escape_time.o image.o inverse_iteration.o parse_options.o 

vpath %.c $(SRC_DIR)
vpath %.o $(OBJ_DIR)

julia: $(OBJ_DIR) $(OBJ_FILES)
	$(CC) -O2 -o 'julia' $(OBJ_DIR)/* -lm

%.o: %.c
	$(CC) -O2 -c $< -o $(OBJ_DIR)/$@ 

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

.PHONY: clean
clean:
	rm ./julia
	rm -rf $(OBJ_DIR)
