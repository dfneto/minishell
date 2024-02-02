NAME = minishell

SRC_DIR = src

OBJ_DIR = obj

READLINE_INSTALL_DIR = $(shell pwd)/readline/library
READLINE_INCLUDE_DIR = $(READLINE_INSTALL_DIR)/include
READLINE_LIB_DIR = $(READLINE_INSTALL_DIR)/lib
READLINE_LIB = $(READLINE_LIB_DIR)/libreadline.a

MINI_H = inc/minishell.h

LIBFT = libft/libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -Ilibft -Iinc -I$(READLINE_INCLUDE_DIR)
LDFLAGS = -L$(READLINE_LIB_DIR) -Llibft -lreadline -lhistory -lft -lncurses

SRC_FILES = \
    $(SRC_DIR)/builtin/cd.c \
    $(SRC_DIR)/builtin/cd_utils.c \
    $(SRC_DIR)/builtin/echo.c \
    $(SRC_DIR)/builtin/env.c \
    $(SRC_DIR)/builtin/execute_builtins.c \
    $(SRC_DIR)/builtin/exit.c \
    $(SRC_DIR)/builtin/export.c \
    $(SRC_DIR)/builtin/export_utils.c \
    $(SRC_DIR)/builtin/init_builtins.c \
    $(SRC_DIR)/builtin/pwd.c \
    $(SRC_DIR)/builtin/unset.c \
    $(SRC_DIR)/debug/printers_processes.c \
    $(SRC_DIR)/debug/printers_tokens.c \
    $(SRC_DIR)/env/env_create.c \
    $(SRC_DIR)/env/ft_getenv.c \
    $(SRC_DIR)/env/ft_setenv.c \
    $(SRC_DIR)/env/ft_unsetenv.c \
    $(SRC_DIR)/env/get_env_array.c \
    $(SRC_DIR)/env/node_utils.c \
    $(SRC_DIR)/execution/execute_cmd.c \
    $(SRC_DIR)/execution/execute_cmd_utils.c \
    $(SRC_DIR)/execution/mult_cmd.c \
    $(SRC_DIR)/execution/mult_cmd_utils.c \
    $(SRC_DIR)/execution/single_cmd.c \
    $(SRC_DIR)/execution/single_cmd_utils.c \
    $(SRC_DIR)/expansion/exp_utils.c \
    $(SRC_DIR)/expansion/exp_utils2.c \
    $(SRC_DIR)/expansion/expansion.c \
    $(SRC_DIR)/expansion/init_expansion.c \
    $(SRC_DIR)/lexical_analysis/clean_tokens.c \
    $(SRC_DIR)/lexical_analysis/create_tokens.c \
    $(SRC_DIR)/lexical_analysis/init_lexical_analysis.c \
    $(SRC_DIR)/lexical_analysis/lex_utils.c \
    $(SRC_DIR)/lexical_analysis/process_quotes.c \
    $(SRC_DIR)/lexical_analysis/validate_tokens.c \
    $(SRC_DIR)/main.c \
    $(SRC_DIR)/process/heredoc.c \
    $(SRC_DIR)/process/init_process.c \
    $(SRC_DIR)/process/process_creation_utills.c \
    $(SRC_DIR)/process/process_utils.c \
    $(SRC_DIR)/process/process_utils2.c \
    $(SRC_DIR)/process/set_redirects.c \
    $(SRC_DIR)/signals/child_signals.c \
    $(SRC_DIR)/signals/main_signals.c \
    $(SRC_DIR)/utils/ft_perror.c \
    $(SRC_DIR)/utils/ft_strcmp.c \
    $(SRC_DIR)/utils/ft_strtok.c \
    $(SRC_DIR)/utils/print_error.c \
    $(SRC_DIR)/utils/safe_allocation.c \
    $(SRC_DIR)/utils/safe_allocation2.c

OBJ_FILES := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

OBJ_DIRS := $(sort $(dir $(OBJ_FILES)))

all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c Makefile $(MINI_H) $(READLINE_LIB) $(LIBFT) | $(OBJ_DIRS)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIRS):
	mkdir -p $@

$(READLINE_LIB):
	@echo "Installing readline..."
	@cd ./readline; ./configure --prefix=$(READLINE_INSTALL_DIR) > /dev/null 2>&1; make > /dev/null 2>&1; make install > /dev/null 2>&1
	@echo "Readline installed"

$(LIBFT):
	make -C libft

clean:
	rm -rf $(OBJ_DIR)
	make clean -C libft

fclean: clean clean_readline
	rm -rf $(NAME)
	make fclean -C libft

clean_readline:
	rm -rf $(READLINE_INSTALL_DIR)

re: fclean all

.PHONY: all clean fclean clean_readline re
