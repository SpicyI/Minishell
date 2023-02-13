/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 21:09:29 by del-khay          #+#    #+#             */
/*   Updated: 2023/02/13 13:05:02 by del-khay         ###   ########.fr       */
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
	char			**tab;
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
		tab = ft_split(str, '*');
		if (search_match(str, de->d_name, tab) > 0)
			i++;
		ft_free2(tab);
	}
	closedir(dir);
	return (i);
}

char   **wild_card(char *str)
{
    struct dirent   *de;
	DIR             *dir;
    char           **replace;
	char			**tab;
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
			tab = ft_split(str, '*');
			if(ft_strncmp(str, "*" , 0) == 0)
				replace[i[1]++] = ft_strdup(de->d_name);
			else if (search_match(str, de->d_name, tab) > 0)
                replace[i[1]++] = ft_strdup(de->d_name);
			ft_free2(tab);
        }
    }
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
		free((cmds +j)->cmd);
		(cmds + j)->cmd = ft_list_arr(tmp);
		ft_lstclear(&tmp, free);
		j++;
	}
}

void	ft_iterforwild(t_list **list)
{
	t_list	*tmp;
	char **replace;
	t_list *prev;

	tmp = *list;
	prev = NULL;
	while (tmp)
	{

		if(ft_strchr(tmp->content, '*'))
		{
			replace = wild_card(tmp->content);
			if (!replace)
			{
				tmp = tmp->next;
				continue;
			}
			if (!prev)
			{
				*list = ft_arr_list(replace);
				ft_lstadd_back(list,tmp->next);
				ft_lstdelone(tmp, free);
				tmp = *list;
			}
			if (prev)
			{
				prev->next = ft_arr_list(replace);
				ft_lstadd_back(&prev->next, tmp->next);
				ft_lstdelone(tmp, free);
				tmp = prev->next;
			}
			free(replace);
			continue;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}