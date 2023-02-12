/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 19:03:32 by del-khay          #+#    #+#             */
/*   Updated: 2023/02/12 18:58:05 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int sig)
{
	int	i;

	i = -1;
	dprintf(2,"hey\n");
	if (g_gfl.pid == 0)
	{
		printf("\n");
		return ;
	}
	else
	{
		while (++i < g_gfl.crp)
			kill(g_gfl.pid[i], sig);
	}
}

void	sigquit_handler(int sig)
{
	int	i;

	i = -1;
	exit(0);
	printf("Quit: 3\n");
	if (g_gfl.pid == 0)
		exit(0);
	else
	{
		while (++i < g_gfl.crp)
			kill(g_gfl.pid[i], sig);
	}
}

void	sigstp_handler(int sig)
{
	dprintf(2,"sig is %d\n", sig);
	return ;
}
