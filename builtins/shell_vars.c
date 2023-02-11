/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_vars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 18:01:10 by del-khay          #+#    #+#             */
/*   Updated: 2023/02/11 22:03:30 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void shell_env_set(t_cmd *cmd, int cmd_n)
{
    int i;

    i = 0;
    if (cmd_n > 1)
    {
        while(i < cmd_n)
        {
            if (has_shell_var(cmd[i].cmd))
                ft_clean_cmd(&cmd[i]);
            i++;
        }
        return ;
    }
    if (!has_shell_var(cmd->cmd) && cmd_n == 1)
        ft_clean_cmd(cmd);
    else
        sender();
}

int has_shell_var(char **str)
{
    int i;

    i = 0;
    while (str && str[i] && str)
    {
        if (!ft_strchr(str[i], '='))
            return (0);
        i++;
    }
    return (1);
}

void ft_clean_cmd(t_cmd *cmd)
{
    int i;
    int j;
    char **tmp;

    i = 0;
    j = 0;
    while (ft_strchr(cmd->cmd[i], '='))
        i++;
    tmp = (char **)ft_calloc(ft_arrlen(cmd->cmd) - i + 1, sizeof(char *));
    while(cmd->cmd[i])
    {
        tmp[j] = ft_strdup(cmd->cmd[i]);
        j++;
        i++;
    }
    i = 0;
    while(cmd->cmd[i])
    {
        free(cmd->cmd[i]);
        cmd->cmd[i] = NULL;
        i++;
    }
    free(cmd->cmd);
    cmd->cmd = tmp;
}