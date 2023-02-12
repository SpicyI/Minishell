/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 16:02:06 by del-khay          #+#    #+#             */
/*   Updated: 2023/02/12 17:53:19 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exitstatus(int status)
{
	int	exitstatus;

	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		exitstatus = WTERMSIG(status);
		return (exitstatus + 128);
	}
	return (0);
}

int	single_cmd(t_cmd *cmd)
{
	int		status;
	pid_t	*id;

	id = malloc(sizeof(pid_t) * 1);
	g_gfl.pid = id;
	g_gfl.crp = 1;
	id[0] = fork();
	if (id[0] == -1)
		return (ft_dprintf("fork error\n", NULL));
	if (!id[0])
		ft_execve(cmd, HERDOC_ON);
	waitpid(id[0], &status, 0);
	free(id);
	g_gfl.pid = NULL;
	return (ft_exitstatus(status));
}

char	*ft_getenv(char *name)
{
	t_env	*ref;

	ref = g_gfl.env;
	if (!name || !*name )
		return (NULL);
	while (ref)
	{
		if (!ft_strncmp(ref->name, name, 0))
			return (ft_strdup(ref->value));
		ref = ref->next;
	}
	return (NULL);
}

char	*getpath(char *cmd, char **path)
{
	char	*check;

	check = NULL;
	if (path && ft_strchr(cmd, '/'))
		check = check_abs_path(cmd);
	if (check)
		return (check);
	while (path && *path && *cmd)
	{
		check = ft_strjoin(ft_strjoin(ft_strdup(*path), "/"), cmd);
		if (!access(check, F_OK))
		{
			if (!access(check, X_OK))
				return (check);
			ft_dprintf(PERMISSION_DENIED, cmd);
			free(check);
			exit(126);
		}
		free(check);
		path++;
	}
	cmd_error(cmd);
	return (NULL);
}

void	ft_execve(t_cmd *cmd, int opt)
{
	t_built	utils;
	char	*cmd_path;

	utils.input_fd = 0;
	utils.output_fd = 1;
	if (cmd->delimiter && opt)
		utils.herdoc_fd = open_herdoc(cmd);
	if (!opener(cmd, &utils))
		exit(1);
	if (!cmd->cmd)
		exit(0);
	ft_isdir(cmd->cmd[0], 0);
	cmd_path = getpath(cmd->cmd[0], ft_split(ft_getenv("PATH"), ':'));
	ft_isdir(cmd_path, 1);
	setfds(&utils, cmd, opt);
	execve(cmd_path, cmd->cmd, env_to_arr());
	exit(0);
	unsetfds(&utils);
}
