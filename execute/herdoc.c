/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 17:44:44 by del-khay          #+#    #+#             */
/*   Updated: 2023/02/09 18:36:31 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	herdoc(char *delmiter, int opt)
{
	int		fds[2];
	char	*line;

	pipe(fds);
	while (1)
	{
		line = readline("> ");
		if (!ft_strncmp(line, delmiter, 0))
		{
			free(line);
			break ;
		}
		line = ft_strjoin(line, "\n");
		write(fds[1], line, ft_strlen(line));
		free(line);
	}
	close(fds[1]);
	if (opt == HERDOC_OFF)
		return (close(fds[0]));
	return (fds[0]);
}
