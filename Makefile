# Makefile

# Set the name of your executable
TARGET = minishell

# Set the source directory
SRC_DIR = src

# Set the object directory
OBJ_DIR = obj

# Set the installation directory for readline
READLINE_INSTALL_DIR = $(shell pwd)/readline/library
READLINE_INCLUDE_DIR = $(READLINE_INSTALL_DIR)/include
READLINE_LIB_DIR = $(READLINE_INSTALL_DIR)/lib
READLINE_LIB = $(READLINE_LIB_DIR)/libreadline.a

MINI_H = inc/minishell.h

LIBFT = libft/libft.a

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Ilibft -Iinc -I$(READLINE_INCLUDE_DIR)
LDFLAGS = -L$(READLINE_LIB_DIR) -Llibft -lreadline -lhistory -lft -lncurses

# Find all source files in the src directory and its subdirectories
SRC_FILES := $(shell find $(SRC_DIR) -name '*.c')

# Generate object file names from source files
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

# Extract directory structure from object file paths
OBJ_DIRS := $(sort $(dir $(OBJ_FILES)))

# Default rule
all: $(TARGET)

run_me: $(TARGET)
	./$(TARGET)

# Rule for the target executable
$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

# Rule for generating object files and creating directories
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(MINI_H) $(READLINE_LIB) $(LIBFT) | $(OBJ_DIRS)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule for creating the obj directory
$(OBJ_DIRS):
	mkdir -p $@

# Rule for configuring, building, and installing readline
$(READLINE_LIB):
	@echo "Installing readline..."
	@cd ./readline; ./configure --prefix=$(READLINE_INSTALL_DIR) > /dev/null 2>&1; make > /dev/null 2>&1; make install > /dev/null 2>&1
	@echo "Readline installed"

$(LIBFT):
	make -C libft

# Clean rule
clean:
	rm -rf $(OBJ_DIR)
	make clean -C libft

fclean: clean clean_readline
	rm -rf $(TARGET)
	make fclean -C libft

clean_readline:
	rm -rf $(READLINE_INSTALL_DIR)

# Phony targets to avoid conflicts with file names
.PHONY: all clean fclean clean_readline run_me
