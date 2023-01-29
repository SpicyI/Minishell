/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 19:50:32 by del-khay          #+#    #+#             */
/*   Updated: 2023/01/29 18:28:54 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void cd(char *path)
{
    if (!path)
        path = getenv("HOME");
    if(!path)
    {
        ft_putendl_fd("cd: HOME not set", 2);
        exit(1);
    }
    if (!ft_strlen(path))
        return ;
    if (chdir(path) == -1)
    {
        perror(ft_strjoin(ft_strdup("cd: "), path));
        exit(1);
    }
}

int main(int ac, char **av)
{
    cd(av[1]);
    printf("%s\n",getcwd(NULL, 0));
    //system("leaks cd");
    return (0);
}
