/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 17:15:37 by del-khay          #+#    #+#             */
/*   Updated: 2022/11/27 19:41:30 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stash[10240];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	stash[fd] = ft_read_line(stash[fd], fd);
	if (!stash[fd])
		return (0);
	line = ft_fget(stash[fd]);
	stash[fd] = ft_clean(stash[fd]);
	return (line);
}

char	*ft_fget(char *stash)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	if (!ft_strlen(stash))
		return (0);
	while (stash[i] && stash[i] != '\n')
		i++;
	j = 0;
	line = ft_calloc(i + 2, sizeof(char));
	if (!line)
		return (0);
	while (j <= i && stash[j])
	{
		line[j] = stash[j];
		j++;
	}
	return (line);
}

char	*ft_read_line(char *stash, int fd)
{
	int		r;
	char	*line;

	line = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!line)
		return (0);
	r = 1;
	while (!is_nl(stash) && r)
	{
		r = read(fd, line, BUFFER_SIZE);
		if (r == -1)
		{
			free(stash);
			free(line);
			return (0);
		}
		stash = ft_strjoin(stash, line);
		if (!stash)
			return (0);
		ft_bzero(line, BUFFER_SIZE + 1);
	}
	free(line);
	return (stash);
}

char	*ft_clean(char *stash)
{
	char	*new_stash;
	int		j;
	int		i;

	j = 0;
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (0);
	}
	new_stash = ft_calloc(ft_strlen(stash) - i + 1, sizeof(char));
	i++;
	if (!new_stash)
		return (0);
	while (stash[i])
		new_stash[j++] = stash[i++];
	free(stash);
	return (new_stash);
}
