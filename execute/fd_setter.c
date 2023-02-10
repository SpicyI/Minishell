/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_setter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 23:23:12 by del-khay          #+#    #+#             */
/*   Updated: 2023/02/10 22:24:46 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setfds(t_built *utils, t_cmd *cmd, int opt)
{
	utils->default_fd[0] = dup(0);
	utils->default_fd[1] = dup(1);
	if (cmd->last_in == HERDOC_FD && opt)
	{
		dup2(utils->herdoc_fd, 0);
		close(utils->herdoc_fd);
		if (utils->input_fd)
			close(utils->input_fd);
	}
	else if (cmd->last_in == INPUT_FD)
	{
		dup2(utils->input_fd, STDIN_FILENO);
		close(utils->input_fd);
		if (utils->herdoc_fd)
			close(utils->herdoc_fd);
	}
	else if (cmd->last_in != HERDOC_FD && cmd->last_in != INPUT_FD)
	{
		if (utils->input_fd)
			close(utils->input_fd);
		if (utils->herdoc_fd)
			close(utils->herdoc_fd);
	}
	if (cmd->append || cmd->output)
		((dup2(utils->output_fd, 1) || 1) && close(utils->output_fd));
}

void	unsetfds(t_built *utils)
{
	dup2(utils->default_fd[0], 0);
	dup2(utils->default_fd[1], 1);
	close(utils->default_fd[0]);
	close(utils->default_fd[1]);
}
