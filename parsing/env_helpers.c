/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 15:10:37 by azakariy          #+#    #+#             */
/*   Updated: 2023/02/13 13:13:28 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_new_env(char *name, char *value)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	new_node->name = name;
	new_node->value = value;
	new_node->next = NULL;
	return (new_node);
}

void	ft_env_add(t_env **lst, t_env *new)
{
	t_env	*holder;

	if (!lst || !new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		holder = *lst;
		while (holder && holder->next)
			holder = holder->next;
		holder->next = new;
	}
}

t_env	*ft_link(char **envp)
{
	int		i;
	int		j;
	t_env	*envi;
	char	*name;
	char	*value;

	if (!envp[0])
		return (ft_no_env());
	i = 0;
	envi = NULL;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] && envp[i][j] != '=')
			j++;
		name = ft_substr(envp[i], 0, j);
		value = ft_substr(envp[i], j + 1, ft_strlen(envp[i]) - j);
		ft_env_add(&envi, ft_new_env(name, value));
		i++;
	}
	return (envi);
}

t_env	*ft_no_env(void)
{
	char	*buffer;
	t_env	*envi;

	envi = NULL;
	buffer = ft_calloc(PATH_MAX, sizeof(char));
	ft_env_add(&envi, ft_new_env(ft_strdup("PWD"), getcwd(buffer, PATH_MAX)));
	ft_env_add(&envi, ft_new_env(ft_strdup("SHLVL"), ft_strdup("1")));
	return (envi);
}
