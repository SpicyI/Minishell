/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   universal_helpers2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 15:02:04 by azakariy          #+#    #+#             */
/*   Updated: 2023/02/10 17:23:47 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_trim(char *line, char *set)
{
	char	*holder;

	holder = line;
	line = ft_strtrim(line, set);
	free(holder);
	return (line);
}

char	*ft_clean_join(char *str, char *str2)
{
	char	*shit;
	char	*new_str;

	if (!str2)
		return (str);
	shit = str2;
	new_str = ft_strjoin(str, str2);
	free(shit);
	return (new_str);
}

char	*ft_color(int i)
{
	if (i)
		return (readline("\033[0;35mWEIRDOO$ \033[0m"));
	else
		return (readline("\033[0;35m> \033[0m"));
}

void	ft_free_stuff(char **array, int start)
{
	int	i;

	i = 0;
	while (i < start)
	{
		if (array[i][0] == '>' || array[i][0] == '<')
		{
			free(array[i]);
			array[i] = NULL;
		}
		i++;
	}
	while (array[start])
	{
		free(array[start]);
		array[start] = NULL;
		start++;
	}
	free(array);
}
