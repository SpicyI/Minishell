/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 17:04:28 by del-khay          #+#    #+#             */
/*   Updated: 2023/02/07 23:15:59 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_Fds(int *fds, int i, int opt)
{
	while (i >= 0)
	{
		close(fds[i]);
		i--;
	}
	if (opt)
		free(fds);
}

int	closer(t_cmd *cmd, int *input_fds, int *output_fds)
{
	if (cmd->input)
		close_Fds(input_fds, ft_arrlen(cmd->input), FREE_FD_ARR);
	if (cmd->output || cmd->append)
		close_Fds(output_fds, (ft_arrlen(cmd->append) + ft_arrlen(cmd->output)),
				FREE_FD_ARR);
	return (0);
}
