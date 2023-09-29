NAME = libft.a

HEADER = libft.h

CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRC_C = ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_memset.c ft_strchr.c ft_strlen.c ft_strrchr.c ft_substr.c ft_tolower.c ft_toupper.c ft_strncmp.c ft_bzero.c ft_memchr.c ft_memcmp.c ft_atoi.c ft_strnstr.c ft_strlcat.c ft_memcpy.c ft_memmove.c ft_strdup.c ft_strlcpy.c ft_calloc.c ft_strjoin.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_itoa.c ft_striteri.c ft_strmapi.c ft_split.c ft_strtrim.c

OBJ = $(SRC_C:.c=.o)

all: 	$(NAME)

%.o: %.c $(HEADER)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ) $(HEADER)
	@ar -rcs $(NAME) $(OBJ) $(HEADER)
	@echo "Libft compiled"

re: fclean all

fclean:
	@rm -f $(OBJ)
	@rm -f $(NAME)
	@echo "Libft objects and libft.a cleaned"
	

clean:
	@rm -f $(OBJ)
	@echo "Libft objects cleaned"
	

.PHONY: clean all fclean re
