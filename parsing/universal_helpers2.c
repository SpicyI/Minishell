/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   universal_helpers2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 15:02:04 by azakariy          #+#    #+#             */
/*   Updated: 2023/02/08 17:07:41 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_fill_with(int size, char c)
{
	char	*str;
	int		i;

	str = ft_calloc(size + 1, sizeof(char));
	i = 0;
	while (i < size)
	{
		str[i] = c;
		i++;
	}
	return (str);
}