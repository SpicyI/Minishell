/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 00:09:50 by azakariy          #+#    #+#             */
/*   Updated: 2023/02/08 17:07:41 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_find_env(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		if (ft_strchr(array[i], '$'))
			array[i] = ft_replace_env(array[i], 0, 0, 0);
		i++;
	}
}

char	*ft_replace_env(char *str, int i, int in_d, int in_s)
{
	char	*new_str;

	new_str = NULL;
	while (str[i])
	{
		if (str[i] == '"' && !in_s)
			in_d = !in_d;
		else if (str[i] == '\'' && !in_d)
			in_s = !in_s;
		if (str[i] == '$' && (in_d || (!in_d && !in_s)) && ++i)
		{
			new_str = ft_strjoin(new_str, ft_get_env(str, i));
			if (str[i] == '?')
				i++;
			else
			{
				while (ft_isalnum(str[i]))
					i++;
			}
		}
		new_str = ft_append_char(new_str, str[i]);
		i++;
	}
	return (new_str);
}

char	*ft_get_env(char *str, int i)
{
	t_env	*env_list;
	int		j;
	char	*name;

	if (str[i] == ' ' || str[i] == 0)
		return ("$");
	else if (str[i] == '?')
		return (ft_itoa(g_gfl->exit));
	j = i;
	while (ft_isalnum(str[i]))
		i++;
	name = ft_substr(str, j, i - j);
	env_list = g_gfl->env;
	while (env_list)
	{
		if (ft_strcmp(name, env_list->name))
		{
			return (ft_strdup(env_list->value));
		}
		env_list = env_list->next;
	}
	return ("");
}
