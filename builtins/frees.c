/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 20:14:12 by del-khay          #+#    #+#             */
/*   Updated: 2023/02/04 21:53:49 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_export_node(t_export *node)
{
	if (!node)
		return ;
	if (node->name)
		free(node->name);
	if (node)
		free(node);
}

void	free_env_node(t_env *node)
{
	if (!node)
		return ;
	if (node->name)
		free(node->name);
	if (node->value)
		free(node->value);
	free(node);
}

void	free_not_env_node(t_not_env *node)
{
	if (!node)
		return ;
	if (node->name)
		free(node->name);
	if (node->value)
		free(node->value);
	free(node);
}

int	ft_env(char *str)
{
	t_env		*tmp;
	t_export	*tmp2;

	tmp = g_gfl.env;
	tmp2 = g_gfl.exp;
	while (tmp)
	{
		if (!ft_strncmp(str, tmp->name, 0))
		{
			free(str);
			return (1);
		}
		tmp = tmp->next;
	}
	while (tmp2)
	{
		if (!ft_strncmp(str, tmp2->name, 0))
		{
			free(str);
			return (1);
		}
		tmp2 = tmp2->next;
	}
	return (0);
}
