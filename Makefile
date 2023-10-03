NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD -g

# readline brew local
LDFLAGS = -L/sgoinfre/Perso/lsulzbac/homebrew/opt/readline/lib
CPPFLAGS = -I/sgoinfre/Perso/lsulzbac/homebrew/opt/readline/include

lib = libft/libft.a

# Folders
SRC_DIR = src
OBJ_DIR = obj
DEP_DIR = dep
INC_DIR = inc

# Source files
SRC = main.c init_minishell.c utils_quotes.c

# Object files
OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))
DEP = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.d))

# Compile SRC files and move to folders
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(INC_DIR)/minishell.h
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -Ilibft $(CPPFLAGS) -O3 -c $< -o $@
	@mkdir -p $(DEP_DIR)
	@mv $(OBJ_DIR)/$*.d $(DEP_DIR)/

all: lib $(NAME)

$(NAME): $(lib) $(OBJ) Makefile
	$(CC) $(OBJ) -L./libft -lft $(LDFLAGS) -lreadline -o $(NAME)
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