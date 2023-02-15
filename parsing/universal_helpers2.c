/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   universal_helpers2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 15:02:04 by azakariy          #+#    #+#             */
/*   Updated: 2023/02/16 00:34:56 by del-khay         ###   ########.fr       */
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
	char	*line;

	if (i)
		line = readline("MINISHELL$ ");
	else
		line = readline("> ");
	if (!line)
	{
		printf("exit");
		exit(0);
	}
	if (line && !ft_strlen(line))
	{
		free(line);
		return (NULL);
	}
	return (line);
}

int	ft_skip_quotes(char *str, int i)
{
	if (str[i] == '"')
	{
		i++;
		while (str[i] && str[i] != '"')
			i++;
		return (i);
	}
	else if (str[i] == '\'')
	{
		i++;
		while (str[i] && str[i] != '\'')
			i++;
		return (i);
	}
	return (i);
}
