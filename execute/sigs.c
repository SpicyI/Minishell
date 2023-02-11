/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 19:03:32 by del-khay          #+#    #+#             */
/*   Updated: 2023/02/11 20:07:05 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int sig)
{
	int i;

	i = sig;
    i = -1;
	if (g_gfl.pid == 0)
	{
		printf("\n");
		return ;
	}
	else
	{
		while (++i < g_gfl.crp)
			kill(g_gfl.pid[i], SIGKILL);
	}
}