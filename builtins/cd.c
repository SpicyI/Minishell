/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 19:50:32 by del-khay          #+#    #+#             */
/*   Updated: 2023/02/05 18:12:09 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd(char *path)
{
	if (!path)
		path = getenv("HOME");
	if (!path)
	{
		ft_putendl_fd("cd: HOME not set", 2);
		return (1);
	}
	// update oldpwd here
	if (!ft_strlen(path))
		return (0);
	if (chdir(path) == -1)
	{
		perror(ft_strjoin(ft_strdup("cd: "), path));
		return (1);
	}
	// update pwd here
}

// int main(int ac, char **av)
// {
//     cd(av[1]);
//     printf("%s\n",getcwd(NULL, 0));
//     //system("leaks cd");
//     return (0);
// }
