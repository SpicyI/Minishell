/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 14:41:05 by del-khay          #+#    #+#             */
/*   Updated: 2022/10/13 23:30:41 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	countwords(const char *s, char c)
{
	unsigned int	count;

	count = 0;
	while (*s)
	{	
		while (*s && c == *s)
			s++;
		if (*s)
			count++;
		while (*s && *s != c)
			s++;
	}
	return (count);
}

static unsigned int	ft_substrlen(const char *s, char c)
{
	unsigned int	len;

	len = 0;
	while (*s && *s != c)
	{
		len++;
		s++;
	}
	return (len);
}

void	ft_freeit(char **string, int i)
{
	while (i-- >= 0)
	{
		free(string[i]);
	}
	free(string);
}

static	char	**ft_fill(const char *s, char **ss, unsigned int sz, char c)
{
	int	i;

	i = 0;
	while (sz--)
	{
		while (*s && *s == c)
			s++;
		ss[i] = ft_substr(s, 0, ft_substrlen(s, c));
		if (!ss[i])
		{
			ft_freeit(ss, i + 1);
			return (0);
		}
		i++;
		s += ft_substrlen(s, c);
	}
	ss[i] = NULL;
	return (ss);
}

char	**ft_split(char const *s, char c)
{
	char			**strings;
	unsigned int	size;

	if (!s)
		return (NULL);
	size = countwords(s, c);
	strings = (char **) malloc(sizeof(char **) * (size + 1));
	if (!strings)
		return (0);
	return (ft_fill(s, strings, size, c));
}
