/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 14:41:40 by del-khay          #+#    #+#             */
/*   Updated: 2022/10/13 18:32:54 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*s0;

	s0 = (char *)s;
	while (*s)
		s++;
	if (*s == (char)c)
		return ((char *)s);
	while (s != s0)
		if (*--s == (char)c)
			return ((char *)s);
	return (0);
}
