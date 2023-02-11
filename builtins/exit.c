/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 00:18:27 by del-khay          #+#    #+#             */
/*   Updated: 2023/02/11 17:59:51 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	shell_exit(char **args)
{
	unsigned char	status;

	printf("exit\n");
	if (!args || !args[0])
		exit(0);
	if ((args && !ft_strncmp(args[0], "--", 0)) || (!args || !args[0]))
		exit(0);
	if (!alldigit(args[0]))
	{
		ft_dprintf(EXIT_NUM, args[0]);
		exit(255);
	}
	if (args[1])
	{
		ft_dprintf(EXIT_MANY, NULL);
		return (1);
	}
	status = ft_atoi(args[0]);
	exit(status);
	return (0);
}
