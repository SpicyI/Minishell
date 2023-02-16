/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minift.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 19:26:02 by azakariy          #+#    #+#             */
/*   Updated: 2023/02/16 18:53:23 by del-khay         ###   ########.fr       */
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
		else if (ft_strlen(line2) == 0)
		{
			free(line2);
			line2 = NULL;
		}
	}
	add_history(line2);
	return (line2);
}

char	**ft_filter2(char *part, int i, int j, int len)
{
	char	**array;
	char	*holder;

	array = NULL;
	holder = NULL;
	while (part && i < len && part[i])
	{
		if (part[i] == '>' || part[i] == '<')
		{
			array = ft_append(array, holder);
			j += ft_skip_me(part + j, part[i]);
			array = ft_append(array, ft_substr(part, i, j - i));
			holder = NULL;
		}
		else if (part[i] == '"' || part[i] == '\'')
		{
			j = ft_skip_quotes(part, i) + 1;
			holder = ft_clean_join(holder, ft_substr(part, i, j - i));
		}
		else if (++j)
			holder = ft_append_char(holder, part[i]);
		i = j;
	}
	return (ft_append(array, holder));
}

int	ft_normals(char *str, int i)
{
	while (str[i])
	{
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

void	ft_fill_double(char **array)
{
	int	i;

	i = 0;
	while (array && array[i])
	{
		array[i] = ft_remove_quotes(array[i]);
		i++;
	}
}
