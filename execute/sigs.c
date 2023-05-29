/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 19:03:32 by del-khay          #+#    #+#             */
/*   Updated: 2023/02/19 00:36:20 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int sig)
{
	int	i;

	i = -1;
	if (!g_gfl.crp)
	{
		ft_putchar_fd('\n', 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (g_gfl.crp)
	{
		if (g_gfl.crp == 1 && g_gfl.pid)
			kill(g_gfl.pid[0], SIGKILL);
		else
		{
			while (g_gfl.pid && ++i < g_gfl.crp)
				kill(g_gfl.pid[i], sig);
		}
		ft_putchar_fd('\n', 1);
		rl_replace_line("", 0);
		rl_redisplay();
	}
	return ;
}

void	sigquit_handler(int sig)
{
	int	i;

	i = -1;
	if (g_gfl.crp == 0 && g_gfl.pid == 0)
	{
		rl_on_new_line();
		rl_redisplay();
	}
	else if (g_gfl.crp == 1 && sig == SIGQUIT)
	{
		kill(g_gfl.pid[0], sig);
	}
	else if (g_gfl.pid && g_gfl.crp && sig == SIGQUIT)
	{
		if (g_gfl.crp == 1)
		{
			kill(g_gfl.pid[0], sig);
			return ;
		}
		while (++i < g_gfl.crp)
			kill(g_gfl.pid[i], sig);
	}
	return ;
}

void	ft_set_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	ft_signals(struct termios oldterm[2])
{
	tcgetattr(0, &oldterm[0]);
	oldterm[1] = oldterm[0];
	oldterm[0].c_lflag &= ~ISIG;
	oldterm[0].c_lflag &= ~ECHOCTL;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
}
