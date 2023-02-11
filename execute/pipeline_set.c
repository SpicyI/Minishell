/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_set.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 00:49:54 by del-khay          #+#    #+#             */
/*   Updated: 2023/02/11 00:50:17 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_first(t_built *utils, t_cmd *cmd)
{
	dup2(utils->b_pipe[1], 1);
	close(utils->b_pipe[1]);
	close(utils->b_pipe[0]);
	close(utils->default_fd[0]);
	if (cmd->append || cmd->output)
		close(utils->default_fd[1]);
}

void	set_last(t_built *utils, t_cmd *cmd)
{
	dup2(utils->input_fd, 0);
	close(utils->input_fd);
	close(utils->b_pipe[0]);
	close(utils->b_pipe[1]);
	if (cmd->input || cmd->delimiter)
	{
		close(utils->default_fd[0]);
		close(utils->input_fd);
	}
	if (cmd->append || cmd->output)
		close(utils->default_fd[1]);
}

void	set_middle(t_built *utils, t_cmd *cmd)
{
	if (!cmd->input)
	{
		dup2(utils->input_fd, 0);
		close(utils->input_fd);
		close(utils->b_pipe[0]);
	}
	else
	{
		close(utils->default_fd[0]);
		close(utils->input_fd);
		close(utils->b_pipe[0]);
	}
	if (!cmd->output && !cmd->append)
	{
		dup2(utils->b_pipe[1], 1);
		close(utils->b_pipe[1]);
	}
	else
	{
		close(utils->default_fd[1]);
		close(utils->b_pipe[1]);
	}
}
