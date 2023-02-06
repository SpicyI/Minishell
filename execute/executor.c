/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 19:57:54 by del-khay          #+#    #+#             */
/*   Updated: 2023/02/07 00:17:24 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_match *init(void)
{
    t_match *ref;

    ref = (t_match *) ft_calloc(N_BUILTIN + 1, sizeof(t_match));
    ref[0].sh_built = &echo;
    ref[0].name = "echo";
    ref[1].sh_built = &cd;
    ref[1].name = "cd";
    ref[2].sh_built = (int (*)(char **)) &pwd;
    ref[2].name = "pwd";
    ref[3].sh_built = &export;
    ref[3].name = "export";
    ref[4].sh_built = &unset;
    ref[4].name = "unset";
    ref[5].sh_built = &env;
    ref[5].name = "env";
    ref[6].sh_built = &shell_exit;
    ref[6].name = "exit";
    return (ref);
}


int builtin(t_cmd *cmd)
{   
    t_match *ref;
    t_built utils;
    int i;

    i = 0;
    utils.status = 0;
    utils.input_fd = 0;
    utils.output_fd = 0;
    ref = init();
    if (cmd->delimiter)
			utils.herdoc_fd = open_herdoc(cmd);
    if (!opener(cmd, &utils))
        return (1);
    setfds(&utils , cmd);
    while(ref[i].name)
    {
        if(!ft_strncmp(cmd->cmd[0], ref[i].name, 0))
        {
            utils.status = ref[i].sh_built(cmd->cmd + 1);
            break ;
        }
        i++;
    }
    printf("done \n");
    unsetfds(&utils);
    //closer(cmd ,utils.input_fd, utils.output_fd);
    return(utils.status);
}


void    executor(t_cmds *cmds)
{
    if (!cmds || !cmds->line || cmds->size <= 0)
        return ;
    if (cmds->size == 1 && cmds->line->is_built_in)
    {
        g_gfl.exit = builtin(cmds->line);
        return ;
    }
    //pipeline(cmds);
}

int main(int argc, char **av, char **envp)
{
    t_cmds *cmds;
    
    cmds = (t_cmds *)ft_calloc(1, sizeof(t_cmds));
    cmds->size = 1;
    cmds->line = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
    cmds->line->append = 0;
    cmds->line->last_in = HERDOC_FD;
    cmds->line->last_out = TRUNC;
    cmds->line->output = ft_calloc(2, sizeof(char *));
    cmds->line->output[0] = ft_strdup("out1");
    cmds->line->output[1] = NULL;
    //+++++++
    cmds->line->delimiter = ft_calloc(2, sizeof(char *));
    cmds->line->delimiter[0] = ft_strdup("EOF");
    cmds->line->delimiter[1] = NULL;
    //+++++++
    cmds->line->input = 0;
    cmds->line->is_built_in = 1;
    cmds->line->cmd = (char **)ft_calloc(3, sizeof(char *));
    cmds->line->cmd[0] = ft_strdup(av[1]);
    cmds->line->cmd[1] = ft_strdup(av[2]);
    cmds->line->cmd[2] = NULL;
    executor(cmds);
}