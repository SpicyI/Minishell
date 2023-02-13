/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 23:46:22 by del-khay          #+#    #+#             */
/*   Updated: 2023/02/13 00:13:32 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list *ft_arr_list(char **arr)
{
    t_list *list;
    int i;

    i = 0;
    list = NULL;
    while (arr[i])
    {
        ft_lstadd_back(&list, ft_lstnew(arr[i]));
        i++;
    }
    return (list);
}

char **ft_list_arr(t_list *list)
{
    char **arr;
    int i;

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
