/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 21:47:13 by del-khay          #+#    #+#             */
/*   Updated: 2023/02/14 21:55:46 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_waitall(pid_t *id, int num_of_cmds)
{
	int	i;
	int	status;

	i = -1;
	while (++i < num_of_cmds)
		waitpid(id[i], &status, 0);
}

void	init_pipeline(t_built *utils, int num_of_cmds)
{
	utils->status = 0;
	utils->input_fd = 0;
	utils->cmd_num = num_of_cmds;
	utils->default_fd[0] = dup(0);
	utils->default_fd[1] = dup(1);
}

int	*init_herdocs(t_cmd *cmds, int num_of_cmds)
{
	int		fds[2];
	pid_t pid;
	int		*herdocs;
	int i = -1;
	int status;

	herdocs = (int *)ft_calloc(num_of_cmds, sizeof(int));
	while(++i < num_of_cmds)
	{
		pipe(fds);
		pid = fork();
		if (!pid)
		{
			open_pipe_docs(cmds + i, fds);
			exit(0);
		}
		g_gfl.pid = &pid;
		g_gfl.crp = 1;
		waitpid(pid, &status, 0);
		close(fds[1]);
		g_gfl.crp = 0;
		g_gfl.pid = 0;
		dprintf(2," pipe 1 = %d pipe 2 = %d\n", fds[0], fds[1]);
		if (ft_exitstatus(status))
		{
			close(fds[0]);
			close_fds(herdocs, i - 1 , FREE_FD_ARR);
			return (NULL);
		}
		herdocs[i] = dup(fds[0]);
		close(fds[0]);
	}
	return (herdocs);
}

int open_pipe_docs(t_cmd *cmd , int *fds)
{
	int	i;
	int	len;

	len = ft_arrlen(cmd->delimiter);
	if (!len)
		return (0);
	i = 0;
	while (cmd->delimiter[i] && i < len - 1)
	{
		pipe_herdoc(cmd->delimiter[i], fds,HERDOC_OFF);
		i++;
	}
	if (cmd->last_in == HERDOC_FD)
		pipe_herdoc(cmd->delimiter[i], fds,HERDOC_ON);
	else
		pipe_herdoc(cmd->delimiter[i], fds,HERDOC_OFF);
	return (1);
}


int	pipeline(t_cmd *cmds, int num_of_cmds)
{
	pid_t	*id;
	t_built	utils;
	int		*herdocs;
	int		i;

	i = -1;
	init_pipeline(&utils, num_of_cmds);
	herdocs = init_herdocs(cmds, num_of_cmds);
	if (!herdocs)
	{
		return (1);
	}
	id = (pid_t *)ft_calloc(num_of_cmds + 1, sizeof(pid_t));
	g_gfl.pid = id;
	g_gfl.crp = num_of_cmds;
	while (++i < num_of_cmds)
	{
		if (pipe(utils.b_pipe) == -1)
			return (ft_dprintf("pipe error\n", NULL));
		id[i] = fork();
		if (id[i] == -1)
			return (ft_dprintf("fork error\n", NULL));
		if (!id[i])
			child_process(cmds, &utils, herdocs, i);
		pipeline_regulator(&utils, i, herdocs);
	}
	return (close_pipeline(&utils, id, herdocs));
}

void	child_process(t_cmd *cmds, t_built *utils, int *herdocs, int i)
{
	if (i == 0)
		set_first(utils, cmds + i);
	else if (i == utils->cmd_num - 1)
		set_last(utils, cmds + i);
	else
		set_middle(utils, cmds + i);
	if ((cmds + i)->delimiter)
	{
		if ((cmds + i)->last_in == HERDOC_FD)
		{
			close(utils->b_pipe[0]);
			close(utils->input_fd);
			dup2(herdocs[i], 0);
		}
		else if ((cmds + i)->last_in == INPUT_FD)
		{
			close(utils->b_pipe[0]);
			close(utils->input_fd);
		}
		close(herdocs[i]);
	}
	if ((cmds + i)->is_built_in)
		exit(builtin(cmds + i, HERDOC_OFF));
	ft_execve(cmds + i, HERDOC_OFF);
}
