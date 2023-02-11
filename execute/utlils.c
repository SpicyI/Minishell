/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utlils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 16:22:16 by del-khay          #+#    #+#             */
/*   Updated: 2023/02/11 17:49:57 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_isdir(char *cmd, int opt)
{
	DIR	*dir;

	if (!cmd || ft_strlen(cmd) == 0)
		return ;
	dir = opendir(cmd);
	if (dir)
	{
		if (ft_strchr(cmd, '/') && opt == 0)
		{
			ft_dprintf(NOT_A_DIRECTORY, cmd);
			exit(126);
		}
		else if (opt)
		{
			ft_dprintf(COMMAND_NOT_FOUND, cmd);
			exit(127);
		}
		closedir(dir);
	}
}

char	**env_to_arr(void)
{
	char	**env;
	t_env	*ref;
	int		i;

	ref = g_gfl.env;
	i = 0;
	if (ft_envlen(g_gfl.env) == 0)
		return (NULL);
	env = ft_calloc(ft_envlen(g_gfl.env) + 1, sizeof(char *));
	while (ref)
	{
		env[i] = ft_strjoin(ft_strjoin(ft_strdup(ref->name), "="), ref->value);
		ref = ref->next;
		i++;
	}
	return (env);
}

int	ft_envlen(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

char	*check_abs_path(char *cmd)
{
	if (!access(cmd, F_OK))
	{
		if (!access(cmd, X_OK))
			return (cmd);
		ft_dprintf(PERMISSION_DENIED, cmd);
		exit(126);
	}
	return (NULL);
}
