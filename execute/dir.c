/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 21:09:29 by del-khay          #+#    #+#             */
/*   Updated: 2023/02/13 19:16:30 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	search_match(char *str, char *file, char **tab)
{
	size_t	i;

	i = 0;
	if (!tab || !*tab)
		return (0);
	if (*str == '*')
	{
		if (!first_match(tab, i, file))
			return (0);
		file = file + ft_strlen(tab[i++]);
	}
	else if (ft_strncmp(file, tab[i], ft_strlen(tab[i])) != 0)
		return (0);
	while (i < ft_arrlen(tab))
	{
		if (i == ft_arrlen(tab) - 1 && ft_strncmp(file + (ft_strlen(file)
					- ft_strlen(tab[i])), tab[i], 0) != 0)
			return (0);
		file = ft_strnstr(file, tab[i], ft_strlen(file));
		if (file == NULL)
			return (0);
		file = file + ft_strlen(tab[i++]);
	}
	return (1);
}

char	**wild_card(char *str)
{
	t_wild	dirs;
	char	**replace;
	int		i[2];

	i[0] = ft_dir_count(str);
	i[1] = 0;
	if (i[0] <= 0)
		return (NULL);
	dirs.dir = opendir(".");
	replace = (char **)ft_calloc(i[0] + 1, sizeof(char *));
	dirs.de = readdir(dirs.dir);
	while (dirs.de && i[1] < i[0])
	{
		if (ft_strncmp(dirs.de->d_name, ".", 1) != 0)
			fill_replacer(str, dirs.de->d_name, replace, i);
		dirs.de = readdir(dirs.dir);
	}
	closedir(dirs.dir);
	return (replace);
}

void	ft_replace(t_cmd *cmds, int size)
{
	int		j;
	t_list	*tmp;

	j = 0;
	while (j < size)
	{
		tmp = ft_arr_list((cmds + j)->cmd);
		ft_iterforwild(&tmp);
		free((cmds + j)->cmd);
		(cmds + j)->cmd = ft_list_arr(tmp);
		ft_lstclear(&tmp, free);
		tmp = NULL;
		j++;
	}
}

void	change_line(t_list **list, t_list **tmp, t_list **prev, char **replace)
{
	if (!(*prev))
	{
		*list = ft_arr_list(replace);
		ft_lstadd_back(list, (*tmp)->next);
		ft_lstdelone(*tmp, free);
		*tmp = *list;
	}
	else if ((*prev))
	{
		(*prev)->next = ft_arr_list(replace);
		ft_lstadd_back(&(*prev)->next, (*tmp)->next);
		ft_lstdelone(*tmp, free);
		*tmp = (*prev)->next;
		(*prev) = NULL;
	}
}

void	ft_iterforwild(t_list **list)
{
	t_list	*tmp;
	char	**replace;
	t_list	*prev;

	tmp = *list;
	prev = NULL;
	while (tmp)
	{
		if (ft_strchr(tmp->content, '*'))
		{
			replace = wild_card(tmp->content);
			if (replace)
			{
				change_line(list, &tmp, &prev, replace);
				free(replace);
				continue ;
			}
		}
		prev = tmp;
		tmp = tmp->next;
	}
}
