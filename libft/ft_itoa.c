/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 14:40:34 by del-khay          #+#    #+#             */
/*   Updated: 2022/10/09 21:40:24 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	arrsize(int n)
{
	unsigned int	size;

	if (n == 0)
		return (2);
	size = 1;
	while (n)
	{
		size++;
		n /= 10;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	long	nbr;
	short	size;
	char	*arr;

	size = arrsize(n);
	nbr = n;
	if (n < 0)
	{
		size++;
		nbr *= -1;
	}
	arr = (char *) malloc(sizeof(char) * size);
	if (!arr)
		return (0);
	arr[--size] = 0;
	while (--size >= 0)
	{
		arr[size] = (nbr % 10) + '0';
		nbr /= 10;
	}
	if (n < 0)
		arr[0] = '-';
	return (arr);
}
