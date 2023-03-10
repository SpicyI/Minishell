/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 20:01:29 by del-khay          #+#    #+#             */
/*   Updated: 2023/02/11 17:42:11 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset_env(char *name)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = g_gfl.env;
	prev = 0;
	while (tmp)
	{
		if (!ft_strncmp(name, tmp->name, 0))
		{
			if (prev)
				prev->next = tmp->next;
			else
				g_gfl.env = tmp->next;
			free_env_node(tmp);
			return (1);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (0);
}

int	unset_export(char *name)
{
	t_export	*tmp;
	t_export	*prev;

	tmp = g_gfl.exp;
	prev = 0;
	while (tmp)
	{
		if (!ft_strncmp(name, tmp->name, 0))
		{
			if (prev)
				prev->next = tmp->next;
			else
				g_gfl.exp = tmp->next;
			free_export_node(tmp);
			return (1);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (0);
}

int	unset_not_env(char *name)
{
	t_not_env	*tmp;
	t_not_env	*prev;

	tmp = g_gfl.not_env;
	prev = 0;
	while (tmp)
	{
		if (!ft_strncmp(name, tmp->name, 0))
		{
			if (prev)
				prev->next = tmp->next;
			else
				g_gfl.not_env = tmp->next;
			free_not_env_node(tmp);
			return (1);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (0);
}

int	unset(char **args)
{
	char	*str;
	int		status;

	status = 0;
	while (*args)
	{
		str = ft_strdup(*args);
		if (!check_name(str, 0))
		{
			ft_dprintf(UNVALID_ID_SET, str);
			status = 1;
			free(str);
			args++;
			continue ;
		}
		unset_env(str);
		unset_export(str);
		unset_not_env(str);
		free(str);
		args++;
	}
	return (status);
}
