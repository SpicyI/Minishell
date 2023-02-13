/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   universal_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 16:28:32 by azakariy          #+#    #+#             */
/*   Updated: 2023/02/13 13:13:28 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_destructor(char **array, char **array2, int j)
{
	int		i;
	char	**new_array;

	i = 0;
	while (array && array[i])
		i++;
	while (array2 && array2[j])
		j++;
	new_array = ft_calloc(i + j + 1, sizeof(char *));
	i = 0;
	while (array && array[i])
	{
		new_array[i] = ft_strdup(array[i]);
		i++;
	}
	j = 0;
	while (array2 && array2[j])
	{
		new_array[i + j] = ft_strdup(array2[j]);
		j++;
	}
	ft_free_double(array);
	ft_free_double(array2);
	return (new_array);
}

char	*ft_append_char(char *str, char c)
{
	int		i;
	char	*new_str;
	int		j;

	i = 0;
	if (str)
		j = ft_strlen(str);
	else
		j = 0;
	new_str = ft_calloc(j + 2, sizeof(char));
	while (str && str[i])
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = c;
	if (str)
		free(str);
	return (new_str);
}

char	*ft_remove_quotes(char *str)
{
	int		i;
	int		in_d;
	int		in_s;
	char	*new_str;

	i = 0;
	in_d = 0;
	in_s = 0;
	new_str = ft_calloc(1, 1);
	while (str[i])
	{
		if (str[i] == '"' && !in_s)
			in_d = !in_d;
		else if (str[i] == '\'' && !in_d)
			in_s = !in_s;
		else if ((!in_d && in_s) || (in_d && !in_s))
			new_str = ft_append_char(new_str, str[i]);
		else if (!in_d && !in_s)
			new_str = ft_append_char(new_str, str[i]);
		i++;
	}
	free(str);
	return (new_str);
}

int	ft_skip(char *line, int i, char c)
{
	int	in_d;
	int	in_s;

	in_d = 0;
	in_s = 0;
	while (line[i])
	{
		if (line[i] == c && !in_d && !in_s)
			break ;
		if (line[i] == '\'' && !in_d)
			in_s = !in_s;
		else if (line[i] == '"' && !in_s)
			in_d = !in_d;
		i++;
	}
	return (i);
}

void	ft_free_struct(t_cmds *cmds)
{
	int	i;

	i = 0;
	if (!cmds)
		return ;
	while (i < cmds->size)
	{
		if ((cmds->line + i)->append)
			ft_free_double((cmds->line + i)->append);
		if ((cmds->line + i)->cmd)
			ft_free_double((cmds->line + i)->cmd);
		if ((cmds->line + i)->output)
			ft_free_double((cmds->line + i)->output);
		if ((cmds->line + i)->input)
			ft_free_double((cmds->line + i)->input);
		if ((cmds->line + i)->delimiter)
			ft_free_double((cmds->line + i)->delimiter);
		i++;
	}
}
