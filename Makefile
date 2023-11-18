NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD -g

lib = libft/libft.a

# Folders
SRC_DIR = src
SRC_DIR_EXPANSION = src/expansion
SRC_DIR_LEXICAL_ANALYSIS = src/lexical_analysis
OBJ_DIR = obj
DEP_DIR = dep
INC_DIR = inc

# Main source files
SRC = main.c init_minishell.c process_quotes.c printers.c process_creation.c \
	init_builtins.c\
	execute_cmd.c \
	echo.c pwd.c exit.c env.c \
	process_utils.c cd.c export.c\
	env_utils.c ft_perror.c export_utils.c \
	unset.c execute_builtins.c \
	print_error.c

# Expansion source files (located in the SRC_DIR_EXPANSION directory)
EXP_SRC = expansion.c utils.c string_expansion.c double_quotes_expansion.c
LEX_SRC = lexical_analysis.c create_tokens.c utils.c

# Combine main source files and expansion source files and adjust the paths for object files
FULL_SRC = $(addprefix $(SRC_DIR)/, $(SRC)) $(addprefix $(SRC_DIR_EXPANSION)/, $(EXP_SRC)) $(addprefix $(SRC_DIR_LEXICAL_ANALYSIS)/, $(LEX_SRC))
OBJ = $(FULL_SRC:%.c=$(OBJ_DIR)/%.o)
DEP = $(FULL_SRC:%.c=$(DEP_DIR)/%.d)

# Compile source files and move to folders
$(OBJ_DIR)/src/%.o: $(SRC_DIR)/%.c | setup
	$(CC) $(CFLAGS) -I$(INC_DIR) -Ilibft $(CPPFLAGS) -O3 -c $< -o $@
	@mv $(@:.o=.d) $(DEP_DIR)/

$(OBJ_DIR)/src/expansion/%.o: $(SRC_DIR_EXPANSION)/%.c | setup
	$(CC) $(CFLAGS) -I$(INC_DIR) -Ilibft $(CPPFLAGS) -O3 -c $< -o $@
	@mv $(@:.o=.d) $(DEP_DIR)/

$(OBJ_DIR)/src/lexical_analysis/%.o: $(SRC_DIR_LEXICAL_ANALYSIS)/%.c | setup
	$(CC) $(CFLAGS) -I$(INC_DIR) -Ilibft $(CPPFLAGS) -O3 -c $< -o $@
	@mv $(@:.o=.d) $(DEP_DIR)/

all: setup lib $(NAME) 

$(NAME): $(lib) $(OBJ)
	$(CC) $(OBJ) -L./libft -lft -lreadline -o $(NAME)
	@echo "Minishell compiled!"

setup:
	@mkdir -p $(OBJ_DIR)/src
	@mkdir -p $(OBJ_DIR)/src/expansion
	@mkdir -p $(OBJ_DIR)/src/lexical_analysis
	@mkdir -p $(DEP_DIR)

clean:
	make clean -C libft
	rm -rf $(OBJ_DIR) $(DEP_DIR)
	rm -rf *.dSYM

fclean:
	make fclean -C libft
	rm -rf $(NAME) $(OBJ_DIR) $(DEP_DIR)

lib:
	make -C libft

re:	fclean all

-include $(DEP)

.PHONY: all re clean fclean