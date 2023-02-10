/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 00:09:50 by azakariy          #+#    #+#             */
/*   Updated: 2023/02/10 17:23:47 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_find_env(char **array)
{
	int		i;
	char	*holder;

	i = 0;
	while (array[i])
	{
		if (ft_strchr(array[i], '$'))
		{
			holder = array[i];
			array[i] = ft_replace_env(array[i], 0, 0, 0);
			free(holder);
		}
		else if (array[i][0] == '~' && ft_strlen(array[i]) == 1)
			array[i] = ft_hyphen(array[i]);
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
			new_str = ft_clean_join(new_str, ft_get_env(str, i));
			if (str[i] == '?')
				i++;
			else
			{
				while (ft_isalnum(str[i]))
					i++;
			}
		}
		new_str = ft_append_char(new_str, str[i]);
		if (str[i])
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
		return (ft_itoa(g_gfl.exit));
	j = i;
	while (ft_isalnum(str[i]))
		i++;
	name = ft_substr(str, j, i - j);
	env_list = g_gfl.env;
	while (env_list)
	{
		if (ft_strcmp(name, env_list->name))
		{
			free(name);
			return (ft_strdup(env_list->value));
		}
		env_list = env_list->next;
	}
	return (ft_find_not_env(name));
}

char	*ft_find_not_env(char *name)
{
	t_not_env	*not_env;

	not_env = g_gfl.not_env;
	while (not_env)
	{
		if (ft_strcmp(name, not_env->name))
		{
			free(name);
			return (ft_strdup(not_env->value));
		}
		not_env = not_env->next;
	}
	return (NULL);
}

char	*ft_hyphen(char *str)
{
	t_env	*envi;

	envi = g_gfl.env;
	while (envi)
	{
		if (ft_strcmp(envi->name, "HOME"))
		{
			free(str);
			return (envi->value);
		}
		envi = envi->next;
	}
	return (str);
}
