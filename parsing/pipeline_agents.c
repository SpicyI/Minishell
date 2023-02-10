/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_agents.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 18:39:51 by azakariy          #+#    #+#             */
/*   Updated: 2023/02/10 21:51:13 by del-khay         ###   ########.fr       */
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
	cmds = ft_calloc(ft_pipe_counter(line) + 1, sizeof(char *));
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
	int	in_d;
	int	in_s;
	int	i;
	int	nbr;

	in_d = 0;
	in_s = 0;
	i = 0;
	nbr = 1;
	while (line[i])
	{
		if (line[i] == '"' && !in_s)
			in_d = !in_d;
		if (line[i] == '\'' && !in_d)
			in_s = !in_s;
		if (line[i] == '|' && !in_s && !in_d)
		{
			nbr++;
			while (line[i] == '|' || line[i] == ' ')
				i++;
		}
		else
			i++;
	}
	return (nbr);
}

void	ft_pipe_syntax(char *line, int i, int in_d, int in_s)
{
	int	nbr;

	nbr = 1;
	while (line[i])
	{
		if (line[i] == '"' && !in_s)
			in_d = !in_d;
		else if (line[i] == '\'' && !in_d)
			in_s = !in_s;
		if (line[i] == '|' && !in_s && !in_d)
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
