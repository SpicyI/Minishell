/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 16:32:39 by del-khay          #+#    #+#             */
/*   Updated: 2023/02/12 15:35:14 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_dprintf(char *format, char *str)
{
	int	tmp_stdout;

	tmp_stdout = dup(1);
	printf("\033[0;31m");
	dup2(STDERR_FILENO, 1);
	if (str)
		printf(format, str);
	else
		printf("%s", format);
	dup2(tmp_stdout, 1);
	close(tmp_stdout);
	printf("\033[0m");
	return (0);
}
