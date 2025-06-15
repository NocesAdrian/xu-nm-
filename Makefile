SRC_DIR = HEADERS_SRC_FILES
OBJ_DIR = BUILD/OBJ
EXECUTABLE_DIR = BUILD/EXECUTABLE

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))
MAIN_C = main.c

CFLAGS = -Wall -Wextra -g
CC = gcc

# Default goal
all: $(EXECUTABLE_DIR)/program

# Create necessary folders
build:
	mkdir -p $(OBJ_DIR) $(EXECUTABLE_DIR)

# Rule for all .c files inside SRC/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | build
	$(CC) $(CFLAGS) -c $< -o $@

# Rule for main.c outside of SRC_DIR
$(OBJ_DIR)/main.o: $(MAIN_C) | build
	$(CC) $(CFLAGS) -c $(MAIN_C) -o $@

# Link everything into final program
$(EXECUTABLE_DIR)/program: $(OBJ_FILES) $(OBJ_DIR)/main.o
	$(CC) $(CFLAGS) $^ -o $@

# Run it
run: $(EXECUTABLE_DIR)/program
	./$<

# debug
debug: $(EXECUTABLE_DIR)/program
	gdb ./$<

# Clean
clean:
	rm -rf $(OBJ_DIR) $(EXECUTABLE_DIR)
