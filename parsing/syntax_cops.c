/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_cops.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 14:49:36 by azakariy          #+#    #+#             */
/*   Updated: 2023/02/10 21:51:13 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_throw_error(char *str, int code)
{
	int	i;

	i = 0;
	ft_putstr_fd("\033[0;31mWEIRDOO: syntax error near unexpected token `", 2);
	if (code == 1)
	{
		g_gfl.syntax_error = 1;
		ft_putstr_fd(str, 2);
	}
	else if (code == 0)
	{
		while (str[i] && str[i] == '|' && i < 2)
		{
			ft_putchar_fd(str[i], 2);
			i++;
		}
	}
	ft_putstr_fd("'\n\033[0m", 2);
}

void	ft_left_arrow(char **cmd, int i, int is_last)
{
	if (ft_strlen(cmd[i]) > 2)
		ft_throw_error(cmd[i] + 2, 1);
	else if (!cmd[i + 1])
	{
		if (is_last)
			ft_throw_error("newline", 1);
		else
			ft_throw_error("|", 1);
	}
	else if (cmd[i + 1][0] == '<')
		ft_throw_error(ft_substr(cmd[i + 1], 0, 3), 1);
	else if (cmd[i + 1][0] == '>')
		ft_throw_error(ft_substr(cmd[i + 1], 0, 2), 1);
}

void	ft_right_arrow(char **cmd, int i, int is_last)
{
	if (ft_strlen(cmd[i]) > 2)
		ft_throw_error(cmd[i] + 2, 1);
	else if (!cmd[i + 1])
	{
		if (is_last)
			ft_throw_error("newline", 1);
		else
			ft_throw_error("|", 1);
	}
	else if (cmd[i + 1][0] == '>')
		ft_throw_error(ft_substr(cmd[i + 1], 0, 2), 1);
	else if (cmd[i + 1][0] == '<')
		ft_throw_error(ft_substr(cmd[i + 1], 0, 2), 1);
}

int	ft_valid_syntax(char **cmd, int i, int is_last)
{
	if (cmd[i][0] == '>')
		ft_right_arrow(cmd, i, is_last);
	else if (cmd[i][0] == '<')
		ft_left_arrow(cmd, i, is_last);
	return (g_gfl.syntax_error);
}
