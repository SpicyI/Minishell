/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opener.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 16:12:37 by del-khay          #+#    #+#             */
/*   Updated: 2023/02/16 00:35:13 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	openinputs(char **in_files)
{
	int	fd;
	int	i;

	i = 0;
	while (in_files[i])
	{
		fd = open(in_files[i], O_RDONLY);
		if (fd < 0)
		{
			ft_dprintf(NO_SUCH_FILE, in_files[i]);
			return (-1);
		}
		if (!in_files[i + 1])
			return (fd);
		close(fd);
		i++;
	}
	return (0);
}

int	openoutputs(t_cmd *cmd)
{
	if (openoutputs_trunc(cmd) != -2)
		return (openoutputs_trunc(cmd));
	if (openoutputs_append(cmd) != -2)
		return (openoutputs_append(cmd));
	return (0);
}

int	open_herdoc(t_cmd *cmd)
{
	int	fd;
	int	i;
	int	len;

	fd = 0;
	len = ft_arrlen(cmd->delimiter);
	if (!len)
		return (0);
	i = 0;
	while (cmd->delimiter[i] && i < len - 1)
	{
		herdoc(cmd->delimiter[i], HERDOC_OFF);
		i++;
	}
	if (cmd->last_in == HERDOC_FD)
		fd = herdoc(cmd->delimiter[i], HERDOC_ON);
	else
		fd = herdoc(cmd->delimiter[i], HERDOC_OFF);
	return (fd);
}

int	opener(t_cmd *cmd, t_built *utils)
{
	if (cmd->input)
		utils->input_fd = openinputs(cmd->input);
	if (utils->input_fd < 0)
		return (0);
	if (cmd->output || cmd->append)
		utils->output_fd = openoutputs(cmd);
	if (utils->output_fd < 0)
		return (0);
	return (1);
}
