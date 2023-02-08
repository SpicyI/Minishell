/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 17:04:28 by del-khay          #+#    #+#             */
/*   Updated: 2023/02/08 16:17:05 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fds(int *fds, int i, int opt)
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
	int	len;
	int	len2;

	len = ft_arrlen(cmd->input);
	len2 = ft_arrlen(cmd->output) + ft_arrlen(cmd->append);
	if (cmd->input)
		close_fds(input_fds, len, FREE_FD_ARR);
	if (cmd->output || cmd->append)
		close_fds(output_fds, len2, FREE_FD_ARR);
	return (0);
}
