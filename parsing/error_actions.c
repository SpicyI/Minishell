/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 18:11:30 by azakariy          #+#    #+#             */
/*   Updated: 2023/02/10 21:51:13 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_open_doc(t_cmd *line, int i)
{
	int		j;
	char	*line_read;
	char	**delimiters;

	j = 0;
	while (j < i)
	{
		delimiters = line[j].delimiter;
		if (delimiters)
		{
			while (*delimiters)
			{
				while (1)
				{
					line_read = readline("\033[0;35m> \033[0m");
					if (ft_strcmp(line_read, *delimiters))
						break ;
					free(line_read);
				}
				free(line_read);
				delimiters++;
			}
		}
		j++;
	}
}

void	ft_doc_doc(t_cmd *line, int i)
{
	if (g_gfl.p_error_index != -1 || g_gfl.syntax_error)
	{
		if (!g_gfl.syntax_error)
			ft_throw_error(g_gfl.pipeline_error, 0);
		ft_open_doc(line, i);
	}
}
