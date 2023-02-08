/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 14:49:57 by azakariy          #+#    #+#             */
/*   Updated: 2023/02/08 17:07:54 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_butcher(char *line, char **cmds, char c)
{
	int	i;
	int	x;
	int	j;

	i = 0;
	j = 0;
	while (line[i])
	{
		x = i;
		i = ft_skip(line, i, c);
		cmds[j] = ft_strtrim(ft_substr(line, x, i - x), " ");
		j++;
		while (line[i] == c)
			i++;
	}
}

int	ft_count_cmds(char *line, char c, int i)
{
	int	in_d;
	int	in_s;
	int	cmds;

	cmds = 1;
	in_d = 0;
	in_s = 0;
	while (line[i])
	{
		if (line[i] == '"' && !in_s)
			in_d = !in_d;
		if (line[i] == '\'' && !in_d)
			in_s = !in_s;
		if (line[i] == c && !in_d && !in_s)
		{
			while (line[i] == c && !in_d && !in_s)
				i++;
			cmds++;
		}
		if (line[i])
			i++;
	}
	return (cmds);
}

char	**ft_super_split(char *line, char c)
{
	int		nbr_of_cmds;
	char	**cmds;
	int		i;

	i = 0;
	nbr_of_cmds = ft_count_cmds(line, c, 0);
	cmds = malloc(sizeof(char *) * (nbr_of_cmds + 1));
	cmds[nbr_of_cmds] = NULL;
	ft_butcher(line, cmds, c);
	return (cmds);
}

void	ft_free_double(char **array)
{
	int	i;

	i = 0;
	while (array && array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	array = NULL;
}

char	***ft_double_spit(char *line, t_cmds *cmds_list)
{
	char	**cmds;
	char	***parts;
	int		i;
	char	*buffer;

	cmds = ft_split_by_pipeline(line);
	i = 0;
	while (cmds[i])
		i++;
	cmds_list->size = i;
	cmds_list->line = malloc(sizeof(t_cmd *) * (i + 1));
	cmds_list->line[i] = NULL;
	parts = malloc(sizeof(char **) * (i + 1));
	parts[i] = NULL;
	i = 0;
	while (cmds[i])
	{
		buffer = ft_strtrim(cmds[i], " ");
		parts[i] = ft_super_split(buffer, ' ');
		free(buffer);
		i++;
	}
	return (parts);
}
