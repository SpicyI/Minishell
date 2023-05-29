/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 17:44:44 by del-khay          #+#    #+#             */
/*   Updated: 2023/02/19 00:30:12 by del-khay         ###   ########.fr       */
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
		if (!line)
			break ;
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

int	builtin_herdoc(t_cmd *cmd)
{
	int		id;
	t_built	utils;

	id = fork();
	if (!id)
	{
		ft_set_signals();
		signal(SIGQUIT, SIG_IGN);
		utils.herdoc_fd = open_herdoc(cmd);
		exit(0);
	}
	g_gfl.pid = &id;
	g_gfl.crp = 1;
	waitpid(id, &(utils.status), 0);
	g_gfl.crp = 0;
	g_gfl.pid = 0;
	return (ft_exitstatus(utils.status));
}

int	pipe_herdoc(char *delmiter, int *fds, int opt)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (!ft_strncmp(line, delmiter, 0))
		{
			free(line);
			break ;
		}
		line = ft_strjoin(line, "\n");
		if (opt == HERDOC_ON)
			write(fds[1], line, ft_strlen(line));
		free(line);
	}
	if (opt == HERDOC_OFF)
		close(fds[0]);
	return (0);
}
