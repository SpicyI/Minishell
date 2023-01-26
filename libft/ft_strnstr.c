/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 14:41:37 by del-khay          #+#    #+#             */
/*   Updated: 2022/10/13 18:54:17 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	len;
	size_t	i;
	size_t	j;

	len = ft_strlen(s2);
	i = 0;
	j = 0;
	if (len == 0)
		return ((char *)s1);
	if (!n)
		return (0);
	while (s1[i])
	{
		while (i + j < n && s1[i + j] && s2[j] && s1[i + j] == s2[j])
			j++;
		if (!s2[j])
			return ((char *)s1 + i);
		j = 0;
		i++;
	}
	return (0);
}
