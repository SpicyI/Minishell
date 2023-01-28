/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 18:54:11 by del-khay          #+#    #+#             */
/*   Updated: 2023/01/28 22:47:41 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H
/*          includes        */
#include <stdio.h>
#include "libft/libft.h"
#include <dirent.h>

/*          defines         */
#define ECHO_NL "-n"

/*          structs         */
// contains the command table for now
// typedef struct s_cmd_table
// {
    
// }

/*          echo            */
void    echo(char **str);
int arrlen(char **arr);

/*          cd              */
// handle OLDPWD and PWD env vars snd cd -
void    cd(char *path);

/*          */
#endif
