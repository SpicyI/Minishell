/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 18:02:59 by azakariy          #+#    #+#             */
/*   Updated: 2023/02/10 21:51:13 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_append(char **array, char *new_str)
{
	int		i;
	char	**new_array;

	i = 0;
	if (ft_strlen(new_str) == 0)
		return (array);
	if (!array)
		new_array = ft_calloc(2, sizeof(char *));
	else
	{
		while (array[i])
			i++;
		new_array = ft_calloc(i + 2, sizeof(char *));
		i = 0;
		while (array[i])
		{
			new_array[i] = array[i];
			i++;
		}
	}
	new_array[i] = new_str;
	free(array);
	return (new_array);
}

int	ft_key_chars(char *str, char ***array)
{
	int	i;

	i = 0;
	if (str[i] == '>')
	{
		while (str[i] == '>')
			i++;
		*array = ft_append(*array, ft_substr(str, 0, i));
	}
	else if (str[i] == '<')
	{
		while (str[i] == '<')
			i++;
		*array = ft_append(*array, ft_substr(str, 0, i));
	}
	return (i);
}

char	**ft_filter(char *part, int i, int j)
{
	int		in_d;
	int		in_s;
	char	**part_array;

	in_d = 0;
	in_s = 0;
	part_array = NULL;
	while (part[i])
	{
		if (part[i] == '"' && !in_s)
			in_d = !in_d;
		else if (part[i] == '\'' && !in_d)
			in_s = !in_s;
		if (!in_s && !in_d && (part[i] == '>' || part[i] == '<'))
		{
			part_array = ft_append(part_array, ft_substr(part, j, i - j));
			i += ft_key_chars(part + i, &part_array);
			j = i;
		}
		else
			i++;
	}
	part_array = ft_append(part_array, ft_substr(part, j, i - j));
	return (part_array);
}

void	ft_printf_double(char **array)
{
	int	i;

	i = 0;
	while (array && array[i])
	{
		printf("%s\n", array[i]);
		i++;
	}
}

void	ft_prod_line(char **cmd, t_cmd *s_cmd, int is_last)
{
	int		i;
	char	**array;

	i = 0;
	array = NULL;
	while (cmd[i])
	{
		array = ft_destructor(array, ft_filter(cmd[i], 0, 0), 0);
		i++;
	}
	ft_free_double(cmd);
	ft_find_env(array);
	ft_set_helpers(array, s_cmd);
	ft_fill_struct(array, s_cmd, 0, is_last);
	i = 0;
	while (s_cmd->cmd && s_cmd->cmd[i])
	{
		s_cmd->cmd[i] = ft_remove_quotes(s_cmd->cmd[i]);
		i++;
	}
}
