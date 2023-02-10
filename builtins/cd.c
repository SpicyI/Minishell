/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 19:50:32 by del-khay          #+#    #+#             */
/*   Updated: 2023/02/09 19:05:28 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd(char **path)
{
	//char	*current_pwd;

	//current_pwd = getcwd(NULL, 0);
	if (!*path)
		*path = ft_getenv("HOME");
	if (!*path)
	{
		ft_putendl_fd("cd: HOME not set", 2);
		return (1);
	}
	//export(ft_strjoin(ft_strdup("OLDPWD="), current_pwd));
	//free(current_pwd);
	if (!ft_strlen(*path))
		return (0);
	if (chdir(*path) == -1)
	{
		perror(ft_strjoin(ft_strdup("cd: "), *path));
		return (1);
	}
	//current_pwd = getcwd(NULL, 0);
	//export(ft_strjoin(ft_strdup("PWD="), current_pwd));
	//free(current_pwd);
	return (0);
}

// int main(int ac, char **av)
// {
//     cd(av[1]);
//     printf("%s\n",getcwd(NULL, 0));
//     //system("leaks cd");
//     return (0);
// }
