/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 16:02:06 by del-khay          #+#    #+#             */
/*   Updated: 2023/02/07 22:04:41 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exitstatus(int status)
{
	int	exitstatus;

    if (WIFEXITED(status))
		return(WEXITSTATUS(status));
    if (WIFSIGNALED(status))
    {
        exitstatus = WTERMSIG(status);
        // if (WCOREDUMP(status))
        //     exitstatus += 128;
        return(exitstatus);
    }
    return (0);
}

int ft_envlen(t_env *env)
{
    int i;
    
    i = 0;
    while(env)
    {
        i++;
        env = env->next;
    }
    return (i);
}

int single_cmd(t_cmd *cmd)
{   
    int status;
    pid_t id;

    id = fork();
    if (id == -1)
        return(printf("fork error\n"));
    if (!id)
        ft_execve(cmd);
    waitpid(id, &status, 0);
    return (ft_exitstatus(status));
}

char *ft_getenv(char *name)
{
    t_env *ref;

    ref = g_gfl.env;
    while(ref)
    {
        if(!ft_strncmp(ref->name, name, 0))
            return (ft_strdup(ref->value));
        ref = ref->next;
    }
    return (NULL);
}

char *getpath(char *cmd, char **path)
{
    char *check;
    if (!access(cmd, F_OK))
    {
		if (!access(cmd, X_OK))
            return (cmd);
        printf("%s : Permission denied\n",cmd);
        exit(126);
    }
    while(path && *path && *cmd)
    {
        check = ft_strjoin(ft_strjoin(ft_strdup(*path), "/"), cmd);
        if (!access(check, F_OK))
        {
            if (!access(check, X_OK))
                return (check);
            printf("%s : Permission denied\n",cmd);
            free(check);
            exit(126);
        }
        free(check);
        path++;
    }
    printf("%s : command not found\n", cmd);
    exit(127);
    return (NULL);
}

char **env_to_arr(void)
{
    char **env;
    t_env *ref;
    int i;

    ref = g_gfl.env;
    i = 0;
    if (ft_envlen(g_gfl.env) == 0)
        return (NULL);
    env = ft_calloc(ft_envlen(g_gfl.env) + 1, sizeof(char *));
    while(ref)
    {
        env [i] = ft_strjoin(ft_strjoin(ft_strdup(ref->name), "="), ref->value);
        ref = ref->next;
        i++;
    }
    return(env);
} 

void ft_isdir(char *cmd , int opt)
{
    DIR *dir;
    if (!cmd  || ft_strlen(cmd) == 0)
        return;
    dir = opendir(cmd);
    if (dir)
    {
        if (ft_strchr(cmd, '/') && opt == 0)
        {
            printf("%s : is a directory\n", cmd);
            exit(126);
        }
        else if (opt)
        {
            printf("%s : command not found\n", cmd);
            exit(127);
        }
        closedir(dir);
    }
}

void ft_execve(t_cmd *cmd)
{
    t_built utils;
    char *cmd_path;

    utils.input_fd = 0;
    utils.output_fd = 0;
    if (cmd->delimiter)
			utils.herdoc_fd = open_herdoc(cmd);
    if (!opener(cmd, &utils))
        exit(1);
    if(!cmd->cmd)
        exit(0);
    ft_isdir(cmd->cmd[0], 0);
    cmd_path = getpath(cmd->cmd[0] , ft_split(getenv("PATH"), ':'));
    ft_isdir(cmd_path, 1);
    setfds(&utils , cmd);
    execve(cmd_path, cmd->cmd, env_to_arr());
    unsetfds(&utils);    
}
