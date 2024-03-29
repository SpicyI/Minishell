/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 19:57:54 by del-khay          #+#    #+#             */
/*   Updated: 2023/02/18 19:29:47 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_match	*init(void)
{
	t_match	*ref;

	ref = (t_match *)ft_calloc(N_BUILTIN + 1, sizeof(t_match));
	ref[0].sh_built = &echo;
	ref[0].name = "echo";
	ref[1].sh_built = &cd;
	ref[1].name = "cd";
	ref[2].sh_built = (int (*)(char **)) & pwd;
	ref[2].name = "pwd";
	ref[3].sh_built = &export;
	ref[3].name = "export";
	ref[4].sh_built = &unset;
	ref[4].name = "unset";
	ref[5].sh_built = (int (*)(char **)) & env;
	ref[5].name = "env";
	ref[6].sh_built = &shell_exit;
	ref[6].name = "exit";
	return (ref);
}

int	builtin(t_cmd *cmd, int opt)
{
	t_built	utils;
	int		i;

	i = -1;
	utils.status = 0;
	utils.input_fd = 0;
	utils.output_fd = 0;
	if (cmd->delimiter && opt)
		if (builtin_herdoc(cmd))
			return (1);
	if (!opener(cmd, &utils))
		return (1);
	utils.ref = init();
	setfds(&utils, cmd, opt);
	while (utils.ref[++i].name)
	{
		if (!ft_strncmp(cmd->cmd[0], utils.ref[i].name, 0))
		{
			utils.status = utils.ref[i].sh_built(cmd->cmd + 1);
			break ;
		}
	}
	unsetfds(&utils);
	free(utils.ref);
	return (utils.status);
}

void	executor(t_cmds *cmds)
{
	if (!cmds || !cmds->line || cmds->size <= 0)
		return ;
	ft_replace(cmds->line, cmds->size);
	shell_env_set(cmds->line, cmds->size);
	if (cmds->size == 1 && cmds->line->is_built_in)
		g_gfl.exit = builtin(cmds->line, HERDOC_ON);
	else if (cmds->size == 1 && !cmds->line->is_built_in)
		g_gfl.exit = single_cmd(cmds->line);
	else if (cmds->size > 1)
		g_gfl.exit = pipeline(cmds->line, cmds->size);
}
