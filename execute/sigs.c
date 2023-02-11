/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 19:03:32 by del-khay          #+#    #+#             */
/*   Updated: 2023/02/11 19:22:08 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int sig)
{
    int i;

    i= sig;
    i = 0;
    if (g_gfl.pid == 0)
        printf("\n");
    else
    {
        kill(g_gfl.pid[0], SIGKILL);
        printf("killed");
    }
}