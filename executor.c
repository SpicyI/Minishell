/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 19:57:54 by del-khay          #+#    #+#             */
/*   Updated: 2023/01/29 19:58:30 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    executor()
{
    if (!cmd)
        return ;
    if (!ft_strcmp(cmd->cmd, "cd"))
        cd(cmd->args[1]);
    else if (!ft_strcmp(cmd->cmd, "echo"))
        echo(cmd->args);
    else if (!ft_strcmp(cmd->cmd, "env"))
        env();
    else if (!ft_strcmp(cmd->cmd, "setenv"))
        setenv(cmd->args[1], cmd->args[2]);
    else if (!ft_strcmp(cmd->cmd, "unsetenv"))
        unsetenv(cmd->args[1]);
    else if (!ft_strcmp(cmd->args[0], "exit"))
        exit(0);
    else
        execve(cmd->cmd, cmd->args, NULL);
}