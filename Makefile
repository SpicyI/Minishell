NAME = minishell
SRC = $(wildcard parsing/*.c) $(wildcard builtins/*.c) $(wildcard execute/*.c) 
LDFLAGS= -L /goinfre/del-khay/homebrew/opt/readline/lib -lreadline
CPPFLAGS= -I /goinfre/del-khay/homebrew/opt/readline/include
CC = cc -Wall -Wextra -Werror
LIB = libft/libft.a
OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	make -C libft
	$(CC) $(LIB) $(LDFLAGS)  $(OBJ) -o $(NAME) 
%.o: %.c
		$(CC) -I .  -o $@ -c $?
clean :
	make fclean -C libft
	rm -rf $(OBJ)
fclean : clean
	rm -rf $(NAME)
re : fclean all