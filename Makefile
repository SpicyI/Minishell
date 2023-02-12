NAME = minishell
SRC = $(wildcard parsing/*.c) $(wildcard builtins/*.c) $(wildcard execute/*.c)

ALL : $(NAME)

$(NAME) : $(SRC)
	gcc -Wall -Wextra -Werror -I . libft/libft.a -lreadline $(SRC) -o $(NAME) -fsanitize=address
fclean :
	rm $(NAME)

norm :
	norminette *.c *.h

re : fclean ALL