NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
SRC = $(wildcard *.c) $(wildcard ./gnl/*.c)
OBJ = $(SRC:.c=.o)


$(NAME): $(SRC) $(OBJ)
		ar -rcs $(NAME) $(OBJ)
		ranlib $(NAME)

all: $(NAME)

%.o: %.c
		$(CC) $(CFLAGS) -o $@ -c $?

clean:
		$(RM) $(OBJ)

fclean: clean
		$(RM) $(NAME)

re: fclean all
