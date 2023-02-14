/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minift.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 19:26:02 by azakariy          #+#    #+#             */
/*   Updated: 2023/02/14 23:24:44 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_line(int nl, char *line)
{
	char	*line2;

	line2 = NULL;
	while (!line2 || (line2 && ft_strlen(line2) == 0))
	{
		if (nl)
			line2 = ft_clean_join(line, ft_trim(ft_color(0), " "));
		else
			line2 = ft_trim(ft_color(1), " ");
		if (!line2)
			printf("\n");
	}
	add_history(line2);
	return (line2);
}

char	**ft_filter2(char *part, int i, int j)
{
	char	**array;

	array = NULL;
	while (part[i])
	{
		j = i;
		if (part[i] == '>')
			j += ft_skip_me(part + j, '>');
		else if (part[i] == '<')
			j += ft_skip_me(part + j, '<');
		else if (part[i] == '"')
			j += ft_skip_me(part + j + 1, '"') + 1;
		else if (part[i] == '\'')
			j += ft_skip_me(part + j + 1, '\'') + 1;
		else
			j = ft_normals(part, i);
		array = ft_append(array, ft_substr(part, i, j - i));
		i = j;
	}
	return (array);
}

int	ft_normals(char *str, int i)
{
	while (str[i])
	{
		if (str[i] == '<' || str[i] == '>')
			break ;
		if (str[i] == '"' || str[i] == '\'')
			break ;
		i++;
	}
	return (i);
}

int	ft_skip_me(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == c)
		i++;
	return (i);
}
