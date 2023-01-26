/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 14:40:43 by del-khay          #+#    #+#             */
/*   Updated: 2022/10/15 00:01:57 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *str, size_t n)
{
	unsigned char	*dest1;
	unsigned char	*str1;

	if (!dest && !str)
		return (0);
	str1 = (unsigned char *) str;
	dest1 = (unsigned char *)dest;
	while (n--)
	{
		*dest1++ = *str1++;
	}
	return (dest);
}
