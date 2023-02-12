/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_vars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 18:01:10 by del-khay          #+#    #+#             */
/*   Updated: 2023/02/12 17:13:12 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shell_env_set(t_cmd *cmd, int cmd_n)
{
	int	i;
	int	j;

	i = 0;
	if (!cmd->cmd)
		return ;
	if (cmd_n > 1)
	{
		while (i < cmd_n)
		{
			j = 0;
			j = has_shell_var(cmd[i].cmd);
			if (j)
				ft_clean_cmd(&cmd[i], j);
			i++;
		}
		return ;
	}
	j = has_shell_var(cmd->cmd);
	if (j != -1 && cmd_n == 1)
		ft_clean_cmd(cmd, j);
	else
		sender(cmd);
}

int	has_shell_var(char **str)
{
	int		i;
	char	**tmp;

	i = 0;
	while (str && str[i] && str)
	{
		if (!ft_strchr(str[i], '='))
			return (i);
		tmp = ft_export_spliter(ft_strdup(str[i]));
		if (!check_name(tmp[0], 1))
		{
			ft_dfree(tmp);
			return (i);
		}
		ft_dfree(tmp);
		i++;
	}
	return (-1);
}

void	ft_clean_cmd(t_cmd *cmd, int n)
{
	int		j;
	char	**tmp;
	int		len;

	j = -1;
	len = ft_arrlen(cmd->cmd);
	if (!n)
		return ;
	tmp = (char **)ft_calloc(len - n + 1, sizeof(char *));
	while (cmd->cmd[n])
		tmp[++j] = ft_strdup(cmd->cmd[n++]);
	n = -1;
	while (cmd->cmd[++n])
	{
		free(cmd->cmd[n]);
		cmd->cmd[n] = NULL;
	}
	free(cmd->cmd);
	if (n == len)
	{
		cmd->cmd = NULL;
		free(tmp);
		return ;
	}
	cmd->cmd = tmp;
}

void	sender(t_cmd *cmd)
{
	int		i;
	char	**tmp;

	i = 0;
	while (cmd->cmd[i])
	{
		tmp = ft_export_spliter(ft_strdup(cmd->cmd[0]));
		if (is_not_env(tmp))
			ft_not_envadd_back(&g_gfl.not_env, ft_not_envnew(tmp));
		else
			ft_not_envadd_back(&g_gfl.not_env, ft_not_envnew(tmp));
		free(tmp);
		i++;
	}
	ft_clean_cmd(cmd, i);
}

t_not_env	*ft_not_envnew(char **content)
{
	t_not_env	*new_node;

	new_node = (t_not_env *)malloc(sizeof(t_not_env));
	if (!new_node)
		return (0);
	if (content)
	{
		new_node->name = content[0];
		new_node->value = content[1];
	}
	else
	{
		new_node->name = 0;
		new_node->value = 0;
	}
	new_node->next = 0;
	return (new_node);
}
