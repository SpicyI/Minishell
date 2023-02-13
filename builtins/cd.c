/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 19:50:32 by del-khay          #+#    #+#             */
/*   Updated: 2023/02/13 15:13:32 by del-khay         ###   ########.fr       */
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

void	cd_error(char *path)
{
	if (path && !ft_strncmp(path, "-", 0))
		ft_dprintf(OLDPWD_NOT_SET, NULL);
	else
		ft_dprintf(HOME_NOT_SET, NULL);
}

char	*cd_path(char **args)
{
	char	*gotothis;

	if (!args || !*args)
		gotothis = ft_getenv("HOME");
	else if (!ft_strncmp(*args, "-", 0))
		gotothis = ft_getenv("OLDPWD");
	else
		gotothis = ft_strdup(*args);
	return (gotothis);
}

int	cd(char **args)
{
	char	*gotothis;

	gotothis = cd_path(args);
	if (!gotothis)
	{
		cd_error(*args);
		return (1);
	}
	set_oldpwd();
	if (!ft_strlen(gotothis))
	{
		free(gotothis);
		return (0);
	}
	if (chdir(gotothis) == -1)
	{
		ft_dprintf(NO_SUCH_FILE, gotothis);
		free(gotothis);
		return (1);
	}
	set_pwd();
	free(gotothis);
	return (0);
}
