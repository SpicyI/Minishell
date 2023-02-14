/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 19:03:32 by del-khay          #+#    #+#             */
/*   Updated: 2023/02/14 18:29:14 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int sig)
{
	int	i;

	i = -1;
	if (g_gfl.crp == 1)
	{
		dprintf(2, "killing herdoc\n");
		kill(g_gfl.pid[0], SIGKILL);
	}
	if (!g_gfl.pid && !g_gfl.crp)
		return ;
	else if (g_gfl.pid && g_gfl.crp)
	{
		if (g_gfl.crp == 1)
		{
			kill(g_gfl.pid[0], SIGKILL);
			return ;
		}
		while (++i < g_gfl.crp)
			kill(g_gfl.pid[i], sig);
	}
}
