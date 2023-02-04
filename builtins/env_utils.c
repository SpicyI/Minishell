/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 20:11:36 by del-khay          #+#    #+#             */
/*   Updated: 2023/02/04 19:08:21 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_envnew(char **content)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (0);
	if (content)
	{
		new_node->name = content[0];
		new_node->value = content[1];
	}
	else
	{
		new_node->name = 0;
		new_node->value = 0;
	}
	new_node->next = 0;
	return (new_node);
}

t_export	*ft_exportnew(char *content)
{
	t_export	*new_node;

	new_node = (t_export *)malloc(sizeof(t_export));
	if (!new_node)
		return (0);
	if (content)
		new_node->name = content;
	else
		new_node->name = 0;
	new_node->next = 0;
	return (new_node);
}

void	ft_envadd_back(t_env **alst, t_env *new)
{
	t_env	*tmp;

	if (!alst || !new)
		return ;
	if (!*alst)
	{
		*alst = new;
		return ;
	}
	tmp = *alst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	ft_exportadd_back(t_export **alst, t_export *new)
{
	t_export	*tmp;

	if (!alst || !new)
		return ;
	if (!*alst)
	{
		*alst = new;
		return ;
	}
	tmp = *alst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}
