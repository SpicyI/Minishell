/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 21:09:29 by del-khay          #+#    #+#             */
/*   Updated: 2023/02/12 23:17:52 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	search_match(char *str, char *file, char **tab)
{
	size_t		i;
	char	*tmp;

	i = 0;
	tmp = file;
	if (!tab || !*tab)
		return (0);
	if (*str == '*')
	{
		tmp = ft_strnstr(tmp, tab[i], ft_strlen(tmp));
		if (tmp == NULL)
			return (0);
		tmp = tmp + ft_strlen(tab[i++]);
	}
	else
	{
		if (ft_strncmp(tmp, tab[i], ft_strlen(tab[i])) != 0)
			return (0);
	}
	while (i < ft_arrlen(tab))
	{
		tmp = ft_strnstr(tmp, tab[i], ft_strlen(tmp));
		if (tmp == NULL)
			return (0);
		tmp = tmp + ft_strlen(tab[i++]);
	}
	return (1);
}

int	ft_dir_count(char *str)
{
	struct dirent   *de;
	DIR             *dir;
	int i = 0;

	dir = opendir(".");
	if (!dir)
	{
		ft_dprintf("Could not open current directory\n", NULL);
		return (-1);
	}
	while ((de = readdir(dir)) != NULL)
	{
		if (ft_strncmp(de->d_name, ".", 1) == 0)
			continue ;
		if(ft_strncmp(str, "*" , 0) == 0)
			i++;
		if (search_match(str, de->d_name, ft_split(str, '*')) > 0)
			i++;
			
		
	}
	closedir(dir);
	return (i);
}

char   **wild_card(char *str)
{
    struct dirent   *de;
	DIR             *dir;
    char           **replace;
    int i[2];

    i[0] = ft_dir_count(str);
    i[1] = 0;
    if (i[0] <= 0)
        return (NULL);
    dir = opendir(".");
    replace = (char **) ft_calloc(i[0] + 1, sizeof(char *));
    while (i[1] < i[0])
    {
        while((de = readdir(dir)) != NULL)
        {
			if (ft_strncmp(de->d_name, ".", 1) == 0)
				continue ;
			if(ft_strncmp(str, "*" , 0) == 0)
				replace[i[1]++] = ft_strdup(de->d_name);
			else if (search_match(str, de->d_name, ft_split(str, '*')) > 0)
                replace[i[1]++] = ft_strdup(de->d_name);
        }
    }
    return (replace);
}

void   ft_change_line(t_cmd *cmds, int i, char **replace)
{
	char **tmp;
	int j;
	
	j = 0;
	tmp = ft_calloc(ft_arrlen(cmds->cmd) + ft_arrlen(replace), sizeof(char *));
	while (j < i)
	{
		tmp[j] = ft_strdup(cmds->cmd[j]);
		j++;
	}
	i = 0;
	while (replace[i])
	{
		tmp[j] = ft_strdup(replace[i]);
		j++;
		i++;
	}
	j = 0;
	while (cmds->cmd[j])
	{
		free(cmds->cmd[j]);
		j++;
	}
	free(cmds->cmd);
	cmds->cmd = tmp;
}

void	ft_replace(t_cmd *cmds, int size)
{
	char	**replace;
	int		j;
	int		i;

	j = 0;
	while (j < size)
	{
		i = 0;
		while((cmds + j)->cmd[i])
		{
			if(ft_strchr((cmds + j)->cmd[i], '*'))
			{
				replace = wild_card((cmds + j)->cmd[i]);
				if (!replace)
				{
					i++;
					continue;
				}
				ft_change_line((cmds + j), i , replace);
				free(replace);
			}
			i++;
		}
		j++;
	}
}