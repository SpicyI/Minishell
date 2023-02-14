/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 18:36:02 by del-khay          #+#    #+#             */
/*   Updated: 2023/02/14 22:27:08 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	ft_putendl_fd(cwd, 1);
	free(cwd);
	return (0);
}

void	reseter(t_cmd *cmd)
{
	if (cmd->cmd && !ft_arrlen(cmd->cmd))
	{
		ft_free2(cmd->cmd);
		cmd->cmd = NULL;
	}
}
