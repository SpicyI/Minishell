/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opener.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 16:12:37 by del-khay          #+#    #+#             */
/*   Updated: 2023/02/07 00:16:08 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	openinputs(char **in_files)
{
	int fd;
	int	i;

	i = 0;
	while (in_files[i])
	{
		fd = open(in_files[i], O_RDONLY);
		if (fd < 0)
		{
			printf("%s: No such file or directory", in_files[i]);
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
	int fd;
	int	i;

	i = 0;
	while (cmd->output && cmd->output[i])
	{
		fd = open(cmd->output[i], O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
		{
			printf("%s: Permission denied", cmd->output[i]);
			return (-1);
		}
		if (!cmd->output[i + 1] && cmd->last_out == TRUNC)
			return (fd);
		close(fd);
		i++;
	}
	i = 0;
	while (cmd->append && cmd->append[i])
	{
		fd = open(cmd->append[i], O_RDWR | O_CREAT | O_APPEND,
				0644);
		if (fd < 0)
		{
			printf("%s: Permission denied", cmd->append[i]);
			return (-1);
		}
		if (!cmd->append[i + 1] && cmd->last_out == APPEND)
			return (fd);
		close(fd);
		i++;
	}
	return (0);
}

int	open_herdoc(t_cmd *cmd)
{
	int fd;
	int i;
	int len;
	
	len = ft_arrlen(cmd->delimiter);
	i = 0;
	while(cmd->delimiter[i] && i < len - 1)
	{
		herdoc(cmd->delimiter[i], HERDOC_OFF);
		i++;
	}
	if (cmd->last_in == HERDOC_FD)
		fd = herdoc(cmd->delimiter[i], HERDOC_ON);
	else
		fd = herdoc(cmd->delimiter[i], HERDOC_OFF);
	return(fd);
}


int	opener(t_cmd *cmd, t_built *utils)
{
	if (cmd->input)
		utils->input_fd = openinputs(cmd->input);
	if (cmd->output || cmd->append)
		utils->output_fd = openoutputs(cmd);
	if (utils->input_fd < 0 && utils->output_fd < 0)
		return (0);
	return (1);
}
