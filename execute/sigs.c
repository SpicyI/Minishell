/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 19:03:32 by del-khay          #+#    #+#             */
/*   Updated: 2023/02/13 13:29:57 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int sig)
{
	int	i;

	i = -1;

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

// void	sigquit_handler(int sig)
// {
// 	// int	i;
// 	return ;
// 	// i = -1;
// 	// printf("Quit: 3\n");
// 	// exit(0);
// 	// if (g_gfl.pid == 0)
// 	// 	exit(0);
// 	// else
// 	// {
// 	// 	while (++i < g_gfl.crp)
// 	// 		kill(g_gfl.pid[i], sig);
// 	// }
// }

// void	sigstp_handler(int sig)
// {
// 	return ;
// }
