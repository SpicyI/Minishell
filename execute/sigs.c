/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 19:03:32 by del-khay          #+#    #+#             */
/*   Updated: 2023/02/14 17:15:53 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int sig)
{
	int	i;

	i = sig;
	i = -1;
	if (!g_gfl.pid && !g_gfl.crp)
	{
		printf("\n");
		return ;
	}
	else if(g_gfl.pid && g_gfl.crp) 
	{
		while (++i < g_gfl.crp)
			kill(g_gfl.pid[i], SIGKILL);
	}
}
