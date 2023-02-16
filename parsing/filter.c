/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 18:02:59 by azakariy          #+#    #+#             */
/*   Updated: 2023/02/16 18:07:42 by del-khay         ###   ########.fr       */
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

int	ft_skip_alnum(char *str, int i)
{
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	return (i);
}

void	ft_prod_line(char **cmd, t_cmd *s_cmd, int is_last)
{
	int		i;
	char	**array;
	int		j;

	array = NULL;
	i = 0;
	while (cmd[i])
	{
		j = ft_strlen(cmd[i]);
		array = ft_destructor(array, ft_filter2(cmd[i], 0, 0, j), 0);
		i++;
	}
	ft_set_helpers(array, s_cmd);
	ft_fill_struct(array, s_cmd, 0, is_last);
	if (s_cmd->cmd)
		ft_find_env(s_cmd->cmd);
	if (s_cmd->append)
		ft_find_env(s_cmd->append);
	if (s_cmd->input)
		ft_find_env(s_cmd->input);
	if (s_cmd->output)
		ft_find_env(s_cmd->output);
	sanitize_quotes(s_cmd);
}

void	sanitize_quotes(t_cmd *s_cmd)
{
	ft_fill_double(s_cmd->cmd);
	ft_fill_double(s_cmd->output);
	ft_fill_double(s_cmd->append);
	ft_fill_double(s_cmd->input);
	ft_fill_double(s_cmd->delimiter);
}
