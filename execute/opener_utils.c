/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opener_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 18:39:33 by del-khay          #+#    #+#             */
/*   Updated: 2023/02/11 17:46:58 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	openoutputs_trunc(t_cmd *cmd)
{
	int	fd;
	int	i;

	i = 0;
	while (cmd->output && cmd->output[i])
	{
		fd = open(cmd->output[i], O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
		{
			ft_dprintf(PERMISSION_DENIED, cmd->output[i]);
			return (-1);
		}
		if (!cmd->output[i + 1] && cmd->last_out == TRUNC)
			return (fd);
		close(fd);
		i++;
	}
	return (-2);
}

int	openoutputs_append(t_cmd *cmd)
{
	int	fd;
	int	i;

	i = 0;
	while (cmd->append && cmd->append[i])
	{
		fd = open(cmd->append[i], O_RDWR | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
		{
			ft_dprintf(PERMISSION_DENIED, cmd->append[i]);
			return (-1);
		}
		if (!cmd->append[i + 1] && cmd->last_out == APPEND)
			return (fd);
		close(fd);
		i++;
	}
	return (-2);
}

void	cmd_error(char *cmd)
{
	if (ft_strchr(cmd, '/'))
		ft_dprintf(NO_SUCH_FILE, cmd);
	else
		ft_dprintf(COMMAND_NOT_FOUND, cmd);
	exit(127);
}
