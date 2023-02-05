/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 18:31:50 by del-khay          #+#    #+#             */
/*   Updated: 2023/02/05 18:14:22 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_option(char *str)
{
	if (!str || ft_strlen(str) < 2 || *str != '-')
		return (0);
	while (*(++str))
	{
		if (*str != 'n')
			return (0);
	}
	return (1);
}

int	echo(char **str)
{
	int	n;

	n = 0;
	if (is_option(*str))
	{
		n = 1;
		str++;
	}
	while (str && *str)
	{
		ft_putstr_fd(*str, 1);
		if (*(str + 1))
			ft_putchar_fd(' ', 1);
		str++;
	}
	if (n == 0)
		ft_putchar_fd('\n', 1);
	return (0);
}

// int	main(int ac, char **av)
// {
// 	echo(av + 1);
// 	return (0);
// }