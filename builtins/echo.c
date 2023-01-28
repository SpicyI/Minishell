#include "minishell.h"

int arrlen(char **arr)
{
    int i;

    i = 0;
    while (arr[i])
        i++;
    return (i);
} 
void    echo(char **str)
{
    int n;

    n = 0;
    if (str && ft_strlen(*str) && ft_strncmp(*str, ECHO_NL,ft_strlen(str[0])) == 0)
    {
        n = 1;
        str++;
    }
    
    while(str && *str)
    {
        ft_putstr_fd(*str, 1);
        if (*(str + 1))
            ft_putchar_fd(' ', 1);
        str++;
    }
    if (n == 0)  
        ft_putchar_fd('\n', 1);
    
}


int main(int ac, char **av)
{
    echo(av + 1);
    return (0);
}