/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 14:41:43 by del-khay          #+#    #+#             */
/*   Updated: 2022/10/13 18:10:35 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	findchar(const char *set, int c)
{
	while (*set)
		if ((char)c == *set++)
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int	start;
	int	end;

	if (!set)
		return (ft_strdup(s1));
	if (!s1)
		return (0);
	if (!ft_strlen(s1))
		return (ft_strdup(""));
	start = 0;
	end = ft_strlen(s1) - 1;
	while (s1[start] && findchar(set, s1[start]))
		start++;
	while (s1[end] && end >= start && findchar(set, s1[end]))
		end--;
	return (ft_substr(s1, start, end - start + 1));
}
