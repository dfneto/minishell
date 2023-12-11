NAME = minishell

SRC_DIR = src
OBJ_DIR = obj
LIBFT_DIR = libft

SRCS := $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/builtin/*.c) $(wildcard $(SRC_DIR)/env/*.c) $(wildcard $(SRC_DIR)/expansion/*.c) $(wildcard $(SRC_DIR)/lexical_analysis/*.c) $(wildcard $(SRC_DIR)/process/*.c) $(wildcard $(SRC_DIR)/utils/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

LIBFT = $(LIBFT_DIR)/libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
# Lucas readline:
LDFLAGS = -L$(LIBFT_DIR) -lft -lreadline
INCLUDES = -I$(SRC_DIR) -I$(LIBFT_DIR) -Iinc
# David readline
# LDFLAGS = -L$(LIBFT_DIR) -lft -L/Users/davifern/.brew/opt/readline/lib -lreadline
# INCLUDES = -I$(SRC_DIR) -I$(LIBFT_DIR) -Iinc -I/Users/davifern/.brew/opt/readline/include
# For compilers to find readline you may need to set:
# export LDFLAGS="-L/Users/davifern/.brew/opt/readline/lib"
# export CPPFLAGS="-I/Users/davifern/.brew/opt/readline/include"

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@rm -rf $(OBJ_DIR)

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
