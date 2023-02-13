/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_vars2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 19:11:10 by del-khay          #+#    #+#             */
/*   Updated: 2023/02/13 15:33:15 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_shell_var_value(char *str)
{
	t_not_env	*tmp;

	tmp = g_gfl.not_env;
	while (tmp)
	{
		if (!ft_strncmp(str, tmp->name, 0))
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (NULL);
}

int	is_shell_var2(char *str)
{
	char	*value;
	char	**tmp;

	value = get_shell_var_value(str);
	if (!value)
	{
		free(value);
		return (0);
	}
	else
	{
		tmp = (char **)ft_calloc(2, sizeof(char *));
		*tmp = ft_strjoin(ft_strjoin(str, "="), value);
		export(tmp);
		free(value);
		free(*tmp);
		free(tmp);
		return (1);
	}
	return (0);
}

t_not_env	*ft_not_envnew(char **content)
{
	t_not_env	*new_node;

	new_node = (t_not_env *)malloc(sizeof(t_not_env));
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
