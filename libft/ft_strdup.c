/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 14:41:10 by del-khay          #+#    #+#             */
/*   Updated: 2023/02/03 16:35:42 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*ptr;
	size_t	i;

	i = 0;
	ptr = (char *) malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (ptr == 0)
		return (0);
	while (s[i])
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = 0;
	return (ptr);
}

void	ft_dfree(char **string)
{
	int i;
	
	i = 0;
	if (string[i])	
		free(string[i]);
	i++;
	if (string[i])
		free(string[i]);
	if (string)
		free(string);
		
}
