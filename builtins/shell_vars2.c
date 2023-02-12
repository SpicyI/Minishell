/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_vars2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 19:11:10 by del-khay          #+#    #+#             */
/*   Updated: 2023/02/12 19:31:39 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *get_shell_var_value(char *str)
{
    t_not_env *tmp;

    tmp = g_gfl.not_env;
    while (tmp)
    {
        if (!ft_strncmp(str, tmp->name, 0))
            return (ft_strdup(tmp->value));
        tmp = tmp->next;
    }
    return (NULL);
}

int is_shell_var2(char *str)
{
    char *value;
    char **tmp;

    value = get_shell_var_value(str);
    if (!value)
    {
        free(value);
        return (0);
    }
    else
    {
        tmp = (char **) ft_calloc(2, sizeof(char *) );
        *tmp = ft_strjoin(ft_strjoin(str, "="), value);
        export(tmp);
        free(value);
        free(*tmp);
        free(tmp);
        return (1);
    }
    return (0);
}