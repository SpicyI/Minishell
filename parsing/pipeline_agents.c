/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_agents.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 18:39:51 by azakariy          #+#    #+#             */
/*   Updated: 2023/02/16 18:07:20 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_split_by_pipeline(char *line)
{
	int		j;
	char	**cmds;
	int		i;
	int		x;

	i = 0;
	j = 0;
	cmds = ft_calloc(ft_pipe_counter(line), sizeof(char *));
	while (line[i])
	{
		x = i;
		i = ft_skip(line, i, '|');
		cmds[j] = ft_trim(ft_substr(line, x, i - x), " ");
		while (line[i] && (line[i] == '|' || line[i] == ' '))
			i++;
		j++;
	}
	return (cmds);
}

int	ft_pipe_counter(char *line)
{
	int	i;
	int	nbr;

	i = 0;
	nbr = 1;
	while (line[i])
	{
		i = ft_skip_quotes(line, i);
		if (line[i] == '|')
		{
			nbr++;
			while (line[i] == '|' || line[i] == ' ')
				i++;
		}
		else if (line[i])
			i++;
	}
	return (nbr + 1);
}

void	ft_pipe_syntax(char *line, int i)
{
	int	nbr;

	nbr = 1;
	if (line[0] == '|')
	{
		ft_pipeline_error(line, i, nbr);
		return ;
	}
	while (line[i])
	{
		i = ft_skip_quotes(line, i);
		if (line[i] == '|')
		{
			nbr++;
			i++;
			while (line[i] == ' ')
				i++;
			if (line[i] == '|')
				ft_pipeline_error(line, i, nbr);
		}
		if (line[i])
			i++;
	}
}

void	ft_pipeline_error(char *line, int i, int nbr)
{
	if (!g_gfl.pipeline_error)
	{
		g_gfl.p_error_index = nbr - 1;
		if (line[i + 1] == '|')
			g_gfl.pipeline_error = "||";
		else
			g_gfl.pipeline_error = "|";
	}
}
