/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 19:50:32 by del-khay          #+#    #+#             */
/*   Updated: 2023/01/26 20:30:34 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void cd(char *path)
{
    char 
    if (chdir(path) == -1)
        perror("cd");
}

int main(int ac, char **av)
{
    cd(av[1]);
    return (0);
}

//my own cd command

void my_cd(char *path)
{
    char *cwd;
    char *new_path;
    int i;
    int j;

    cwd = getcwd(NULL, 0);
    i = 0;
    j = 0;
    if (path[0] == '/')
    {
        new_path = ft_strdup(path);
    }
    else
    {
        new_path = ft_strjoin(cwd, "/");
        new_path = ft_strjoin(new_path, path);
    }
    if (chdir(new_path) == -1)
        perror("cd");
    free(new_path);
    free(cwd);
}