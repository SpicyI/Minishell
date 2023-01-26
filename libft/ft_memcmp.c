/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 14:40:40 by del-khay          #+#    #+#             */
/*   Updated: 2022/10/15 00:12:17 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*bloc1;
	unsigned char	*bloc2;
	unsigned int	i;

	bloc1 = (unsigned char *)s1;
	bloc2 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (n--)
	{
		if (bloc1[i] != bloc2[i])
			return (bloc1[i] - bloc2[i]);
		i++;
	}
	return (0);
}
