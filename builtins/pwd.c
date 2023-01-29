/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 18:36:02 by del-khay          #+#    #+#             */
/*   Updated: 2023/01/29 17:16:43 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void   pwd(void)
{
    char *cwd;

    cwd = getcwd(NULL, 0);
    ft_putendl_fd(cwd, 1);
    free(cwd);
}

int main(void)
{
    pwd();
    return (0);
}