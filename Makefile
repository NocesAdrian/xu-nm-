SRC_DIR = SRC
OBJ_DIR = BUILD/OBJ
EXECUTABLE_DIR = BUILD/EXECUTABLE

MAIN_C = main.c
CFLAGS = -Wall -Wextra -g
CC = gcc

OBJ = $(OBJ_DIR)/main.o $(OBJ_DIR)/fileio.o

build:
	mkdir -p $(OBJ_DIR) $(EXECUTABLE_DIR)
	$(CC) $(CFLAGS) -c $(MAIN_C) -o $(OBJ_DIR)/main.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/fileio.c -o $(OBJ_DIR)/fileio.o
	$(CC) $(CFLAGS) $(OBJ) -o $(EXECUTABLE_DIR)/program

run: $(EXECUTABLE_DIR)/program
	./$(EXECUTABLE_DIR)/program

clean:
	rm -rf $(OBJ_DIR)
