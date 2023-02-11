/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 17:04:28 by del-khay          #+#    #+#             */
/*   Updated: 2023/02/11 17:59:38 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exporter(char **tab)
{
	if (!check_name(tab[0], 1))
	{
		ft_dprintf(UNVALID_ID, ft_strjoin(ft_strjoin(ft_strdup(tab[0]), "="),
				tab[1]));
		ft_dfree(tab);
		return (1);
	}
	else if (!export_type(tab))
		ft_envadd_back(&g_gfl.env, ft_envnew(tab));
	free(tab);
	return (0);
}

int	importer(char *str)
{
	if (check_name(str, 0))
	{
		if (ft_env(str))
			return (0);
		ft_exportadd_back(&g_gfl.exp, ft_exportnew(str));
	}
	else
	{
		ft_dprintf(UNVALID_ID, str);
		return (1);
		free(str);
	}
	return (0);
}

int	is_env(char **tab)
{
	t_env	*tmp;
	char	*trim;

	tmp = g_gfl.env;
	trim = ft_strtrim(tab[0], "+");
	while (tmp)
	{
		if (!ft_strncmp(trim, tmp->name, 0))
		{
			free(trim);
			free(tmp->value);
			if (tab[0][ft_strlen(tab[0]) - 1] == '+')
			{
				tmp->value = ft_strjoin(ft_strdup(tmp->value), tab[1]);
				free(tab[1]);
			}
			else
				tmp->value = tab[1];
			free(tab[0]);
			return (1);
		}
		tmp = tmp->next;
	}
	free(trim);
	return (0);
}

int	is_export(char **tab)
{
	t_export	*tmp;
	t_export	*holder;
	char		*trim;

	tmp = g_gfl.exp;
	trim = ft_strtrim(tab[0], "+");
	holder = 0;
	while (tmp)
	{
		if (!ft_strncmp(trim, tmp->name, 0))
		{
			free(tab[0]);
			tab[0] = trim;
			if (!holder)
				g_gfl.exp = tmp->next;
			else
				holder->next = tmp->next;
			free_export_node(tmp);
			return (1);
		}
		holder = tmp;
		tmp = tmp->next;
	}
	free(trim);
	return (0);
}

int	is_not_env(char **tab)
{
	t_not_env	*tmp;
	t_not_env	*holder;
	char		*trim;

	tmp = g_gfl.not_env;
	trim = ft_strtrim(tab[0], "+");
	holder = 0;
	while (tmp)
	{
		if (!ft_strncmp(trim, tmp->name, 0))
		{
			free(tab[0]);
			tab[0] = trim;
			if (!holder)
				g_gfl.not_env = tmp->next;
			else
				holder->next = tmp->next;
			free_not_env_node(tmp);
			return (1);
		}
		holder = tmp;
		tmp = tmp->next;
	}
	free(trim);
	return (0);
}
