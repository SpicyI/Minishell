/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 14:40:37 by del-khay          #+#    #+#             */
/*   Updated: 2022/10/14 21:41:27 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*s1;
	unsigned char	chr;

	s1 = (unsigned char *)s;
	chr = c;
	while (n > 0)
	{
		if (*s1 == chr)
			return ((void *)s1);
		n--;
		s1++;
	}
	return (0);
}
