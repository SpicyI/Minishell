/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 19:50:32 by del-khay          #+#    #+#             */
/*   Updated: 2023/02/11 18:28:30 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd(char **path)
{
	char	**current_pwd;
	char	*tmp;

	current_pwd = (char **)ft_calloc(2, sizeof(char *));
	tmp = getcwd(NULL, 0);
	if (!tmp)
		tmp = ft_strdup("..");
	*current_pwd = ft_strjoin(ft_strdup("OLDPWD="), tmp);
	if (!*path)
		*path = ft_getenv("HOME");
	if (!*path)
	{
		ft_putendl_fd("cd: HOME not set", 2);
		return (1);
	}
	export(current_pwd);
	free(tmp);
	free(*current_pwd);
	if (!ft_strlen(*path))
		return (0);
	if (chdir(*path) == -1)
	{
		perror(ft_strjoin(ft_strdup("cd: "), *path));
		return (1);
	}
	tmp = getcwd(NULL, 0);
	if (!tmp)
		tmp = ft_strdup("..");
	*current_pwd = ft_strjoin(ft_strdup("PWD="), tmp);
	free(tmp);
	export(current_pwd);
	free(*current_pwd);
	free(current_pwd);
	return (0);
}

