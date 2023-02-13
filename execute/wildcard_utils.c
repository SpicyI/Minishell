/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 23:46:22 by del-khay          #+#    #+#             */
/*   Updated: 2023/02/13 19:17:00 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_arr_list(char **arr)
{
	t_list	*list;
	int		i;

	i = 0;
	list = NULL;
	while (arr[i])
	{
		ft_lstadd_back(&list, ft_lstnew(arr[i]));
		i++;
	}
	return (list);
}

char	**ft_list_arr(t_list *list)
{
	char	**arr;
	int		i;

	i = 0;
	arr = (char **)ft_calloc(ft_lstsize(list) + 1, sizeof(char *));
	while (list)
	{
		arr[i] = ft_strdup(list->content);
		list = list->next;
		i++;
	}
	return (arr);
}

int	ft_dir_count(char *str)
{
	struct dirent	*de;
	DIR				*dir;
	char			**tab;
	int				i;

	i = 0;
	dir = opendir(".");
	if (!dir)
		return (ft_dprintf(CAN_NOT_OPEN_DIR, NULL));
	de = readdir(dir);
	while (de)
	{
		if (ft_strncmp(de->d_name, ".", 1) != 0)
		{
			if (ft_strncmp(str, "*", 0) == 0)
				i++;
			tab = ft_split(str, '*');
			if (search_match(str, de->d_name, tab) > 0)
				i++;
			ft_free2(tab);
		}
		de = readdir(dir);
	}
	closedir(dir);
	return (i);
}

void	fill_replacer(char *str, char *file, char **replace, int *i)
{
	char	**tab;

	tab = ft_split(str, '*');
	if (ft_strncmp(str, "*", 0) == 0)
		replace[i[1]++] = ft_strdup(file);
	else if (search_match(str, file, tab) > 0)
		replace[i[1]++] = ft_strdup(file);
	ft_free2(tab);
}

int	first_match(char **tab, size_t i, char *tmp)
{
	if (i == ft_arrlen(tab) - 1 && ft_strncmp(tmp + (ft_strlen(tmp)
				- ft_strlen(tab[i])), tab[i], 0) != 0)
		return (0);
	tmp = ft_strnstr(tmp, tab[i], ft_strlen(tmp));
	if (tmp == NULL)
		return (0);
	return (1);
}
