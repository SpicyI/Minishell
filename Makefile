NAME = minishell
SRC = $(wildcard parsing/*.c) $(wildcard builtins/*.c) $(wildcard execute/*.c) 

LDFLAGS= -L /goinfre/del-khay/homebrew/opt/readline/lib -lreadline
CPPFLAGS= -I /goinfre/del-khay/homebrew/opt/readline/include
ALL : $(NAME)

$(NAME) : $(SRC)
	cc -Wall -Wextra -Werror -I . libft/libft.a  $(LDFLAGS)  $(SRC) -o $(NAME) 
fclean :
	rm $(NAME)

norm :
	norminette *.c *.h

re : fclean ALL