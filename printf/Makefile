NAME = libftprintf.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror

OBJ = $(SRC:.c=.o)

LIBC =	ft_printf.c\
		ft_puts.c\
		ft_utilities.c\
		ft_hex.c\
		ft_hex_recursive.c

SRC = $(LIBC)

all : $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY: all clean fclean re
