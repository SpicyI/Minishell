/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 19:57:54 by del-khay          #+#    #+#             */
/*   Updated: 2023/02/06 00:33:48 by del-khay         ###   ########.fr       */
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
    ref[2].sh_built = &pwd;
    ref[2].name = "pwd";
    ref[3].sh_built = &export;
    ref[3].name = "export";
    ref[4].sh_built = &unset;
    ref[4].name = "unset";
    ref[5].sh_built = &env;
    ref[5].name = "env";
    ref[6].sh_built = &exit;
    ref[6].name = "exit";
    return (ref);
}

close_Fds(int *input_fds, int i, int opt)
{
    while (i >= 0)
    {
        close(input_fds[i]);
        i--;
    }
    if (opt)
        free(input_fds);
}

int *openinputs(char **in_files)
{
    int *input_fds;
    int i;

    i = 0;
    input_fds = (int *) ft_calloc(ft_arrlen(in_files), sizeof(int)); 
    while(in_files[i] && input_fds)
    {
        input_fds[i] = open(in_files[i], O_RDONLY);
        if (input_fds[i] < 0)
        {
            printf("%s: No such file or directory", in_files[i]);
            colse_Fds(input_fds, i , 1);
            return (NULL);
        }
        i++;
    }
    return (input_fds);
}

int *openoutputs(char **out_files)
{
    int *output_fds;
    int i;

    i = 0;
    output_fds = (int *) ft_calloc(ft_arrlen(out_files), sizeof(int)); 
    while(out_files[i] && output_fds)
    {
        output_fds[i] = open(out_files[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        // if (output_fds[i] < 0)
        // {
        //     printf("%s: No such file or directory", out_files[i]);
        //     colse_inputFds(output_fds, i);
        //     return (NULL);
        // }
        i++;
    }
    return (output_fds);
}
int builtin(t_cmd *cmd)
{   
    t_match *ref;
    int *input_fd;
    int *output_fd;
    int i;

    i = 0;
    ref = init();
    // if (cmd->delimiter)
    // {
    //     //open herdoc here    
    // }
    if (cmd->input)
    {
        input_fd = openinputs(cmd->input);
        if (!input_fd)
            return (1);
    }
    if (cmd->append)
    {
        output_fd = openoutputs_appeded(cmd->append);
    }
    if (cmd->output)
    {
        output_fd = openoutputs(cmd->output);
    }
    while(ref[i].name)
    {
        if(!ft_strncmp(cmd->cmd[0], ref[i].name, 0))
        {
            return (ref[i].sh_built(cmd->cmd));
        }
        i++;
    }
    if (cmd->input)
    {
        close_Fds(input_fd, ft_arrlen(cmd->input), FREE_FD_ARR);
    }
    if (cmd->append)
    {
        close_Fds(output_fd, ft_arrlen(cmd->append), FREE_FD_ARR);
    }
    if (cmd->output)
    {
        close_Fds(output_fd, ft_arrlen(cmd->output), FREE_FD_ARR);
    }
    
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
    pipeline(cmds);
}