/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 20:14:12 by del-khay          #+#    #+#             */
/*   Updated: 2023/02/04 19:18:53 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_export_node(t_export *node)
{
	if (!node)
		return ;
	if (node)
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
	t_env	*tmp;

	tmp = g_gfl.env;
	while (tmp)
	{
		if (!ft_strncmp(str, tmp->name, 0))
		{
			free(str);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
