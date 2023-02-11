/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 21:47:13 by del-khay          #+#    #+#             */
/*   Updated: 2023/02/11 17:48:18 by del-khay         ###   ########.fr       */
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
	int	*herdocs;
	int	i;

	i = -1;
	herdocs = (int *)ft_calloc(num_of_cmds, sizeof(int));
	while (++i < num_of_cmds)
		herdocs[i] = open_herdoc(cmds + i);
	return (herdocs);
}

int	pipeline(t_cmd *cmds, int num_of_cmds)
{
	pid_t	*id;
	t_built	utils;
	int		*herdocs;
	int		i;

	i = -1;
	init_pipeline(&utils, num_of_cmds);
	id = (pid_t *)ft_calloc(num_of_cmds + 1, sizeof(pid_t));
	herdocs = init_herdocs(cmds, num_of_cmds);
	while (++i < num_of_cmds)
	{
		if (pipe(utils.b_pipe) == -1)
			return (ft_dprintf("pipe error\n", NULL));
		id[i] = fork();
		if (id[i] == -1)
			return (ft_dprintf("fork error\n", NULL));
		if (!id[i])
			child_process(cmds, &utils, herdocs, i);
		close(utils.b_pipe[1]);
		close(utils.input_fd);
		utils.input_fd = utils.b_pipe[0];
		dup2(utils.default_fd[0], 0);
		dup2(utils.default_fd[1], 1);
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
			close(herdocs[i]);
		}
		else
		{
			close(herdocs[i]);
		}
	}
	if ((cmds + i)->is_built_in)
		exit(builtin(cmds + i, HERDOC_OFF));
	ft_execve(cmds + i, HERDOC_OFF);
}
