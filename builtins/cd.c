/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 19:50:32 by del-khay          #+#    #+#             */
/*   Updated: 2023/02/12 00:48:19 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd(char **path)
{
	char	**current_pwd;
	char	*tmp;
	char	*gotothis;

	gotothis = NULL;
	current_pwd = (char **)ft_calloc(2, sizeof(char *));
	tmp = getcwd(NULL, 0);
	if (!tmp)
		tmp = ft_strdup("..");
	*current_pwd = ft_strjoin(ft_strdup("OLDPWD="), tmp);
	if (!path || !*path)
		gotothis = ft_getenv("HOME");
	else
		gotothis = *path;
	if (!gotothis)
	{
		ft_putendl_fd("cd: HOME not set", 2);
		return (1);
	}
	export(current_pwd);
	free(tmp);
	free(*current_pwd);
	if (!ft_strlen(gotothis))
		return (0);
	if (chdir(gotothis) == -1)
	{
		perror(ft_strjoin(ft_strdup("cd: "), gotothis));
		return (1);
	}
	tmp = getcwd(NULL, 0);
	if (!tmp)
		tmp = ft_strdup("..");
	*current_pwd = ft_strjoin(ft_strdup("PWD="), tmp);
	export(current_pwd);
	free(tmp);
	free(*current_pwd);
	free(current_pwd);
	return (0);
}
