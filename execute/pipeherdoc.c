/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeherdoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 22:31:36 by del-khay          #+#    #+#             */
/*   Updated: 2023/02/14 23:18:42 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*init_herdocs(t_cmd *cmds, int num_of_cmds)
{
	t_built	utils;
	pid_t	pid;
	int		*herdocs;
	int		i;

	i = -1;
	herdocs = (int *)ft_calloc(num_of_cmds, sizeof(int));
	while (++i < num_of_cmds)
	{
		pipe(utils.b_pipe);
		pid = fork();
		if (!pid)
		{
			open_pipe_docs(cmds + i, utils.b_pipe);
			exit(0);
		}
		if (!ft_herdoc_set2(&utils, herdocs, pid, i))
			return (0);
		herdocs[i] = dup(utils.b_pipe[0]);
		close(utils.b_pipe[0]);
	}
	return (herdocs);
}

int	ft_herdoc_set2(t_built *utils, int *herdocs, pid_t pid, int i)
{
	g_gfl.pid = &pid;
	g_gfl.crp = 1;
	waitpid(pid, &(utils->status), 0);
	close(utils->b_pipe[1]);
	g_gfl.crp = 0;
	g_gfl.pid = 0;
	if (ft_exitstatus(utils->status))
	{
		close(utils->b_pipe[0]);
		close_fds(herdocs, i - 1, FREE_FD_ARR);
		return (0);
	}
	return (1);
}

int	open_pipe_docs(t_cmd *cmd, int *fds)
{
	int	i;
	int	len;

	len = ft_arrlen(cmd->delimiter);
	if (!len)
		return (0);
	i = 0;
	while (cmd->delimiter[i] && i < len - 1)
	{
		pipe_herdoc(cmd->delimiter[i], fds, HERDOC_OFF);
		i++;
	}
	if (cmd->last_in == HERDOC_FD)
		pipe_herdoc(cmd->delimiter[i], fds, HERDOC_ON);
	else
		pipe_herdoc(cmd->delimiter[i], fds, HERDOC_OFF);
	return (1);
}

int	mark_start(pid_t *id, int num_of_cmds, int *herdocs)
{
	if (!herdocs)
	{
		free(id);
		return (1);
	}
	g_gfl.pid = id;
	g_gfl.crp = num_of_cmds;
	return (0);
}
