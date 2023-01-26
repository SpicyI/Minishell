/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 14:41:30 by del-khay          #+#    #+#             */
/*   Updated: 2022/10/07 14:41:30 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f) (unsigned int, char))
{
	char			*arr;
	unsigned int	i;

	i = 0;
	if (!s)
		return (0);
	arr = (char *) malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!arr)
		return (0);
	while (s[i])
	{
		arr[i] = (*f)(i, (char)s[i]);
		i++;
	}
	arr[i] = 0;
	return (arr);
}
