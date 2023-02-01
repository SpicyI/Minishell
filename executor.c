/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 19:57:54 by del-khay          #+#    #+#             */
/*   Updated: 2023/01/31 21:30:55 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    executor()
{
    if (!cmd)
        return ;
    if (cmd->type == BUILTIN)
    {
        builtin(cmd);
        return ;
    }
    pipeline(cmds);
}