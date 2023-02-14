/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 18:02:59 by azakariy          #+#    #+#             */
/*   Updated: 2023/02/14 15:52:27 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_append(char **array, char *new_str)
{
	int		i;
	char	**new_array;

	i = 0;
	if (!new_str)
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
			new_array[i] = ft_strdup(array[i]);
			i++;
		}
		ft_free_double(array);
	}
	new_array[i] = new_str;
	return (new_array);
}

int	ft_key_chars(char *str)
{
	int	i;

	i = 0 ;
	if (str[i] == '>')
	{
		while (str[i] == '>')
			i++;
		return (i);
	}
	else
	{
		while (str[i] == '<')
			i++;
		return (i);
	}
}

char	**ft_filter(char *part, int i)
{
	char	**part_array;
	char	*holder;
	int		x;
	int		j;
	
	part_array = NULL;
	holder = NULL;
	while (part[i])
	{
		j = ft_skip_quotes(part, i);
		if (j > i)
			holder = ft_substr(part, i, j - i);
		else if (part[i] == '>' || part[i] == '<')
		{
			part_array = ft_append(part_array, holder);
			holder = NULL;
			x = ft_key_chars(part + i);
			if (x + i > i)
				part_array = ft_append(part_array, ft_substr(part, i, x));
			i += x;
		}
		else
			holder = ft_append_char(holder, part[i]);
		i = j;
		if (part[i])
			i++;
	}
	return (ft_append(part_array, holder));
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
		array = ft_destructor(array, ft_filter2(cmd[i], 0, 0), 0);
		i++;
	}
	ft_set_helpers(array, s_cmd);
	ft_fill_struct(array, s_cmd, 0, is_last);
	if (s_cmd->cmd)
		ft_find_env(s_cmd->cmd);
	i = 0;
	while (s_cmd->cmd && s_cmd->cmd[i])
	{
		s_cmd->cmd[i] = ft_remove_quotes(s_cmd->cmd[i]);
		i++;
	}
}
