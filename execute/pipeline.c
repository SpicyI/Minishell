/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 21:47:13 by del-khay          #+#    #+#             */
/*   Updated: 2023/02/08 16:45:23 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_waitall(pid_t *id, int num_of_cmds)
{
    int i;
    int status;
    
    i = -1;
    while (++i < num_of_cmds)
        waitpid(id[i], &status, 0);
}
 
int pipeline(t_cmd *cmds, int num_of_cmds)
{
    pid_t *id;
    t_built utils;
    int *herdocs;
    int i;
    
    utils.status = 0;
    i = -1;
    utils.default_fd[0] = dup(0);
    utils.default_fd[1] = dup(1);
    id = (pid_t *) ft_calloc(num_of_cmds + 1, sizeof(pid_t));
    herdocs = (int *) ft_calloc(num_of_cmds, sizeof(int));
    //openeing all herdoc files
    
    while (++i < num_of_cmds)
            herdocs[i] = open_herdoc(cmds + i);
    
    while (++i < num_of_cmds)
    {
        pipe(utils.b_pipe);
        //first cmd
        if (!i)
        {
            dup2(utils.b_pipe[1], 1);
            close(utils.b_pipe[1]);
            close(utils.b_pipe[0]);
        }
        //last cmd
        else if (i == num_of_cmds - 1)
        {
            dup2(utils.b_pipe[0], 0);
            close(utils.b_pipe[0]);
            close(utils.b_pipe[1]);
        }
        //middle cmds
        else
        {
            dup2(utils.b_pipe[0], 0);
            dup2(utils.b_pipe[1], 1);
            close(utils.b_pipe[0]);
            close(utils.b_pipe[1]);
        }
        // set herdoc input
        if ((cmds + i)->delimiter)
        {
            dup2(herdocs[i], 0);
            close(herdocs[i]);
        }
        //executing cmd
        id[i] = fork();
        if (id[i] == -1)
            return(printf("fork error\n"));
        if (!id[i])
            ft_execve(cmds + i , HERDOC_OFF);
        //reset stdin and stdout
        dup2(utils.default_fd[0], 0);
        dup2(utils.default_fd[1], 1);
        i++;
    }
    waitpid(id[num_of_cmds - 1], &utils.status, 0);
    ft_waitall(id , num_of_cmds - 1);
    free(id);
    free(herdocs);
    unsetfds(&utils);
    close(utils.b_pipe[1]);
    close(utils.b_pipe[0]);
    return (ft_exitstatus(utils.status));
}