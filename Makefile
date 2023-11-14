NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD

lib = libft/libft.a

# Folders
SRC_DIR = src
OBJ_DIR = obj
DEP_DIR = dep
INC_DIR = inc

# Source files
SRC = main.c init_builtins.c\
	init_minishell.c execute_cmd.c \
	echo.c pwd.c exit.c env.c \
	process_utils.c cd.c export.c\
	env_utils.c ft_perror.c export_utils.c \
	unset.c execute_builtins.c \
	print_error.c

# Object files
OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))
DEP = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.d))

# Compile SRC files and move to folders
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(INC_DIR)/minishell.h
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -Ireadline -Ilibft -g -O3 -c $< -o $@
	@mkdir -p $(DEP_DIR)
	@mv $(OBJ_DIR)/$*.d $(DEP_DIR)/

all: lib $(NAME)

$(NAME): $(lib) $(OBJ)
	$(CC) $(OBJ) -L./libft -lft -lreadline -o $(NAME)
	@echo "Minishell compiled!"

clean:
	make clean -C libft
	rm -rf $(OBJ_DIR) $(DEP_DIR)


fclean:
	make fclean -C libft
	rm -rf $(NAME) $(OBJ_DIR) $(DEP_DIR)

lib:
	make -C libft


re:	fclean all


-include $(DEP)

.PHONY: all re clean fclean