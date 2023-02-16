/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 19:03:32 by del-khay          #+#    #+#             */
/*   Updated: 2023/02/16 19:35:06 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int sig)
{
	int	i;

	i = -1;
	if (!g_gfl.crp)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (g_gfl.crp)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		if (g_gfl.crp == 1 && g_gfl.pid)
		{
			kill(g_gfl.pid[0], SIGKILL);
			return ;
		}
		while (g_gfl.pid && ++i < g_gfl.crp)
			kill(g_gfl.pid[i], sig);
	}
	return ;
}

void	sigquit_handler(int sig)
{
	int	i;

	i = -1;
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	if (g_gfl.crp == 1 && sig == SIGQUIT)
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
}
