/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 00:18:27 by del-khay          #+#    #+#             */
/*   Updated: 2023/02/05 00:32:09 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shell_exit(char **args)
{
	unsigned char	status;

	printf("exit\n");
	if (!args[1])
		exit(0);
	if (!alldigit(args[1]))
	{
		printf("exit: %s: numeric argument required\n", args[1]);
		exit(255);
	}
	if (args[2])
	{
		printf("exit: too many arguments\n");
		return ;
	}
	status = ft_atoi(args[1]);
	exit(status);
}

// int main(int argc, char **argv)
// {
//     shell_exit(argv);
//     return (0);
// }