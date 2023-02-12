/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 19:50:32 by del-khay          #+#    #+#             */
/*   Updated: 2023/02/12 16:45:57 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_oldpwd(void)
{
	char	**current_pwd;
	char	*tmp;

	current_pwd = (char **)ft_calloc(2, sizeof(char *));
	tmp = getcwd(NULL, 0);
	if (!tmp)
		tmp = ft_strdup("..");
	*current_pwd = ft_strjoin(ft_strdup("OLDPWD="), tmp);
	export(current_pwd);
	free(tmp);
	free(*current_pwd);
	free(current_pwd);
}

void	set_pwd(void)
{
	char	**current_pwd;
	char	*tmp;

	current_pwd = (char **)ft_calloc(2, sizeof(char *));
	tmp = getcwd(NULL, 0);
	if (!tmp)
		tmp = ft_strdup("..");
	*current_pwd = ft_strjoin(ft_strdup("PWD="), tmp);
	export(current_pwd);
	free(tmp);
	free(*current_pwd);
	free(current_pwd);
}

int	cd(char **path)
{
	char	*gotothis;

	if (!path || !*path)
		gotothis = ft_getenv("HOME");
	else
		gotothis = *path;
	if (!gotothis)
	{
		ft_dprintf(HOME_NOT_SET, NULL);
		return (1);
	}
	set_oldpwd();
	if (!ft_strlen(gotothis))
		return (0);
	if (chdir(gotothis) == -1)
	{
		perror(ft_strjoin(ft_strdup("cd: "), gotothis));
		return (1);
	}
	set_pwd();
	return (0);
}
