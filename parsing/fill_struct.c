/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 16:15:21 by azakariy          #+#    #+#             */
/*   Updated: 2023/02/14 15:52:27 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *str, char *str2)
{
	int	i;

	i = 0;
	if ((!str && str2) || (str && !str2))
		return (0);
	else if (!str && !str2)
		return (1);
	while (str && str2 && str[i] && str2[i])
	{
		if (str[i] != str2[i])
			return (0);
		i++;
	}
	return (str[i] == str2[i]);
}

void	ft_init_struct(t_cmd *cmd)
{
	cmd->is_built_in = 0;
	cmd->append = NULL;
	cmd->output = NULL;
	cmd->input = NULL;
	cmd->delimiter = NULL;
	cmd->cmd = NULL;
	cmd->last_in = 0;
	cmd->last_out = 0;
}

int	ft_is_built_in(char *str)
{
	if (ft_strcmp(str, "echo") || ft_strcmp(str, "cd"))
		return (1);
	if (ft_strcmp(str, "export") || ft_strcmp(str, "pwd"))
		return (1);
	if (ft_strcmp(str, "unset") || ft_strcmp(str, "env"))
		return (1);
	if (ft_strcmp(str, "exit"))
		return (1);
	return (0);
}

void	ft_fill_struct(char **array, t_cmd *cmd, int i, int is_last)
{
	while (array[i])
	{
		if (ft_valid_syntax(array, i, is_last))
			break ;
		if (ft_strcmp(array[i], ">>"))
			cmd->append = ft_append(cmd->append, ft_strdup(array[++i]));
		else if (ft_strcmp(array[i], "<<"))
			cmd->delimiter = ft_append(cmd->delimiter, ft_strdup(array[++i]));
		else if (ft_strcmp(array[i], ">"))
			cmd->output = ft_append(cmd->output, ft_strdup(array[++i]));
		else if (ft_strcmp(array[i], "<"))
			cmd->input = ft_append(cmd->input, ft_strdup(array[++i]));
		else
		{
			if (!cmd->is_built_in)
				cmd->is_built_in = ft_is_built_in(array[i]);
			cmd->cmd = ft_append(cmd->cmd, ft_strdup(array[i]));
		}
		if (array[i])
			i++;
	}
	ft_free_double(array);
}

void	ft_set_helpers(char **array, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (array[i])
	{
		if (ft_strcmp(array[i], ">>"))
			cmd->last_out = 1;
		else if (ft_strcmp(array[i], ">"))
			cmd->last_out = 2;
		else if (ft_strcmp(array[i], "<<"))
			cmd->last_in = 1;
		else if (ft_strcmp(array[i], "<"))
			cmd->last_in = 2;
		i++;
	}
}
